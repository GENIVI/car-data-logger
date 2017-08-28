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

#ifndef LOG_H
#define LOG_H

#include <boost/log/trivial.hpp>

#define LOGD()        BOOST_LOG_TRIVIAL(debug)
#define LOGI()        BOOST_LOG_TRIVIAL(info)
#define LOGW()        BOOST_LOG_TRIVIAL(warning)
#define LOGE()        BOOST_LOG_TRIVIAL(error)

void init_log(boost::log::trivial::severity_level logLevel, bool printScope = false);

#endif // LOG_H
