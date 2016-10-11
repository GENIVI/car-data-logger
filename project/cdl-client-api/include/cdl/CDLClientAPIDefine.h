/*
 * Copyright (C) 2016, IVIS
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
 * \author Seung-Hyun Yun <shyun@ivisolution.com>
 *
 * \copyright Copyright (c) 2016, IVIS \n
 * License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
 *
 * \file CDLClientAPIDefine.h
*/

#ifndef CDLCLIENTAPIDEFINE
#define CDLCLIENTAPIDEFINE

#include <CommonAPI/CommonAPI.hpp>

#ifndef COMMONAPI_INTERNAL_COMPILATION
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/Variant.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

namespace CDL
{

enum CDLError
{
    CDL_OK,
    CDL_NOOP,
    CDL_NOT_READY,
    CDL_ERROR,
};

enum CDLRuntimeType
{
    RUNTIME_DBUS,
    RUNTIME_SOMEIP,
};

typedef CommonAPI::Variant<bool, int16_t, uint16_t, uint32_t, std::string>  CDLData;
typedef std::function<void(std::string, std::string, std::string, CDLData)> notifyCallback;

}

#endif // CDLCLIENTAPIDEFINE

