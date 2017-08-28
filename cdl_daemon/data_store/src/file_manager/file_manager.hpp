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

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "file_info_db_handler.hpp"

using namespace std;

class DataStoreConfiguration;

/**
 *
 * @brief Provide and Manage the file infomation.
 *
 * This class stores and provides the file information using DataBase.
 *
 * [ Store file info to DB ]
 *  1. file save start time
 *  2. file save end time
 *  3. file name
 *  4. file exists
 *  5. file provides
 *
 * [ Provide file info from DB ]
 *  1. create new filename
 *  2. search file name(oldest filename / lateset filename)
 *
 */

typedef FileInfoDBHandler::UPDATE_FILE_INFO_TYPE    UpdateFileInfoType;
typedef FileInfoDBHandler::SEARCH_FILE_TYPE         SearchFileMothodType;
typedef FileInfoDBHandler::FILE_INFO                FileInfo;

class FileManager
{
public:
    FileManager(DataStoreConfiguration *configManager, FileInfoDBHandler *fileInfoDBHandler);
    virtual ~FileManager();

    bool init();

public:
    void requestUpdateFileInfo(UpdateFileInfoType updateFileType, string filename);
    void requestUpdateNewFileCreated(string filename);

    /**
     * @brief Create new file name.
     *
     * format : (date)_(time).json
     * ( ex : 20170209_194524.json )
     *
     * @return created new file name
     *
     */
    string createNewFileName();

    /**
     * @brief Request the file name from FileInfoList file.
     *
     * @param search file type
     *
     * @return filename
     */
    string searchFileName(SearchFileMothodType fileType);

private:
    bool createFileInfoListFile();
    string getCurrentDateTime();

private:
    DataStoreConfiguration * m_configManager;
    FileInfoDBHandler * m_fileInfoDBHandler;

    string m_storagePath;
    string m_fileInfoListFilePath;
};

#endif // FILEMANAGER_H
