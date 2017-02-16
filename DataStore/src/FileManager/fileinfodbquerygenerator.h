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

#ifndef FILEINFODBQUERYGENERATOR_H
#define FILEINFODBQUERYGENERATOR_H

#include <string>

using namespace std;

/**
 *
 * @brief Generate the DB query to manage the file info list.
 *
 */

class FileInfoDBQueryGenerator
{
public:
    FileInfoDBQueryGenerator();
    virtual ~FileInfoDBQueryGenerator();

public:
    string tableExistQuery(const string tableName);
    string createTableQuery(const string tableName);
    string insertQuery(const string tableName);
    string updateFileExistQuery(const string tableName, string filename);
    string updateFailDeleteFileQuery(const string tableName, string filename);
    string updateSaveFileEndTimeQuery(const string tableName, string filename, string endTime);
    string searchOldestFileQuery(const string tableName);
    string searchLatestFileQuery(const string tableName);
};

#endif // FILEINFODBQUERYGENERATOR_H
