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


#ifndef CLIENTAUTHENTICATIONENCRYPTIONHANDLER_H
#define CLIENTAUTHENTICATIONENCRYPTIONHANDLER_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

class ClientAuthenticationEncryptionHandler
{
public:
    ClientAuthenticationEncryptionHandler();
    virtual ~ClientAuthenticationEncryptionHandler();

private:
    void init();

public:
    virtual string createPrivateKey(string publicKey);  //encryptionPublicKey

private:
    map<char, int> m_keyMapTable;
};

#endif // CLIENTAUTHENTICATIONENCRYPTIONHANDLER_H
