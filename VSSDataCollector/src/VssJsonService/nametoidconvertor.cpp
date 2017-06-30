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

#include "nametoidconvertor.h"
#include "../../common/log.h"

NameToIdConvertor::NameToIdConvertor()
{
    m_nameToIdList.clear();
}

NameToIdConvertor::~NameToIdConvertor()
{

}

bool NameToIdConvertor::read(string vsiFilePath)
{
    ifstream file;

    file.open(vsiFilePath);

    if( !file.is_open() )
    {
        LOGE() << "<< openVSIFile() >> Fail to Open SignalPath To ID Definition Json File";
        return false;
    }

    parseVSIFile(file);

    return true;
}

int NameToIdConvertor::convertToID( string name )
{
    int id = NameToIdConvertor::INVALID_ID;

    auto convertID = m_nameToIdList.find(name);

    if(convertID != m_nameToIdList.end())
    {
        id=convertID->second;
        LOGD() << "Succeed to convert Name to ID ( name : " << name << " / id : " << id;
    }
    else
    {
        LOGE() << "Failed to convert Name to ID ( name : " << name << " / id : " << id;
    }

    return id;
}

void NameToIdConvertor::parseVSIFile( ifstream & file )
{
    string readFileStr;
    vector<string> resultStr;

    while( getline( file, readFileStr ) )
    {
        resultStr = stringSplit( readFileStr, " " );

        if( !resultStr.at(0).compare("#") || resultStr.empty() )
        {
            continue;
        }

        m_nameToIdList.insert( NameToIdList::value_type(resultStr.at(SPLIT_SIGNAL_PATH), stoi(resultStr.at(SPLIT_SIGNAL_ID))) );
    }
}

vector<string> NameToIdConvertor::stringSplit( string name, string delimiter )
{
    size_t pos=0;
    string preToken;
    string postToken;
    vector<string> splitStr;

    pos=name.find(delimiter);

    if( pos != 0 )
    {
        preToken=name.substr(0, pos);
        postToken=name.erase(0, pos+delimiter.length());

        splitStr.push_back(preToken);
        splitStr.push_back(postToken);
    }

    return splitStr;
}
