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
 * \file cluster.cpp
*/

#include "Cluster.h"
#include <QLocale>

static Cluster * clusterInstance = Q_NULLPTR;

Cluster::Cluster(QObject *parent)
    : QObject(parent), m_speed(), m_rpm(), m_fuel(), m_totalDistance()
{
    mTotalDistance = 23567 * 1000;

    connect(&distanceTimer, SIGNAL(timeout()), this, SLOT(calcTotalDistance()));

    distanceTimer.setInterval(1000);
    distanceTimer.start();
}

Cluster *Cluster::instance()
{
    if ( clusterInstance == Q_NULLPTR )
    {
        clusterInstance = new Cluster;
        clusterInstance->init();
    }

    return clusterInstance;
}

void Cluster::finalize()
{
    if ( clusterInstance != Q_NULLPTR )
    {
        delete clusterInstance;
        clusterInstance = Q_NULLPTR;
    }
}

Cluster::~Cluster()
{
//    if ( distanceTimer.isActive() )
//    {
//        distanceTimer.stop();
//    }
}

void Cluster::init()
{
    setSpeed(QVariant(0));
    setRpm(QVariant(0));
    setFuel(QVariant(0));
    setTotalDistance(QVariant("23,567 km"));
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

QVariant Cluster::totalDistance() const
{
    return m_totalDistance;
}

void Cluster::setTotalDistance(const QVariant &totalDistance)
{
    m_totalDistance = totalDistance;
    emit totalDistanceChanged();
}

void Cluster::calcTotalDistance()
{
    int speed = m_speed.toInt();
    int move = (speed * 1000) / (60 * 60);

    mTotalDistance += move;

    QString distance = QLocale(QLocale::English).toString(mTotalDistance / 1000) + " km";

    setTotalDistance(distance);
}
