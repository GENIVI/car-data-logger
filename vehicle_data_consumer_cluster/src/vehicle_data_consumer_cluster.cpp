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
#include "../cdl_daemon/common/client_authentication/client_authentication_encryption_handler.hpp"

#include <CommonAPI/CommonAPI.hpp>

/******************************************************
 *
 * < Register ID List >
 *
 * - Vehicle Data -
 * Signal.Drivetrain.InternalCombustionEngine.RPM 54
 * Signal.Drivetrain.Transmission.Speed 63
 * Signal.Drivetrain.Transmission.Gear
 *
 * - Warning Data -
 * Signal.Cabin.Seat.Row1.Pos1.Airbag.IsDeployed
 * Signal.Drivetrain.FuelSystem.Level
 * Signal.Body.Windshield.Front.WasherFluid.LevelLow
 * Signal.Chassis.ParkingBrake.IsEngaged
 * Signal.Cabin.Seat.Row1.Pos1.IsBelted
 * Signal.Body.Lights.IsFrontFogOn
 * Signal.Body.Lights.IsLowBeamOn
 * Signal.Body.Lights.IsHighBeamOn
 * Signal.Body.Lights.IsLeftIndicatorOn
 * Signal.Body.Lights.IsRightIndicatorOn
 * Signal.Drivetrain.InternalCombustionEngine.ECT
 *
 ******************************************************/

VehicleDataConsumerCluster::VehicleDataConsumerCluster()
    :m_handle(0), m_publicKey("IVIS")
    ,m_clientAuthenticationEncryptionHandler(nullptr)
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
    m_requestSignalNameList.clear();

    m_clientAuthenticationEncryptionHandler = new ClientAuthenticationEncryptionHandler();

    m_requestSignalNameList.push_back("Signal.Drivetrain.InternalCombustionEngine.RPM");
    m_requestSignalNameList.push_back("Signal.Drivetrain.Transmission.Speed");
    m_requestSignalNameList.push_back("Signal.Cabin.Seat.Row1.Pos1.Airbag.IsDeployed");
    m_requestSignalNameList.push_back("Signal.Drivetrain.FuelSystem.Level");
    m_requestSignalNameList.push_back("Signal.Body.Windshield.Front.WasherFluid.LevelLow");
    m_requestSignalNameList.push_back("Signal.Chassis.ParkingBrake.IsEngaged");
    m_requestSignalNameList.push_back("Signal.Cabin.Seat.Row1.Pos1.IsBelted");
    m_requestSignalNameList.push_back("Signal.Body.Lights.IsFrontFogOn");
    m_requestSignalNameList.push_back("Signal.Body.Lights.IsLowBeamOn");
    m_requestSignalNameList.push_back("Signal.Body.Lights.IsHighBeamOn");
    m_requestSignalNameList.push_back("Signal.Body.Lights.IsLeftIndicatorOn");
    m_requestSignalNameList.push_back("Signal.Body.Lights.IsRightIndicatorOn");
    m_requestSignalNameList.push_back("Signal.Drivetrain.Transmission.Gear");
    m_requestSignalNameList.push_back("Signal.Drivetrain.InternalCombustionEngine.ECT");

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
        if( !registerClient() )
        {
            return;
        }
    }
    else
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< VehicleDataConsumerDBusClientCluster::onConnectionStatusChanged >> Failed to connect with on_board_provider" );
    }
}

void VehicleDataConsumerCluster::onNotifyData(const string &_id, const ClientAPITypes::Types &_type, const string &_unit, const ClientAPITypes::CDLValue &_value, const uint64_t &_timeStamp)
{
    BOOST_LOG_TRIVIAL( info ) << boost::format( "============== << Vehicle Data Consumer Cluster  : Notify Data() >> =======================" );
    BOOST_LOG_TRIVIAL( info ) << boost::format( "1. ID         : %s" ) % _id;
    BOOST_LOG_TRIVIAL( info ) << boost::format( "2. Type       : %s" ) % _type;
    BOOST_LOG_TRIVIAL( info ) << boost::format( "3. Unit       : %s" ) % _unit;
    BOOST_LOG_TRIVIAL( info ) << boost::format( "5. Time Stamp : %d" ) % _timeStamp;

    if( _id == "Signal.Drivetrain.InternalCombustionEngine.RPM" )   //RPM
    {
        if ( _value.isType<uint16_t>() )
        {
            m_clusterDataService->setEngineSpeedAttribute( _value.get<uint16_t>() );
        }
    }
    else if( _id == "Signal.Drivetrain.Transmission.Speed" )  //Speed
    {
        if ( _value.isType<int16_t>() )
        {
            m_clusterDataService->setVehicleSpeedAttribute( _value.get<int16_t>() );
        }
    }

    else if( _id == "Signal.Cabin.Seat.Row1.Pos1.Airbag.IsDeployed" )  //AirBag
    {
        if ( _value.isType<bool>() )
        {
            m_clusterDataService->setAirBagDeployedAttribute(_value.get<bool>() );
        }
    }
    else if( _id == "Signal.Drivetrain.FuelSystem.Level" )  //Low Fuel
    {
        if ( _value.isType<uint8_t>() )
        {
            m_clusterDataService->setFuelLevelAttribute(_value.get<uint8_t>() );
        }
    }
    else if( _id == "Signal.Body.Windshield.Front.WasherFluid.LevelLow" )  //Low Washer Fluid
    {
        if ( _value.isType<bool>() )
        {
            m_clusterDataService->setLowWasherFluidAttribute(_value.get<bool>() );
        }
    }
    else if( _id == "Signal.Chassis.ParkingBrake.IsEngaged" )  //Parking Brake
    {
        if ( _value.isType<bool>() )
        {
            m_clusterDataService->setParkingBrakeAttribute(_value.get<bool>() );
        }
    }
    else if( _id == "Signal.Cabin.Seat.Row1.Pos1.IsBelted" )  //Seat Belt
    {
        if ( _value.isType<bool>() )
        {
            m_clusterDataService->setSeatBeltActiveAttribute(_value.get<bool>() );
        }
    }
    else if( _id == "Signal.Body.Lights.IsFrontFogOn" )  //Fog Light
    {
        if ( _value.isType<bool>() )
        {
            m_clusterDataService->setFogLightAttribute(_value.get<bool>() );
        }
    }
    else if( _id == "Signal.Body.Lights.IsLowBeamOn" )  //Head Light
    {
        if ( _value.isType<bool>() )
        {
            m_clusterDataService->setHeadLightAttribute(_value.get<bool>() );
        }
    }
    else if( _id == "Signal.Body.Lights.IsHighBeamOn" )  //High Beam
    {
        if ( _value.isType<bool>() )
        {
            m_clusterDataService->setHighBeamAttribute(_value.get<bool>() );
        }
    }
    else if( _id == "Signal.Body.Lights.IsLeftIndicatorOn" )  //Left Indicator
    {
        if ( _value.isType<bool>() )
        {
            m_clusterDataService->setLeftIndicatorAttribute(_value.get<bool>() );
        }
    }
    else if( _id == "Signal.Body.Lights.IsRightIndicatorOn" )  //Right Indicator
    {
        if ( _value.isType<bool>() )
        {
            m_clusterDataService->setRightIndicatorAttribute(_value.get<bool>() );
        }
    }
    else if( _id == "Signal.Drivetrain.Transmission.Gear" )  //Gear State
    {
        if ( _value.isType<int8_t>() )
        {
            m_clusterDataService->setGearStateAttribute(_value.get<int8_t>() );
        }
    }
    else if( _id == "Signal.Drivetrain.InternalCombustionEngine.ECT" )
    {
        if ( _value.isType<int16_t>() )
        {
            m_clusterDataService->setEngineCoolantTemperatureAttribute(_value.get<int16_t>() );
        }
    }
    else
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< VehicleDataConsumerDBusClientCluster::onNotifyData() >> vehicle-data-consumer-cluster doesn't need this data id : %s." ) %_id;
    }
}

bool VehicleDataConsumerCluster::registerClient()
{
    CommonAPI::CallStatus callStatus;
    ClientAPITypes::ResultCode result;
    string privateKey;

    privateKey = m_clientAuthenticationEncryptionHandler->createPrivateKey(m_publicKey);

    m_proxy->registerClient(privateKey, callStatus, m_handle, result);

    if ( callStatus != CommonAPI::CallStatus::SUCCESS )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< VehicleDataConsumerCluster::registerClient >> Error call status" );

        return false;
    }

    if( result != ClientAPITypes::ResultCode::RC_OK )
    {
        switch( result )
        {
        case ClientAPITypes::ResultCode::RC_AUTHENTICATION_FAILED:
        {
            BOOST_LOG_TRIVIAL( error ) << boost::format( "<< VehicleDataConsumerCluster::registerClient >> Failed to Authentication client" );

            break;
        }
        case ClientAPITypes::ResultCode::RC_CLIENT_ALREADY_REGISTERED:
        {
            BOOST_LOG_TRIVIAL( error ) << boost::format( "<< VehicleDataConsumerCluster::registerClient >> Client is already registered" );

            break;
        }
        default:
        {
            BOOST_LOG_TRIVIAL( error ) << boost::format( "<< VehicleDataConsumerCluster::registerClient >> Invailed fail type on register client" );

            break;
        }
        }
        return false;
    }

    BOOST_LOG_TRIVIAL( info ) << boost::format("============ < VehicleDataConsumerCluster Authentication Succeed > ================");
    BOOST_LOG_TRIVIAL( info ) << boost::format("VehicleDataConsumerCluster is registered as handle :  %d") % m_handle;

    if( m_handle != 0 )
    {
        CommonAPI::CallStatus callStatus;
        ClientAPITypes::ResultCode result;

        m_proxy->setListenData(m_handle, m_requestSignalNameList, m_notiType, callStatus, result);

        if( callStatus != CommonAPI::CallStatus::SUCCESS )
        {
            BOOST_LOG_TRIVIAL( error ) << boost::format( "<< VehicleDataConsumerCluster::registerClient >> Failed to setListenData() with on_board_provider" );

            return false;
        }
    }

    return true;
}
