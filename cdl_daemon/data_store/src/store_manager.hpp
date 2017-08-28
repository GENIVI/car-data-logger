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

#ifndef STOREMANAGER_H
#define STOREMANAGER_H

#include <iostream>
#include <functional>
#include <boost/thread.hpp>

#include "../../common/cdl_common_define.hpp"

using namespace std;

class DataStoreConfiguration;
class FileInfoDBHandler;
class FileManager;
class StorageManager;
class DataStoreJSONHandler;

/**
 *
 * @brief Buffering the data receiving from VSSDataCollector until it reaches
 *        the maximum buffer size set from configuration file.
 *
 *        Request to DataStoreHandler to store data in json format when the data
 *        reaches to maximum buffer size.
 *
 */

typedef std::function<void(string)> completeDataStoreCallBack;

class StoreManager
{
public:
    struct CDL_DATA
    {
        string id;
        string value;
        string name;
        string type;
        string unit;
        string valid_state;
        string time_stamp;
    };

    typedef vector<CDL_DATA> CDLDataList;
    typedef vector<CDLDataList*> CDLDataListQueue;

public:
    StoreManager();
    virtual ~StoreManager();

public:
    /**
     * @brief Set configuration JSON file and start DataStoreManager.
     *
     */
    virtual bool init();

    /**
     * @brief Stop DataStoreManager.
     *
     */
    virtual void stop();

public:
    /**
     * @brief Event call to dataStoreThread when the buffer is full of data as much as max buffer size.
     *
     * @param CDLData
     */
    virtual void storeData(string _id, char* _value, string _name, CDLDataTypes _type, string _unit, bool _valid_state, uint64_t _timeStamp);
    virtual void registerCompleteDataStoreCallBack(completeDataStoreCallBack callback);

private:
    void setConfigurationFile();

    /**
     * @brief When the evnet is called, store the data to JSON file with DataStoreHandler.
     *
     */
    void dataStoreThread();

private:
    DataStoreConfiguration * m_configManager;
    FileInfoDBHandler * m_fileInfoDBHandler;
    FileManager * m_fileManager;
    StorageManager * m_storageManager;
    DataStoreJSONHandler * m_dataStoreJSONHandler;

    CDLDataList * m_cdlDataList;
    CDLDataListQueue m_cdlDataListQueue;

    int m_dataBufferMaxSize;

    boost::thread * m_dataStoreThread;
    boost::mutex m_cdlDataListQueueMutex;
    boost::mutex m_eventMutex;
    boost::condition_variable m_eventCondition;
    boost::mutex::scoped_lock m_eventLock;

    bool thread_work_done;

    string m_configFile;
};

#endif // STOREMANAGER_H
