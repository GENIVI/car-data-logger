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

#include "rvi_data_manager.hpp"
#include "compression_handler.hpp"
#include "base64_handler.hpp"
#include "../../../common/log.hpp"
#include "../../../common/data_encryption/data_encryption_handler.hpp"

RVIDataManager::RVIDataManager()
{

}

RVIDataManager::~RVIDataManager()
{

}

string RVIDataManager::encryptProvideData(string filePath, string aes256Key, string aes256IV)
{
    ifstream openFile(filePath.c_str());
    stringstream fileData;

    fileData << openFile.rdbuf();

    /* compressed Data */
    string compress_data = compressData(fileData.str());

    if( compress_data.empty() )
    {
        return "";
    }

    /* Encryption Data & Base 64 Encode */
    string providedData = encryptionData(compress_data, aes256Key, aes256IV);

    if( providedData.empty() )
    {
        return "";
    }

    return providedData;
}

int RVIDataManager::getProvideFileTotalIndex(string &fileData)
{
    int fileDataLen = fileData.length();
    int fileDataTotalIndex = fileDataLen/FILE_DATA_BUF_MAX_LENGTH;

    if( fileDataLen%FILE_DATA_BUF_MAX_LENGTH != 0 )
    {
        fileDataTotalIndex+=1;
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

string RVIDataManager::encryptionData(string data, string aes256Key, string aes256IV)
{
    string encryptedData = AES256_CBC_encrypt_data((byte*)aes256Key.c_str(), (byte*)aes256IV.c_str(), data);

    return encryptedData;
}

string RVIDataManager::compressData(string data)
{
    return compress(data);
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
