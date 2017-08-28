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

#ifndef CANROUTERSERVER_H
#define CANROUTERSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class CANRouterServer : public QObject
{
    Q_OBJECT

public:
    explicit CANRouterServer(QObject *parent=NULL);
    ~CANRouterServer();

    static CANRouterServer *instance();

public:
    void init();

signals:
    void signalNotifyVehicleSpeedChanged(qint16 data);
    void signalNotifyVehicleEngineSpeedChanged(qint16 data);

public slots:
    void acceptConnection();
    void receiveData();
    void disconnectedSocket();

private:
    QTcpServer m_server;
    QTcpSocket *m_socketClient;
};


#endif // CANROUTERSERVER_H

