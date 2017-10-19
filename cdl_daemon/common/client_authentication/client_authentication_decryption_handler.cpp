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


#include "client_authentication_decryption_handler.hpp"

/***************************
 *
 * | Key Map Table |
 *
 *  ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
 * | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 |
 *  ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
 * | A  | B  |  C |  D |  E |  F |  G |  H |  I |  J |  K |  L |  M |
 *
 *  =================================================================
 *
 * | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35 |
 * ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
 * |  N |  O |  P |  Q |  R |  S |  T |  U |  V |  W |  X |  Y |  Z |
 * ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
 *
 * ex) Public Key  : "PRIVATEKEY"
 *     Private Key :  25 27 18 31 10 29 14 20 14 34
 *
 ****************************/

ClientAuthenticationDecryptionHandler::ClientAuthenticationDecryptionHandler()
{
    m_keyMapTable.clear();
    init();
}

ClientAuthenticationDecryptionHandler::~ClientAuthenticationDecryptionHandler()
{
    m_keyMapTable.clear();
}

void ClientAuthenticationDecryptionHandler::init()
{
    char ch = 'A';
    for( int key = 10; key <= 35; key++ )
    {
        m_keyMapTable.insert( pair<int, char>(key, ch) );

        ch++;
    }
}

string ClientAuthenticationDecryptionHandler::decodePrivateKey(string privateKey)
{
    string decodedKey;
    vector<string> splitPrivateKey;
    map<int, char>::iterator findIter;

    splitPrivateKey = stringSplit(privateKey, " ");
    for( unsigned int i = 0; i < splitPrivateKey.size(); i++ )
    {
        findIter = m_keyMapTable.find( stoi(splitPrivateKey.at(i)) );
        decodedKey.append(std::string(1, (*findIter).second));
    }

    return decodedKey;
}

vector<string> ClientAuthenticationDecryptionHandler::stringSplit(string key, string delimiter)
{
    size_t pos = 0;
    string token;
    vector<string> splitStr;

    while( (pos = key.find(delimiter)) != string::npos )
    {
        token = key.substr(0, pos);
        splitStr.push_back(token);
        key.erase(0, pos+delimiter.length());
    }

    return splitStr;
}
