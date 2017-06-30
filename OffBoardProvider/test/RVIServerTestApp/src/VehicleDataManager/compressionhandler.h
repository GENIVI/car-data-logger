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

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <string>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/detail/config/zlib.hpp>

std::string compress(std::string data)
{
    std::stringstream compressed;
    std::stringstream decompressed;
    decompressed << data;

    boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
    out.push(boost::iostreams::zlib_compressor());
    out.push(decompressed);

    boost::iostreams::copy(out, compressed);

    return compressed.str();
}

std::string decompress(std::string data)
{
    std::stringstream compressed;
    std::stringstream decompressed;
    compressed << data;

    boost::iostreams::filtering_streambuf<boost::iostreams::input> out;
    out.push(boost::iostreams::zlib_decompressor());
    out.push(compressed);

    boost::iostreams::copy(out, decompressed);

    return decompressed.str();
}

#endif // COMPRESSION_H
