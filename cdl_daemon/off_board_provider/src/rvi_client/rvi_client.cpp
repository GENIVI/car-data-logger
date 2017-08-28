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

#include "rvi_client.hpp"
#include "../../../common/log.hpp"

RVIClient::RVIClient()
{

}

RVIClient::~RVIClient()
{

}

bool RVIClient::init()
{
    Py_Initialize();

    PyRun_SimpleString("import sys\n");
    PyRun_SimpleString("sys.path.append(\"/usr/lib/rvi_core\")");

    m_pyName = PyString_FromString("rvi_call");

    if( !m_pyName )
    {
        LOGE() << "Failed to create rvi_call Python Name";
        PyErr_Print();
        return false;
    }

    m_pyModule = PyImport_Import(m_pyName);
    if( !m_pyModule )
    {
        LOGE() << "Failed to create rvi_call Python Module";
        PyErr_Print();
        return false;
    }

    m_pyStartFunc = PyObject_GetAttrString(m_pyModule, "transmission_start");
    m_pyDataFunc = PyObject_GetAttrString(m_pyModule, "transmission_data");
    m_pyFinishFunc = PyObject_GetAttrString(m_pyModule, "transmission_finish");

    return true;
}

void RVIClient::transmissionStart(string fileName, int fileSize, int totalFileIndex)
{
    PyObject *pyArgs = PyTuple_New(3);

    PyTuple_SetItem(pyArgs, 0, PyString_FromString(fileName.c_str()));
    PyTuple_SetItem(pyArgs, 1, PyInt_FromSize_t(fileSize));
    PyTuple_SetItem(pyArgs, 2, PyInt_FromSize_t(totalFileIndex));

    PyObject *pyResult = PyObject_CallObject(m_pyStartFunc, pyArgs);

    Py_DECREF(pyArgs);

    if ( pyResult != NULL )
    {
        Py_DECREF(pyResult);
    }
}

void RVIClient::transmissionData(int currentIndex, string data)
{
    PyObject *pyArgs = PyTuple_New(2);

    PyTuple_SetItem(pyArgs, 0, PyInt_FromSize_t(currentIndex));
    PyTuple_SetItem(pyArgs, 1, PyString_FromString(data.c_str()));

    PyObject *pyResult = PyObject_CallObject(m_pyDataFunc, pyArgs);

    Py_DECREF(pyArgs);

    if ( pyResult != NULL )
    {
        Py_DECREF(pyResult);
    }
}

void RVIClient::transmissionFinish()
{
    PyObject *pyResult = PyObject_CallObject(m_pyFinishFunc, NULL);

    if ( pyResult != NULL )
    {
        Py_DECREF(pyResult);
    }
}
