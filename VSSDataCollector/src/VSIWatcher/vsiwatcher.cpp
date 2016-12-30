/*
* Copyright (C) 2016, IVIS
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
* \copyright Copyright (c) 2016, IVIS \n
* License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
*
*/

#include "vsiwatcher.h"

#define VSI_DOMAIN_ID 0
#define VSI_DATA_MAX_SIZE 1024

VSIWatcher::VSIWatcher(VssItemManager *vssItemManager, DataCollectConfiguration *dataConfigParser,
                         NameToIdConvertor *nameToIdConvertor)
    :m_cycleDataThread(NULL), m_eventDataThread(NULL), m_vsiHandle(NULL)
    ,m_vssItemManager(vssItemManager)
    ,m_dataCollectionConfiguration(dataConfigParser)
    ,m_nameToIdConvertor(nameToIdConvertor)
{

}

VSIWatcher::~VSIWatcher()
{
    m_ioService.stop();
    deleteTimerObject();

    stopCycleDataCollectionThread();
}

bool VSIWatcher::init()
{
    m_vsiHandle = vsi_initialize();

    if ( !m_vsiHandle )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "Failed to allocate memory for VSI( Data handle for group )" );
        return false;
    }

    createCycleDataCollectionThread();

    return true;
}

void VSIWatcher::collectCycleData(int interval, int groupID, int signalCount)
{
    BOOST_LOG_TRIVIAL( info ) << boost::format( "=================================================================================" );
    BOOST_LOG_TRIVIAL( info ) << boost::format( "VSIWatcher::CollectData() : interval = %1%, groupID = %2%" ) % interval % groupID;

    // create result array
    vsi_result* results = (vsi_result*)malloc( sizeof(vsi_result) * signalCount );
    memset ( results, 0, sizeof(vsi_result) * signalCount );

    for ( int i = 0; i < signalCount; i++ )
    {
        results[i].data = (char*)malloc(VSI_DATA_MAX_SIZE);
        results[i].dataLength = VSI_DATA_MAX_SIZE;
        *results[i].data = 0;
    }


    // get data from VSI
    int get_newest_in_group_status = vsi_get_newest_in_group ( m_vsiHandle, groupID, results);

    if ( get_newest_in_group_status )
    {
        BOOST_LOG_TRIVIAL( error ) << boost::format( "Failed to get the newest data in group %1%, Error code : %2%") % groupID % get_newest_in_group_status;
    }
    else
    {
        for ( int i = 0; i < signalCount; i++ )
        {
            signal_t signalID = results[i].signalId;
            VssItem * item = m_vssItemManager->getVSSItem(signalID);

            if ( item != NULL )
            {
                storeData(item, results[i].data, signalID);
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

void VSIWatcher::storeData(VssItem *item, const char *data, signal_t signalId)
{
    // common log
    BOOST_LOG_TRIVIAL( info ) << boost::format( "Signal ID : %1%, Name : %2%, Value : %3%, Type : %4% unit: %5%" )
                                 % signalId % item->getName() % item->convertToValueString(data) % item->getType() % (item->getHasUnitValue() ? item->getUnit() : "N/A");
    // validation
    if ( !validateData(item, data) )
    {
        if ( item->getHasEnumValue() )
        {
            // invalid
            BOOST_LOG_TRIVIAL( warning ) << boost::format( "  -> Invalid Data!!! >> %1% is not included" )
                                         % item->convertToValueString(data);
        }
        else
        {
            // invalid
            BOOST_LOG_TRIVIAL( warning ) << boost::format( "  -> Invalid Data!!! >> min : %1%, max : %2%, data : %3%" )
                                         % item->getMinValue() % item->getMaxValue() % item->convertToValueString(data);
        }
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
        BOOST_LOG_TRIVIAL( warning ) << boost::format( "Cycle data thread is already existed" );
    }
}

void VSIWatcher::createEventDataCollectionThread()
{
    // not implemented yet.
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
    // not implemented yet.
}

void VSIWatcher::deleteTimerObject()
{    
    for( unsigned int count=0; count<m_vsi_cycle_timer.size(); count++ )
    {
        delete m_vsi_cycle_timer.at(count);
    }
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
        BOOST_LOG_TRIVIAL( info ) << boost::format( "Interval : %1%, Group ID : %2%" ) % interval % groupId;

        int status = vsi_create_signal_group(m_vsiHandle, groupId);
        if ( status != 0 )
        {
            BOOST_LOG_TRIVIAL( error ) << boost::format( "Fail to create signal group for cycle interval : %1%" ) % interval;

            iter++;
            continue;
        }

        for (unsigned int i = 0; i < item->nameList.size(); i++)
        {
            signal_t signalID = m_nameToIdConvertor->convertToID( item->nameList.at(i) );

            if ( signalID != NameToIdConvertor::INVALID_ID )
            {
                status = vsi_add_signal_to_group(m_vsiHandle, domainID, signalID, groupId);

                if ( status != 0 )
                {
                    BOOST_LOG_TRIVIAL( error ) << boost::format( "Failed to add signal %1% ( %2% ) in group ( %3% ). Error Code : %4%") % item->nameList.at(i) % signalID % groupId % status;
                }
            }
        }

        // create timer;

        CycleDataTimer *timer = new CycleDataTimer(interval, groupId, item->nameList.size(), m_ioService);

        timer->registerCollectDataCallback(std::bind(&VSIWatcher::collectCycleData, this, placeholders::_1, placeholders::_2, placeholders::_3));

        m_vsi_cycle_timer.push_back(timer);

        groupId++; iter++;
    }

    m_ioService.run();
}

void VSIWatcher::eventDataCollectionThread()
{
    // not implemented yet.
}
