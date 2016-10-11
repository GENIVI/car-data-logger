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
 * \file VehicleDataManagerService.h
*/

#ifndef VEHICLEDATAMANAGERSERVICE_H
#define VEHICLEDATAMANAGERSERVICE_H

#include <QObject>
#include <com/ivis/VehicleDataManager/VehicleDataManagerStubDefault.hpp>
#include <dlt.h>

#include "DataHandlerFactory.h"

using namespace v1::com::ivis::VehicleDataManager;

class VehicleDataHandler;

class VehicleManagerService : public QObject , public VehicleDataManagerStubDefault
{
    Q_OBJECT

private:
    VehicleManagerService();

public:
    ~VehicleManagerService();

    static std::shared_ptr<VehicleManagerService> & instance();
    static void finalize();

public:
    void initService();

public:
    static int VehicleCallback(u_int32_t service_id, void *data, u_int32_t length);

signals:
    void callBackCommand(QString command);

public slots:
    void callbackCommandReceived(QString command);

public: // callbacks
    DECLARE_SERVICE_CALLBACK (VehicleSpeedChanged,           const VehicleDataManagerTypes::VehicleSpeed &);
    DECLARE_SERVICE_CALLBACK (VinChanged,                    const std::string &);
    DECLARE_SERVICE_CALLBACK (TransmissionGearStatusChanged, const VehicleDataManagerTypes::TransmissionGearStatus &);
    DECLARE_SERVICE_CALLBACK (DrivingRestrictionChanged,     const bool &);
    DECLARE_SERVICE_CALLBACK (LowFuelWarningChanged,         const bool &);

private:
    DLT_DECLARE_CONTEXT(mContext)

    VehicleDataHandler * mDataHandler;
};

#endif // VEHICLEDATAMANAGERSERVICE_H
