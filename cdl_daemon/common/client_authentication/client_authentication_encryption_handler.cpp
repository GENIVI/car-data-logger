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


#include "client_authentication_encryption_handler.hpp"

/***************************
 *
 * | Key Map Table |
 *
 *  ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
 * | A  | B  |  C |  D |  E |  F |  G |  H |  I |  J |  K |  L |  M |
 *  ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
 * | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 |
 *
 *  =================================================================
 *
 * |  N |  O |  P |  Q |  R |  S |  T |  U |  V |  W |  X |  Y |  Z |
 * ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
 * | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35 |
 * ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
 *
 * ex) Public Key  : "PRIVATEKEY"
 *     Private Key :  25 27 18 31 10 29 14 20 14 34
 *
 ****************************/

ClientAuthenticationEncryptionHandler::ClientAuthenticationEncryptionHandler()
{
    m_keyMapTable.clear();
    init();
}

ClientAuthenticationEncryptionHandler::~ClientAuthenticationEncryptionHandler()
{
    m_keyMapTable.clear();
}

void ClientAuthenticationEncryptionHandler::init()
{
    // A  ~ Z
    // 65 ~ 90
    int value = 10;

    for( int i = 65; i <= 90; i++ )
    {
        char ch = i;
        m_keyMapTable.insert(pair<char, int>(ch, value));

        value++;
    }
}

string ClientAuthenticationEncryptionHandler::createPrivateKey(string publicKey)
{
    string privateKey;
    map<char, int>::iterator findIter;

    for( unsigned int i=0; i<publicKey.length(); i++ )
    {
        findIter = m_keyMapTable.find( publicKey.at(i) );
        privateKey.append( std::to_string((*findIter).second) );

        if( i != publicKey.length() )
        {
            privateKey.append(" ");
        }
    }

    cout<<"public Key : "<<publicKey<<" / privateKey : "<<privateKey<<endl;

    return privateKey;
}
