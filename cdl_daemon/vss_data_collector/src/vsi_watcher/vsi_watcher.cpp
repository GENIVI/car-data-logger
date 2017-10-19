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

#include "vsi_watcher.hpp"
#include "../../common/log.hpp"

#define VSI_DOMAIN_ID 0
#define VSI_DATA_MAX_SIZE 1024

#define UNUSED(x) (void)(x)

VSIWatcher::VSIWatcher(VssItemManager *vssItemManager, DataCollectConfiguration *dataConfigParser, NameToIdConvertor *nameToIdConvertor)
    :m_cycleDataThread(NULL), m_eventDataThread(NULL), m_vsiHandle(NULL)
    ,m_vssItemManager(vssItemManager)
    ,m_dataCollectionConfiguration(dataConfigParser)
    ,m_nameToIdConvertor(nameToIdConvertor)
    ,m_epoch(boost::gregorian::date(1970,1,1))
{

}

VSIWatcher::~VSIWatcher()
{
    m_cycleIOService.stop();
    m_eventIOService.stop();

    deleteTimerObject();

    stopCycleDataCollectionThread();
    stopEventDataCollectionThread();
}

bool VSIWatcher::init()
{
    m_vsiHandle = vsi_initialize();
    m_managerEventData.clear();

    if ( !m_vsiHandle )
    {
        LOGE() << "Failed to allocate memory for VSI( Data handle for group )";
        return false;
    }

    createCycleDataCollectionThread();
    createEventDataCollectionThread();

    return true;
}

void VSIWatcher::collectCycleData(int interval, int groupID, int signalCount)
{
    UNUSED(interval);

    vsi_result* results = (vsi_result*)malloc( sizeof(vsi_result) * signalCount );
    memset ( results, 0, sizeof(vsi_result) * signalCount );

    for ( int i = 0; i < signalCount; i++ )
    {
        results[i].data = (char*)malloc(VSI_DATA_MAX_SIZE);
        results[i].dataLength = VSI_DATA_MAX_SIZE;
        *(results[i].data) = 0;
        results[i].status = -61;
    }

    // get data from VSI
    int get_newest_in_group_status = vsi_get_newest_in_group ( m_vsiHandle, groupID, results);

    if ( get_newest_in_group_status )
    {
        LOGE() << "Failed to get the newest data in group : " << groupID << ", Error code : " << get_newest_in_group_status;
    }
    else
    {
        for ( int i = 0; i < signalCount; i++ )
        {
            if ( results[i].status == 0 )
            {
                signal_t signalID = results[i].signalId;
                VssItem * item = m_vssItemManager->getVSSItem(signalID);

                if ( item != NULL )
                {
                    m_storeDataMutex.lock();
                    storeData(item, results[i].data, signalID, results[i].dataLength);
                    m_storeDataMutex.unlock();
                }
            }
        }
    }

    // delete result array
    for ( int i = 0; i < signalCount; i++ )
    {
        free(results[i].data);
    }

    free(results);
}

void VSIWatcher::collectEventData(int interval, int groupID, int signalCount)
{
    vsi_result* results = (vsi_result*)malloc( sizeof(vsi_result) * signalCount );
    memset ( results, 0, sizeof(vsi_result) * signalCount );

    for ( int i = 0; i < signalCount; i++ )
    {
        results[i].data = (char*)malloc(VSI_DATA_MAX_SIZE);
        results[i].dataLength = VSI_DATA_MAX_SIZE;
        *(results[i].data) = 0;
        results[i].status = -61;
    }

    int get_newest_in_group_status = vsi_get_newest_in_group(m_vsiHandle, groupID, results);

    if ( get_newest_in_group_status )
    {
//        LOGE() << "[Event Data] Failed to get the newest data in group " << groupID << " ( Error code : " << get_newest_in_group_status << " )";
    }
    else
    {
        for ( int i = 0; i < signalCount; i++ )
        {
            if ( results[i].status == 0 )
            {
                signal_t signalID = results[i].signalId;

                VssItem * item = m_vssItemManager->getVSSItem(signalID);

                if( m_managerEventData[signalID] != item->convertToValueString(results[i].data) )
                {
                    m_storeDataMutex.lock();
                    storeData(item, results[i].data, signalID, results[i].dataLength);
                    m_managerEventData[signalID] = item->convertToValueString(results[i].data);
                    m_storeDataMutex.unlock();
                }
                else
                {
                    //not changed event type data
                }
            }
        }
    }

    // delete result array
    for ( int i = 0; i < signalCount; i++ )
    {
        free(results[i].data);
    }

    free(results);
}

bool VSIWatcher::validateData(VssItem *item, const char *data)
{
    if ( (item->getHasMinValue() && item->getHasMaxValue()) || item->getHasEnumValue() )
    {
        return item->validateData(data);
    }

    return true;
}

void VSIWatcher::storeData(VssItem *item, const char *data, signal_t signalId, unsigned long dataLength)
{
    UNUSED(signalId);

    bool valid_state;
    uint64_t time_stamp;

    valid_state = validateData(item, data);

    /* Sample provide time_stamp */
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::universal_time();
    boost::posix_time::time_duration currentUTCTime = now - m_epoch;

    time_stamp = currentUTCTime.total_milliseconds();

    LOGD() << "--------------------------------------------------";
    LOGD() << "[ Collected Data ]";
    LOGD() << " 1. Signal ID   : " << signalId;
    LOGD() << " 2. Signal Name : " << item->getName();
    LOGD() << " 3. Value       : " << item->convertToValueString(data, dataLength);
    LOGD() << " 4. Valid State : " << valid_state;

    if( this->onCDLDaemonCallBack != NULL )
    {
        this->onCDLDaemonCallBack(to_string(item->getID()), (char*)data, item->getName(), item->getType(), item->getUnit(), valid_state, time_stamp, dataLength);
    }
}

void VSIWatcher::createCycleDataCollectionThread()
{
    if ( m_cycleDataThread == NULL )
    {
        m_cycleDataThread = new boost::thread(std::bind(&VSIWatcher::cycleDataCollectionThread, this));
    }
    else
    {
        LOGW() << "Cycle data thread is already existed";
    }
}

void VSIWatcher::createEventDataCollectionThread()
{
    if ( m_eventDataThread == NULL )
    {
        m_eventDataThread = new boost::thread(std::bind(&VSIWatcher::eventDataCollectionThread, this));
    }
    else
    {
        LOGW() << "Event data thread is already existed";
    }
}

void VSIWatcher::stopCycleDataCollectionThread()
{
    if ( m_cycleDataThread != NULL )
    {
        m_cycleDataThread->join();
    }
}

void VSIWatcher::stopEventDataCollectionThread()
{
    if ( m_eventDataThread != NULL )
    {
        m_eventDataThread->join();
    }
}

void VSIWatcher::deleteTimerObject()
{    
    for( unsigned int count=0; count<m_vsi_cycle_timer.size(); count++ )
    {
        delete m_vsi_cycle_timer.at(count);
    }

    for( unsigned int count=0; count<m_vsi_event_timer.size(); count++ )
    {
        delete m_vsi_event_timer.at(count);
    }
}

void VSIWatcher::registerCDLDaemonCallBack(cdlDaemonCallBack callback)
{
    onCDLDaemonCallBack = callback;
}

void VSIWatcher::cycleDataCollectionThread()
{
    group_t groupId = 1;
    domain_t domainID = VSI_DOMAIN_ID;

    CycleDataList & cycleDataList = m_dataCollectionConfiguration->getCycleDataList();
    CycleDataList::iterator iter = cycleDataList.begin();

    while( iter != cycleDataList.end() )
    {
        CycleDataItem * item = iter->second;
        int interval = stoi(iter->first);
        LOGD() << "Cycle Data Collect Info -> Interval : " << interval << ", GroupID : " << groupId;

        int status = vsi_create_signal_group(m_vsiHandle, groupId);
        if ( status != 0 )
        {
            LOGE() << "Failed to create signal group with cycle interval : " << interval;

            iter++;
            continue;
        }

        for( unsigned int i = 0; i < item->nameList.size(); i++ )
        {
            signal_t signalID = m_nameToIdConvertor->convertToID( item->nameList.at(i) );

            if ( signalID != NameToIdConvertor::INVALID_ID )
            {
                status = vsi_add_signal_to_group(m_vsiHandle, domainID, signalID, groupId);

                if ( status != 0 )
                {
                    LOGE() << "Failed to add signal Info ( name : " << item->nameList.at(i) << " , signalID : " << signalID
                           << ", groupID(interval) : " << groupId << ", Error Code : " << status;
                }
            }
        }

        // create timer;

        CycleDataTimer *timer = new CycleDataTimer(interval, groupId, item->nameList.size(), m_cycleIOService);

        timer->registerCollectDataCallback(std::bind(&VSIWatcher::collectCycleData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        m_vsi_cycle_timer.push_back(timer);

        groupId++; iter++;
    }

    m_cycleIOService.run();
}

void VSIWatcher::eventDataCollectionThread()
{
    group_t groupId = 50;
    domain_t domainId = VSI_DOMAIN_ID;
    int interval = 400;

    EventDataList & eventDataList = m_dataCollectionConfiguration->getEventDataList();

    for( unsigned int index = 0; index < eventDataList.size(); index++ )
    {
        int status = vsi_create_signal_group(m_vsiHandle, groupId);
        if( status != 0 )
        {
            LOGE() << "Failed to create signal group with event interval : " << groupId;

            continue;
        }

        signal_t signalId = m_nameToIdConvertor->convertToID(eventDataList.at(index));

        if( signalId != NameToIdConvertor::INVALID_ID )
        {
            status = vsi_add_signal_to_group(m_vsiHandle, domainId, signalId, groupId);

            if ( status != 0 )
            {
                LOGE() << "Failed to add event signal Info ( name : " << eventDataList.at(index) << " , signalID : " << signalId
                       << ", groupID(interval) : " << groupId << ", Error Code : " << status;
            }
        }

        CycleDataTimer * timer = new CycleDataTimer(interval, groupId, 1, m_eventIOService);
        timer->registerCollectDataCallback(std::bind(&VSIWatcher::collectEventData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        m_vsi_event_timer.push_back(timer);

        groupId++;
    }

    m_eventIOService.run();
}
