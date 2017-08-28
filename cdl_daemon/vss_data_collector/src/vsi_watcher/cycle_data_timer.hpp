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

#ifndef CYCLEDATATIMER_H
#define CYCLEDATATIMER_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <unordered_map>
#include <functional>

using namespace std;

typedef boost::asio::deadline_timer Timer;
typedef std::function<void(int, int, int)> collectDataCallBack;

/**
 * @brief Call the data collection function.
 *
 * This class will create a timer when the constructor is called with
 * provided arguments.
 *
 * The interval parameter operates a timer for each interval.
 *
 * The groupID parameter identifies the group of data to collect.
 *
 * The signalCount parameter is the number of data contained in the data group.
 *
 * The io parameter is needed to use the timer.
 *
 * @param interval
 * @param groupID
 * @param signalCount
 * @param io
 *
 */

class CycleDataTimer
{
public:
    CycleDataTimer(int interval, int groupID, int signalCount, boost::asio::io_service &io);
    virtual ~CycleDataTimer();

    /**
     * @brief Register callback function to be called every cycle of data.
     *
     * @param callbackFunc
     */
    void registerCollectDataCallback(collectDataCallBack callback);

private:
    collectDataCallBack onCollectData;

    /**
     * @brief Timer callback function to be executed every cycle of data.
     *
     */
    void expire();

private:
    Timer m_timer;
    int m_interval;
    int m_groupID;
    int m_signalCount;
};

#endif // CYCLEDATATIMER_H
