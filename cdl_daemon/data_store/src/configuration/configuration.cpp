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

#include "configuration.hpp"
#include "../../common/log.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

DataStoreConfiguration::DataStoreConfiguration()
    :m_dataStoreLocation(""), m_maxFileSize(0), m_maxStorageSize(0)
    ,m_fileExpirePeriod(0), m_transactionBufferSize(0)
{

}

DataStoreConfiguration::~DataStoreConfiguration()
{

}

bool DataStoreConfiguration::read(const string jsonFilePath)
{
    property_tree::ptree jsonDoc;

    try
    {
        property_tree::json_parser::read_json(jsonFilePath, jsonDoc);
    }
    catch(std::exception & e)
    {
        LOGE() << "Failed to read JSON file : " << e.what();

        return false;
    }

    if( !parseStoreConfigFile(jsonDoc) )
    {
        return false;
    }

    return true;
}

string DataStoreConfiguration::getDataStoreLocation()
{
    return m_dataStoreLocation;
}

int DataStoreConfiguration::getMaxFileSize()
{
    return m_maxFileSize;
}

int DataStoreConfiguration::getMaxStorageSize()
{
    return m_maxStorageSize;
}

int DataStoreConfiguration::getFileExpirePeriod()
{
    return m_fileExpirePeriod;
}

int DataStoreConfiguration::getTransactionBufferSize()
{
    return m_transactionBufferSize;
}

bool DataStoreConfiguration::parseStoreConfigFile(property_tree::ptree &jsonDoc)
{
    if( jsonDoc.empty() )
    {
        LOGE() << "JSON file is empty";
        return false;
    }

    BOOST_FOREACH( property_tree::ptree::value_type & value_type, jsonDoc )
    {
        string objName = value_type.first.data();

        if( !objName.compare("DataStoreLocation") )
        {
            m_dataStoreLocation = value_type.second.data();
            checkDataStoreLocation();
        }
        else if( !objName.compare("MaxFileSize") )
        {
            m_maxFileSize = stoi(value_type.second.data());
        }
        else if( !objName.compare("MaxStorageSize") )
        {
            m_maxStorageSize = stoi(value_type.second.data());
        }
        else if( !objName.compare("MaxFileExpirePeriod") )
        {
            m_fileExpirePeriod = stoi(value_type.second.data());
        }
        else if( !objName.compare("TransactionBufferSize") )
        {
            m_transactionBufferSize = stoi(value_type.second.data());
        }
        else
        {
            LOGW() << "No configuration list in JSON file : " << objName;
        }
    }

    if( !checkConfigInfo() )
    {
        return false;
    }

    return true;
}

bool DataStoreConfiguration::checkConfigInfo()
{
    if( m_dataStoreLocation.empty() )
    {
        LOGE() << "Invalid DataStoreLocation Path ( " << m_dataStoreLocation << " )";
        return false;
    }

    if( m_maxFileSize <= 0 )
    {
        LOGE() << "Invalid MaxFileSize Value ( " << m_maxFileSize << " )";
        return false;
    }

    if( m_maxStorageSize <= 0 )
    {
        LOGE() << "Invalid MaxStorageSize Value ( " << m_maxStorageSize << " )";
        return false;
    }

    if( m_fileExpirePeriod <= 0 )
    {
        LOGE() << "Invalid FileExpirePeriod Value ( " << m_fileExpirePeriod << " )";
        return false;
    }

    if( m_transactionBufferSize <= 0 )
    {
        LOGE() << "Invalid TransactionBufferSize Value ( " << m_transactionBufferSize << " )";
        return false;
    }

    return true;
}

void DataStoreConfiguration::checkDataStoreLocation()
{
    string checkDataStoreLocation;

    checkDataStoreLocation.push_back(m_dataStoreLocation.back());

    if( checkDataStoreLocation.compare("/") )
    {
        m_dataStoreLocation.append("/");
    }
}
