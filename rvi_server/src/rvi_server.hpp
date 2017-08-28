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

#ifndef RVISERVER_H
#define RVISERVER_H

#include <QObject>
#include <QString>

#include <string>

#include <boost/thread.hpp>
#include <Python.h>

using namespace std;

class DataManager;

class RVIServer : public QObject
{
    Q_OBJECT
public:
    explicit RVIServer(QObject *parent=NULL);
    virtual ~RVIServer();

public:
    static RVIServer * getInstance();
    void init();

signals:
    void signalTransmissionStart(QString fileName, int fileSize, int totalIndex);
    void signalTransmissionData(QString data, int currentIndex);
    void signalTransmissionFinish();

private:
    void rviServerThread();

private:
    DataManager * m_dataManager;
    boost::thread * m_rviServerThread;
    PyObject * m_pyName;
    PyObject * m_pyModule;
    PyObject * m_pyFunc;
};

#endif // RVISERVER_H
