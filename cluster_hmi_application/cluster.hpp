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

#ifndef CLUSTER_H
#define CLUSTER_H

#include <QObject>
#include <QVariant>
#include <QTimer>

class Cluster : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(QVariant rpm   READ rpm   NOTIFY rpmChanged)
    Q_PROPERTY(QVariant fuel  READ fuel  NOTIFY fuelChanged)
    Q_PROPERTY(QVariant gearState  READ gearState  NOTIFY gearStateChanged)
    Q_PROPERTY(QVariant airBagDeployed  READ airBagDeployed  NOTIFY airBagDeployedChanged)
    Q_PROPERTY(QVariant lowWasherFluid  READ lowWasherFluid  NOTIFY lowWasherFluidChanged)
    Q_PROPERTY(QVariant parkingBrakeEngaged  READ parkingBrakeEngaged  NOTIFY parkingBrakeEngagedChanged)
    Q_PROPERTY(QVariant seatBelt  READ seatBelt  NOTIFY seatBeltChanged)
    Q_PROPERTY(QVariant fogLight  READ fogLight  NOTIFY fogLightChanged)
    Q_PROPERTY(QVariant headLight  READ headLight  NOTIFY headLightChanged)
    Q_PROPERTY(QVariant highBeam  READ highBeam  NOTIFY highBeamChanged)
    Q_PROPERTY(QVariant leftIndicator  READ leftIndicator  NOTIFY leftIndicatorChanged)
    Q_PROPERTY(QVariant rightIndicator  READ rightIndicator  NOTIFY rightIndicatorChanged)
    Q_PROPERTY(QVariant engineCoolantTemperature  READ engineCoolantTemperature  NOTIFY engineCoolantTemperatureChanged)

    Q_PROPERTY(QVariant totalDistance READ totalDistance NOTIFY totalDistanceChanged)

public:
    static QSharedPointer<Cluster> instance(QObject *parent = Q_NULLPTR);
    ~Cluster();

    void init();

private:
    explicit Cluster(QObject *parent = 0);

public:
    // Q_PROPERTY
    QVariant m_speed;
    QVariant m_rpm;
    QVariant m_fuel;
    QVariant m_totalDistance;
    QVariant m_gearState;
    QVariant m_airBagDeployed;
    QVariant m_lowWasherFluid;
    QVariant m_parkingBrakeEngaged;
    QVariant m_seatBelt;
    QVariant m_fogLight;
    QVariant m_headLight;
    QVariant m_highBeam;
    QVariant m_leftIndicator;
    QVariant m_rightIndicator;

public:
    // Q_PROPERTY getter setter
    QVariant speed() const;
    void setSpeed(QVariant value);

    QVariant rpm() const;
    void setRpm(QVariant value);

    QVariant fuel() const;
    void setFuel(const QVariant &fuel);

    QVariant totalDistance() const;
    void setTotalDistance(const QVariant & totalDistance);

    QVariant gearState() const;
    void setGearState(const QVariant &gear);

    QVariant lowWasherFluid() const;
    void setLowWasherFluid(const QVariant &washerFluid);

    QVariant parkingBrakeEngaged() const;
    void setParkingBrakeEnaged(const QVariant &parkingBrake);

    QVariant seatBelt() const;
    void setSeatBelt(const QVariant &seatBeltActive);

    QVariant fogLight() const;
    void setFogLight(const QVariant &fogLightActive);

    QVariant headLight() const;
    void setHeadLight(const QVariant &headLightActive);

    QVariant highBeam() const;
    void setHighBeam(const QVariant &highBeamActive);

    QVariant leftIndicator() const;
    void setLeftIndicator(const QVariant &leftIndicatorActive);

    QVariant rightIndicator() const;
    void setRightIndicator(const QVariant &rightIndicatorActive);

    QVariant airBagDeployed() const;
    void setAirBagDeployed(const QVariant &airBag);

    QVariant engineCoolantTemperature() const;
    void setEngineCoolantTemperature(const QVariant &engineCoolantTemperature);

public slots:
    void calcTotalDistance();

signals:
    // Q_PROPERTY signal
    void speedChanged();
    void rpmChanged();
    void fuelChanged();
    void totalDistanceChanged();

    void gearStateChanged();
    void lowWasherFluidChanged();
    void parkingBrakeEngagedChanged();
    void seatBeltChanged();
    void fogLightChanged();
    void headLightChanged();
    void highBeamChanged();
    void leftIndicatorChanged();
    void rightIndicatorChanged();
    void airBagDeployedChanged();
    void engineCoolantTemperatureChanged();

private:
    quint32 mTotalDistance;
    QTimer distanceTimer;
    QTimer *m_testTimer;

    int speedTestValue;
    int rpmTestValue;
    QVariant m_engineCoolantTemperature;
};

#endif // CLUSTER_H
