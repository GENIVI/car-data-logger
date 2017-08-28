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

#ifndef RVICLIENT_H
#define RVICLIENT_H

#include <Python.h>
#include <string>

using namespace std;

class RVIClient
{
public:
    RVIClient();
    virtual ~RVIClient();

    bool init();

public:
    void transmissionStart(string fileName, int fileSize, int totalFileIndex);
    void transmissionData(int currentIndex, string data);
    void transmissionFinish();

private:
    PyObject * m_pyName;
    PyObject * m_pyModule;
    PyObject * m_pyStartFunc;
    PyObject * m_pyDataFunc;
    PyObject * m_pyFinishFunc;
};

#endif // RVICLIENT_H
