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

#include "offboardprovidertestapp.h"
#include "offboardprovider.h"

#include <QDir>
#include <QDebug>

OffBoardProviderTestApp::OffBoardProviderTestApp()
    : m_offBoardProvider(NULL), m_fileStoragePath(""), m_timer(NULL), m_fileCount(0)
{
    m_fileList.clear();
}

OffBoardProviderTestApp::~OffBoardProviderTestApp()
{
    m_timer->stop();
    disconnect(m_timer, SIGNAL(timeout()), this, SLOT(transferFileData()));

    if( m_timer != NULL )
    {
        delete m_timer;
    }

    m_offBoardProvider->stop();

    qDebug() << "Press < [CTRL] + C > to exit this application ... ";
}

bool OffBoardProviderTestApp::init()
{
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(transferFileData()));

    if( m_offBoardProvider ==  NULL )
    {
        m_offBoardProvider = new OffBoardProvider();
        m_offBoardProvider->init();
    }

    if( !m_offBoardProvider->init() )
    {
        return false;
    }

    setFileStoragePath();

    if( !setJSONFileLists() )
    {
        return false;
    }

    printJSONFileLists();

    transferFileData();
    m_timer->start(8000);

    return true;
}

void OffBoardProviderTestApp::setFileStoragePath()
{
    m_fileStoragePath = QDir::currentPath();
    m_fileStoragePath.append("/SampleJSONFiles");

    qDebug() << "Set JSON File Storage Path : " << m_fileStoragePath;
}

bool OffBoardProviderTestApp::setJSONFileLists()
{
    QDir dir(m_fileStoragePath);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();

    qDebug() << "file path : " << m_fileStoragePath;
    qDebug() << "list size : " << list.size();

    if( list.size() == 0 )
    {
        qDebug() << "No File in storage";

        return false;
    }

    for( int i=0; i<list.size(); i++ )
    {
        QString filePath = m_fileStoragePath;

        QFileInfo fileInfo = list.at(i);

        m_fileList.push_back( filePath.append("/").append(fileInfo.fileName()) );
    }

    return true;
}

void OffBoardProviderTestApp::printJSONFileLists()
{
    for( int i=0; i<m_fileList.size(); i++ )
    {
        qDebug() << "File " << i << ": " << m_fileList.at(i);
    }
}

void OffBoardProviderTestApp::transferFileData()
{
    qDebug() << "\n\n";
    if( m_fileCount != m_fileList.size() )
    {
        qDebug() << "======================= << Transmission File ( File Index : " << m_fileCount+1 << " ) >> ===================================";
        qDebug() << "Transmission File : " << m_fileList.at(m_fileCount) << "\n";
        m_offBoardProvider->transferData(m_fileList.at(m_fileCount).toLocal8Bit().data());

        m_fileCount++;
    }
    else
    {
        qDebug() << "======================= << File Transmission Done >> ===================================";
        delete this;
    }
}

