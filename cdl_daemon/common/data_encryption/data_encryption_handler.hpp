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

#ifndef ENCRYPTIONDATA_H
#define ENCRYPTIONDATA_H

#include <iostream>

#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/filters.h"
#include "cryptopp/base64.h"

#include "../log.hpp"

std::string AES256_CBC_encrypt_data(byte * key, byte * iv, const std::string & plainText)
{
    std::string cbc_encrypted_data;

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption aes_encrpyt(key, CryptoPP::AES::MAX_KEYLENGTH, iv);

    try
    {
        CryptoPP::StringSource( plainText, true,
                new CryptoPP::StreamTransformationFilter(aes_encrpyt,
                        new CryptoPP::Base64Encoder(
                                new CryptoPP::StringSink(cbc_encrypted_data), false
                                ), CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
                        )
                );
    }
    catch( std::exception &e )
    {
        LOGE() << "Data encrypt Error ( msg : " << e.what() << " )";
    }

    return cbc_encrypted_data;
}

#endif // ENCRYPTIONDATA_H
