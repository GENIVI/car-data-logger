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

#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <iostream>
#include <boost/thread.hpp>

using namespace std;

class DataStoreConfiguration;
class FileManager;

/**
 *
 * @brief Manage the storage size and period of files.
 *
 * This class checks storage size, file size and deletes the oldest file when the storage is not enough.
 *
 */

class StorageManager
{
public:
    StorageManager(DataStoreConfiguration *configManager, FileManager *fileManager);
    virtual ~StorageManager();

    /**
     * @brief Set the infomation about max file/storage size, data store location from configuration JSON file.
     *        Create the Storage(Directory) using data store location.
     *
     */
    bool init();

    /**
     * @brief Check the storage size using the maximum storage size defined
     *        in the configuration file and actual storage size used.
     *
     *  If the storage is not enough to store data, delete the oldest file.
     *
     * @param data size ( Length of data to write )
     */
    void manageStorage(int dataSize);

    /**
     * @brief Check whether the vehicle data exceeds the maximum file size defined
     *        in the configuration file when it is saved to a file.
     *
     * @param data size ( Length of data to write )
     * @param filePath ( FilePath to write )
     *
     * @return [true]  : save data unavailable in file. ( The file size is exceeded the max file size. )
     *         [false] : save data available in file.   ( The file size is enough to store data. )
     */
    bool isFileExceedSizeLimit(int dataSize, string filePath);

private:
    int getCurrentFileUsageSize(string filePath);
    int getCurrentStorageUsageSize();
    bool deleteFile(string oldestFilePath);
    void requestDeleteOldestFile();
    bool createDataStoreLocation();

    void checkFileExpiredThread();     //not implemented yet

private:
    DataStoreConfiguration * m_configManager;
    FileManager * m_fileManager;
    boost::thread * m_checkFileExpiredThread;

    string m_storagePath;
    int m_maxFileSize;
    int m_maxStorageSize;
    int m_maxFileExpirePeriod;    //p2
};

#endif // STORAGEMANAGER_H
