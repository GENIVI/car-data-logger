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

#include "can_router_server.hpp"

CANRouterServer * g_vehicle_data_provider_server_instance = NULL;


CANRouterServer::CANRouterServer(QObject *parent)
    :QObject(parent)
{
    init();
    bool status = m_server.listen(QHostAddress::Any, 9000);
    if(status)
    {

        qDebug()<<"==========================================";
        qDebug()<<"Socket Open ( Port : 9000 )";
        qDebug()<<"------- wait client -------";
        qDebug()<<"==========================================";
    }
}

CANRouterServer::~CANRouterServer()
{

}

CANRouterServer *CANRouterServer::instance()
{
    if ( g_vehicle_data_provider_server_instance == NULL )
    {
        g_vehicle_data_provider_server_instance = new CANRouterServer;
    }

    return g_vehicle_data_provider_server_instance;
}

void CANRouterServer::init()
{
    connect(&m_server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}



void CANRouterServer::acceptConnection()
{
    qDebug()<<"<< CANRouterServer::acceptConnection() >> Socket Connected";
    m_socketClient=m_server.nextPendingConnection();

    connect(m_socketClient, SIGNAL(readyRead()), this, SLOT(receiveData()));
    connect(m_socketClient, SIGNAL(disconnected()), this, SLOT(disconnectedSocket()));
    m_socketClient->setSocketOption(QAbstractSocket::LowDelayOption, 1);
}

void CANRouterServer::receiveData()
{
    QByteArray rxData;

    rxData = m_socketClient->readAll();

    QString text = QString::fromUtf8(rxData.data(), rxData.size());

    QStringList items = text.split("\n");

    uint16_t engineSpeed = 0;
    uint16_t vehicleSpeed = 0;

    for (int i = 0; i < items.size(); i++)
    {
        QStringList item = items[i].split(", ");

        if ( item[0] == "EngineSpeed" )
        {
            engineSpeed = item[1].toDouble();
            emit signalNotifyVehicleEngineSpeedChanged(engineSpeed);
        }

        if ( item[0] == "VehicleSpeed" )
        {
            vehicleSpeed = item[1].toDouble();
            emit signalNotifyVehicleSpeedChanged(vehicleSpeed);
        }
    }

    // flush engine speed and vehicle speed to VSI
}

void CANRouterServer::disconnectedSocket()
{
    qDebug()<<"Socket Disconnected";
    m_server.close();
    m_server.listen(QHostAddress::Any, 1234);
}
