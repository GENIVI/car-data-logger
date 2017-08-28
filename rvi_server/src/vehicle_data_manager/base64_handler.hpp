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

#ifndef ENCRYPTIONHANDLER_H
#define ENCRYPTIONHANDLER_H

#include <string>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>

typedef boost::archive::iterators::base64_from_binary<
          boost::archive::iterators::transform_width< std::string::const_iterator, 6, 8>
> base64_encode;

typedef boost::archive::iterators::transform_width<
    boost::archive::iterators::binary_from_base64< std::string::const_iterator >, 8, 6
> base64_decode;

#endif // ENCRYPTIONHANDLER_H
