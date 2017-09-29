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

#ifndef DECRYPTIONDATA_H
#define DECRYPTIONDATA_H

#include <iostream>

#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/filters.h"
#include "cryptopp/base64.h"

#include "../log.hpp"

std::string AES256_CBC_decrypt_data(byte * key, byte * iv, const std::string & plainText)
{
    std::string cbc_decrypted_data;

    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption aes_decrpyt(key, CryptoPP::AES::MAX_KEYLENGTH, iv);

    try
    {
        CryptoPP::StringSource( plainText, true,
                new CryptoPP::Base64Decoder(
                        new CryptoPP::StreamTransformationFilter(aes_decrpyt,
                                new CryptoPP::StringSink(cbc_decrypted_data),
                                CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
                                )
                        )
                );
    }
    catch( std::exception &e )
    {

    }

    return cbc_decrypted_data;
}

#endif // DECRYPTIONDATA_H
