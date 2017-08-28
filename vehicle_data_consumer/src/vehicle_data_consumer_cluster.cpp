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

#include "vehicle_data_consumer_cluster.hpp"
#include "common_log_header.hpp"

#include <CommonAPI/CommonAPI.hpp>

/******************************************************
 *
 * < Register ID List >
 *
 * - Common Signals -
 * Signal.Drivetrain.InternalCombustionEngine.RPM 54
 * Signal.Drivetrain.Transmission.Speed 63
 *
 ******************************************************/

VehicleDataConsumerCluster::VehicleDataConsumerCluster()
    :m_handle(0)
{
    initLog();
    init();
    createProxy();
    subscribeEvents();
}

VehicleDataConsumerCluster::~VehicleDataConsumerCluster()
{
    auto clusterRuntime = CommonAPI::Runtime::get();

    clusterRuntime->unregisterService("local", ClusterData::getInterface(), ClusterData::getInterface());
}

void VehicleDataConsumerCluster::init()
{
    m_requestIDList.clear();

    m_requestIDList.push_back("Drivetrain.InternalCombustionEngine.RPM");
    m_requestIDList.push_back("Drivetrain.Transmission.Speed");
    m_notiType = ClientAPITypes::NotifyType::NT_CHANGED;

    m_clusterDataService = make_shared<ClusterDataStubDefault>();

    auto runtime = CommonAPI::Runtime::get();
    if( runtime->registerService("local", ClusterData::getInterface(), m_clusterDataService) )
    {
        BOOST_LOG_TRIVIAL( info ) << boost::format( "Succeed to register ClusterDataService");
    }
    else
    {
        BOOST_LOG_TRIVIAL( info ) << boost::format( "Failed to register ClusterDataService");
    }
}

void VehicleDataConsumerCluster::initLog()
{
    boost::log::add_common_attributes();
    boost::log::core::get()->set_filter( boost::log::trivial::severity >= boost::log::trivial::severity_level::info );

    auto fmtTimeStamp = boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%H:%M:%S.%f");
    auto fmtSeverity = boost::log::expressions::attr<boost::log::trivial::severity_level>("Severity");

    boost::log::formatter logFmt;

    logFmt = boost::log::expressions::format("[%1%] [%2%] \t %3%")
            % fmtTimeStamp % fmtSeverity
            % boost::log::expressions::smessage;

    /* console sink */
    auto consoleSink = boost::log::add_console_log(std::clog);
    consoleSink->set_formatter(logFmt);
}

void VehicleDataConsumerCluster::createProxy()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    m_proxy = runtime->buildProxy<ClientAPIProxy>("local", ClientAPI::getInterface());
}

void VehicleDataConsumerCluster::subscribeEvents()
{
    m_proxy->getProxyStatusEvent().subscribe(std::bind(&VehicleDataConsumerCluster::onConnectionsStatusChanged, this, std::placeholders::_1));
    m_proxy->getNotifyDataSelectiveEvent().subscribe(std::bind(&VehicleDataConsumerCluster::onNotifyData,
                                                      this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
}

void VehicleDataConsumerCluster::onConnectionsStatusChanged(CommonAPI::AvailabilityStatus status)
{
    if ( status == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        registerClient();
    }
    else
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< VehicleDataConsumerDBusClientCluster::onConnectionStatusChanged >> Failed to connect with OnBoardProvider" );
    }
}

void VehicleDataConsumerCluster::onNotifyData(const string &_id, const ClientAPITypes::Types &_type, const string &_unit, const ClientAPITypes::CDLValue &_value, const uint64_t &_timeStamp)
{
    BOOST_LOG_TRIVIAL( debug ) << boost::format( "============== << Vehicle Data Consumer Cluster  : Notify Data() >> =======================" );
    BOOST_LOG_TRIVIAL( debug ) << boost::format( "1. ID         : %s" ) % _id;
    BOOST_LOG_TRIVIAL( debug ) << boost::format( "2. Type       : %s" ) % _type;
    BOOST_LOG_TRIVIAL( debug ) << boost::format( "3. Unit       : %s" ) % _unit;
    BOOST_LOG_TRIVIAL( debug ) << boost::format( "5. Time Stamp : %d" ) % _timeStamp;

    if( _id == "Drivetrain.InternalCombustionEngine.RPM" )   //RPM
    {
        if ( _value.isType<uint16_t>() )
        {
            m_clusterDataService->setEngineSpeedAttribute( _value.get<uint16_t>() );
        }
    }
    else if( _id == "Drivetrain.Transmission.Speed" )  //Speed
    {
        if ( _value.isType<int16_t>() )
        {
            m_clusterDataService->setVehicleSpeedAttribute( _value.get<int16_t>() );
        }
    }
    else
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< VehicleDataConsumerDBusClientCluster::onNotifyData() >> vehicle-data-consumer-cluster doesn't need this data id : %s." ) %_id;
    }
}

void VehicleDataConsumerCluster::registerClient()
{
    CommonAPI::CallStatus callStatus;
    ClientAPITypes::ResultCode result;

    m_proxy->registerClient("VehicleDataConsumerCluster", callStatus, m_handle, result);

    if( callStatus != CommonAPI::CallStatus::SUCCESS )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< VehicleDataConsumerDBusClientCluster::registerClient::registerClient() >> Error call status." );
        return;
    }

    if ( result != ClientAPITypes::ResultCode::RC_OK )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< VehicleDataConsumerDBusClientCluster::registerClient() >> Failed to registered this client." );
        return;
    }

    if( m_handle != 0 )
    {
        BOOST_LOG_TRIVIAL( info ) << boost::format( "<< VehicleDataConsumerDBusClientCluster::registerClient() >> Registered handle is %d from OnBoardProvider" ) % m_handle;

        CommonAPI::CallStatus callStatus;
        ClientAPITypes::ResultCode result;

        m_proxy->setListenData(m_handle, m_requestIDList, m_notiType, callStatus, result);

        if ( callStatus != CommonAPI::CallStatus::SUCCESS )
        {
            BOOST_LOG_TRIVIAL( error ) << boost::format( "<< VehicleDataConsumerDBusClientCluster::registerClient::setNotigyData() >> Error call status." );
            return;
        }
    }
}
