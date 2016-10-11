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
 * \file Cluster.h
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
    Q_PROPERTY(QVariant totalDistance READ totalDistance NOTIFY totalDistanceChanged)

public:
    static Cluster * instance();
    static void finalize();

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

public slots:
    void calcTotalDistance();

signals:
    // Q_PROPERTY signal
    void speedChanged();
    void rpmChanged();
    void fuelChanged();
    void totalDistanceChanged();

private:
    quint32 mTotalDistance;
    QTimer distanceTimer;
};

#endif // CLUSTER_H
