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
 * \file DataHandlerFactory.cpp
*/

#include "DataHandlerFactory.h"
#include <QDebug>
#include <dlfcn.h>
#include <unistd.h>

std::shared_ptr<DataHandlerFactory> & DataHandlerFactory::instance()
{
    static std::shared_ptr<DataHandlerFactory> g_data_handler_factory = Q_NULLPTR;

    if ( g_data_handler_factory == Q_NULLPTR )
    {
        g_data_handler_factory = std::make_shared<DataHandlerFactory>();
    }

    return g_data_handler_factory;
}

void DataHandlerFactory::setCreateDataHandlerFunction(QString name, CreateDataHandlerFunction callback)
{
    mCreateDataHandlerFunctionList.insert(name, callback);
}

IDataHandler *DataHandlerFactory::loadLibrary(QString name)
{
    QString libraryName = "lib";
    libraryName += name;
    libraryName += "Data.so";

    if ( dlopen(libraryName.toStdString().data(), RTLD_LAZY | RTLD_GLOBAL) != 0 )
    {
        qDebug() << "library open success => " << name;

        QMap<QString, CreateDataHandlerFunction>::iterator iter = mCreateDataHandlerFunctionList.find(name);

        if ( iter != mCreateDataHandlerFunctionList.end() )
        {
            return iter.value()();
        }
    }
    else
    {
        qDebug() << "library open failed " << name << ", error = " << dlerror();
    }

    return nullptr;
}
