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

#ifndef CONFIGURATIONMANAGER_H
#define CONFIGURATIONMANAGER_H

#include <boost/property_tree/ptree.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace boost;

/**
 *
 * @brief Parses the configuration file json format to provide information
 *        of default value to StorageManager and FileManager.
 *
 * [ Data Infomation ]
 *  1. File path to store json and database file
 *  2. Max file size
 *  3. Max storage size
 *  4. Max data buffer size
 *  5. Delete Period
 *
 */

class DataStoreConfiguration
{
public:
    DataStoreConfiguration();
    virtual ~DataStoreConfiguration();

public:
    /**
     * @brief Reads and parses the Store_Config Json File.
     *
     * @param jsonFilePath
     *
     */
    bool read(const string jsonFilePath);

    string getDataStoreLocation();
    int getMaxFileSize();
    int getMaxStorageSize();
    int getFileExpirePeriod();
    int getTransactionBufferSize();

private:
    bool parseStoreConfigFile(property_tree::ptree & jsonDoc);
    bool checkConfigInfo();

    /**
     * @brief check the DataStoreLocation.
     *
     * If the "/" character is not existed at the end of the StoreDataLocation,
     * append the "/" at the end of StoreDataLocation.
     *
     */
    void checkDataStoreLocation();

private:
    string m_dataStoreLocation;
    int m_maxFileSize;
    int m_maxStorageSize;
    int m_fileExpirePeriod;
    int m_transactionBufferSize;
};

#endif // CONFIGURATIONMANAGER_H
