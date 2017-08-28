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

#include "cdl_daemon.hpp"
#include "vss_data_collector/src/vss_data_collector.hpp"
#include "data_store/src/store_manager.hpp"
#include "on_board_provider/src/on_board_provider.hpp"
#include "off_board_provider/src/off_board_provider.hpp"
#include "common/log.hpp"

CDLDaemon::CDLDaemon()
    : m_vssDataCollector(NULL), m_storeManager(NULL), m_onBoardProvider(NULL), m_offBoardProvider(NULL)
{

}

CDLDaemon::~CDLDaemon()
{

}

bool CDLDaemon::init()
{
    m_vssDataCollector = new VSSDataCollector();
    m_storeManager = new StoreManager();
    m_onBoardProvider = new OnBoardProvider();
    m_offBoardProvider = new OffBoardProvider();

    if( !m_vssDataCollector->start() )
    {
        return false;
    }

    if( !m_storeManager->init() )
    {
        return false;
    }

    if( !m_onBoardProvider->start() )
    {
        return false;
    }

    if( !m_offBoardProvider->init() )
    {
        return false;
    }

    m_vssDataCollector->registerCollectDataCallback(std::bind(&CDLDaemon::registerDataCollectedCallBack, this, placeholders::_1, placeholders::_2, placeholders::_3,
                                                              placeholders::_4, placeholders::_5, placeholders::_6, placeholders::_7, placeholders::_8));

    m_storeManager->registerCompleteDataStoreCallBack(std::bind(&CDLDaemon::notifyCompleteDataStoreCallBack, this, placeholders::_1));

    return true;
}

void CDLDaemon::stop()
{
    if( m_storeManager != NULL )
    {
        LOGD() << "StoreManager Stop";
        m_storeManager->stop();
        delete m_storeManager;
        m_storeManager = NULL;
    }

    if( m_vssDataCollector != NULL )
    {
        LOGD() << "VSSDataCollector Stop";
        m_vssDataCollector->stop();
        delete m_vssDataCollector;
        m_vssDataCollector = NULL;
    }

    if( m_offBoardProvider != NULL )
    {
        LOGD() << "OffBoardProvider Stop";
        m_offBoardProvider->stop();
        delete m_offBoardProvider;
        m_offBoardProvider = NULL;
    }

    if( m_onBoardProvider != NULL )
    {
        LOGD() << "OnBoardProvider Stop";
        m_onBoardProvider->stop();
        delete m_onBoardProvider;
        m_onBoardProvider = NULL;
    }
}

void CDLDaemon::registerDataCollectedCallBack(string id, char *value, string name, CDLDataTypes type, string unit, bool valid_state, uint64_t time_stamp, unsigned long dataLength)
{
    LOGD() << "===============================================";
    LOGD() << "1. id          : " << id;
    LOGD() << "2. value       : " << value;
    LOGD() << "3. name        : " << name;
    LOGD() << "4. type        : " << type;
    LOGD() << "5. unit        : " << unit;
    LOGD() << "6. valid_state : " << valid_state;
    LOGD() << "7. time_stamp  : " << time_stamp;
    LOGD() << "8. data_length : " << dataLength;

    m_storeManager->storeData(id, value, name, type, unit, valid_state, time_stamp);
    m_onBoardProvider->provideData(id, value, name, type, unit, valid_state, time_stamp, dataLength);
}

void CDLDaemon::notifyCompleteDataStoreCallBack(string jsonFilePath)
{
    m_offBoardProvider->transferData(jsonFilePath);
}
