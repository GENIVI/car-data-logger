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
 * \file PlaybackLogHelper.cpp
*/

#include "PlaybackLogHelper.h"

PlaybackLoghelper::PlaybackLoghelper()
{
}

PlaybackLoghelper::~PlaybackLoghelper()
{
}


void PlaybackLoghelper::ErrorLog(const char *func_info, const char *message)
{
    DLT_LOG( ContextPlayback, DLT_LOG_ERROR, DLT_STRING(func_info), DLT_STRING(message) );
}

void PlaybackLoghelper::WarnLog(const char *func_info, const char *message)
{
    DLT_LOG( ContextPlayback, DLT_LOG_WARN, DLT_STRING(func_info), DLT_STRING(message) );
}

void PlaybackLoghelper::InfoLog(const char *func_info, const char *message)
{
    DLT_LOG( ContextPlayback, DLT_LOG_INFO, DLT_STRING(func_info), DLT_STRING(message) );
}

void PlaybackLoghelper::DebugLog(const char *func_info, const char *message)
{
    DLT_LOG( ContextPlayback, DLT_LOG_DEBUG, DLT_STRING(func_info), DLT_STRING(message) );
}


void PlaybackLoghelper::ErrorLog(const char *func_info, QString message)
{
    ErrorLog(func_info, message.toLocal8Bit().data());
}

void PlaybackLoghelper::WarnLog(const char *func_info, QString message)
{
    WarnLog(func_info, message.toLocal8Bit().data());
}

void PlaybackLoghelper::InfoLog(const char *func_info, QString message)
{
    InfoLog(func_info, message.toLocal8Bit().data());
}

void PlaybackLoghelper::DebugLog(const char *func_info, QString message)
{
    DebugLog(func_info, message.toLocal8Bit().data());
}
