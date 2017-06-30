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

#include "datagenerator.h"
#include "onboardprovider.h"

#include <QDebug>
#include <QCoreApplication>

/******************************************************
 *
 * < Register ID List >
 *
 * - Common Signals -
 * Signal.Drivetrain.Transmission.Speed 63
 * Signal.Drivetrain.InternalCombustionEngine.RPM 54
 *
 * - Difference Signals -
 * Signal.Chassis.Accelerator.PedalPosition 980 (DBus1)
 * Signal.Chassis.Brake.PedalPosition 981       (DBus2)
 *
 ******************************************************/

#define DATA_LENGTH 2

DataGenerator::DataGenerator(OnBoardProvider *onBoardProvider)
    : m_rpmData(0), m_speedData(0), m_accelPedlaPos(0), m_breakPedalPos(0), m_timeStamp(1500)
    , m_onBoardProvider(onBoardProvider), m_epoch(boost::gregorian::date(1970,1,1), boost::posix_time::time_duration(0,0,0))
{
    m_idList << 63 << 54 << 980 << 981;
    m_unitList << "km/h" << "rpm" << "degree" << "degree";
    m_typeList << "INT16" << "UINT32" << "UINT16" << "UINT16";
    m_nameList << "Signal.Drivetrain.Transmission.Speed" << "Signal.Drivetrain.InternalCombustionEngine.RPM"
               <<"Signal.Chassis.Accelerator.PedalPosition" << "Signal.Chassis.Brake.PedalPosition";
}

DataGenerator::~DataGenerator()
{
    if ( m_timer->isActive() )
    {
        m_timer->stop();
    }

    delete m_timer;
    m_timer = Q_NULLPTR;
}

void DataGenerator::init()
{
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(provideData()));

    m_timer->start(500);
}

CDLDataTypes DataGenerator::getCDLDataType(string type)
{
    CDLDataTypes cdlDataType = (CDLDataTypes)-1;

    if( type == "INT16" )
    {
        cdlDataType = CDLDataTypes::INT16;
    }
    else if( type == "UINT32" )
    {
        cdlDataType = CDLDataTypes::UINT32;
    }
    else if( type == "UINT16" )
    {
        cdlDataType = CDLDataTypes::UINT16;
    }
    else
    {

    }

    return cdlDataType;
}

uint64_t DataGenerator::getTimeStamp()
{
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::universal_time();

    boost::posix_time::time_duration currentUTCTime = now - m_epoch;

    return currentUTCTime.total_milliseconds();
}

void DataGenerator::getCDLValue(int _value, string _type, char** data)
{
    if( _type == "INT16" )
    {
        *data = new char[sizeof(int16_t)];
        memcpy(*data, &_value, sizeof(int16_t));
    }
    else if( _type == "UINT32" )
    {
        *data = new char[sizeof(uint32_t)];
        memcpy(*data, &_value, sizeof(uint32_t));
    }
    else if( _type == "UINT16" )
    {
        *data = new char[sizeof(uint16_t)];
        memcpy(*data, &_value, sizeof(uint16_t));
    }
    else
    {

    }
}

void DataGenerator::provideData()
{
    int index = rand() % m_nameList.length();
    int value = rand() % 9;
    bool state = (bool)(rand() % 1);

    _CDLData cdlData;
    cdlData.id = to_string(m_idList[index]);
    cdlData.name = m_nameList[index];
    cdlData.type = getCDLDataType(m_typeList[index]);
    cdlData.unit = m_unitList[index];

    getCDLValue(value, m_typeList[index], &cdlData.value);
    cdlData.valid_state = state;
    cdlData.time_stamp = getTimeStamp();

    m_onBoardProvider->provideData(cdlData.id, cdlData.value, cdlData.name, cdlData.type, cdlData.unit, cdlData.valid_state, cdlData.time_stamp, DATA_LENGTH);

    delete cdlData.value;
}
