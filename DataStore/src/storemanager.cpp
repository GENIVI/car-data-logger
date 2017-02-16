#include "storemanager.h"
#include "configuration.h"
#include "fileinfodbhandler.h"
#include "filemanager.h"
#include "storagemanager.h"

#include "commonlogheader.h"

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

void StoreManager::storeData(string _id, string _value, string _name, string _type, string _unit, string _valid_state, string _timeStamp)
{
    CDLData cdlData;

    cdlData.id          = _id;
    cdlData.value       = _value;
    cdlData.name        = _name;
    cdlData.type        = _type;
    cdlData.unit        = _unit;
    cdlData.valid_state = _valid_state;
    cdlData.time_stamp  = _timeStamp;

    if ( m_cdlDataList == NULL )
    {
        m_cdlDataList = new CDLDataList();
    }

    if ( m_cdlDataList != NULL )
    {
        m_cdlDataList->push_back(cdlData);

        BOOST_LOG_TRIVIAL( debug ) << boost::format( "======================= < cdlDataList size : %d / data count : %d >===========================") % m_cdlDataList->size() % cdlData.value;

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
        BOOST_LOG_TRIVIAL( error ) << boost::format( "<< StoreManager::storeData >> Failed to create object of cdlDataList");
    }
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
