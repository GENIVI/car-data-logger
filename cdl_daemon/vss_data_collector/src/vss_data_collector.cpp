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

#include "vss_data_collector.hpp"
#include "data_config_service/data_config_parser.hpp"
#include "vss_json_service/vss_json_parser.hpp"
#include "vsi_watcher/vsi_watcher.hpp"
#include "../../common/log.hpp"


VSSDataCollector::VSSDataCollector()
    :m_vssJsonParser(NULL), m_dataConfigParser(NULL), m_vssItemManager(NULL)
    ,m_nameToIdConvertor(NULL), m_vsiWatcher(NULL)
    ,m_vssJsonFile(""), m_configJsonFile(""), m_vsiFile("")
{
    m_vssItemManager = new VssItemManager();
    m_dataConfigParser = new DataCollectConfiguration();
    m_vssJsonParser = new VssJsonParser(m_vssItemManager);
    m_nameToIdConvertor = new NameToIdConvertor();
    m_vsiWatcher = new VSIWatcher(m_vssItemManager, m_dataConfigParser, m_nameToIdConvertor);
}

VSSDataCollector::~VSSDataCollector()
{

}

void VSSDataCollector::setConfigurationFiles()
{
    const char * vss_json_file = getenv("VSS_JSON_FILE");

    if ( vss_json_file )
    {
        m_vssJsonFile = vss_json_file;
    }
    else
    {
        m_vssJsonFile = "./vss_rel_1.json";
    }

    const char * data_configuration = getenv("VSS_COLLECTOR_CONFIGURATION_FILE");

    if ( data_configuration )
    {
        m_configJsonFile = data_configuration;
    }
    else
    {
        m_configJsonFile = "./data_config.json";
    }

    const char * vsi_file = getenv("VSS_VSI_FILE");

    if ( vsi_file )
    {
        m_vsiFile = vsi_file;
    }
    else
    {
        m_vsiFile = "./vss_rel_1.vsi";
    }
}

bool VSSDataCollector::start()
{
    setConfigurationFiles();

    if( m_nameToIdConvertor == NULL || !(m_nameToIdConvertor->read(m_vsiFile)) )
    {
        return false;
    }

    if( m_vssJsonParser == NULL || !(m_vssJsonParser->read(m_vssJsonFile)) )
    {
        return false;
    }

    if( m_dataConfigParser == NULL || !(m_dataConfigParser->read(m_configJsonFile)) )
    {
        return false;
    }

    if( m_vsiWatcher==NULL || !(m_vsiWatcher->init()) )
    {
        return false;
    }

    LOGD() << "Succeed to create VSSDataCollector";

    return true;
}

void VSSDataCollector::stop()
{
    if ( m_vsiWatcher != NULL )
    {
        delete m_vsiWatcher;
        m_vsiWatcher = NULL;
    }

    if ( m_nameToIdConvertor != NULL )
    {
        delete m_nameToIdConvertor;
        m_nameToIdConvertor = NULL;
    }

    if ( m_dataConfigParser != NULL )
    {
        delete m_dataConfigParser;
        m_dataConfigParser = NULL;
    }

    if ( m_vssJsonParser != NULL )
    {
        delete m_vssJsonParser;
        m_vssJsonParser = NULL;
    }

    if ( m_vssItemManager != NULL )
    {
        delete m_vssItemManager;
        m_vssItemManager = NULL;
    }
}

void VSSDataCollector::registerCollectDataCallback(cdlDaemonCallBack callback)
{
    m_vsiWatcher->registerCDLDaemonCallBack(callback);
}
