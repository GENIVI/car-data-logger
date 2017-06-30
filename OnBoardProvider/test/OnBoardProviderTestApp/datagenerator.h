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

#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include "../../../common/cdlcommondefine.h"

#include <QObject>
#include <QTimer>
#include <QList>
#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;

class OnBoardProvider;

class DataGenerator : public QObject
{
    Q_OBJECT
public:
    struct _CDLData
    {
        string id;
        char * value;
        string name;
        CDLDataTypes type;
        string unit;
        bool valid_state;
        uint64_t time_stamp;
    };

public:
    DataGenerator(OnBoardProvider * onBoardProvider);
    virtual ~DataGenerator();

public:
    void init();

private:
    CDLDataTypes getCDLDataType(string type);
    uint64_t getTimeStamp();
    void getCDLValue(int _value, string _type, char **data);

public slots:
    void provideData();

private:
    QTimer *m_timer;
    int m_rpmData;
    int m_speedData;
    int m_accelPedlaPos;
    int m_breakPedalPos;
    int m_timeStamp;

    QList<int> m_idList;
    QList<string> m_typeList;
    QList<string> m_unitList;
    QList<string> m_nameList;

    OnBoardProvider * m_onBoardProvider;

    boost::posix_time::ptime m_epoch;
};

#endif // DATAGENERATOR_H
