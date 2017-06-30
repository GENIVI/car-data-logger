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

/*
 * << Data Infomation >>
 *
 * 8 - string / enum(unknown, fwd, rwd, awd)
 *
 * 54 - int / 0 ~ 10000
 * 57 - int / 0 ~ 2000
 * 58 - int / 0 ~ 3000
 * 59 - int / -250 ~ 250
 * 63 - int / -250 ~ 250
 * 973 - int
 *
 * 70 - unsigned int
 * 955 - unsigned int
 * 975 - unsigned int
 *
 * 957 - float
 *
 * 970 - bool
 *
 */

DataGenerator::DataGenerator(QObject *parent)
    :QObject(parent), m_timer(NULL)
{
    m_signalIdList << 8 << 54 <<  57 <<  58 <<  59 <<  973 <<  70 << 63
                   <<  955 <<  975 <<  957 <<  970;
    m_stingDataList << "unknown" <<  "fwd" <<  "rwd" <<  "awd" <<  "invalid1" << "invalid2";

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(storeData()));

    start();
}

DataGenerator::~DataGenerator()
{

}

void DataGenerator::start()
{
    m_handle = vsi_initialize();

    m_result.domainId = 0;
    m_result.data = (char*)malloc( 1024 );
    m_timer->start(600);
}

void DataGenerator::stop()
{
    if ( m_timer != NULL && m_timer->isActive() )
    {
        m_timer->stop();
        disconnect(m_timer, SIGNAL(timeout()), this, SLOT(storeData()));
        delete m_timer;
    }

    vsi_destroy(m_handle);
}

void DataGenerator::storeData()
{
    int dataCount = 0;
    qDebug() << "\n==================== << Store Data in VSI >> ====================";

    for( int i=0; i<3; i++ )
    {
        int index = rand() % CONFIGURATION_DATA_COUNT;
        int signalId = m_signalIdList[index];

        dataCount++;
        qDebug() << dataCount << ". signalID : " << signalId;

        //string type
        if( signalId == 8 )
        {
            int randNum = rand() % STRING_DATA_COUNT;

            QByteArray temp = m_stingDataList.at(randNum).toLatin1();

            qDebug() << "    data     : " << temp.data();

            m_result.signalId = signalId;
            m_result.data = temp.data();
            m_result.dataLength = strlen(m_result.data)+1;
            vsi_fire_signal(m_handle, &m_result);
        }
        //boolean type
        else if( signalId == 970 )
        {
            int data = (rand() % 2);
            qDebug() << "    data     : " << data;

            m_result.signalId = signalId;
            memcpy(m_result.data, &data, sizeof(int));
            m_result.dataLength = sizeof(int);
            vsi_fire_signal(m_handle, &m_result);
        }
        //float type
        else if( signalId == 957 )
        {
            float data = (rand() % 450)/(float)4;   //to make a float type
            qDebug() << "    data     : " << data;

            m_result.signalId = signalId;
            memcpy(m_result.data, &data, sizeof(float));
            m_result.dataLength = sizeof(float);
            vsi_fire_signal(m_handle, &m_result);
        }
        //unsigned int type
        else if( signalId == 70 || signalId == 948 || signalId == 955  || signalId == 975
                  || signalId == 976 || signalId == 977 )
        {
            int data = (rand() % 101);
            qDebug() << "    data     : " << data;

            m_result.signalId = signalId;
            memcpy(m_result.data, &data, sizeof(int));
            m_result.dataLength = sizeof(int);
            vsi_fire_signal(m_handle, &m_result);
        }
        //RPM ( unsigned int )
        else if( signalId == 54 )
        {
            int data = (rand() % 10101) - 100;
            qDebug() << "    data     : " << data;

            m_result.signalId = signalId;
            memcpy(m_result.data, &data, sizeof(int));
            m_result.dataLength = sizeof(int);
            vsi_fire_signal(m_handle, &m_result);
        }
        //Speed
        else if( signalId == 63 )
        {
            int data = (rand() % 511) - 260;
            qDebug() << "    data     : " << data;

            m_result.signalId = signalId;
            memcpy(m_result.data, &data, sizeof(int));
            m_result.dataLength = sizeof(int);
            vsi_fire_signal(m_handle, &m_result);
        }
        //int type
        else
        {
            int data = (rand() % 3251) - 250;
            qDebug() << "    data     : " << data;

            m_result.signalId = signalId;
            memcpy(m_result.data, &data, sizeof(int));
            m_result.dataLength = sizeof(int);
            vsi_fire_signal(m_handle, &m_result);
        }
    }
}
