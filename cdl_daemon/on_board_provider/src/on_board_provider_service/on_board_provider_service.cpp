/*
* Copyright (C) 2017, IVIS
*
* This file is part of GENIVI Project CDL - Car Data Logger.
*
* This Source Code Form is subject to the terms of the
* Mozilla Public License (MPL), v. 2.0.
* If a copy of the MPL was not distributed with this file,
* You can obtain one at http://mozilla.org/MPL/2.0/.
*
* For further information see http://www.genivi.org/.
*/

/*!
* \author Seok-Heum Choi <seokheum.choi@ivisolution.com>
*
* \copyright Copyright (c) 2017, IVIS \n
* License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
*
*/

#include "on_board_provider_service.hpp"
#include "on_board_provider_dbus_service.hpp"
#include "on_board_provider_someip_service.hpp"
#include "data_manager/data_manager.hpp"
#include "../../common/log.hpp"

#define UNUSED_PARAMETER(x) (void)(x)
#define DEFAULT_NOTIFY_TYPE 2

OnBoardProviderService::OnBoardProviderService(DataManager *dataManager)
    : m_dataManager(dataManager), m_clientHandle(1)
{
    m_onBoardProviderDBusService = std::make_shared<OnBoardProviderDBusService>(this);
    m_onBoardProviderSomeIPService = std::make_shared<OnBoardProviderSomeIPService>(this);

    auto runtime = CommonAPI::Runtime::get();
    runtime->registerService("local", ClientAPI::getInterface(), m_onBoardProviderDBusService);
    runtime->registerService("local", "org.genivi.CDL.ClientAPI.SomeIp", m_onBoardProviderSomeIPService);
}

OnBoardProviderService::~OnBoardProviderService()
{
    auto runtime = CommonAPI::Runtime::get();
    runtime->unregisterService("local", ClientAPI::getInterface(), ClientAPI::getInterface());
    runtime->unregisterService("local", ClientAPI::getInterface(), "org.genivi.CDL.ClientAPI.SomeIp");

    m_registeredClientInfoList.clear();
    m_clientIdToHandleList.clear();
    m_clientDataNameList.clear();
}

void OnBoardProviderService::registerClient(RuntimeType _runtime, const std::shared_ptr<CommonAPI::ClientId> _client, std::string _key, ClientAPITypes::Handle &handleOut, ClientAPITypes::ResultCode &result)
{
    UNUSED_PARAMETER(_key);

    unordered_map<std::shared_ptr<CommonAPI::ClientId>, ClientAPITypes::Handle>::iterator clientHandleIter
            = m_clientIdToHandleList.find(_client);

    if( clientHandleIter != m_clientIdToHandleList.end() )    // data( clientId / Handle ) is already existed
    {
        result = ClientAPITypes::ResultCode::RC_CLIENT_ALREADY_REGISTERED;
        handleOut = 0;

        return;
    }

    ClientInfo clientInfo;
    clientInfo.clientID = _client;
    clientInfo.runTimeType = _runtime;

    m_registeredClientInfoList.insert( pair<ClientAPITypes::Handle, ClientInfo>(m_clientHandle, clientInfo) );
    m_clientIdToHandleList.insert(pair<std::shared_ptr<CommonAPI::ClientId>, ClientAPITypes::Handle>(_client, m_clientHandle));

    handleOut = m_clientHandle;
    result = ClientAPITypes::ResultCode::RC_OK;

    LOGI() << "Register Client Info ( handle : " << m_clientHandle << ", runtime type : " << _runtime << " )";

    m_clientHandle++;
}

void OnBoardProviderService::setListenData(const std::shared_ptr<CommonAPI::ClientId> _client, ClientAPITypes::Handle _handle, std::vector<string> _signalName, ClientAPITypes::NotifyType _type, ClientAPITypes::ResultCode &result)
{
    UNUSED_PARAMETER(_client);

    if( _handle == 0 )
    {
        result = ClientAPITypes::ResultCode::RC_INVALID_HANDLE;
        return;
    }

    manageListenData(_handle);

    m_clientDataNameList.insert(pair<ClientAPITypes::Handle, vector<string>>(_handle, _signalName));

    manageProvideData(_handle, _type, _signalName);

    LOGI() << "===================================================================================";
    LOGI() << "Data Noti_type of Registered Client ( noti_type : " << _type << " )";

    for(unsigned int i=0; i<_signalName.size(); i++)
    {
        LOGI() << i << ". Registered Signal Name : " << _signalName.at(i);
    }

    result = ClientAPITypes::ResultCode::RC_OK;
}

void OnBoardProviderService::getData(const std::shared_ptr<CommonAPI::ClientId> _client, ClientAPITypes::Handle _handle, string _signalName, ClientAPITypes::ResultCode &result)
{
    UNUSED_PARAMETER(_client);

    if( _handle == 0 )
    {
        result = ClientAPITypes::ResultCode::RC_INVALID_HANDLE;
        return;
    }

    CDLData cdlData = m_dataManager->getCDLData(_signalName);

    ClientInfoList::iterator clientInfoIter = m_registeredClientInfoList.find(_handle);

    switch(clientInfoIter->second.runTimeType)
    {
    case RuntimeType::RUNTIME_DBUS:
    {
        CommonAPI::ClientIdList dbus_clientIdList;
        dbus_clientIdList.insert(clientInfoIter->second.clientID);

        notifyDBusClientData(cdlData, dbus_clientIdList);

        break;
    }
    case RuntimeType::RUNTIME_SOMEIP:
    {
        CommonAPI::ClientIdList someIP_clientIdList;
        someIP_clientIdList.insert(clientInfoIter->second.clientID);

        notifySomeIPClientData(cdlData, someIP_clientIdList);

        break;
    }
    }

    result = ClientAPITypes::ResultCode::RC_OK;
}

void OnBoardProviderService::provideCDLData(ClientAPITypes::NotifyType notiType, CDL_DATA &cdlData)
{
    // find the clientID in container via provided cdlData(id, name, value).
    CommonAPI::ClientIdList providedDBusClientIdList;
    CommonAPI::ClientIdList providedSomeIPClientIdList;

    providedDBusClientIdList = getProvideDBusClientIdList(cdlData.name, notiType);
    providedSomeIPClientIdList = getProvideSomeIPClientIdList(cdlData.name, notiType);

    if( notiType == ClientAPITypes::NotifyType::NT_CHANGED )
    {
        LOGD() << "----- Data Changed ( id : " << cdlData.name << " )-----";
    }
    else
    {
        LOGD() << "----- Data Updated ----- ( time stamp : " << cdlData.time_stamp << ", name : " << cdlData.name;
    }

    if( !providedDBusClientIdList.empty() )
    {
        notifyDBusClientData(cdlData, providedDBusClientIdList);
    }

    if( !providedSomeIPClientIdList.empty() )
    {
        notifySomeIPClientData(cdlData, providedSomeIPClientIdList);
    }
}

ClientAPITypes::CDLValue OnBoardProviderService::getCDLValue(char *_value, CDLDataTypes _type, unsigned long _dataLength)
{
    ClientAPITypes::CDLValue returnCDLValue;

    switch( _type )
    {
    case CDLDataTypes::UINT8:
    {
        uint8_t value;

        memcpy(&value, _value, sizeof(uint8_t));

        LOGD() << "UINT8 value : " << value;
        returnCDLValue = value;

        break;
    }
    case CDLDataTypes::INT8:
    {
        int8_t value;

        memcpy(&value, _value, sizeof(int8_t));

        LOGD() << "INT8 value : " << value;
        returnCDLValue = value;

        break;
    }
    case CDLDataTypes::UINT16:
    {
        uint16_t value;

        memcpy(&value, _value, sizeof(uint16_t));

        LOGD() << "UINT16 value : " << value;
        returnCDLValue = value;

        break;
    }
    case CDLDataTypes::INT16:
    {
        int16_t value;

        memcpy(&value, _value, sizeof(int16_t));

        LOGD() << "INT16 value : " << value;
        returnCDLValue = value;

        break;
    }
    case CDLDataTypes::UINT32:
    {
        uint32_t value;

        memcpy(&value, _value, sizeof(uint32_t));

        LOGD() << "UINT32 value : " << value;
        returnCDLValue = value;

        break;
    }
    case CDLDataTypes::INT32:
    {
        int32_t value;

        memcpy(&value, _value, sizeof(int32_t));

        LOGD() << "INT32 value : " << value;
        returnCDLValue = value;

        break;
    }
    case CDLDataTypes::UINT64:
    {
        uint64_t value;

        memcpy(&value, _value, sizeof(uint64_t));
        returnCDLValue = value;

        break;
    }
    case CDLDataTypes::INT64:
    {
        int64_t value;

        memcpy(&value, _value, sizeof(int64_t));
        returnCDLValue = value;

        break;
    }
    case CDLDataTypes::BOOLEAN:
    {
        bool value;

        memcpy(&value, _value, sizeof(bool));
        returnCDLValue = value;

        break;
    }
    case CDLDataTypes::FLOAT:
    {
        float value;

        memcpy(&value, _value, sizeof(float));
        returnCDLValue = value;

        break;
    }
    case CDLDataTypes::DOUBLE:
    {
        double value;

        memcpy(&value, _value, sizeof(double));
        returnCDLValue = value;

        break;
    }
    case CDLDataTypes::STRING:
    {
        string value;

        value = _value;
        returnCDLValue = value;

        break;
    }
    case CDLDataTypes::BYTEBUFFER:
    {
        CommonAPI::ByteBuffer value;

        for( unsigned long i=0; i<_dataLength; i++ )
        {
            value.push_back(_value[i]);
        }
        returnCDLValue = value;

        break;
    }
    default:
    {
        break;
    }
    }

    return returnCDLValue;
}

ClientAPITypes::Types OnBoardProviderService::getCDLValueType(CDLDataTypes _type)
{
    ClientAPITypes::Types returnCDLDataType;

    switch( _type )
    {
    case CDLDataTypes::UINT8:
    {
        returnCDLDataType = ClientAPITypes::Types::UINT8;

        break;
    }
    case CDLDataTypes::INT8:
    {
        returnCDLDataType = ClientAPITypes::Types::INT8;

        break;
    }
    case CDLDataTypes::UINT16:
    {
        returnCDLDataType = ClientAPITypes::Types::UINT16;

        break;
    }
    case CDLDataTypes::INT16:
    {
        returnCDLDataType = ClientAPITypes::Types::INT16;

        break;
    }
    case CDLDataTypes::UINT32:
    {
        returnCDLDataType = ClientAPITypes::Types::UINT32;

        break;
    }
    case CDLDataTypes::INT32:
    {
        returnCDLDataType = ClientAPITypes::Types::INT32;

        break;
    }
    case CDLDataTypes::UINT64:
    {
        returnCDLDataType = ClientAPITypes::Types::UINT64;

        break;
    }
    case CDLDataTypes::INT64:
    {
        returnCDLDataType = ClientAPITypes::Types::INT64;

        break;
    }
    case CDLDataTypes::BOOLEAN:
    {
        returnCDLDataType = ClientAPITypes::Types::BOOLEAN;

        break;
    }
    case CDLDataTypes::FLOAT:
    {
        returnCDLDataType = ClientAPITypes::Types::FLOAT;

        break;
    }
    case CDLDataTypes::DOUBLE:
    {
        returnCDLDataType = ClientAPITypes::Types::DOUBLE;

        break;
    }
    case CDLDataTypes::STRING:
    {
        returnCDLDataType = ClientAPITypes::Types::STRING;

        break;
    }
    case CDLDataTypes::BYTEBUFFER:
    {
        returnCDLDataType = ClientAPITypes::Types::BYTEBUFFER;

        break;
    }
    default:
    {
        break;
    }
    }

    return returnCDLDataType;
}

void OnBoardProviderService::manageListenData(ClientAPITypes::Handle &handle)
{
    ClientDataNameList::iterator clientDataNameListIter = m_clientDataNameList.find(handle);

    if( clientDataNameListIter != m_clientDataNameList.end() )  //data already existed ( handle - id list )
    {
        ClientInfoList::iterator clientInfoIter = m_registeredClientInfoList.find(handle);

        if( clientInfoIter != m_registeredClientInfoList.end() )  //data exist
        {
            switch(clientInfoIter->second.runTimeType)
            {
            case RuntimeType::RUNTIME_DBUS:
            {
                eraseListenData(clientDataNameListIter, m_changeDBusClientIDList, handle);
                eraseListenData(clientDataNameListIter, m_updateDBusClientIDList, handle);

                m_clientDataNameList.erase(clientDataNameListIter);

                break;
            }
            case RuntimeType::RUNTIME_SOMEIP:
            {
                eraseListenData(clientDataNameListIter, m_changeSomeIPClientIDList, handle);
                eraseListenData(clientDataNameListIter, m_updateSomeIPClientIDList, handle);

                m_clientDataNameList.erase(clientDataNameListIter);

                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
    else
    {

    }
}

void OnBoardProviderService::eraseListenData(ClientDataNameList::iterator &clientDataNameListIter, ProvideCDLDataList &provideClientIDList, ClientAPITypes::Handle &handle)
{
    for( unsigned int i=0; i<clientDataNameListIter->second.size(); i++ )
    {
        ProvideCDLDataList::iterator clientIDListIter = provideClientIDList.find(clientDataNameListIter->second.at(i));

        if( clientIDListIter != provideClientIDList.end() )
        {
            ClientInfoList::iterator clientIDIter = clientIDListIter->second.find(handle);

            if( clientIDIter != clientIDListIter->second.end() )
            {
                LOGD() << "Registered client delete signal name : " << clientDataNameListIter->second.at(i);
                clientIDListIter->second.erase(clientIDIter);
            }
        }
    }
}

void OnBoardProviderService::manageProvideData(ClientAPITypes::Handle &handle, ClientAPITypes::NotifyType &type, vector<string> &signalNameList)
{
    ClientInfoList::iterator registeredClientInfoIter = m_registeredClientInfoList.find(handle);

    switch( registeredClientInfoIter->second.runTimeType )
    {
    case RuntimeType::RUNTIME_DBUS:
    {
        if( type == ClientAPITypes::NotifyType::NT_CHANGED )
        {
            insertProvideData(signalNameList, handle, m_changeDBusClientIDList);
        }
        else if( type == ClientAPITypes::NotifyType::NT_UPDATED )
        {
            insertProvideData(signalNameList, handle, m_updateDBusClientIDList);
        }
        else
        {

        }

        break;
    }
    case RuntimeType::RUNTIME_SOMEIP:
    {
        if( type == ClientAPITypes::NotifyType::NT_CHANGED )
        {
            insertProvideData(signalNameList, handle, m_changeSomeIPClientIDList);
        }
        else if( type == ClientAPITypes::NotifyType::NT_UPDATED )
        {
            insertProvideData(signalNameList, handle, m_updateSomeIPClientIDList);
        }
        else
        {

        }
        break;
    }
    }
}

void OnBoardProviderService::insertProvideData(vector<string> &signalNameList, ClientAPITypes::Handle &handle, ProvideCDLDataList &provideClientIDList)
{
    for( unsigned int i=0; i<signalNameList.size(); i++ )
    {
        ProvideCDLDataList::iterator provideClientIDListIter = provideClientIDList.find(signalNameList.at(i));

        ClientInfoList::iterator clientInfoIter = m_registeredClientInfoList.find(handle);

        if( provideClientIDListIter == provideClientIDList.end() )    //no data
        {
            ClientInfoList clientInfoList;
            clientInfoList.insert(pair<ClientAPITypes::Handle, ClientInfo>(handle, clientInfoIter->second));
            provideClientIDList.insert(pair<string, ClientInfoList>(signalNameList.at(i), clientInfoList));
        }
        else
        {
            provideClientIDListIter->second.insert(pair<ClientAPITypes::Handle, ClientInfo>(handle, clientInfoIter->second));
        }
    }
}

CommonAPI::ClientIdList OnBoardProviderService::getProvideDBusClientIdList(const string &signalName, const ClientAPITypes::NotifyType &noti_type)
{
    vector<std::shared_ptr<CommonAPI::ClientId>> dbusClientIdList;
    CommonAPI::ClientIdList providedDBusClientIdList;

    if( noti_type == ClientAPITypes::NotifyType::NT_CHANGED )
    {
        ProvideCDLDataList::iterator changedDBusClientIDListIter = m_changeDBusClientIDList.find(signalName);

        if( changedDBusClientIDListIter != m_changeDBusClientIDList.end() )  //data exist
        {
            for( ClientInfoList::iterator iter = changedDBusClientIDListIter->second.begin(); iter != changedDBusClientIDListIter->second.end(); iter++ )
            {
                dbusClientIdList.push_back(iter->second.clientID);
            }
        }
    }

    ProvideCDLDataList::iterator updatedDBusClientIDListIter = m_updateDBusClientIDList.find(signalName);

    if( updatedDBusClientIDListIter != m_updateDBusClientIDList.end() )  //data exist
    {
        for( ClientInfoList::iterator iter = updatedDBusClientIDListIter->second.begin(); iter != updatedDBusClientIDListIter->second.end(); iter++ )
        {
            dbusClientIdList.push_back(iter->second.clientID);
        }
    }

    for( unsigned int i = 0; i<dbusClientIdList.size(); i++ )
    {
        providedDBusClientIdList.insert(dbusClientIdList.at(i));
    }

    return providedDBusClientIdList;
}

CommonAPI::ClientIdList OnBoardProviderService::getProvideSomeIPClientIdList(const string &signalName, const ClientAPITypes::NotifyType &noti_type)
{
    vector<std::shared_ptr<CommonAPI::ClientId>> someIPClientIdList;
    CommonAPI::ClientIdList providedSomeIPClientIdList;

    if( noti_type == ClientAPITypes::NotifyType::NT_CHANGED )
    {
        ProvideCDLDataList::iterator changedSomeIPClientIDListIter = m_changeSomeIPClientIDList.find(signalName);

        if( changedSomeIPClientIDListIter != m_changeSomeIPClientIDList.end() )  //data exist
        {
            for( ClientInfoList::iterator iter = changedSomeIPClientIDListIter->second.begin(); iter != changedSomeIPClientIDListIter->second.end(); iter++ )
            {
                someIPClientIdList.push_back(iter->second.clientID);
            }
        }
    }

    ProvideCDLDataList::iterator updatedsomeIPClientIdListIter = m_updateSomeIPClientIDList.find(signalName);

    if( updatedsomeIPClientIdListIter != m_updateSomeIPClientIDList.end() )  //data exist
    {
        for( ClientInfoList::iterator iter = updatedsomeIPClientIdListIter->second.begin(); iter != updatedsomeIPClientIdListIter->second.end(); iter++ )
        {
            someIPClientIdList.push_back(iter->second.clientID);
        }
    }

    for( unsigned int i = 0; i<someIPClientIdList.size(); i++ )
    {
        providedSomeIPClientIdList.insert(someIPClientIdList.at(i));
    }

    return providedSomeIPClientIdList;
}

void OnBoardProviderService::notifyDBusClientData(CDL_DATA &cdlData, CommonAPI::ClientIdList &dbusClientIDList)
{
    const std::shared_ptr<CommonAPI::ClientIdList> clientIdList = std::make_shared<CommonAPI::ClientIdList>(dbusClientIDList);

    m_onBoardProviderDBusService->fireNotifyDataSelective(cdlData.name, getCDLValueType(cdlData.type), cdlData.unit, cdlData.value, cdlData.time_stamp, clientIdList);
}

void OnBoardProviderService::notifySomeIPClientData(CDL_DATA &cdlData, CommonAPI::ClientIdList &someipClientIDList)
{
    const std::shared_ptr<CommonAPI::ClientIdList> clientIdList = std::make_shared<CommonAPI::ClientIdList>(someipClientIDList);

    m_onBoardProviderSomeIPService->fireNotifyDataSelective(cdlData.name, getCDLValueType(cdlData.type), cdlData.unit, cdlData.value, cdlData.time_stamp, clientIdList);
}
