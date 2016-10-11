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
 * \file PlaybackLogHelper.h
*/

#ifndef PLAYBACKLOGHELPER_H
#define PLAYBACKLOGHELPER_H

#include <QString>

#include <dlt.h>
DLT_IMPORT_CONTEXT(ContextPlayback) /*!< TODO: describe */

#define FUNC_INFO()      LOG_DEBUG("")

#define LOG_ERROR(msg)   {PlaybackLoghelper::ErrorLog(Q_FUNC_INFO, msg);}
#define LOG_WARN(msg)    {PlaybackLoghelper::WarnLog(Q_FUNC_INFO, msg);}
#define LOG_INFO(msg)    {PlaybackLoghelper::InfoLog(Q_FUNC_INFO, msg);}
#define LOG_DEBUG(msg)   {PlaybackLoghelper::DebugLog(Q_FUNC_INFO, msg);}

/*!
 \brief

 \class PlaybackLoghelper playbackloghelper.h "playbackloghelper.h"
*/
class PlaybackLoghelper
{
public:
    /*!
     \brief

     \fn PlaybackLoghelper
    */
    PlaybackLoghelper();
    /*!
     \brief

     \fn ~PlaybackLoghelper
    */
    ~PlaybackLoghelper();

public:
    /*!
     \brief

     \fn ErrorLog
     \param func_info
     \param message
    */
    static void ErrorLog(const char *func_info, const char *message);
    /*!
     \brief

     \fn WarnLog
     \param func_info
     \param message
    */
    static void WarnLog(const char *func_info, const char *message);
    /*!
     \brief

     \fn InfoLog
     \param func_info
     \param message
    */
    static void InfoLog(const char *func_info, const char *message);
    /*!
     \brief

     \fn DebugLog
     \param func_info
     \param message
    */
    static void DebugLog(const char *func_info, const char *message);

    /*!
     \brief

     \fn ErrorLog
     \param func_info
     \param message
    */
    static void ErrorLog(const char *func_info, QString message);
    /*!
     \brief

     \fn WarnLog
     \param func_info
     \param message
    */
    static void WarnLog(const char *func_info, QString message);
    /*!
     \brief

     \fn InfoLog
     \param func_info
     \param message
    */
    static void InfoLog(const char *func_info, QString message);
    /*!
     \brief

     \fn DebugLog
     \param func_info
     \param message
    */
    static void DebugLog(const char *func_info, QString message);
};

#endif // PLAYBACKLOGHELPER_H
