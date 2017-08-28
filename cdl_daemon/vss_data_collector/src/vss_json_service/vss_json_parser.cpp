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

#include "vss_json_parser.hpp"
#include "../../common/log.hpp"

VssJsonParser::VssJsonParser(VssItemManager *vssItemManager)
    : m_vssItemManager(vssItemManager), m_signalPath(""), m_keyDepth(0)
{

}

VssJsonParser::~VssJsonParser()
{

}

bool VssJsonParser::read( const string vssJsonFilePath )
{
    property_tree::ptree jsonDoc;

    readVSSJsonFile(vssJsonFilePath, jsonDoc);

    boost::property_tree::ptree & attribute = jsonDoc.get_child("Attribute");
    if(!attribute.empty())
    {
        parseVSSJson(attribute, m_signalPath);
    }
    else
    {
        LOGE() << "Attribute object JSON ptree is empty";
        return false;
    }

    boost::property_tree::ptree & signal = jsonDoc.get_child("Signal");
    if(!signal.empty())
    {
        parseVSSJson(signal, m_signalPath);
    }
    else
    {
        LOGE() << "Signal object JSON ptree is empty";
        return false;
    }

    return true;
}

void VssJsonParser::readVSSJsonFile( const string vssJsonFilePath, property_tree::ptree & jsonDoc )
{
    try
    {
        property_tree::read_json(vssJsonFilePath, jsonDoc);
    }
    catch(std::exception & e)
    {
        LOGE() << "Failed to read JSON ( " << e.what() << " )";
    }
}

void VssJsonParser::parseVSSJson(property_tree::ptree &jsonTree, string signalPath)
{
    auto child = jsonTree.find("children");

    if ( child != jsonTree.not_found() )        //children exists
    {
        string childrenPath("children");

        BOOST_FOREACH(property_tree::ptree::value_type& value_type, jsonTree.get_child(childrenPath))
        {
            string key = value_type.first.data();

            boost::property_tree::ptree& childrenKey = jsonTree.get_child(childrenPath+"."+key);

            if(signalPath == "")
            {
                signalPath.append(key);
            }
            else
            {
                signalPath.append("."+key);
            }

            m_keyDepth++;
            parseVSSJson(childrenKey, signalPath);
            m_keyDepth--;

            if(m_keyDepth==0)
            {
                signalPath = "";
            }
            else
            {
                signalPath = stringSplit(signalPath, "."+key);
            }

        }
    }
    else                                        //No children
    {
        /* Get Data From Json File */
        string type = getChildData("type", jsonTree);
        string unit = getChildData("unit", jsonTree);
        string id = getChildData("id", jsonTree);
        string min = getChildData("min", jsonTree);
        string max = getChildData("max", jsonTree);
        string defaultValue = getChildData("defaultValue", jsonTree);
        string value = getChildData("value", jsonTree);

        /* get enum Data (Array Format) */
        auto child = jsonTree.find("enum");
        vector<string> vssEnumValueList;
        if( child != jsonTree.not_found() )
        {
            BOOST_FOREACH(property_tree::ptree::value_type& enumValue, jsonTree.get_child("enum"))
            {
                vssEnumValueList.push_back(enumValue.second.data());
            }
        }

        /* Create VssItem to save Vehicle Data in Json */
        VssItem * vssItem = new VssItem();

        if(type != "")              vssItem->setType(type);
        if(unit != "")              vssItem->setUnit(unit);
        if(id != "")                vssItem->setID(id);
        if(min != "")               vssItem->setMinValue(min);
        if(max != "")               vssItem->setMaxValue(max);
        if(defaultValue != "")      vssItem->setDefaultValue(defaultValue);
        if(value != "")             vssItem->setValue(value);
        if(signalPath != "")        vssItem->setName(signalPath);
        if(!vssEnumValueList.empty())   vssItem->setVssEnumValueList(vssEnumValueList);

        /* Set Data in Map Value*/
        if(m_vssItemManager!=NULL)
        {
            m_vssItemManager->addVssItem(vssItem->getID(), vssItem);
        }
    }
}

string VssJsonParser::stringSplit(string str, string delimiter)
{
    size_t pos = 0;
    string token;
    string strResult;

    while((pos = str.find(delimiter)) != string::npos){
        token = str.substr(0, pos);
        strResult.append(token);
        str.erase(0, pos+delimiter.length());
    }
    strResult.append(str);

    return strResult;
}

string VssJsonParser::getChildData(string path, property_tree::ptree &jsonTree)
{
    auto child = jsonTree.find(path);

    if(child == jsonTree.not_found())
    {
        return "";
    }

    property_tree::ptree::iterator iter = jsonTree.to_iterator(child);
    string value(iter->second.data());

    return value;
}
