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
 * \file DataHandlerFactory.h
*/

#ifndef DATAHANDLERFACTORY_H
#define DATAHANDLERFACTORY_H

#include <CommonAPI/CommonAPI.hpp>
#include <QString>
#include <QMap>

#ifndef DEINITIALIZER
#define DEINITIALIZER(f) \
    static void f(void) __attribute__((destructor)); \
    static void f(void)
#endif

#ifndef INITIALIZER
#define INITIALIZER(f) \
    static void f(void) __attribute__((constructor)); \
    static void f(void)
#endif



#define DECLARE_CALLBACK(NAME, ARGS...) \
    public: \
        typedef std::function<void (ARGS)> NAME##Callback; \
        void set##NAME##Callback (NAME##Callback callback); \
    protected: \
        NAME##Callback m##NAME##Callback

#define IMPLEMENT_CALLBACK(CLASS, NAME) \
    void CLASS::set##NAME##Callback (NAME##Callback callback) \
    { \
        m##NAME##Callback = callback ; \
    }

#define INIT_CALLBACK(NAME) \
    m##NAME##Callback = nullptr;


#define DECLARE_SERVICE_CALLBACK(NAME, ARGS...) \
    void NAME##Callback (ARGS)

#define BIND_CALLBACK(INSTANCE, CLASS, NAME, PLACEHOLDERS...) \
    INSTANCE->set##NAME##Callback( std::bind(&CLASS::NAME##Callback, this, PLACEHOLDERS))

#define IMPLEMENT_SERVICE_CALLBACK(CLASS, NAME, ARGS...) \
    void CLASS::NAME##Callback (ARGS)

#define PLACEHOLDERS(n)  PLACEHOLDER##n

#define PLACEHOLDER1    std::placeholders::_1
#define PLACEHOLDER2    PLACEHOLDER1, std::placeholders::_2
#define PLACEHOLDER3    PLACEHOLDER2, std::placeholders::_3
#define PLACEHOLDER4    PLACEHOLDER3, std::placeholders::_4
#define PLACEHOLDER5    PLACEHOLDER4, std::placeholders::_5
#define PLACEHOLDER6    PLACEHOLDER5, std::placeholders::_6
#define PLACEHOLDER7    PLACEHOLDER6, std::placeholders::_7
#define PLACEHOLDER8    PLACEHOLDER7, std::placeholders::_8
#define PLACEHOLDER9    PLACEHOLDER8, std::placeholders::_9
#define PLACEHOLDER10   PLACEHOLDER9, std::placeholders::_10


class IDataHandler {};

class DataHandlerFactory
{
public:
    typedef std::function<IDataHandler * (void)> CreateDataHandlerFunction;

public:
    static std::shared_ptr<DataHandlerFactory> & instance();

public:
    void setCreateDataHandlerFunction(QString name, CreateDataHandlerFunction callback);

    template<typename T>
    T * createDataHandler(QString name = QString::null);

private:
    IDataHandler * loadLibrary(QString name);

private:
    QMap<QString, CreateDataHandlerFunction> mCreateDataHandlerFunctionList;
};

template<typename T>
T *DataHandlerFactory::createDataHandler(QString name)
{
    typedef typename QMap<QString, CreateDataHandlerFunction>::iterator mapIterator;

    if ( name == QString::null )
    {
        if ( mCreateDataHandlerFunctionList.isEmpty() == false )
        {
            return static_cast<T*>( mCreateDataHandlerFunctionList.first()() );
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        mapIterator iter = mCreateDataHandlerFunctionList.find(name);

        if ( iter != mCreateDataHandlerFunctionList.end() )
        {
            return static_cast<T*>( iter.value()() );
        }
    }

    return static_cast<T*>( loadLibrary(name) );
}

#endif // DATAHANDLERFACTORY_H
