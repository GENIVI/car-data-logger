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

#include "store_manager.hpp"
#include "configuration.hpp"
#include "file_info_db_handler.hpp"
#include "file_manager.hpp"
#include "storage_manager.hpp"
#include "data_store_json_handler.hpp"

#include "../../common/log.hpp"

#define UNUSED(x) (void)(x)

StoreManager::StoreManager()
    :m_cdlDataList(NULL), m_dataBufferMaxSize(0), m_dataStoreThread(NULL), m_eventLock(m_eventMutex)
    ,thread_work_done(false), m_configFile("")
{
    m_configManager = new DataStoreConfiguration();
    m_fileInfoDBHandler = new FileInfoDBHandler();
    m_fileManager = new FileManager(m_configManager, m_fileInfoDBHandler);
    m_storageManager = new StorageManager(m_configManager, m_fileManager);
    m_dataStoreJSONHandler = new DataStoreJSONHandler(m_fileManager, m_storageManager);
}

StoreManager::~StoreManager()
{
    if( m_cdlDataList != NULL )
    {
        m_cdlDataList->clear();
        delete m_cdlDataList;
        m_cdlDataList = NULL;
    }
}

bool StoreManager::init()
{
    setConfigurationFile();

    if( m_configManager == NULL || !(m_configManager->read(m_configFile)) )
    {
        return false;
    }

    if( m_storageManager == NULL || !(m_storageManager->init()) )
    {
        return false;
    }

    if( m_fileManager == NULL || !(m_fileManager->init()) )
    {
        return false;
    }

    m_dataBufferMaxSize = m_configManager->getTransactionBufferSize();

    if( m_cdlDataList == NULL )
    {
        m_cdlDataList = new CDLDataList();
    }

    m_dataStoreThread = new boost::thread(std::bind(&StoreManager::dataStoreThread, this));

    LOGD() << "Succeed to create DataStore";

    return true;
}

void StoreManager::stop()
{
    thread_work_done = true;
    m_eventCondition.notify_one();

    if( m_dataStoreThread != NULL )
    {
        m_dataStoreThread->join();
        m_dataStoreThread = NULL;
    }

    if ( m_cdlDataList != NULL )
    {
        if( m_cdlDataList->size() != 0 )
        {
            if( m_dataStoreJSONHandler->storeData(m_cdlDataList) )
            {
                delete m_cdlDataList;
                m_cdlDataList = NULL;
            }
        }
    }

    m_dataStoreJSONHandler->stop();

    if( m_storageManager != NULL )
    {
        delete m_storageManager;
        m_storageManager = NULL;
    }

    if( m_dataStoreJSONHandler != NULL )
    {
        delete m_dataStoreJSONHandler;
        m_dataStoreJSONHandler = NULL;
    }

    if( m_fileManager != NULL )
    {
        delete m_fileManager;
        m_fileManager = NULL;
    }

    if( m_fileInfoDBHandler != NULL )
    {
        delete m_fileInfoDBHandler;
        m_fileInfoDBHandler = NULL;
    }

    if( m_configManager != NULL )
    {
        delete m_configManager;
        m_configManager = NULL;
    }
}

void StoreManager::storeData(string _id, char* _value, string _name, CDLDataTypes _type, string _unit, bool _valid_state, uint64_t _timeStamp)
{    
    CDL_DATA cdlData;

    cdlData.id          = _id;
    cdlData.value       = m_dataStoreJSONHandler->convertValueToString(_value, _type);
    cdlData.name        = _name;
    cdlData.type        = to_string(_type);
    cdlData.unit        = _unit;
    cdlData.valid_state = to_string(_valid_state);
    cdlData.time_stamp  = to_string(_timeStamp);

    if ( m_cdlDataList == NULL )
    {
        m_cdlDataList = new CDLDataList();
    }

    if ( m_cdlDataList != NULL )
    {
        m_cdlDataList->push_back(cdlData);

        LOGD() << "======================= < cdlDataList size : " << m_cdlDataList->size() << "/ data count : " << cdlData.value << " >===========================";

        if( m_cdlDataList->size() >= (unsigned int)m_dataBufferMaxSize )
        {
            m_cdlDataListQueueMutex.lock();
            m_cdlDataListQueue.push_back(m_cdlDataList);
            m_cdlDataListQueueMutex.unlock();

            m_cdlDataList = NULL;

            m_eventCondition.notify_one();
        }
    }
    else
    {
        LOGE() << "Failed to create object of cdlDataList";
    }
}

void StoreManager::registerCompleteDataStoreCallBack(completeDataStoreCallBack callback)
{
    m_dataStoreJSONHandler->registerCompleteDataStoreCallBack(callback);
}

void StoreManager::setConfigurationFile()
{
    const char * store_config_file = getenv("STORE_CONFIG_FILE");

    if ( store_config_file )
    {
        m_configFile = store_config_file;
    }
    else
    {
        m_configFile = "./store_config_file.json";
    }
}

void StoreManager::dataStoreThread()
{
    while ( !thread_work_done )
    {
        m_eventCondition.wait(m_eventLock);
        if ( m_cdlDataListQueue.empty() )
        {
            continue;
        }

        do
        {
            m_cdlDataListQueueMutex.lock();
            CDLDataList * list = m_cdlDataListQueue.front();
            m_cdlDataListQueueMutex.unlock();

            if( m_dataStoreJSONHandler->storeData(list) )
            {
                list->clear();
                delete list;
                m_cdlDataListQueueMutex.lock();
                m_cdlDataListQueue.erase( m_cdlDataListQueue.begin() );
                m_cdlDataListQueueMutex.unlock();
            }

        } while( m_cdlDataListQueue.size() != 0 );

    }
}
