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
 * \file DATCControl.cpp
*/

#include "DATCControl.h"
#include <QSharedPointer>
#include <QDebug>

#include "CommonAPI/CommonAPI.hpp"

static QSharedPointer<DatcControl> datcControlInstance;

QSharedPointer<DatcControl> DatcControl::instance(QObject *parent)
{
    if (datcControlInstance.isNull())
    {
        datcControlInstance =  QSharedPointer<DatcControl>(new DatcControl(parent));
    }

    return datcControlInstance;
}

DatcControl::DatcControl(QObject *parent) : QObject(parent)
  ,m_sync(false), m_frontDefrost(false), m_airCirculation(false), currentScreen(false)
  ,m_airDirection(0), m_airVolume(0) , m_driverSeat("0") , m_passengerSeat("0")
{
    init();
    setObjectName("DatcControl");

}

void DatcControl::init()
{
    auto runtime = CommonAPI::Runtime::get();

    mDatcManagerProxy = runtime->buildProxy<DATCManagerProxy>("local", "com.ivis.DATCManager.DATCManager");

    mDatcManagerProxy->getDualModeAttribute().getChangedEvent().subscribe(
                std::bind(&DatcControl::onSyncModeChanged, this, std::placeholders::_1) );

    mDatcManagerProxy->getDefrostsAttribute().getChangedEvent().subscribe(
                std::bind(&DatcControl::onDefrostsChanged, this, std::placeholders::_1) );

    mDatcManagerProxy->getAirRecirculationAttribute().getChangedEvent().subscribe(
                std::bind(&DatcControl::onAirRecirculationChanged, this, std::placeholders::_1) );

    mDatcManagerProxy->getFanDirectionsAttribute().getChangedEvent().subscribe(
                std::bind(&DatcControl::onFanDirectionsChanged, this, std::placeholders::_1) );

    mDatcManagerProxy->getFanSpeedsAttribute().getChangedEvent().subscribe(
                std::bind(&DatcControl::onFanSpeedsChanged, this, std::placeholders::_1) );

    mDatcManagerProxy->getTargetTemperaturesAttribute().getChangedEvent().subscribe(
                std::bind(&DatcControl::onTargetTemperaturesChanged, this, std::placeholders::_1) );
}






bool DatcControl::sync() const
{
    return m_sync;
}

bool DatcControl::frontDefrost() const
{
    return m_frontDefrost;
}

bool DatcControl::airCirculation() const
{
    return m_airCirculation;
}

qint8 DatcControl::airDirection() const
{
    return m_airDirection;
}

qint8 DatcControl::airVolume() const
{
    return m_airVolume;
}

QString DatcControl::driverSeat() const
{
    return m_driverSeat;
}

QString DatcControl::passengerSeat() const
{
    return m_passengerSeat;
}








void DatcControl::setSync(const bool &sync)
{
    if (m_sync == sync)
        return;

    m_sync = sync;
    emit syncChanged(sync);
}

void DatcControl::setFrontDefrost(const bool &frontDefrost)
{
    if (m_frontDefrost == frontDefrost)
        return;

    m_frontDefrost = frontDefrost;
    emit frontDefrostChanged(frontDefrost);
}

void DatcControl::setAirCirculation(const bool &airCirculation)
{
    if (m_airCirculation == airCirculation)
        return;

    m_airCirculation = airCirculation;
    emit airCirculationChanged(airCirculation);
}

void DatcControl::setAirDirection(const qint8 &airDirection)
{
    if (m_airDirection == airDirection)
        return;

    m_airDirection = airDirection;
    emit airDirectionChanged(airDirection);
}

void DatcControl::setAirVolume(const qint8 &airVolume)
{
    if (m_airVolume == airVolume)
        return;

    m_airVolume = airVolume;
    emit airVolumeChanged(airVolume);
}

void DatcControl::setDriverSeat(const QString &driverSeat)
{
    if (m_driverSeat == driverSeat)
        return;

    m_driverSeat = driverSeat;
    emit driverSeatChanged(driverSeat);
}

void DatcControl::setPassengerSeat(const QString &passengerSeat)
{
    if (m_passengerSeat == passengerSeat)
        return;

    m_passengerSeat = passengerSeat;
    emit passengerSeatChanged(passengerSeat);
}









void DatcControl::onSyncModeChanged(const bool &syncMode)
{
    setSync(syncMode);
}

void DatcControl::onDefrostsChanged(const DATCManagerTypes::Defrosts &defrosts)
{
    for(size_t i=0; i<defrosts.size(); i++)
    {
        if(DATCManagerTypes::EDefrostTarget::WIND_SHIELD == defrosts.at(i).getDefrostTarget() )
        {
            setFrontDefrost(defrosts.at(i).getOn());
        }
    }
}

void DatcControl::onAirRecirculationChanged(const bool &airRecirculation)
{
    setAirCirculation(airRecirculation);
}

void DatcControl::onFanDirectionsChanged(const DATCManagerTypes::FanDirections &fanDirections)
{
    for(size_t i=0; i<fanDirections.size(); i++)
    {
        setAirDirection(fanDirections.at(i).getFanDirection());
    }
}

void DatcControl::onFanSpeedsChanged(const DATCManagerTypes::FanSpeeds &fanSpeeds)
{
    for(size_t i=0; i<fanSpeeds.size(); i++)
    {
        if(DATCManagerTypes::EAreaType::DRIVER == fanSpeeds.at(i).getAreaType())
        {
            setAirVolume(fanSpeeds.at(i).getFanSpeed());
        }
    }
}

void DatcControl::onTargetTemperaturesChanged(const DATCManagerTypes::TargetTemperatures &targetTemperatures)
{
    for(size_t i=0; i<targetTemperatures.size(); i++)
    {
        if(DATCManagerTypes::EAreaType::DRIVER == targetTemperatures.at(i).getAreaType())
        {
            if(QString::number(targetTemperatures.at(i).getTemperature()) != "255")
            {
                setDriverSeat(QString::number(targetTemperatures.at(i).getTemperature()));
            }
            else
            {

            }
        }

        else if(DATCManagerTypes::EAreaType::PASSENGER == targetTemperatures.at(i).getAreaType())
        {
            if(QString::number(targetTemperatures.at(i).getTemperature()) != "255")
            {
                setPassengerSeat(QString::number(targetTemperatures.at(i).getTemperature()));
            }
            else
            {

            }
        }
    }
}
