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

#include "offboardprovider.h"
#include "RVIDataManager/RVIDataManager.h"
#include "RVIClient/rviclient.h"
#include "../../common/log.h"

OffBoardProvider::OffBoardProvider()
    : m_dataManager(NULL), m_rviClient(NULL)
{
    m_dataManager = new RVIDataManager();
    m_rviClient = new RVIClient();
}

OffBoardProvider::~OffBoardProvider()
{

}

bool OffBoardProvider::init()
{
    if( m_dataManager == NULL )
    {
        LOGE() << "Failed to create DataManager";

        return false;
    }

    if( m_rviClient == NULL || !(m_rviClient->init()) )
    {
        return false;
    }

    LOGD() << "Succeed to create OffBoardProvider";

    return true;
}

void OffBoardProvider::transferData(string filePath)
{
    LOGD() << "Transmission File Path : " << filePath;

    boost::thread(std::bind(&OffBoardProvider::transferFileData, this, filePath));
}

void OffBoardProvider::stop()
{
    if( m_dataManager != NULL )
    {
        delete m_dataManager;
    }

    if( m_rviClient != NULL )
    {
        delete m_rviClient;
    }
}

void OffBoardProvider::transferFileData(string filePath)
{
    string fileData;
    string fileName;
    int fileSize;
    int fileDataTotalindex;
    vector<string> dividedFileData;

    if( !filePath.empty() )
    {
        fileData = m_dataManager->prepareProvideData(filePath);
        fileName = m_dataManager->getFileName(filePath);
        fileSize = fileData.length();
        fileDataTotalindex = m_dataManager->getProvideFileTotalIndex(fileData);
        dividedFileData = m_dataManager->getDivideFileData(fileData, fileDataTotalindex);

        // transmission start
        m_rviClient->transmissionStart(fileName, fileSize, fileDataTotalindex);

        // transmission data
        for( int index=0; index<fileDataTotalindex; index++ )
        {
            m_rviClient->transmissionData( index, dividedFileData.at(index) );
        }

        // transmission finish
        m_rviClient->transmissionFinish();
    }
    else
    {
        LOGE() << "Invalid file Path ( " << filePath << " )";
    }
}
