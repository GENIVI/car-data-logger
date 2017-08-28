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

#include "data_manager.hpp"
#include "rvi_server.hpp"
#include "base64_handler.hpp"
#include "compression_handler.hpp"
#include "vehicle_data_viewer_window.hpp"
#include "vehicle_data_manager_window.hpp"

#include <QDebug>
#include <QDir>

static DataManager * g_data_manager_instance = NULL;

DataManager::DataManager(QObject *parent)
    :QObject(parent), m_resultFileStoragePath("")
{

}

DataManager::~DataManager()
{

}

DataManager *DataManager::getInstance()
{
    if( g_data_manager_instance == NULL )
    {
        g_data_manager_instance = new DataManager();
        g_data_manager_instance->init();
    }

    return g_data_manager_instance;
}

void DataManager::init()
{
    connect(RVIServer::getInstance(), SIGNAL(signalTransmissionStart(QString,int,int)), this, SLOT(slotTransmissionStart(QString,int,int)));
    connect(RVIServer::getInstance(), SIGNAL(signalTransmissionData(QString, int)), this, SLOT(slotTransmissionData(QString, int)));
    connect(RVIServer::getInstance(), SIGNAL(signalTransmissionFinish()), this, SLOT(slotTransmissionFinish()));

    createTransmissionResultStorage();
}

void DataManager::createTransmissionResultStorage()
{
    m_resultFileStoragePath = QDir::currentPath();
    m_resultFileStoragePath.append("/results");

    QDir dir(m_resultFileStoragePath);
    if ( !dir.exists() )
    {
        dir.mkpath(".");
    }
    else
    {
        qDebug() << "Storage is already existed";
    }
}

void DataManager::slotTransmissionStart(QString fileName, int fileSize, int totalIndex)
{
    m_fileName = fileName;
    m_fileSize = fileSize;
    m_totalIndex = totalIndex;
}

void DataManager::slotTransmissionData(QString data, int currentIndex)
{
    m_dataBuf.append(data.toLocal8Bit().data());

    qDebug() << "Data received ( data index : " << currentIndex << ", total index : " << m_totalIndex << " )";

    if( currentIndex > m_totalIndex )
    {
        qDebug() << "[ Error ] Invalid Data Index";
    }

    qDebug() << "---------------------------------------------------------------------";

    emit signalTransferCurrentFileIndex(currentIndex, m_totalIndex);
}

void DataManager::slotTransmissionFinish()
{
    int transferredDataSize = m_dataBuf.length();

    if( m_fileSize == transferredDataSize )
    {
        // data decording
        string decodedData( base64_decode(m_dataBuf.begin()), base64_decode(m_dataBuf.end()));

        // data unzip
        string decompressedData = decompress(decodedData);

        // call VehicleDataViewer for displaying the graph
        QString resultFileStoragePath = m_resultFileStoragePath;
        resultFileStoragePath.append("/").append(m_fileName);

        qDebug() << "Store File Path : " << resultFileStoragePath;

        ofstream writeJsonFile(resultFileStoragePath.toLocal8Bit().constData());
        writeJsonFile << decompressedData.data();
        writeJsonFile.close();

        emit signalCompletedTransferData(resultFileStoragePath);
        emit signalCompletedStoreFile(resultFileStoragePath);
    }
    else
    {
        qDebug() << "[ Error ] Invalid Transferred Data ( Can't display the vehicleData on Viewer )";
    }

    emit signalFinishTransfer();

    m_dataBuf.clear();
}
