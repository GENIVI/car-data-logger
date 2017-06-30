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

#ifndef VSSDATACOLLECTOR_H
#define VSSDATACOLLECTOR_H

#include <string>
#include <functional>

#include "../../common/cdlcommondefine.h"

using namespace std;

/**
 *
 * @brief Provide start and stop function as a main class.
 *
 * This class is executed by calling the 'start' function in another process.
 * When the main process is terminated, the 'stop' function should be called
 * so that it can be terminated normally.
 *
 */

class VssJsonParser;
class DataCollectConfiguration;
class VssItemManager;
class NameToIdConvertor;
class VSIWatcher;

typedef std::function<void(string, char*, string, CDLDataTypes, string, bool, uint64_t, unsigned long)> cdlDaemonCallBack;

class VSSDataCollector
{
public:
    VSSDataCollector();
    virtual ~VSSDataCollector();

public:
    /**
     * @brief Start VSS data collector.
     *
     */
    virtual bool start();

    /**
     * @brief Stop VSS data collector.
     *
     */
    virtual void stop();

    /**
     * @brief Register to collector.
     *
     */
    virtual void registerCollectDataCallback(cdlDaemonCallBack callback);

private:
    void setConfigurationFiles();

private:
    VssJsonParser * m_vssJsonParser;
    DataCollectConfiguration * m_dataConfigParser;
    VssItemManager * m_vssItemManager;
    NameToIdConvertor * m_nameToIdConvertor;
    VSIWatcher * m_vsiWatcher;

    string m_vssJsonFile;
    string m_configJsonFile;
    string m_vsiFile;
};

#endif // VSSDATACOLLECTOR_H
