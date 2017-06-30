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

#include "datamanager.h"
#include "../../common/log.h"

DataManager::DataManager()
{
    m_cdlDataBuffer.clear();
}

DataManager::~DataManager()
{
    m_cdlDataBuffer.clear();
}

ClientAPITypes::NotifyType DataManager::getCDLDataNotifyType(CDLData &data)
{
    ClientAPITypes::NotifyType notiType;

    m_cdlDataMutex.lock();

    map<string, CDLData>::iterator findCDLDataIter;
    findCDLDataIter = m_cdlDataBuffer.find(data.name);

    if( findCDLDataIter == m_cdlDataBuffer.end() )                  // no data
    {
        m_cdlDataBuffer.insert( std::make_pair(data.name, data) );
        notiType = ClientAPITypes::NotifyType::NT_CHANGED;
    }
    else                                                            // succeed to find data
    {
        if( findCDLDataIter->second.value != data.value )
        {
            notiType = ClientAPITypes::NotifyType::NT_CHANGED;      // Notify type = change
            findCDLDataIter->second = data;                         // modify the data
        }
        else
        {
            findCDLDataIter->second.time_stamp = data.time_stamp;
            notiType = ClientAPITypes::NotifyType::NT_UPDATED;      //Notify type = update
        }
    }

    m_cdlDataMutex.unlock();

    return notiType;
}

/* return type can change at any time ( e.g: CDLData ) */
CDLData DataManager::getCDLData(string name)
{
    CDLData cdlData;

    m_cdlDataMutex.lock();
    map<string, CDLData>::iterator findCDLDataIter;
    findCDLDataIter = m_cdlDataBuffer.find(name);

    if( findCDLDataIter != m_cdlDataBuffer.end() )
    {
        cdlData = findCDLDataIter->second;
    }
    else
    {
        LOGW() << "No Signal in CDLData ( name : " << name << " )";
    }

    m_cdlDataMutex.unlock();
    return cdlData;
}

