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

#ifndef ONBOARDPROVIDERSERVICE_H
#define ONBOARDPROVIDERSERVICE_H

#include "../../common/cdl_common_define.hpp"

#include <org/genivi/CDL/ClientAPIStubDefault.hpp>
#include <CommonAPI/CommonAPI.hpp>
#include <boost/thread.hpp>
#include <unordered_map>

using namespace std;
using namespace v1::org::genivi::CDL;

class OnBoardProviderDBusService;
class OnBoardProviderSomeIPService;
class DataManager;
class ClientAuthenticationDecryptionHandler;

/**
 * @brief This class is an interface between Clients( DBus or SomeIP ) and OnBoardProvider.
 *
 * This class provides data to the clients according to the desired data notify_type.
 *
 * When clients register with each service( DBus, SomeIP ), the OnBoardProviderService provides a handle to the clients.
 *
 */

class OnBoardProviderService
{
public:
    struct CDL_DATA
    {
        std::string id;
        ClientAPITypes::CDLValue value;
        std::string name;
        CDLDataTypes type;
        std::string unit;
        bool valid_state;
        uint64_t time_stamp;
    };

    enum RuntimeType
    {
        RUNTIME_DBUS=0,
        RUNTIME_SOMEIP
    };

    struct ClientInfo
    {
        std::shared_ptr<CommonAPI::ClientId> clientID;
        RuntimeType runTimeType;
    };

    /**
     * --------------------------------------------------
     *         Type         |   Key    |     Value
     * --------------------------------------------------
     *       ClientInfo     |  Handle  |   ClientInfo
     * ClientIDToHandleList | ClientID |     Handle
     *  ProvideCDLDataList  | SignalID | ClientInfo List
     *   ClientDataNameList   |  Handle  |  ClientID List
     *
     */
    typedef unordered_map<ClientAPITypes::Handle, ClientInfo> ClientInfoList;
    typedef unordered_map<std::shared_ptr<CommonAPI::ClientId>, ClientAPITypes::Handle> ClientIDToHandleList;
    typedef unordered_map<string, ClientInfoList> ProvideCDLDataList;
    typedef unordered_map<ClientAPITypes::Handle, vector<string>> ClientDataNameList;

public:
    OnBoardProviderService(DataManager *dataManager);
    virtual ~OnBoardProviderService();

public:
    void registerClient(RuntimeType _runtime, const std::shared_ptr<CommonAPI::ClientId> _client, std::string _key, ClientAPITypes::Handle & handleOut, ClientAPITypes::ResultCode & result);
    void setListenData(const std::shared_ptr<CommonAPI::ClientId> _client, ClientAPITypes::Handle _handle, std::vector<std::string> _signalNameList, ClientAPITypes::NotifyType _type, ClientAPITypes::ResultCode & result);
    void getData(const std::shared_ptr<CommonAPI::ClientId> _client, ClientAPITypes::Handle _handle, std::string _signalName, ClientAPITypes::ResultCode & result);

    /**
     * @brief Provide the CDL data received from the VSSDataCollector to registered clients.
     *
     * The NotifyType param is the type of data that the registered client wants to receive.
     *
     * The CDLData Param is the data received from the VSSDataCollector.
     *
     * @param NotifyType
     * @param CDLData
     *
     */
    void provideCDLData(ClientAPITypes::NotifyType notiType, CDL_DATA & cdlData);
    ClientAPITypes::CDLValue getCDLValue(char * _value, CDLDataTypes _type, unsigned long _dataLength);
    ClientAPITypes::Types getCDLValueType(CDLDataTypes _type);

private:
    /**
     * @brief Manage the Client Id List to set with new.
     *
     * Update or insert the ProvideCDLDataList to new when the client registers the wanted ID lists with setListenData.
     *
     * If the id list exists, delete it before saving the new id list.
     *
     * @param ClientHandle
     *
     */
    void manageListenData(ClientAPITypes::Handle & handle);
    void eraseListenData(ClientDataNameList::iterator & clientDataNameListIter, ProvideCDLDataList & provideClientIDList, ClientAPITypes::Handle & handle);

    /**
     * @brief Manage the data in seperate containers according to the infomation of client.
     *
     * @param ClientHandle
     * @param NotifyType
     * @param ID List
     *
     */
    void manageProvideData(ClientAPITypes::Handle & handle, ClientAPITypes::NotifyType & type, vector<string> & signalNameList);
    void insertProvideData(vector<string> & signalNameList, ClientAPITypes::Handle & handle, ProvideCDLDataList & provideClientIDList);

    /**
     * @brief Get the client ID list from the DBus/SomeIP containers to provide the data.
     *
     * The SignalId param is a key value to find the notifyType in the containers.
     *
     * @param SignalId
     * @param NotifyType
     *
     */
    CommonAPI::ClientIdList getProvideDBusClientIdList(const string & signalName, const ClientAPITypes::NotifyType & noti_type);
    CommonAPI::ClientIdList getProvideSomeIPClientIdList(const string & signalName, const ClientAPITypes::NotifyType & noti_type);

    /**
     * @brief Provide the CDL Data to registered DBus type client using the ClientAPI interface.
     *
     * The DBusClientIDList param is a DBus-type client-id-list wants to receive.
     *
     * @param CDLData
     * @param DBusClientIDList
     *
     */
    void notifyDBusClientData(CDL_DATA & cdlData, CommonAPI::ClientIdList & dbusClientIDList);

    /**
     * @brief Provide the CDL Data to registered SomeIP type client using the ClientAPI interface.
     *
     * The DBusClientIDList param is a someIP-type client-id-list wants to receive.
     *
     * @param CDLData
     * @param DBusClientIDList
     *
     */
    void notifySomeIPClientData(CDL_DATA & cdlData, CommonAPI::ClientIdList & someipClientIDList);

    /**
     * @brief Authenicate whether the client is valid or not.
     *
     * Check the client is valid or not through comparing the privateKey provided with the publicKey using Client_Authentication API.
     *
     * @param privateKey
     *
     */
    bool authenticationClient(string privateKey);

    vector<string> stringSplit(string name, string delimiter);

private:
    DataManager * m_dataManager;
    std::shared_ptr<OnBoardProviderDBusService> m_onBoardProviderDBusService;
    std::shared_ptr<OnBoardProviderSomeIPService> m_onBoardProviderSomeIPService;

    ClientAuthenticationDecryptionHandler * m_clientAuthenticationDecryptionHandler;

    ClientInfoList m_registeredClientInfoList;
    ClientIDToHandleList m_clientIdToHandleList;

    ProvideCDLDataList m_updateDBusClientIDList;
    ProvideCDLDataList m_changeDBusClientIDList;
    ProvideCDLDataList m_updateSomeIPClientIDList;
    ProvideCDLDataList m_changeSomeIPClientIDList;

    ClientDataNameList m_clientDataNameList;

    ClientAPITypes::Handle m_clientHandle;

    string m_publicKey;
};

#endif // ONBOARDPROVIDERSERVICE_H
