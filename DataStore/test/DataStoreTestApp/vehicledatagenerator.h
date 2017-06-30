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

#ifndef VEHICLEDATAGENERATOR_H
#define VEHICLEDATAGENERATOR_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QTimer>
#include <string>

#include <storemanager.h>

using namespace std;

class vehicleDataGenerator : public QObject
{
    Q_OBJECT

public:
    struct CDLData
    {
        string id;
        char* value;
        string name;
        CDLDataTypes type;
        string unit;
        bool valid_state;
        uint64_t timeStamp;
    };

public:
    explicit vehicleDataGenerator(QObject *parent = 0);
    virtual ~vehicleDataGenerator();

    bool init();

private:
    void nameDataFormatinit();
    void typeDataFormatInit();
    void unitDataFormatInit();
    void startTimer();
    uint64_t getUTCTime();
    void convertDataType(int sampleValue, CDLDataTypes type, char *data);

private slots:
    void insertData();

private:
    StoreManager * m_storeManager_instance;
    QTimer * m_timer;
    QList<string> m_nameList;
    QList<CDLDataTypes> m_typeList;
    QList<string> m_unitList;

    int m_sampleData;
    boost::posix_time::ptime m_epoch;
};

#endif // VEHICLEDATAGENERATOR_H
