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

#include "rvi_server.hpp"
#include "data_manager.hpp"

#include <QDebug>

static RVIServer * g_rvi_server_instance = NULL;

static PyObject* notifyTransStartCallBack(PyObject *self, PyObject *args)
{
    qDebug() << "<< Start >> Transmission Start Command Received";

    Q_UNUSED(self)

    PyObject *dict;

    PyArg_ParseTuple(args, "O!", &PyDict_Type, &dict);

    char* fileName;
    long fileTotalIndex, fileSize;

    PyObject *keyFileName, *pyFileName;
    PyObject *keyTotalIndex, *pyTotalIndex;
    PyObject *keyFileSize, *pyFileSize;

    keyFileName = PyString_FromString("fileName");
    keyTotalIndex = PyString_FromString("fileTotalIndex");
    keyFileSize = PyString_FromString("fileSize");

    pyFileName = PyDict_GetItem(dict, keyFileName);
    pyTotalIndex = PyDict_GetItem(dict, keyTotalIndex);
    pyFileSize = PyDict_GetItem(dict, keyFileSize);

    fileName = PyString_AsString(pyFileName);
    fileTotalIndex = PyInt_AsLong(pyTotalIndex);
    fileSize = PyInt_AsLong(pyFileSize);

    qDebug() << "====================== < Start > ===========================";
    qDebug() << "1. FileName   : " << QString::fromLocal8Bit(fileName);
    qDebug() << "2. TotalIndex : " << fileTotalIndex;
    qDebug() << "3. FileSize   : " << fileSize;

    emit RVIServer::getInstance()->signalTransmissionStart(QString::fromLocal8Bit(fileName), (int)fileSize, (int)fileTotalIndex);

    return Py_None;
}

static PyObject* notifyTransFinishCallBack(PyObject *self, PyObject *args)
{
    qDebug() << "<< Finish >> Transmission Finish Command Received";

    Q_UNUSED(self)
    Q_UNUSED(args)

    emit RVIServer::getInstance()->signalTransmissionFinish();

    return Py_None;
}

static PyObject* notifyTransDataCallBack(PyObject *self, PyObject *args)
{
    qDebug() << "<< Transfer Data >> Transmission Send Data Command Received";

    Q_UNUSED(self)

    PyObject *dict;

    PyArg_ParseTuple(args, "O!", &PyDict_Type, &dict);

    char* data;
    long currentIndex;

    PyObject *keyData, *pyData;
    PyObject *keyCurIndex, *pyCurIndex;

    keyData = PyString_FromString("data");
    keyCurIndex = PyString_FromString("currentIndex");

    pyData = PyDict_GetItem(dict, keyData);
    pyCurIndex = PyDict_GetItem(dict, keyCurIndex);

    data = PyString_AsString(pyData);
    currentIndex = PyInt_AsLong(pyCurIndex);

    emit RVIServer::getInstance()->signalTransmissionData(QString::fromLocal8Bit((const char*)data), (int)(currentIndex+1));

    return Py_None;
}

static PyMethodDef CallBackMethods[] = {
    { "CallBackTransDataFunc", notifyTransDataCallBack , METH_VARARGS, NULL },
    { "CallBackTransStartFunc", notifyTransStartCallBack , METH_VARARGS, NULL },
    { "CallBackTransFinishFunc", notifyTransFinishCallBack , METH_VARARGS, NULL },
    { NULL, NULL, 0, NULL }
};

RVIServer::RVIServer(QObject *parent)
    : QObject(parent)
    , m_dataManager(NULL)
{

}

RVIServer::~RVIServer()
{
    Py_DECREF(m_pyFunc);
    Py_DECREF(m_pyModule);
    Py_DECREF(m_pyName);
}

RVIServer *RVIServer::getInstance()
{
    if( g_rvi_server_instance == NULL )
    {
        g_rvi_server_instance = new RVIServer();
        g_rvi_server_instance->init();
    }

    return g_rvi_server_instance;
}

void RVIServer::init()
{
    m_rviServerThread = new boost::thread(std::bind(&RVIServer::rviServerThread, this));
}

void RVIServer::rviServerThread()
{
    Py_Initialize();

    Py_InitModule("callback", CallBackMethods);

    PyRun_SimpleString("import sys\n");
    PyRun_SimpleString("sys.path.append(\"/usr/lib/rvi_core\")");

    m_pyName = PyString_FromString("rvi_service");

    if( !m_pyName )
    {
        qDebug() << "<< Python Object >> pyName is Not OK";
        PyErr_Print();
    }

    m_pyModule = PyImport_Import(m_pyName);

    if( !m_pyModule )
    {
        qDebug() << "<< Python Object >> pyModule is Not OK";
        PyErr_Print();
    }

    m_pyFunc = PyObject_GetAttrString(m_pyModule, "init_service");
    PyObject_CallObject(m_pyFunc, NULL);

    if( !m_pyFunc )
    {
        qDebug() << "<< Python Object >> pyFunc is Not OK";
        PyErr_Print();
    }
}
