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
 * \file LogHelper.h
*/

#ifndef LOGHELPER
#define LOGHELPER

#include <dlt.h>
#include <QElapsedTimer>

DLT_IMPORT_CONTEXT( ContextModeManager )

class LogHelper
{
public:
    QString function;
    QElapsedTimer elapsedTimer;
    LogHelper( QString _function ):function( _function )
    {
        DLT_LOG( ContextModeManager, DLT_LOG_INFO , DLT_STRING( QString( "-> %1" ).arg( function ).toLocal8Bit().data() ) );
        elapsedTimer.start();
    }
    ~LogHelper()
    {
        DLT_LOG( ContextModeManager, DLT_LOG_INFO , DLT_STRING( QString( "\t elapsed time : %1 msec" ).arg( elapsedTimer.elapsed() ).toLocal8Bit().data() ) );
        DLT_LOG( ContextModeManager, DLT_LOG_INFO , DLT_STRING( QString( "<- %1" ).arg( function ).toLocal8Bit().data() ) );
    }
    void print( QString text, DltLogLevelType level=DLT_LOG_INFO )
    {
        DLT_LOG( ContextModeManager, level , DLT_STRING( QString( "\t %1" ).arg( text ).toLocal8Bit().data() ) );
    }
};


#endif // LOGHELPER

