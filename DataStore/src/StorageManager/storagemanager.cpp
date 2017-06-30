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

#include "storagemanager.h"
#include "filemanager.h"
#include "configuration.h"
#include "../../common/log.h"

#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem.hpp>

#define KB_SIZE 1024
#define PERIOD_SIZE 60

StorageManager::StorageManager(DataStoreConfiguration *configManager, FileManager *fileManager)
    :m_configManager(configManager), m_fileManager(fileManager), m_storagePath("")
    ,m_maxFileSize(0), m_maxStorageSize(0), m_maxFileExpirePeriod(0)
{

}

StorageManager::~StorageManager()
{

}

bool StorageManager::init()
{
    m_storagePath = m_configManager->getDataStoreLocation();
    m_maxFileSize = (m_configManager->getMaxFileSize() * KB_SIZE);
    m_maxStorageSize = (m_configManager->getMaxStorageSize() * KB_SIZE);

    if( !createDataStoreLocation() )
    {
        return false;
    }

    return true;
}


void StorageManager::manageStorage(int dataSize)
{
    if( (m_maxStorageSize - getCurrentStorageUsageSize()) < dataSize )
    {
        requestDeleteOldestFile();
    }
}

bool StorageManager::isFileExceedSizeLimit(int dataSize, string filePath)
{
    static int printInformationSize = 1024 * 10;

    int currentUsageSize = getCurrentFileUsageSize(filePath);

    if( (m_maxFileSize - currentUsageSize) < dataSize )
    {
        LOGI() << "[Exceed] current file = " << filePath << ", size = " << currentUsageSize;
        printInformationSize = 1024 * 10;

        return true;
    }
    else
    {
        if ( currentUsageSize + dataSize > printInformationSize )
        {
            LOGI() << "current file = " << filePath << ", size = " << currentUsageSize + dataSize;

            printInformationSize += (1024 * 10);
        }

        return false;
    }
}



void StorageManager::checkFileExpiredThread()
{
    //not implemented yet
}

int StorageManager::getCurrentFileUsageSize(string filePath)
{
    int size;
    boost::filesystem::path path(filePath);

    if( boost::filesystem::exists(path) )
    {
        size = boost::filesystem::file_size(path);
    }
    else
    {
        LOGE() << "File is not existed ( File Path : " << filePath << " )";
        return 0;
    }

    return size;
}

int StorageManager::getCurrentStorageUsageSize()
{
    size_t size=0;

    boost::filesystem::directory_iterator end_iter;
    for( boost::filesystem::directory_iterator iter(m_storagePath); iter != end_iter; iter++ )
    {
        try
        {
            if( !boost::filesystem::is_directory(*iter) )
            {
                size += boost::filesystem::file_size(*iter);
            }
        }
        catch( std::exception &e )
        {
            LOGE() << "Retry calculate directory size ( Error Msg : " << e.what() << " )";
            size = getCurrentStorageUsageSize();
        }
    }

    return size;
}

bool StorageManager::deleteFile(string oldestFilePath)
{
    boost::filesystem::path filePath(oldestFilePath);
    bool result = 0;

    if( boost::filesystem::exists(filePath) )
    {
        result = boost::filesystem::remove_all(filePath);
    }

    if( result == 0 )
    {
        LOGE() << "Failed to delete file ( Delete File Name : " << oldestFilePath << " )";
        return false;
    }

    return true;
}

void StorageManager::requestDeleteOldestFile()
{
    string oldestFileName = m_fileManager->searchFileName(SearchFileMothodType::OLDEST_FILE);

    if( !oldestFileName.empty() )
    {
        if( deleteFile(oldestFileName) )
        {
            // succeed to delete file ( update the file exist to false )
            m_fileManager->requestUpdateFileInfo(UpdateFileInfoType::UPDATE_FILE_DELETED, oldestFileName);
        }
        else
        {
            //failed to delete file ( update the file exist to error )
            m_fileManager->requestUpdateFileInfo(UpdateFileInfoType::UPDATE_FILE_DELETION_FAILED, oldestFileName);
        }
    }
    else
    {
        LOGE() << "Failed to search oldest file name";
    }

    LOGD() << "================================================================================";
    LOGD() << "Succeed to delete oldest file ( Oldest File Name : " << oldestFileName << " )";
    LOGD() << "================================================================================";
}

bool StorageManager::createDataStoreLocation()
{
    string storagePath = m_storagePath.erase( m_storagePath.size() - 1 );
    boost::filesystem::path directory_path(storagePath);

    if( !boost::filesystem::exists(directory_path) )
    {
        try
        {
            if( !boost::filesystem::create_directories(directory_path) )
            {
                LOGE() << "Failed to create storage ( Storage Path : " << m_storagePath << " )";
                return false;
            }
        }
        catch(std::exception &e)
        {
            LOGE() << "Error in create_directories : " << e.what();
        }
    }
    else
    {
        if( boost::filesystem::is_directory(directory_path) )
        {
            return true;
        }
        else
        {
            LOGE() << "Invalid Storage Path ( Invalid Path : " << m_storagePath << " )";
            return false;
        }
    }

    return true;
}
