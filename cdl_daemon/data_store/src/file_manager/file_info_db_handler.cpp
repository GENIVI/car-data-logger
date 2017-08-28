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

#include "file_info_db_handler.hpp"
#include "file_info_db_query_generator.hpp"
#include "../../common/log.hpp"

FileInfoDBHandler::FileInfoDBHandler()
    :m_fileInfoDBQueryGenerator(NULL), m_db(NULL)
{
    m_fileInfoDBQueryGenerator = new FileInfoDBQueryGenerator();
}

FileInfoDBHandler::~FileInfoDBHandler()
{
    if( m_fileInfoDBQueryGenerator != NULL )
    {
        delete m_fileInfoDBQueryGenerator;
        m_fileInfoDBQueryGenerator = NULL;
    }

    m_dbHandlerMutex.lock();
    sqlite3_close(m_db);
    m_dbHandlerMutex.unlock();
}

bool FileInfoDBHandler::addNewFileInfo(FILE_INFO &fileInfo)
{
    bool result = true;

    m_dbHandlerMutex.lock();
    if( !InsertData(FileInfoListTableName, fileInfo) )
    {
        LOGW() << "Failed to update new file info in DB file";
        result = false;
    }
    m_dbHandlerMutex.unlock();

    return result;
}

bool FileInfoDBHandler::updateFileInfo(UPDATE_FILE_INFO_TYPE type, string filename)
{
    string updateQuery;
    bool result;

    switch(type)
    {
    case UPDATE_FILE_DELETED:
    {
        updateQuery = m_fileInfoDBQueryGenerator->updateFileExistQuery(FileInfoListTableName, filename);
        break;
    }
    case UPDATE_FILE_PROVIDED:
    {
        /* not implemented yet */
        break;
    }
    case UPDATE_FILE_DELETION_FAILED:
    {
        updateQuery = m_fileInfoDBQueryGenerator->updateFailDeleteFileQuery(FileInfoListTableName, filename);
        break;
    }
    default:
    {
        break;
    }
    }
    m_dbHandlerMutex.lock();
    result = UpdateData(updateQuery);
    m_dbHandlerMutex.unlock();
    return result;
}

bool FileInfoDBHandler::updateFileInfo(FileInfoDBHandler::UPDATE_FILE_INFO_TYPE type, string filename, string time)
{
    string updateQuery;
    bool result;

    switch(type)
    {
    case UPDATE_FILE_SAVE_FINISHED:
    {
        updateQuery = m_fileInfoDBQueryGenerator->updateSaveFileEndTimeQuery(FileInfoListTableName, filename, time);
        break;
    }
    default:
    {
        break;
    }
    }

    m_dbHandlerMutex.lock();
    result = UpdateData(updateQuery);
    m_dbHandlerMutex.unlock();

    return result;
}

string FileInfoDBHandler::getFileName(SEARCH_FILE_TYPE type)
{
    string fileName;
    string getDataQuery;

    switch(type)
    {
    case OLDEST_FILE:
    {
        getDataQuery = m_fileInfoDBQueryGenerator->searchOldestFileQuery(FileInfoListTableName);
        break;
    }
    default:
    {
        break;
    }
    }

    m_dbHandlerMutex.lock();
    fileName = GetData(getDataQuery);
    m_dbHandlerMutex.unlock();

    return fileName;
}

bool FileInfoDBHandler::openFileInfoListFile(string &filePath)
{
    bool result = true;

    m_dbHandlerMutex.lock();
    if( Open(filePath) )
    {
        if( !IsTableExist(FileInfoListTableName) )
        {
            if( !CreateTable(FileInfoListTableName) )
            {
                LOGE() << "Failed to create table in DB ( Table name : " << FileInfoListTableName << " )";
                result = false;
            }
        }
    }
    else
    {
        LOGE() << "Failed to open FileInfo DB File";
        result =  false;
    }
    m_dbHandlerMutex.unlock();

    return result;
}

bool FileInfoDBHandler::Open(const string fileName)
{
    const char *file = fileName.c_str();

    int result = sqlite3_open(file, &m_db);

    if( result != SQLITE_OK )
    {
        sqlite3_close(m_db);
        return false;
    }

    return true;
}

bool FileInfoDBHandler::IsTableExist(const string tableName)
{
    sqlite3_stmt *stmt;
    string tableExistQueryStr = m_fileInfoDBQueryGenerator->tableExistQuery(tableName);

    int result;

    result = sqlite3_prepare_v2(m_db, tableExistQueryStr.c_str(), -1, &stmt, NULL);    //5th argu is NULL because of query is just one
    if( result != SQLITE_OK )
    {
        LOGD() << "Table is existed ( Error Msg : " << sqlite3_errmsg(m_db) << " )";
        return false;
    }

    result = sqlite3_step(stmt);
    if( result == SQLITE_DONE )       //find table success : SQLITE_ROW | find table Fail : SQLITE_DONE
    {
        LOGE() << "Failed to find table ( Table name : " << tableName << " )";
        return false;
    }
    else
    {
        LOGD() << "Succeed to find table ( Table name : " << tableName << " )";
    }

    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    return true;
}

bool FileInfoDBHandler::CreateTable(const string tableName)
{
    sqlite3_stmt *stmt;
    string createTableQueryStr;
    int result;

    createTableQueryStr = m_fileInfoDBQueryGenerator->createTableQuery(tableName);

    result = sqlite3_prepare_v2(m_db, createTableQueryStr.c_str(), -1, &stmt, NULL);
    if( result != SQLITE_OK )
    {
        LOGE() << "Failed to create table ( Error Msg : " << sqlite3_errmsg(m_db) << " )";
        return false;
    }

    result = sqlite3_step(stmt);
    if( result != SQLITE_DONE )
    {
        LOGD() << "Failed to create table ( Table name : " << tableName << " )";
        return false;
    }
    else
    {
        LOGD() << "Succeed to create table ( Table name : " << tableName << " )";
    }

    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    return true;
}

bool FileInfoDBHandler::InsertData(const string tableName, FILE_INFO &fileInfo)
{
    sqlite3_stmt *stmt;
    string insertQueryStr = m_fileInfoDBQueryGenerator->insertQuery(tableName);
    int result;

    result = sqlite3_prepare_v2(m_db, insertQueryStr.c_str(), -1, &stmt, NULL);
    if( result != SQLITE_OK )
    {
        LOGE() << "Failed to insert data ( Error Msg : " << sqlite3_errmsg(m_db) << " )";
        return false;
    }

    sqlite3_bind_text(stmt, 1, fileInfo.start_time.c_str(), -1, SQLITE_STATIC);     //Start Time
    sqlite3_bind_text(stmt, 2, fileInfo.end_time.c_str(), -1, SQLITE_STATIC);       //End Time
    sqlite3_bind_text(stmt, 3, fileInfo.fileName.c_str(), -1, SQLITE_STATIC);       //FileName
    sqlite3_bind_text(stmt, 4, fileInfo.file_exist.c_str(), -1, SQLITE_STATIC);     //File Exist
    sqlite3_bind_text(stmt, 5, fileInfo.file_provide.c_str(), -1, SQLITE_STATIC);   //File Provide

    result = sqlite3_step(stmt);

    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    return true;
}

bool FileInfoDBHandler::UpdateData(const string updateQueryStr)
{
    sqlite3_stmt *stmt;
    int result;

    result = sqlite3_prepare_v2(m_db, updateQueryStr.c_str(), -1, &stmt, NULL);
    if( result != SQLITE_OK )
    {
        LOGE() << "Failed to update data ( Error Msg : " << sqlite3_errmsg(m_db) << " )";
        return false;
    }

    result = sqlite3_step(stmt);

    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    return true;
}

string FileInfoDBHandler::GetData(const string getDataQueryStr)
{
    sqlite3_stmt *stmt;
    string data = "";
    int cols=0;
    int result;

    result = sqlite3_prepare_v2(m_db, getDataQueryStr.c_str(), -1, &stmt, NULL);

    if( result == SQLITE_OK )
    {
        cols = sqlite3_column_count(stmt);
        while( true )
        {
            result = sqlite3_step(stmt);
            if( result == SQLITE_ROW )
            {

                for( int col=0; col<cols; col++ )
                {
                    switch( sqlite3_column_type(stmt, col) )
                    {
                    case SQLITE_INTEGER:
                    {
                        data = to_string(sqlite3_column_int(stmt, col));
                        break;
                    }
                    case SQLITE_TEXT:
                    {
                        data = (const char*)(sqlite3_column_text(stmt, col));
                        break;
                    }
                    case SQLITE_NULL:
                    {
                        LOGW() << "Data type is NULL";
                        break;
                    }
                    default:
                    {
                        break;
                    }
                    }
                }
            }
            else if( result == SQLITE_DONE )  //finish data search
            {
                break;
            }
            else                            //not used
            {
                break;
            }
        }
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);

    return data;
}
