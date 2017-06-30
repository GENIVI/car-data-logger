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

#include "dbusclienttestapp1.h"
#include "CommonAPI/CommonAPI.hpp"

#include <QDebug>
#include <functional>
#include <QDateTime>
#include <iomanip>
#include <sstream>

/******************************************************
 *
 * < Register ID List >
 *
 * - Common Signals -
 * Signal.Drivetrain.Transmission.Speed 63
 * Signal.Drivetrain.InternalCombustionEngine.RPM 54
 *
 * - Difference Signals -
 * Signal.Chassis.Accelerator.PedalPosition 980
 * Signal.Chassis.Brake.PedalPosition 981       ( Request Data )
 *
 ******************************************************/

DBusClientTestApp1::DBusClientTestApp1()
    :m_handle(0)
{
    qDebug() << "DBusClientTestApp1 created";
    init();
    createProxy();
    subscribeEvents();
}

DBusClientTestApp1::~DBusClientTestApp1()
{
    qDebug() << "delete DBusClientTestApp1";
}

void DBusClientTestApp1::createProxy()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    m_proxy = runtime->buildProxy<ClientAPIProxy>("local", ClientAPI::getInterface());
}

void DBusClientTestApp1::subscribeEvents()
{
    m_proxy->getProxyStatusEvent().subscribe(std::bind(&DBusClientTestApp1::onConnectionsStatusChanged, this, std::placeholders::_1));
    m_proxy->getNotifyDataSelectiveEvent().subscribe(std::bind(&DBusClientTestApp1::onNotifyData,
                            this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
}

void DBusClientTestApp1::init()
{
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(requestCDLData()));
    connect(this, SIGNAL(dbusClientConnected()), this, SLOT(registerClient()));;
    m_dbusRequestedNameList.clear();

    m_notiType = ClientAPITypes::NotifyType::NT_CHANGED;
    m_dbusRequestedNameList.push_back("Signal.Drivetrain.Transmission.Speed");
    m_dbusRequestedNameList.push_back("Signal.Drivetrain.InternalCombustionEngine.RPM");
    m_dbusRequestedNameList.push_back("Signal.Chassis.Accelerator.PedalPosition");
}

void DBusClientTestApp1::onConnectionsStatusChanged(CommonAPI::AvailabilityStatus status)
{
    if ( status == CommonAPI::AvailabilityStatus::AVAILABLE )
    {   qDebug() << "<< DBusClientTestApp1::onConnectionStatusChanged >> Succeed to connect with DataProvider";
        emit dbusClientConnected();
    }
    else
    {
        qDebug() << "<< DBusClientTestApp1::onConnectionStatusChanged >> Failed to connect with DataProvider";
    }
}

void DBusClientTestApp1::onNotifyData(const string &_signalName, const ClientAPITypes::Types &_type, const string &_unit, const ClientAPITypes::CDLValue &_value, const uint64_t &_timeStamp)
{
    if( _signalName == "Signal.Chassis.Brake.PedalPosition")
    {
        qDebug() << "============== << Client 1  : Request Data >> =======================";
    }
    else
    {
        qDebug() << "============== << Client 1  : Notify Data >> =======================";
    }
    qDebug() << "1. Name  : " << QString::fromStdString(_signalName);
    qDebug() << "2. Type  : " << _type;
    qDebug() << "3. Unit  : " << QString::fromStdString(_unit);
    qDebug() << "4. Value : " << getCDLValue(_value);
    qDebug() << "5. T_S   : " << getDateTime(_timeStamp);
}

QString DBusClientTestApp1::getDateTime(const uint64_t _utcTimeStamp)
{
    QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(_utcTimeStamp);
    QString dateTimeFormat = dateTime.toString("yyyy/MM/dd_hh:mm:ss:zzz");

    return dateTimeFormat;
}

QString DBusClientTestApp1::getCDLValue(const ClientAPITypes::CDLValue &value)
{
    QString cdlValue;

    if( value.isType<uint8_t>() )
    {
        uint8_t data = value.get<uint8_t>();

        cdlValue = QString::number(data);
    }
    else if( value.isType<int8_t>() )
    {
        int8_t data = value.get<int8_t>();

        cdlValue = QString::number(data);
    }
    else if( value.isType<uint16_t>() )
    {
        uint16_t data = value.get<uint16_t>();

        cdlValue = QString::number(data);
    }
    else if( value.isType<int16_t>() )
    {
        int16_t data = value.get<int16_t>();

        cdlValue = QString::number(data);
    }
    else if( value.isType<uint32_t>() )
    {
        uint32_t data = value.get<uint32_t>();

        cdlValue = QString::number(data);
    }
    else if( value.isType<int32_t>() )
    {
        int32_t data = value.get<int32_t>();

        cdlValue = QString::number(data);
    }
    else if( value.isType<uint64_t>() )
    {
        uint64_t data = value.get<uint64_t>();

        cdlValue = QString::number(data);
    }
    else if( value.isType<int64_t>() )
    {
        int64_t data = value.get<int64_t>();

        cdlValue = QString::number(data);
    }
    else if( value.isType<bool>() )
    {
        bool data = value.get<bool>();

        cdlValue = QString::number(data);
    }
    else if( value.isType<float>() )
    {
        float data = value.get<float>();

        cdlValue = QString::number(data);
    }
    else if( value.isType<double>() )
    {
        double data = value.get<double>();

        cdlValue = QString::number(data);
    }
    else if( value.isType<string>() )
    {
        string data = value.get<string>();

        cdlValue = QString::fromStdString(data);
    }
    else if( value.isType<CommonAPI::ByteBuffer>() )
    {
        CommonAPI::ByteBuffer data = value.get<CommonAPI::ByteBuffer>();
        string dataStr;

        for( unsigned int i=0; i<data.size(); i++ )
        {
            stringstream tmp;

            tmp << setfill('0') << std::hex << setw(2) << (int)data.at(i);
            dataStr.append(tmp.str());

            if( i >= 10 )
            {
                break;
            }

            if( i != data.size() )
            {
                dataStr.append(" ");
            }
        }

        cdlValue = QString::fromStdString(dataStr);
    }
    else
    {
        qDebug() << "Invalid CDL Value Type";
    }

    return cdlValue;
}

void DBusClientTestApp1::registerClient()
{
    CommonAPI::CallStatus callStatus;
    ClientAPITypes::ResultCode result;

    m_proxy->registerClient("Client1", callStatus, m_handle, result);

    if ( callStatus != CommonAPI::CallStatus::SUCCESS )
    {
        qDebug() << "<< DBusClientTestApp1::registerClient >> Error call status";

        return;
    }

    if ( result != ClientAPITypes::ResultCode::RC_OK )
    {
        qDebug() << "<< DBusClientTestApp1::registerClient >> Failed to registered this client";

        return;
    }

    qDebug() << "DBusClient1 is registered as handle : "<<m_handle;

    if ( m_handle != 0 )
    {
        CommonAPI::CallStatus callStatus;
        ClientAPITypes::ResultCode result;

        m_proxy->setListenData(m_handle, m_dbusRequestedNameList, m_notiType, callStatus, result);

        if ( callStatus != CommonAPI::CallStatus::SUCCESS )
        {
            qDebug() << "<< DBusClientTestApp1::registerClient >> Failed to setListenData() wit DataProvider";

            return;
        }
    }

    m_timer->start(800);
}

void DBusClientTestApp1::requestCDLData()
{
    if( m_handle != 0 )
    {
        CommonAPI::CallStatus callStatus;
        ClientAPITypes::ResultCode result;

        m_proxy->getData(m_handle, "Signal.Chassis.Brake.PedalPosition", callStatus, result);
    }
    else
    {
        qDebug() << "<< DBusClientTestApp1::requestVehicleData() >> Client is not connected with DataProvider ( Handle : )" << m_handle;
        return;
    }
}
