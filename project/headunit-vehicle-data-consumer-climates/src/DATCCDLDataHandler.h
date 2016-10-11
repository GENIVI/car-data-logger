/*
 * Copyright (C) 2016, IVIS
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
 * \author Seung-Hyun Yun <shyun@ivisolution.com>
 *
 * \copyright Copyright (c) 2016, IVIS \n
 * License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
 *
 * \file DATCCDLDataHandler.h
*/

#ifndef DATCCDLDATAHANDLER_H
#define DATCCDLDATAHANDLER_H

#include <cdl/CDLClientAPIDefine.h>
#include <com/ivis/DATCManager/DATCManagerTypes.hpp>
#include <QObject>
#include <dlt.h>

#include "DATCDataHandler.h"

using namespace v1::com::ivis::DATCManager;

class DATCCDLDataHandler : public QObject, public DATCDataHandler
{
    Q_OBJECT

private:
    DATCCDLDataHandler();

public:
    virtual ~DATCCDLDataHandler();

    static DATCCDLDataHandler * instance();
    static void finalize();

public:
    virtual void initHandler();

public:
    virtual void requestGetSupportedTemperatureRange();
    virtual void requestSetTargetTemperature(const DATCManagerTypes::EAreaType &_areaType, const double &_temperature);
    virtual void requestSetTargetTemperatureByDelta(const DATCManagerTypes::EAreaType &_areaType, const double &_temperatureDelta);
    virtual void requestGetSupportedFanDirection();
    virtual void requestGetSupportedFanSpeedRange();
    virtual void requestSetFanSpeed(const DATCManagerTypes::EAreaType &_areaType, const uint16_t &_fanSpeed);
    virtual void requestSetFanSpeedByDelta(const DATCManagerTypes::EAreaType &_areaType, const uint16_t &_fanSpeedDelta);
    virtual void requestGetSupportedDefrostTarget();
    virtual void requestGetSteeringWheelHeaterSupported();
    virtual void requestGetSeatHeaterSupported();
    virtual void requestGetSeatCoolerSupported();

private:
    void callbackDATCClient(std::string _domain, std::string _subDomain, std::string _id, CDL::CDLData _data);

private:
    DLT_DECLARE_CONTEXT(mContext)
};



#endif // DATCCDLDATAHANDLER_H
