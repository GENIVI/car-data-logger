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

#ifndef RVIDATAMANAGER_H
#define RVIDATAMANAGER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define FILE_DATA_BUF_MAX_LENGTH 512

class RVIDataManager
{
public:
    RVIDataManager();
    virtual ~RVIDataManager();

public:
    string encryptProvideData(string filePath, string aes256Key, string aes256IV);
    int getProvideFileTotalIndex(string &fileData);
    vector<string> getDivideFileData(string fileData, int provideFileTotalIndex);
    string getFileName(string filePath);    

private:
    string encryptionData(string data, string aes256Key, string aes256IV);
    string compressData(string data);
    string stringSplit(string str, string delimiter);
};

#endif // RVIDATAMANAGER_H
