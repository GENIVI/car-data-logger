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

#include "dataconfigparser.h"
#include "../../common/log.h"

DataCollectConfiguration::DataCollectConfiguration()
{
    m_eventDataList.clear();
    m_cycleDataList.clear();
}

DataCollectConfiguration::~DataCollectConfiguration()
{
    CycleDataList::iterator iter = m_cycleDataList.begin();

    while( iter != m_cycleDataList.end() )
    {
        delete iter->second;
        iter++;
    }

    m_cycleDataList.clear();
    m_eventDataList.clear();
}

bool DataCollectConfiguration::read(const string jsonFilePath)
{
    property_tree::ptree jsonDoc;

    try
    {
        property_tree::json_parser::read_json(jsonFilePath, jsonDoc);
    }
    catch(std::exception & e)
    {
        LOGE() << "Failed to read json file ( Error Msg : " << e.what() << " )";

        return false;
    }

    parseCycleData(jsonDoc, "Cycle");
    parseEventData(jsonDoc, "Event");

    return true;
}

void DataCollectConfiguration::parseCycleData(property_tree::ptree & jsonDoc, string objName)
{
    property_tree::ptree & childTree = jsonDoc.get_child(objName);

    if ( childTree.empty() )
    {
        LOGW() << "JSON value(ptree) is empty";
        return;
    }

    LOGD() << "============ < Cycle > ==============";

    BOOST_FOREACH(property_tree::ptree::value_type &value_type, childTree)
    {
        string interval = value_type.first.data();

        CycleDataItem * cycleItem = getCycleDataItem( interval );

        if ( cycleItem != NULL )
        {
            BOOST_FOREACH(property_tree::ptree::value_type &cycleValue, childTree.get_child(interval))
            {
                cycleItem->nameList.push_back( cycleValue.second.data() );

                LOGD() << "Cycle data : " << cycleValue.second.data();
            }
        }
    }
}

void DataCollectConfiguration::parseEventData(property_tree::ptree & jsonDoc, string objName)
{
    property_tree::ptree & childTree = jsonDoc.get_child(objName);

    if ( childTree.empty() )
    {
        LOGW() << "JSON value(ptree) is empty";
        return;
    }

    /* Event Data Case */
    LOGD() << "============ < Event > ==============";

    BOOST_FOREACH(property_tree::ptree::value_type &eventValue, childTree)
    {
        LOGD() << "Event data : " << eventValue.second.data();
        m_eventDataList.push_back(eventValue.second.data());
    }
}

CycleDataItem *DataCollectConfiguration::getCycleDataItem(string interval)
{
    CycleDataItem * cycleItem = NULL;

    CycleDataList::iterator iter = m_cycleDataList.find(interval);

    if ( iter != m_cycleDataList.end() )
    {
        cycleItem = iter->second;
    }
    else
    {
        cycleItem = new CycleDataItem;

        cycleItem->interval = stoi(interval);

        m_cycleDataList.insert(CycleDataList::value_type(interval, cycleItem));
    }

    return cycleItem;
}

EventDataList &DataCollectConfiguration::getEventDataList()
{
    return m_eventDataList;
}

CycleDataList &DataCollectConfiguration::getCycleDataList()
{
    return m_cycleDataList;
}
