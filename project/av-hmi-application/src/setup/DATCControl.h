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
 * \file DATCControl.h
*/

#ifndef DATCCONTROL_H
#define DATCCONTROL_H

#include <QObject>
#include <com/ivis/DATCManager/DATCManagerProxy.hpp>

using namespace v1::com::ivis::DATCManager;

class DatcControl: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool sync           READ sync            NOTIFY syncChanged)
    Q_PROPERTY(bool frontDefrost    READ frontDefrost     NOTIFY frontDefrostChanged)
    Q_PROPERTY(bool airCirculation READ airCirculation  NOTIFY airCirculationChanged)

    Q_PROPERTY(qint8 airDirection  READ airDirection    NOTIFY airDirectionChanged)
    Q_PROPERTY(qint8 airVolume     READ airVolume       NOTIFY airVolumeChanged)

    Q_PROPERTY(QString driverSeat READ driverSeat WRITE setDriverSeat NOTIFY driverSeatChanged)
    Q_PROPERTY(QString passengerSeat READ passengerSeat WRITE setPassengerSeat NOTIFY passengerSeatChanged)

private:
    explicit DatcControl(QObject *parent = Q_NULLPTR);

public:
    static QSharedPointer<DatcControl> instance(QObject *parent = Q_NULLPTR);

public:
    void init();

    bool sync() const;
    bool frontDefrost() const;
    bool airCirculation() const;
    qint8 airDirection() const;
    qint8 airVolume() const;
    QString driverSeat() const;
    QString passengerSeat() const;

public:
    void setSync(const bool &sync);
    void setFrontDefrost(const bool &frontDefrost);
    void setAirCirculation(const bool &airCirculation);
    void setAirDirection(const qint8 &airDirection);
    void setAirVolume(const qint8 &airVolume);
    void setDriverSeat(const QString &driverSeat);
    void setPassengerSeat(const QString &passengerSeat);

private:
    bool m_sync;
    bool m_frontDefrost;
    bool m_airCirculation;
    bool currentScreen;

    qint8 m_airDirection;
    qint8 m_airVolume;
    QString m_driverSeat;
    QString m_passengerSeat;

signals:
    void syncChanged(bool sync);
    void frontDefrostChanged(bool frontHeater);
    void airCirculationChanged(bool airCirculation);
    void airDirectionChanged(qint8 airDirection);
    void airVolumeChanged(qint8 airVolume);
    void driverSeatChanged(QString driverSeat);
    void passengerSeatChanged(QString passengerSeat);

public:
    void onSyncModeChanged(const bool & syncMode);
    void onDefrostsChanged(const DATCManagerTypes::Defrosts & defrosts);
    void onAirRecirculationChanged(const bool & airRecirculation);
    void onFanDirectionsChanged(const DATCManagerTypes::FanDirections & fanDirections);
    void onFanSpeedsChanged(const DATCManagerTypes::FanSpeeds & fanSpeeds);
    void onTargetTemperaturesChanged(const DATCManagerTypes::TargetTemperatures & targetTemperatures);
    void onTemperatureModeChanged(const DATCManagerTypes::ETemperatureMode & temperatureMode);

private:
    std::shared_ptr<DATCManagerProxy<>> mDatcManagerProxy;
};

#endif // DATCCONTROL_H
