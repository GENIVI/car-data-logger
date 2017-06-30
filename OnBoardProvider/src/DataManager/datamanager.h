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

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "onboardproviderservice.h"

#include <vector>
#include <map>

/**
 * @brief Manage the latest vehicle data in container reveiced from the collector in the container.
 *
 * This class notifies the OnBoardProviderService of the data type( update, change ) or gets the data when the clients needs.
 *
 */

typedef OnBoardProviderService::CDL_DATA CDLData;

class DataManager
{
public:
    DataManager();
    virtual ~DataManager();

public:
    ClientAPITypes::NotifyType getCDLDataNotifyType(CDLData & data);
    CDLData getCDLData(string name);

private:
    map<string, CDLData> m_cdlDataBuffer;

    boost::mutex m_cdlDataMutex;
};

#endif // DATAMANAGER_H
