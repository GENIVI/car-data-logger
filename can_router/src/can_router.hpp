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

#ifndef CANROUTER_H
#define CANROUTER_H

#include <QObject>
#include <dlt.h>
#include <QTimer>

extern "C"
{
    #include <vsi/vsi.h>
}

class CANRouterServer;

class CANRouter : public QObject
{
    Q_OBJECT

public:
    static CANRouter * instance();

private:
    CANRouter();
    ~CANRouter();

public slots:
    void onVehicleSpeedChanged(qint16 vehicleSpeed);
    void onVehicleEngineSpeedChanged(qint16 engineSpeed);

public:
    void init();
    void vsiInit();

private:
    DLT_DECLARE_CONTEXT(mContext)
    vsi_handle m_handle;
    vsi_result m_result;
    CANRouterServer * m_canRouterServer;
};


#endif // CANROUTER_H

