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

#ifndef VSSJSONPARSER_H
#define VSSJSONPARSER_H

#include "vssitem.h"
#include "vssitemmanager.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using namespace boost;

/**
 * @brief Parse a VSS JSON file defined infomation of data
 *        and store the results of the parsing in a VSSItem class.
 */

class VssJsonParser
{
public:
    VssJsonParser(VssItemManager *vssItemManager );
    virtual ~VssJsonParser();

public:
    /**
     * @brief Reads and parses the VSS(Vehicle Signal Specification) Json File.
     *
     * @param vssJsonFilePath
     */
    bool read( const string vssJsonFilePath );

private:
    void readVSSJsonFile(const string jsonFilePath, property_tree::ptree &jsonDoc);

    /**
     * @brief Parse a VSS JSON file which is defined data lists(type, ID, unit, min, max, value).
     *
     * @param JsonTree
     * @param VehicleDataSignalPath
     */
    void parseVSSJson(property_tree::ptree & jsonTree, string signalPath);

    string stringSplit(string str, string delimiter);
    string getChildData(string path, property_tree::ptree &jsonTree);

private:
    VssItemManager * m_vssItemManager;
    string m_signalPath;
    int m_keyDepth;

};

#endif // VSSJSONPARSER_H
