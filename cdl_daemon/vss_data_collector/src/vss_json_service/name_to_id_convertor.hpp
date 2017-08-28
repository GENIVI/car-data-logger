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

#ifndef NAMETOIDCONVERTOR_H
#define NAMETOIDCONVERTOR_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

/**
 *
 * @brief Parse the list(signal path, ID) defined in the vsi file and
 *        store the results in the container. Provides a function that
 *        converts signalpath to ID.
 */

class NameToIdConvertor
{
public:
    static const unsigned int INVALID_ID = -1;

    enum _SPLIT_STRING_TYPE
    {
        SPLIT_SIGNAL_PATH=0,
        SPLIT_SIGNAL_ID,

        SPLIT_SIGNAL_MAX
    };

    typedef unordered_map<string, int> NameToIdList;

public:
    NameToIdConvertor();
    virtual ~NameToIdConvertor();

public:
    /**
     * @brief Read the file in vsi format, defined by the vehicle data signal and integer ID.
     *
     */
    bool read(string vsiFilePath);

    /**
     * @brief Convert the vehicle data signal to a defined integer ID.
     *
     * @param vehicleDataFSignalFullPath
     */
    int convertToID(string name);

private:
    /**
     * @brief Parses the file and stores the vehicle data signal and integer ID in the container(hash).
     *
     */
    void parseVSIFile(ifstream &file);
    vector<string> stringSplit(string name, string delimiter);

private:
    NameToIdList m_nameToIdList;
};

#endif // NAMETOIDCONVERTOR_H
