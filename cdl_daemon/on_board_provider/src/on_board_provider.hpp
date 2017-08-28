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

#ifndef ONBOARDPROVIDER_H
#define ONBOARDPROVIDER_H

#include "../../common/cdl_common_define.hpp"

#include <string>

using namespace std;

class DataManager;
class OnBoardProviderService;

/**
 * @brief Receive the vehicle data from collector.
 *
 * This class gets the notify_type of the data from the DataManager
 * and provides the vehicle data to the clients using the notify_type of data.
 *
 */

class OnBoardProvider
{
public:
    OnBoardProvider();
    virtual ~OnBoardProvider();

public:
    /**
     * @brief Start the DataProvider.
     *
     */
    virtual bool start();

    /**
     * @brief Stop the DataProvider.
     *
     */
    virtual void stop();

    /**
     * @brief Provide the data to registered clients.
     *
     * @param CDL-Data format
     *
     */
    virtual void provideData(string id, char *value, string name, CDLDataTypes type, string unit, bool valid_state, uint64_t time_stamp, unsigned long dataLength);

private:
    void setConfigurationFiles();

private:
    OnBoardProviderService * m_onBoardProviderService;
    DataManager * m_dataManager;

    string m_commonapiConfigFile;
    string m_vsomeipConfigFile;
};

#endif // ONBOARDPROVIDER_H
