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

#include "RVIDataManager.h"
#include "compressionhandler.h"
#include "Base64Handler.h"
#include "../../../common/log.h"

RVIDataManager::RVIDataManager()
{

}

RVIDataManager::~RVIDataManager()
{

}

string RVIDataManager::prepareProvideData(string filePath)
{
    ifstream openFile(filePath.c_str());
    stringstream fileStr;

    fileStr << openFile.rdbuf();

    /* compressed Data */
    string compress_data = compressData(fileStr.str());

    /* Encoded Data */
    string encode_data = encodeData(compress_data);

    return encode_data;

}

int RVIDataManager::getProvideFileTotalIndex(string &fileData)
{
    int fileDataLen = fileData.length();
    int fileDataTotalIndex = fileDataLen / FILE_DATA_BUF_MAX_LENGTH;

    if( fileDataLen % FILE_DATA_BUF_MAX_LENGTH != 0 )
    {
        fileDataTotalIndex++;
    }

    return fileDataTotalIndex;
}

vector<string> RVIDataManager::getDivideFileData(string fileData, int provideFileTotalIndex)
{
    vector<string> divideFileData;

    divideFileData.clear();

    if( !fileData.empty() )
    {
        for( int i=0; i<provideFileTotalIndex; i++ )
        {
            string subFileData;

            subFileData = fileData.substr(0, FILE_DATA_BUF_MAX_LENGTH);
            divideFileData.push_back(subFileData);

            if( !subFileData.empty() )
            {
                fileData.erase(0, FILE_DATA_BUF_MAX_LENGTH);
            }
        }
    }
    else
    {
        LOGE() << "No Data in JSON File";
    }

    return divideFileData;
}

string RVIDataManager::getFileName(string filePath)
{
    return stringSplit(filePath, "/");
}

string RVIDataManager::compressData(string data)
{
    return compress(data);
}

string RVIDataManager::encodeData(string data)
{
    string base64EncodeStr( base64_encode(data.begin()), base64_encode(data.end()));

    return base64EncodeStr;
}

string RVIDataManager::stringSplit(string str, string delimiter)
{
    size_t pos = 0;
    string token;
    string strResult;

    while((pos = str.find(delimiter)) != string::npos){
        token = str.substr(0, pos);
        str.erase(0, pos+delimiter.length());
    }
    strResult.append(str);

    return strResult;
}
