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

#ifndef DATACONFIGPARSER_H
#define DATACONFIGPARSER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
using namespace boost;

struct CycleDataItem
{
    int interval;
    vector<string> nameList;
};

typedef unordered_map<string, CycleDataItem*> CycleDataList;
typedef vector<string> EventDataList;

/**
 * @brief Parse a configuration JSON file defined cycle and event type data
 *        and store the results of the parsing in a container.
 *
 * [Cycle Data] : Get data by polling every cycle with VSI API.
 * [Event Data] : Get data when vehicle data is received.
 *
 */

class DataCollectConfiguration
{
public:
    DataCollectConfiguration();
    virtual ~DataCollectConfiguration();

public:
    /**
     * @brief Reads and parses the Data Configuration JSON file.
     *
     * @param jsonFilePath
     *
     * @return Results of reading and parsing.
     */
    bool read(const string jsonFilePath);
    EventDataList & getEventDataList();
    CycleDataList & getCycleDataList();

private:
    /**
     * @brief Parse a JSON file which is defined the cycle and event data lists.
     *
     * @param jsonDoc
     * @param jsonObjName
     */
    void parseCycleData(property_tree::ptree &jsonDoc, string objName);
    void parseEventData(property_tree::ptree &jsonDoc, string objName);

    CycleDataItem * getCycleDataItem(string interval);

private:
    CycleDataList m_cycleDataList;
    EventDataList m_eventDataList;
};

#endif // DATACONFIGPARSER_H
