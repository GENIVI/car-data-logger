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

#include "cluster.hpp"
#include <QSharedPointer>
#include <QLocale>
#include <QDebug>

static QSharedPointer<Cluster> clusterInstance;

Cluster::Cluster(QObject *parent)
    : QObject(parent), m_speed(), m_rpm(), m_fuel(), m_totalDistance(), speedTestValue(0), rpmTestValue(0)
{
    mTotalDistance = 23567 * 1000;

    connect(&distanceTimer, SIGNAL(timeout()), this, SLOT(calcTotalDistance()));

    distanceTimer.setInterval(1000);
    distanceTimer.start();
}

QSharedPointer<Cluster> Cluster::instance(QObject *parent)
{
    if (clusterInstance.isNull())
    {
        clusterInstance = QSharedPointer<Cluster>(new Cluster(parent));

        clusterInstance.data()->init();
    }

    return clusterInstance;
}

Cluster::~Cluster()
{
    if ( distanceTimer.isActive() )
    {
        distanceTimer.stop();
    }
}

void Cluster::init()
{
    setSpeed(QVariant(0));
    setRpm(QVariant(0));
    setTotalDistance(QVariant("23,567 km"));

    setFuel(QVariant(20));
    setEngineCoolantTemperature(QVariant(130));
    setAirBagDeployed(QVariant(0));
    setGearState(QVariant(0));
    setFogLight(QVariant(0));
    setHeadLight(QVariant(0));
    setHighBeam(QVariant(0));
    setLeftIndicator(QVariant(0));
    setLowWasherFluid(QVariant(0));
    setParkingBrakeEnaged(QVariant(0));
    setRightIndicator(QVariant(0));
    setSeatBelt(QVariant(0));
}

QVariant Cluster::speed() const
{
    return m_speed;
}
void Cluster::setSpeed(QVariant value)
{
    m_speed = value;
    emit speedChanged();
}

QVariant Cluster::rpm() const
{
    return m_rpm;
}
void Cluster::setRpm(QVariant value)
{
    m_rpm = value;
    emit rpmChanged();
}

QVariant Cluster::fuel() const
{
    return m_fuel;
}
void Cluster::setFuel(const QVariant &fuel)
{
    m_fuel = fuel;
    emit fuelChanged();
}

QVariant Cluster::rightIndicator() const
{
    return m_rightIndicator;
}

void Cluster::setRightIndicator(const QVariant &rightIndicatorActive)
{
    m_rightIndicator = rightIndicatorActive;
    emit rightIndicatorChanged();
}

QVariant Cluster::airBagDeployed() const
{
    return m_airBagDeployed;
}

void Cluster::setAirBagDeployed(const QVariant &airBag)
{
    m_airBagDeployed = airBag;
    emit airBagDeployedChanged();
}

QVariant Cluster::engineCoolantTemperature() const
{
    return m_engineCoolantTemperature;
}

void Cluster::setEngineCoolantTemperature(const QVariant &engineCoolantTemperature)
{
    m_engineCoolantTemperature = engineCoolantTemperature;
    emit engineCoolantTemperatureChanged();
}

QVariant Cluster::totalDistance() const
{
    return m_totalDistance;
}

void Cluster::setTotalDistance(const QVariant &totalDistance)
{
    m_totalDistance = totalDistance;
    emit totalDistanceChanged();
}

QVariant Cluster::gearState() const
{
    return m_gearState;
}

void Cluster::setGearState(const QVariant &gear)
{
    m_gearState = gear;
    emit gearStateChanged();
}

QVariant Cluster::lowWasherFluid() const
{
    return m_lowWasherFluid;
}

void Cluster::setLowWasherFluid(const QVariant &washerFluid)
{
    m_lowWasherFluid = washerFluid;
    emit lowWasherFluidChanged();
}

QVariant Cluster::parkingBrakeEngaged() const
{
    return m_parkingBrakeEngaged;
}

void Cluster::setParkingBrakeEnaged(const QVariant &parkingBrake)
{
    m_parkingBrakeEngaged = parkingBrake;
    emit parkingBrakeEngagedChanged();
}

QVariant Cluster::seatBelt() const
{
    return m_seatBelt;
}

void Cluster::setSeatBelt(const QVariant &seatBeltActive)
{
    m_seatBelt = seatBeltActive;
    emit seatBeltChanged();
}

QVariant Cluster::fogLight() const
{
    return m_fogLight;
}

void Cluster::setFogLight(const QVariant &fogLightActive)
{
    m_fogLight = fogLightActive;
    emit fogLightChanged();
}

QVariant Cluster::headLight() const
{
    return m_headLight;
}

void Cluster::setHeadLight(const QVariant &headLightActive)
{
    m_headLight = headLightActive;
    emit headLightChanged();
}

QVariant Cluster::highBeam() const
{
    return m_highBeam;
}

void Cluster::setHighBeam(const QVariant &highBeamActive)
{
    m_highBeam = highBeamActive;
    emit highBeamChanged();
}

QVariant Cluster::leftIndicator() const
{
    return m_leftIndicator;
}

void Cluster::setLeftIndicator(const QVariant &leftIndicatorActive)
{
    m_leftIndicator = leftIndicatorActive;
    emit leftIndicatorChanged();
}

void Cluster::calcTotalDistance()
{
    int speed = m_speed.toInt();
    int move = (speed * 1000) / (60 * 60);

    mTotalDistance += move;

    QString distance = QLocale(QLocale::English).toString(mTotalDistance / 1000) + " km";

    setTotalDistance(distance);
}
