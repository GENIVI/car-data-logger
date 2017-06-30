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

extern "C"
{
    #include <vsi.h>
}

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <cstdlib>
#include <iostream>

#define CONFIGURATION_DATA_COUNT 14
#define STRING_DATA_COUNT 6

using namespace std;

class DataGenerator : public QObject
{
    Q_OBJECT
public:
    explicit DataGenerator(QObject *parent = 0);
    virtual ~DataGenerator();

public:
    void start();
    void stop();

private slots:
    void storeData();

private:
    QTimer *m_timer;
    QList<int> m_signalIdList;
    QList<QString> m_stingDataList;
    vsi_handle m_handle;
    vsi_result m_result;
};

#endif // DATAGENERATOR_H
