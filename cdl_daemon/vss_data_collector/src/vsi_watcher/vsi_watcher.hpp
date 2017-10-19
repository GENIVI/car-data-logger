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

#ifndef VSIWATCHER_H
#define VSIWATCHER_H

extern "C"
{
    #include <vsi/vsi.h>
}

#include "vss_data_collector.hpp"
#include "vss_item_manager.hpp"
#include "name_to_id_convertor.hpp"
#include "data_config_parser.hpp"
#include "cycle_data_timer.hpp"

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

/**
 *
 * @brief Get the vehicle data using the VSI API
 *
 */

class VSIWatcher
{
public:
    VSIWatcher(VssItemManager *vssItemManager, DataCollectConfiguration *dataConfigParser,
                NameToIdConvertor *nameToIdConvertor);
    virtual ~VSIWatcher();

public:
    /**
     * @brief Initialize the objects to use the VSI API.
     *        Initialize the variales needed to read data using VSI API.
     *        Initialize and execute thread to get cycle and event type data.
     */
    bool init();

private:
    /**
     * @brief Data is collected by calling from the timer every cycle of data.
     *
     * @param interval
     * @param groupID
     * @param signalCount
     */
    void collectCycleData(int interval, int groupID, int signalCount);

    /* Function for event data */
    void collectEventData(int interval, int groupID, int signalCount);

    /**
     * @brief Validate the data to store in database.
     *
     * @param item
     * @param data
     *
     * @return Result of validate the data.
     */
    bool validateData(VssItem * item, const char * data);

    /**
     * @brief Save the data in the database. ( Not implement yet. )
     *        Just print the result to the log.
     *
     * @param item
     * @param data
     * @param signalID
     */
    void storeData(VssItem * item, const char * data, signal_t signalId, unsigned long dataLength);

    void createCycleDataCollectionThread();
    void createEventDataCollectionThread();

    void stopCycleDataCollectionThread();
    void stopEventDataCollectionThread();

    void cycleDataCollectionThread();
    void eventDataCollectionThread();

    void deleteTimerObject();

public:
    // void register callback function
    void registerCDLDaemonCallBack(cdlDaemonCallBack callback);

private:
    boost::thread *m_cycleDataThread;
    boost::thread *m_eventDataThread;
    boost::asio::io_service m_cycleIOService;
    boost::asio::io_service m_eventIOService;

    vsi_handle m_vsiHandle;

    vector<CycleDataTimer*> m_vsi_cycle_timer;
    vector<CycleDataTimer*> m_vsi_event_timer;
    VssItemManager * m_vssItemManager;
    DataCollectConfiguration * m_dataCollectionConfiguration;
    NameToIdConvertor * m_nameToIdConvertor;

    // callback function
    cdlDaemonCallBack onCDLDaemonCallBack;

    boost::posix_time::ptime m_epoch;
    boost::mutex m_storeDataMutex;
    map<signal_t, string> m_managerEventData;
};

#endif // VSIWATCHER_H
