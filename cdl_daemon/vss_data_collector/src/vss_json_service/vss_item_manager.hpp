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

#ifndef VSSITEMMANAGER_H
#define VSSITEMMANAGER_H

#include "vss_item.hpp"

typedef unordered_map<uint32_t, VssItem*> VssItemList;

/**
 *
 * @brief Adds and provides the VSSItem class in which VSS data is stored.
 *
 */

class VssItemManager
{
public:
    VssItemManager();
    virtual ~VssItemManager();
    void init();

public:
    void addVssItem(uint32_t id, VssItem* vssItem);
    VssItem * getVSSItem(uint32_t id);

private:
    VssItemList m_vssItemList;
};

#endif // VSSITEMMANAGER_H
