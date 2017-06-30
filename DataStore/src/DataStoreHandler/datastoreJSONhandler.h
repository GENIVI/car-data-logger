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

#ifndef DATASTOREHANDLER_H
#define DATASTOREHANDLER_H

#include "storemanager.h"
#include "../../common/cdlcommondefine.h"

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace std;

class FileManager;
class StorageManager;

/**
 *
 * @brief Store data to file in JSON format
 *
 * [ Save Data ]
 *  1. ID
 *  2. Value
 *  3. Name
 *  4. Type
 *  5. Valid_state
 *  6. Time_stamp
 *
 */

typedef StoreManager::CDL_DATA CDL_DATA;

class DataStoreJSONHandler
{
public:
    DataStoreJSONHandler(FileManager * fileManager, StorageManager * storageManager);
    virtual ~DataStoreJSONHandler();

    /**
     * @brief Store the CDL data to json file.
     *
     * @param CDLDataList
     *
     */
    bool storeData(vector<CDL_DATA> * cdlDataList);

    /**
     * @brief Finish saving the JSON file.
     *
     * This function is called when the system is turned off.
     *
     */
    void stop();

    string convertValueToString(const char* value, CDLDataTypes type);

    void registerCompleteDataStoreCallBack(completeDataStoreCallBack callback);

private:
    bool writeData(const string filePath, string cdlJSONData);
    string convertToJSON(vector<CDL_DATA> * cdlDataList);
    bool createNewFile();
    void addJSONHeader(const string filePath);
    void addJSONFooter(const string filePath);
    bool isFileEmpty(const string filePath);

private:
    FileManager * m_fileManager;
    StorageManager * m_storageManager;

    string m_latestFileName;

    completeDataStoreCallBack onCompleteDataStoreCalllback;
};

#endif // DATASTOREHANDLER_H
