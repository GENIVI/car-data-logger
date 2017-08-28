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

#include "file_info_db_query_generator.hpp"
#include <boost/format.hpp>

FileInfoDBQueryGenerator::FileInfoDBQueryGenerator()
{

}

FileInfoDBQueryGenerator::~FileInfoDBQueryGenerator()
{

}



string FileInfoDBQueryGenerator::tableExistQuery(const string tableName)
{
    string tableExistQueryStr;

    tableExistQueryStr = boost::str( boost::format( "SELECT name FROM sqlite_master WHERE type=\"table\" AND name='%s';" ) % tableName );

    return tableExistQueryStr;
}

string FileInfoDBQueryGenerator::createTableQuery(const string tableName)
{
    string createTableQueryStr;

    createTableQueryStr = boost::str(
                boost::format( "CREATE TABLE %s (\"RowId\" INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "\"Start Time\" TEXT, \"End Time\" TEXT, \"FileName\" TEXT, \"Exist\" TEXT, \"Provide\" TEXT);" ) % tableName );

    return createTableQueryStr;
}

string FileInfoDBQueryGenerator::insertQuery(const string tableName)
{
    string insertDBQuery;

    insertDBQuery = boost::str( boost::format( "INSERT INTO %s "
                                               "(\"RowId\", \"Start Time\", \"End Time\", \"FileName\", \"Exist\", \"Provide\") VALUES(null, ?, ?, ?, ?, ?)" ) % tableName );

    return insertDBQuery;
}

string FileInfoDBQueryGenerator::updateFileExistQuery(const string tableName, string filename)
{
    string updateQuery;

    updateQuery = boost::str( boost::format( "UPDATE %s SET \"Exist\"='false' WHERE \"RowId\" "
                                             "= (SELECT \"RowId\" FROM %s WHERE \"Exist\"='true' AND \"FileName\"='%s' ORDER BY \"RowId\" ASC LIMIT 1);" ) % tableName % tableName % filename);

    return updateQuery;
}

string FileInfoDBQueryGenerator::updateFailDeleteFileQuery(const string tableName, string filename)
{
    string updateFailQuery;

    updateFailQuery = boost::str( boost::format( "UPDATE %s SET \"Exist\"='error' WHERE \"RowId\" "
                                             "= (SELECT \"RowId\" FROM %s WHERE \"Exist\"='true' AND \"FileName\"='%s' ORDER BY \"RowId\" ASC LIMIT 1);" ) % tableName % tableName % filename);

    return updateFailQuery;
}

string FileInfoDBQueryGenerator::updateSaveFileEndTimeQuery(const string tableName, string filename, string endTime)
{
    string updateEndTimeQuery;

    updateEndTimeQuery = boost::str( boost::format( "UPDATE %s SET \"End Time\"='%s' WHERE \"FileName\"='%s';" ) % tableName % endTime % filename);

    return updateEndTimeQuery;
}

string FileInfoDBQueryGenerator::searchOldestFileQuery(const string tableName)
{
    string searchOldestFileQuery;

    searchOldestFileQuery = boost::str( boost::format( "SELECT \"FileName\" FROM %s WHERE \"Exist\"='true' ORDER BY \"RowId\" ASC LIMIT 1;" ) % tableName );

    return searchOldestFileQuery;
}

string FileInfoDBQueryGenerator::searchLatestFileQuery(const string tableName)
{
    string searchLatestFileQuery;

    searchLatestFileQuery = boost::str( boost::format( "SELECT \"FileName\" FROM %s WHERE \"Exist\"='true' ORDER BY \"RowId\" DESC LIMIT 1;" ) % tableName );

    return searchLatestFileQuery;
}
