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

#ifndef FILEINFODATABASEHANDLER_H
#define FILEINFODATABASEHANDLER_H

#include <boost/thread/mutex.hpp>
#include <sqlite3.h>
#include <string>

using namespace std;

class FileInfoDBQueryGenerator;

/**
 *
 * @brief Manage the list of files created in json format with DB file. ( using sqlite )
 *
 * This class provides APIs for databases such as open, get, insert, update.
 *
 */

static const string FileInfoListTableName = "FileInfoList";

class FileInfoDBHandler
{
public:
    enum SEARCH_FILE_TYPE
    {
        OLDEST_FILE=0,
    };

    enum UPDATE_FILE_INFO_TYPE
    {
        UPDATE_FILE_DELETED=0,
        UPDATE_FILE_PROVIDED,
        UPDATE_FILE_DELETION_FAILED,
        UPDATE_FILE_SAVE_FINISHED,
    };

    struct FILE_INFO
    {
        string start_time;
        string end_time;
        string fileName;
        string file_exist;
        string file_provide;
    };

public:
    FileInfoDBHandler();
    virtual ~FileInfoDBHandler();

    /**
     * @brief Insert the infomation of file about created new file into the database file.
     *
     * @param fileInfo
     */
    bool addNewFileInfo(FILE_INFO & fileInfo);

    /**
     * @brief Update files with information about changing infomation. (result of delete or provide)
     *
     * @param file update type
     * @param filename
     *
     */
    bool updateFileInfo(UPDATE_FILE_INFO_TYPE type, string filename);

    /**
     * @brief Update files with information about changing infomation. (time to save file)
     *
     * @param file update type
     * @param filename
     * @param file save end time
     *
     */
    bool updateFileInfo(UPDATE_FILE_INFO_TYPE type, string filename, string time);

    string getFileName(SEARCH_FILE_TYPE type);
    bool openFileInfoListFile(string & filePath);

private:
    bool Open(const string fileName);
    bool IsTableExist(const string tableName);
    bool CreateTable(const string tableName);
    bool InsertData(const string tableName, FILE_INFO & fileInfo);
    bool UpdateData(const string updateQueryStr);
    string GetData(const string getDataQuery);

private:
    FileInfoDBQueryGenerator * m_fileInfoDBQueryGenerator;

    sqlite3 * m_db;
    boost::mutex m_dbHandlerMutex;
};

#endif // FILEINFODATABASEHANDLER_H
