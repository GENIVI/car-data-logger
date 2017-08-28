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

#include "can_router.hpp"
#include "can_router_server.hpp"

#include <QDebug>
#include <QtMath>

#define VEHICLE_SPEED_ID            63     //Signal.Drivetrain.Transmission.Speed              63
#define ENGINE_SPEED_ID             54     //Signal.Drivetrain.InternalCombustionEngine.RPM    54

CANRouter * g_can_router_instance = NULL;

CANRouter *CANRouter::instance()
{
    if ( g_can_router_instance == NULL )
    {
        g_can_router_instance = new CANRouter;
    }

    return g_can_router_instance;
}

CANRouter::CANRouter()
{
    m_canRouterServer = CANRouterServer::instance();
    init();
    DLT_REGISTER_CONTEXT( mContext, "vedp", "Vehicle Data Provider");
}

void CANRouter::vsiInit()
{
    m_handle = vsi_initialize();

    m_result.domainId = 0;
    m_result.data = (char*)malloc(1024);
}

CANRouter::~CANRouter()
{
    vsi_destroy(m_handle);
}


void CANRouter::init()
{
    connect(m_canRouterServer, SIGNAL(signalNotifyVehicleSpeedChanged(qint16)), this, SLOT(onVehicleSpeedChanged(qint16)));
    connect(m_canRouterServer, SIGNAL(signalNotifyVehicleEngineSpeedChanged(qint16)), this, SLOT(onVehicleEngineSpeedChanged(qint16)));

    vsiInit();
}

void CANRouter::onVehicleSpeedChanged(qint16 vehicleSpeed)
{
    m_result.signalId = VEHICLE_SPEED_ID;
    memcpy(m_result.data, &vehicleSpeed, sizeof(qint16));
    m_result.dataLength = sizeof(qint16);
    vsi_fire_signal(m_handle, &m_result);
}

void CANRouter::onVehicleEngineSpeedChanged(qint16 engineSpeed)
{
    m_result.signalId = ENGINE_SPEED_ID;
    memcpy(m_result.data, &engineSpeed, sizeof(qint16));
    m_result.dataLength = sizeof(qint16);
    vsi_fire_signal(m_handle, &m_result);
}

