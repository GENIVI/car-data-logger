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

#include "vssitemmanager.h"

VssItemManager::VssItemManager()
{
    m_vssItemList.clear();
}

VssItemManager::~VssItemManager()
{
    VssItemList::iterator iter = m_vssItemList.begin();
    while( iter != m_vssItemList.end() )
    {
        delete iter->second;
        iter++;
    }
    m_vssItemList.clear();
}

void VssItemManager::addVssItem(uint32_t id, VssItem *vssItem)
{
    pair<unordered_map<uint32_t, VssItem*>::iterator, bool> pr;
    pr = m_vssItemList.insert(pair<uint32_t, VssItem*>(id, vssItem));

    if( pr.second )
    {

    }
    else
    {
        BOOST_LOG_TRIVIAL( warning ) << boost::format( "Data is Already Saved" );
    }
}

VssItem *VssItemManager::getVSSItem( uint32_t id )
{
    VssItem * vssItem = NULL;

    VssItemList::iterator iter = m_vssItemList.find(id);

    if( iter != m_vssItemList.end() )
    {
        vssItem = iter->second;
    }
    else
    {
        BOOST_LOG_TRIVIAL( warning ) << boost::format( "<< VssItemManager::getVSSItem >> No Data in vssItemList" );
    }

    return vssItem;
}
