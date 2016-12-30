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

#include "cycledatatimer.h"

CycleDataTimer::CycleDataTimer(int interval,int groupID, int signalCount, boost::asio::io_service &io)
    :m_timer(io, boost::posix_time::milliseconds(interval))
    ,m_interval(interval), m_groupID(groupID), m_signalCount(signalCount)
{    
    m_timer.async_wait(std::bind(&CycleDataTimer::expire, this));
}

CycleDataTimer::~CycleDataTimer()
{
    m_timer.cancel();
}

void CycleDataTimer::expire()
{
    this->onCollectData(m_interval, m_groupID, m_signalCount);

    m_timer.expires_at(m_timer.expires_at() + boost::posix_time::milliseconds(m_interval));
    m_timer.async_wait(std::bind(&CycleDataTimer::expire, this));
}

void CycleDataTimer::registerCollectDataCallback(collectDataCallBack callback)
{
    onCollectData = move(callback);
}
