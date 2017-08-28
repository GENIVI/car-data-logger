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

#include "on_board_provider.hpp"
#include "data_manager.hpp"
#include "on_board_provider_service.hpp"
#include "../../common/log.hpp"

typedef OnBoardProviderService::CDL_DATA CDLData;

OnBoardProvider::OnBoardProvider()
    : m_onBoardProviderService(NULL), m_dataManager(NULL)
{

}

OnBoardProvider::~OnBoardProvider()
{

}

bool OnBoardProvider::start()
{
    setConfigurationFiles();

    if( m_dataManager == NULL )
    {
        m_dataManager = new DataManager();
    }

    if( m_onBoardProviderService == NULL )
    {
        m_onBoardProviderService = new OnBoardProviderService(m_dataManager);
    }

    LOGD() << "Succeed to create OnBoardProvider";

    return true;
}

void OnBoardProvider::stop()
{
    if( m_onBoardProviderService != NULL )
    {
        delete m_onBoardProviderService;
        m_onBoardProviderService = NULL;
    }

    if( m_dataManager != NULL )
    {
        delete m_dataManager;
        m_dataManager = NULL;
    }
}

void OnBoardProvider::setConfigurationFiles()
{
    const char * commonapi_config_file = getenv("COMMONAPI_CONFIG");

    if( commonapi_config_file )
    {
        m_commonapiConfigFile = commonapi_config_file;
    }
    else
    {
        m_commonapiConfigFile = "../../config/commonapi.ini";
    }

    const char * vsomeip_config_file = getenv("VSOMEIP_CONFIGURATION");

    if( vsomeip_config_file )
    {
        m_vsomeipConfigFile = vsomeip_config_file;
    }
    else
    {
        m_vsomeipConfigFile = "../../config/vsomeip-onboard-provider.json";
    }

}

void OnBoardProvider::provideData(string id, char* value, string name, CDLDataTypes type, string unit, bool valid_state, uint64_t time_stamp, unsigned long dataLength)
{
    LOGD() << "===================================================";
    LOGD() << "Provide Data Name : " << name;

    CDLData cdlData;
    cdlData.id = id;
    cdlData.value = m_onBoardProviderService->getCDLValue(value, type, dataLength);
    cdlData.name = name;
    cdlData.type = type;
    cdlData.unit = unit;
    cdlData.valid_state = valid_state;
    cdlData.time_stamp = time_stamp;

    ClientAPITypes::NotifyType noti_type = m_dataManager->getCDLDataNotifyType(cdlData);

    //data received from collector sends to DataManager to store in data buffer.
    m_onBoardProviderService->provideCDLData(noti_type, cdlData);

}
