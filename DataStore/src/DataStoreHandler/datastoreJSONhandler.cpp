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

#include "datastoreJSONhandler.h"
#include "filemanager.h"
#include "storagemanager.h"
#include "../../common/log.h"

#include <boost/format.hpp>

#define FOOTER_SEEK_POSITION -2
#define HEADER_STRING_FORMAT "{\n\"VehicleData\":\n[\n"
#define FOOTER_STRING_FORMAT "\n]\n}"

DataStoreJSONHandler::DataStoreJSONHandler(FileManager *fileManager, StorageManager *storageManager)
    :m_fileManager(fileManager), m_storageManager(storageManager), m_latestFileName("")
{

}

DataStoreJSONHandler::~DataStoreJSONHandler()
{

}

void DataStoreJSONHandler::stop()
{
    if( !m_latestFileName.empty() )
    {
        addJSONFooter(m_latestFileName);
        m_fileManager->requestUpdateFileInfo(UpdateFileInfoType::UPDATE_FILE_SAVE_FINISHED, m_latestFileName);
    }
    else
    {
        LOGE() << "Stored file is empty";
    }
}

string DataStoreJSONHandler::convertValueToString(const char *data, CDLDataTypes type)
{
    string convertedValue = "";

    switch ( type )
    {
    case UINT8:
    {
        uint8_t value = 0;
        memcpy(&value, data, sizeof(uint8_t));

        convertedValue = to_string(value);

        break;
    }
    case INT8:
    {
        int8_t value = 0;
        memcpy(&value, data, sizeof(int8_t));

        convertedValue = to_string(value);

        break;
    }
    case UINT16:
    {
        uint16_t value = 0;
        memcpy(&value, data, sizeof(uint16_t));

        convertedValue = to_string(value);

        break;
    }
    case INT16:
    {
        int16_t value = 0;
        memcpy(&value, data, sizeof(int16_t));

        convertedValue = to_string(value);

        break;
    }
    case UINT32:
    {
        uint32_t value = 0;
        memcpy(&value, data, sizeof(uint32_t));

        convertedValue = to_string(value);

        break;
    }
    case INT32:
    {
        int32_t value = 0;
        memcpy(&value, data, sizeof(int32_t));

        convertedValue = to_string(value);

        break;
    }
    case UINT64:
    {
        uint64_t value = 0;
        memcpy(&value, data, sizeof(uint64_t));

        convertedValue = to_string(value);

        break;
    }
    case INT64:
    {
        int64_t value = 0;
        memcpy(&value, data, sizeof(int64_t));

        convertedValue = to_string(value);

        break;
    }
    case BOOLEAN:
    {
        bool value = 0;
        memcpy(&value, data, sizeof(bool));
        convertedValue = to_string(value);

        break;
    }
    case FLOAT:
    {
        float value = 0;
        memcpy(&value, data, sizeof(float));

        convertedValue = to_string(value);

        break;
    }
    case DOUBLE:
    {
        double value = 0;
        memcpy(&value, data, sizeof(double));

        convertedValue = to_string(value);

        break;
    }
    case STRING:
    {
        convertedValue = data;

        break;
    }
    case BYTEBUFFER:
    {
        break;
    }
    default:
    {
        LOGW() << "<< convertToValueString() >> This data is not VSS value type";
        break;
    }
    }

    return convertedValue;
}

void DataStoreJSONHandler::registerCompleteDataStoreCallBack(completeDataStoreCallBack callback)
{
    onCompleteDataStoreCalllback = callback;
}

bool DataStoreJSONHandler::storeData(vector<CDL_DATA> *cdlDataList)
{
    string dataFormat = convertToJSON(cdlDataList);
    m_storageManager->manageStorage(dataFormat.length());

    if( m_latestFileName.empty() )
    {
        if( !createNewFile() )
        {            
            return false;
        }
    }

    if(  m_storageManager->isFileExceedSizeLimit(dataFormat.length(), m_latestFileName) )
    {

        addJSONFooter(m_latestFileName);

        m_fileManager->requestUpdateFileInfo(UpdateFileInfoType::UPDATE_FILE_SAVE_FINISHED, m_latestFileName);

        if( !createNewFile() )
        {
            return false;
        }

        LOGD() << "==================================================================================";
        LOGD() << "File size is not enough to save CDL data";
        LOGD() << "Create New File Name : " << m_latestFileName;
        LOGD() << "==================================================================================";
    }

    if( !writeData(m_latestFileName, dataFormat) )
    {
        LOGE() << "Failed to write vehicle data in JSON file";
        return false;
    }

    LOGD() << "================================================================================";
    LOGD() << "Succeed to save CDL data in JSON file";
    LOGD() << "================================================================================";

    return true;
}

bool DataStoreJSONHandler::writeData(const string filePath, string cdlJSONData)
{
    boost::filesystem::ofstream file;

    if( isFileEmpty(filePath) )
    {
        addJSONHeader(filePath);
    }

    boost::filesystem::path path(filePath);
    file.open(path, ios_base::in | ios_base::out);
    file.seekp(0, ios_base::end);
    if( !file.is_open() )
    {
        LOGE() << "Failed to file open to write data in JSON file";
        return false;
    }

    file.write(cdlJSONData.c_str(), cdlJSONData.length());

    return true;
}


string DataStoreJSONHandler::convertToJSON(vector<CDL_DATA> *cdlDataList)
{
    string jsonDataFormat;
    for( unsigned int index=0; index<cdlDataList->size(); index++ )
    {
        jsonDataFormat.append(boost::str( boost::format( "{\"id\":\"%s\", \"value\":\"%s\", \"name\":\"%s\", \"type\":\"%s\", \"unit\":\"%s\",\"valid_state\":\"%s\", \"time_stamp\":\"%s\"},\n" )
                                          % cdlDataList->at(index).id % cdlDataList->at(index).value % cdlDataList->at(index).name % cdlDataList->at(index).type
                                          % cdlDataList->at(index).unit % cdlDataList->at(index).valid_state % cdlDataList->at(index).time_stamp));
    }

    return jsonDataFormat;
}

bool DataStoreJSONHandler::createNewFile()
{
    boost::filesystem::ofstream file;

    string newFilename = m_fileManager->createNewFileName();
    boost::filesystem::path path(newFilename);

    file.open(path);

    if( !file.is_open() )
    {
        LOGE() << "Failed to create new file ( Failed filename : " << m_latestFileName << " )";
        return false;
    }

    m_latestFileName = newFilename;
    m_fileManager->requestUpdateNewFileCreated(m_latestFileName);

    file.close();

    return true;
}

void DataStoreJSONHandler::addJSONHeader(const string filePath)
{
    boost::filesystem::ofstream file;
    boost::filesystem::path path(filePath);

    string header;

    file.open(path, ios_base::in | ios_base::out);

    header.append(HEADER_STRING_FORMAT);
    file.write(header.c_str(), header.length());

    file.close();
}

void DataStoreJSONHandler::addJSONFooter(const string filePath)
{
    boost::filesystem::ofstream file;
    boost::filesystem::path path(filePath);

    string footer;

    file.open(path, ios_base::in | ios_base::out);

    footer.append(FOOTER_STRING_FORMAT);
    file.seekp(FOOTER_SEEK_POSITION, ios_base::end);
    file.write(footer.c_str(), footer.length());
    file.close();

    //complete data callback
    if( this->onCompleteDataStoreCalllback != NULL )
    {
        this->onCompleteDataStoreCalllback(filePath);
    }
}

bool DataStoreJSONHandler::isFileEmpty(const string filePath)
{
    boost::filesystem::ofstream file;
    boost::filesystem::path path(filePath);

    file.open(path, ios_base::in | ios_base::out);

    if( file.is_open() )
    {
        file.seekp(0, ios_base::end);

        int fileSize = file.tellp();
        file.close();

        if( fileSize == 0 )
        {
            return true;
        }
    }

    return false;
}
