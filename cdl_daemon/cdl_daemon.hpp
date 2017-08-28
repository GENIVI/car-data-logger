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

#ifndef CDLDAEMON_H
#define CDLDAEMON_H

#include <string>
#include <functional>

#include "common/cdl_common_define.hpp"

using namespace std;

class VSSDataCollector;
class StoreManager;
class OnBoardProvider;
class OffBoardProvider;

/**
 * @brief Car-data-logger is a component operated with collector, store, provider(On/Off Board).
 *
 * The component Car Data Logger is responsible for collecting, storing car related data,
 * and providing the data to other GENIVI compliance components and off-board servers.
 *
 */

class CDLDaemon
{
public:
    CDLDaemon();
    virtual ~CDLDaemon();

public:
    /**
     * @brief Initialize the objects of collector, store, provider.
     *        Register a callback function to the collector to store collected vehicle data.
     *        Register a callback function that notifies the completion of data store.
     *
     */
    virtual bool init();

    /**
     * @brief Stop the CDL-Damon.
     *
     */
    virtual void stop();

private:
    void registerDataCollectedCallBack(string id, char *value, string name, CDLDataTypes type, string unit, bool valid_state, uint64_t time_stamp, unsigned long dataLength);
    void notifyCompleteDataStoreCallBack(string jsonFilePath);

private:
    VSSDataCollector * m_vssDataCollector;
    StoreManager * m_storeManager;
    OnBoardProvider * m_onBoardProvider;
    OffBoardProvider * m_offBoardProvider;
};

#endif // CDLDAEMON_H
