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

#include "vehicledatagenerator.h"

vehicleDataGenerator::vehicleDataGenerator(QObject *parent)
    :QObject(parent)
    , m_storeManager_instance(NULL), m_sampleData(0)
    , m_epoch(boost::gregorian::date(1970,1,1))
{

}

vehicleDataGenerator::~vehicleDataGenerator()
{
    m_timer->stop();
    disconnect(m_timer, SIGNAL(timeout()), this, SLOT(insertData()));
    delete m_timer;

    m_storeManager_instance->stop();
    delete m_storeManager_instance;
}

void vehicleDataGenerator::nameDataFormatinit()
{
    m_nameList << "Signal.Drivetrain.InternalCombustionEngine.RPM" << "Signal.Chassis.Accelerator.PedalPosition"
               << "Signal.Chassis.Axle.Row1.Wheel.Right.Tire.Pressure" << "Signal.Cabin.Door.Row1.Right.Window.Position";
}

void vehicleDataGenerator::typeDataFormatInit()
{
    m_typeList << UINT32 << INT16 << UINT32 << INT32;
}

void vehicleDataGenerator::unitDataFormatInit()
{
    m_unitList << "rpm" << "NONE" << "p" << "Pos";
}

bool vehicleDataGenerator::init()
{
    m_storeManager_instance = new StoreManager();

    if ( !m_storeManager_instance->init() )
    {
        qDebug() << "Failed to init DataStoreManager";
        return false;
    }

    nameDataFormatinit();
    typeDataFormatInit();
    unitDataFormatInit();

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(insertData()));

    startTimer();

    return true;
}

void vehicleDataGenerator::insertData()
{
    CDLData generatedData;

    generatedData.value = (char*)malloc(1024);

    generatedData.id = to_string(m_sampleData%4);
    generatedData.name = m_nameList.at(m_sampleData%4);
    generatedData.type = m_typeList.at(m_sampleData%4);
    generatedData.unit = m_unitList.at(m_sampleData%4);

    convertDataType(m_sampleData, generatedData.type, generatedData.value);
    (m_sampleData%2==0)?generatedData.valid_state=true:generatedData.valid_state=false;
    generatedData.timeStamp = getUTCTime();

    m_storeManager_instance->storeData(generatedData.id, generatedData.value, generatedData.name, generatedData.type,
                                       generatedData.unit, generatedData.valid_state, generatedData.timeStamp);
    m_sampleData++;

    if( m_sampleData > 1000 )
    {
        m_sampleData = 0;
    }

    free(generatedData.value);
}

void vehicleDataGenerator::startTimer()
{
    m_timer->start(100);
}

uint64_t vehicleDataGenerator::getUTCTime()
{
    uint64_t time_stamp;

    boost::posix_time::ptime now = boost::posix_time::microsec_clock::universal_time();
    boost::posix_time::time_duration currentUTCTime = now - m_epoch;

    time_stamp = currentUTCTime.total_milliseconds();

    return time_stamp;
}

void vehicleDataGenerator::convertDataType(int sampleValue, CDLDataTypes type, char* data)
{
    switch(type)
    {
    case UINT32:
    {
        memcpy(data, &sampleValue, sizeof(uint32_t));
        break;
    }
    case INT16:
    {
        memcpy(data, &sampleValue, sizeof(int16_t));
        break;
    }
    case INT32:
    {
        memcpy(data, &sampleValue, sizeof(int32_t));
        break;
    }
    default:
    {
        qDebug()<<"<< DataGenerator >> Invaild Data Type";
    }
    }
}


