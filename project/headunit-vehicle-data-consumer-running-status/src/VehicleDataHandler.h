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
 * \file VehicleDataHandler.h
*/

#ifndef VEHICLEDATAHANDLER_H
#define VEHICLEDATAHANDLER_H

#include <QObject>
#include <CommonAPI/CommonAPI.hpp>
#include <com/ivis/VehicleDataManager/VehicleDataManagerTypes.hpp>

#include "DataHandlerFactory.h"

using namespace v1::com::ivis::VehicleDataManager;

class VehicleDataHandler : public IDataHandler
{
    DECLARE_CALLBACK (VehicleSpeedChanged,           const VehicleDataManagerTypes::VehicleSpeed &);
    DECLARE_CALLBACK (VinChanged,                    const std::string &);
    DECLARE_CALLBACK (TransmissionGearStatusChanged, const VehicleDataManagerTypes::TransmissionGearStatus &);
    DECLARE_CALLBACK (DrivingRestrictionChanged,     const bool &);
    DECLARE_CALLBACK (LowFuelWarningChanged,         const bool &);

public:
    VehicleDataHandler();
    virtual ~VehicleDataHandler();
};

#endif // VEHICLEDATAHANDLER_H
