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

#include "file_manager.hpp"
#include "configuration.hpp"
#include "../../common/log.hpp"

#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

FileManager::FileManager(DataStoreConfiguration *configManager, FileInfoDBHandler *fileInfoDBHandler)
    :m_configManager(configManager), m_fileInfoDBHandler(fileInfoDBHandler), m_fileInfoListFilePath("")
{

}

FileManager::~FileManager()
{

}

bool FileManager::init()
{
    m_storagePath = m_configManager->getDataStoreLocation();

    if( !createFileInfoListFile() )
    {
        return false;
    }

    return true;
}

bool FileManager::createFileInfoListFile()
{
    m_fileInfoListFilePath.append(m_storagePath).append(FileInfoListTableName);

    return m_fileInfoDBHandler->openFileInfoListFile(m_fileInfoListFilePath);
}
void FileManager::requestUpdateFileInfo(UpdateFileInfoType updateFileType, string filename)
{
    bool updateFileResult = true;
    switch(updateFileType)
    {
    case UpdateFileInfoType::UPDATE_FILE_DELETED:
    case UpdateFileInfoType::UPDATE_FILE_PROVIDED:
    case UpdateFileInfoType::UPDATE_FILE_DELETION_FAILED:
    {
        if( !m_fileInfoDBHandler->updateFileInfo(updateFileType, filename) )
        {
            updateFileResult = false;
        }

        break;
    }
    case UpdateFileInfoType::UPDATE_FILE_SAVE_FINISHED:
    {
        string endTime = getCurrentDateTime();
        if( !m_fileInfoDBHandler->updateFileInfo(updateFileType, filename, endTime) )
        {
            updateFileResult = false;
        }

        break;
    }
    }

    if( !updateFileResult )
    {
        LOGE() << "Failed to update data ( File managing type : " << updateFileType << " )";
    }
}

void FileManager::requestUpdateNewFileCreated(string filename)
{
    FileInfo fileInfo;
    fileInfo.start_time = getCurrentDateTime();
    fileInfo.end_time = "";
    fileInfo.fileName = filename;
    fileInfo.file_exist = "true";
    fileInfo.file_provide = "false";

    m_fileInfoDBHandler->addNewFileInfo(fileInfo);
}

string FileManager::createNewFileName()
{
    string fileName;
    string dateTimeFormat;

    dateTimeFormat = getCurrentDateTime();
    fileName.append(m_storagePath).append(dateTimeFormat).append(".json");

    return fileName;
}

string FileManager::searchFileName(SearchFileMothodType fileType)
{
    string fileName;

    fileName = m_fileInfoDBHandler->getFileName(fileType);

    return fileName;
}

string FileManager::getCurrentDateTime()
{
    boost::posix_time::ptime localTime =
                boost::posix_time::second_clock::local_time();

    string dateTimeFormat = boost::str( boost::format( "%04d%02d%02d_%02d%02d%02d" )
                                       % localTime.date().year() % static_cast<int>(localTime.date().month()) % localTime.date().day()
                                       % localTime.time_of_day().hours() % localTime.time_of_day().minutes() % localTime.time_of_day().seconds() );

    return dateTimeFormat;
}
