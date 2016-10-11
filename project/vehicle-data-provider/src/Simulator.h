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
 * \file Simulator.h
*/

#ifndef SIMULATOR
#define SIMULATOR

#include <QObject>

namespace HardWareSimulator
{

/* Vehicle Data Simulator */
class VehicleDataSimulator : public QObject
{
    Q_OBJECT

private:
    VehicleDataSimulator();

public:
    ~VehicleDataSimulator();

public:
    static VehicleDataSimulator * instance();
    static void finalize();

public:
    Q_INVOKABLE void setFuelLevel(quint16 fuelLevel);
    Q_INVOKABLE void setVehicleSpeedLevel(quint16 vehicleSpeed);
    Q_INVOKABLE void setEngineSpeedLevel(quint16 engineSpeed);

signals:
    void notifyFuelLevelData(quint16 fuelLevel);
    void notifyVehicleSpeedData(quint16 vehicleSpeed);
    void notifyEngineSpeedData(quint16 EngineSpeed);

private:
    quint16 mFuelLevel;
    quint16 mVehicleSpeed;
    quint16 mEngineSpeed;
};




/* HVAC Data Simulator */
class HVACDataSimulator : public QObject
{
    Q_OBJECT

private:
    HVACDataSimulator();

public:
    ~HVACDataSimulator();

public:
    static HVACDataSimulator * instance();
    static void finalize();

public:
    Q_INVOKABLE void setSyncMode(bool sync);
    Q_INVOKABLE void setAirConditionMode(bool airCondition);
    Q_INVOKABLE void setDefrostWindshiledMode(bool front);
    Q_INVOKABLE void setAirIntakeMode(bool airIntake);

    Q_INVOKABLE void setFanSpeedLevel(qint8 fanSpeed);
    Q_INVOKABLE void setFanDirectionMode(qint8 fanDirection);
    Q_INVOKABLE void setDriverTempC(quint16 drTempC);
    Q_INVOKABLE void setPassengerTempC(quint16 psTempC);


signals:
    void syncModeUpdated(bool on);
    void airConditionUpdated(bool on);
    void defrostWindshiledUpdated(bool on);
    void airIntakeUpdated(bool on);

    void fanSpeedUpdated(quint8 speed);
    void fanDirectionUpdated(quint8 direction);
    void driverTargetTemperatureUpdated(quint16 temperature);
    void passengerTargetTemperatureUpdated(quint16 temperature);

public:
    bool   mSyncValue;
    bool   mAirCondition;
    bool   mFrontValue;
    bool   mAirIntake;

    qint8  mFanSpeed;
    qint8  mFanDirection;
    qint16 mDriverTempC;
    qint16 mPassengerTempC;

};

}

#endif // SIMULATOR

