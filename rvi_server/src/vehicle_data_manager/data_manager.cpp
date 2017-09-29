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
#include "../../cdl_daemon/common/data_encryption/data_decryption_handler.hpp"

#include <QDebug>
#include <QDir>

static DataManager * g_data_manager_instance = NULL;

DataManager::DataManager(QObject *parent)
    : QObject(parent), m_resultFileStoragePath(""),
      m_aes256Key("12345678901234567890123456789012"), m_aes256IV("09876543210987654321098765432109")
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
    m_dataBuf.clear();

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

string DataManager::decryptData(string &aes256Key, string &aes256Iv, string &dataBuf)
{
    string decryption_data = AES256_CBC_decrypt_data((byte*)aes256Key.c_str(), (byte*)aes256Iv.c_str(), dataBuf);

    // data decryption
    if( decryption_data.empty() )
    {
        qDebug() << "<< DataManager::decryptionData >> Invalid decrypt data";

        return "";
    }

    // data unzip
    string decompressedData = decompress(decryption_data);

    if( decompressedData.empty() )
    {
        qDebug() << "<< DataManager::decryptionData >> Invalid depress data";

        return "";
    }

    return decompressedData;
}

bool DataManager::createResultFile(QString &resultFileStoragePath, string &decryptedData)
{
    // call VehicleDataViewer for displaying the graph
    resultFileStoragePath = m_resultFileStoragePath;
    resultFileStoragePath.append("/").append(m_fileName);

    qDebug() << "<< DataManager::createResultFile >> Store File Path : " << resultFileStoragePath;

    ofstream writeJsonFile(resultFileStoragePath.toLocal8Bit().constData());

    if( !writeJsonFile.is_open() )
    {
        qDebug() << "<< DataManager::createResultFile >> Failed to file open. ( Invalid file path : " << resultFileStoragePath << " )";

        return false;
    }

    writeJsonFile << decryptedData.data();
    writeJsonFile.close();

    return true;
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
        string decryptedData = decryptData(m_aes256Key,  m_aes256IV, m_dataBuf);
        QString resultFileStoragePath;

        if( createResultFile(resultFileStoragePath, decryptedData) )
        {
            emit signalCompletedTransferData(resultFileStoragePath);
            emit signalCompletedStoreFile(resultFileStoragePath);
        }
    }
    else
    {
        qDebug() << "[ Error ] Invalid Transferred Data ( Can't display the vehicleData on Viewer )";
    }

    emit signalFinishTransfer();

    m_dataBuf.clear();
}
