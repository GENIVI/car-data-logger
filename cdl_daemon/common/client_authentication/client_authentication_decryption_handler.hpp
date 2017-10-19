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


#ifndef CLIENTAUTHENTICATIONDECRYPTIONHANDLER_H
#define CLIENTAUTHENTICATIONDECRYPTIONHANDLER_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class ClientAuthenticationDecryptionHandler
{
public:
    ClientAuthenticationDecryptionHandler();
    virtual ~ClientAuthenticationDecryptionHandler();

private:
    void init();
    vector<string> stringSplit(string key, string delimiter);

public:
    virtual string decodePrivateKey(string privateKey);

private:
    map<int, char> m_keyMapTable;
};

#endif // CLIENTAUTHENTICATIONDECRYPTIONHANDLER_H
