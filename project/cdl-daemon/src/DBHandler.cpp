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
 * \file DBHandler.cpp
*/

#include "DBHandler.h"
#include <QSqlQuery>
#include <QVectorIterator>
#include <QVariant>
#include <QDateTime>
#include <QSqlError>

#include <QTimer>

DBHandler * gDBHandler = nullptr;

int DBHandler::dbConnectionCount = 0;
const QString DBHandler::kDATABASE_DRIVER = "QSQLITE"; // means QSQLITE3
const QString DBHandler::kDOMAIN_DATABASE_VEHICLE_DATA = "vehicleData"; // domain name
const QString DBHandler::kFILE_NAME_EXTENSION_MARK = ".db";
const QString DBHandler::kDEFAULT_REQUESTER = "SOME_IP_VEHICLE_DATA";

int DLT_Callback_DBHandler( u_int32_t serviceId, void *data, u_int32_t length );


DBHandler *DBHandler::instance()
{
    if( gDBHandler == nullptr )
        gDBHandler = new DBHandler();

    return gDBHandler;
}

void DBHandler::finalize()
{
    if ( gDBHandler != nullptr )
    {
        delete gDBHandler;
        gDBHandler = nullptr;
    }
}


DBHandler::DBHandler(QObject *parent) // private. singleton pattern
    : QObject(parent),
      m_databaseInfoList(QVector<databaseInfo_t>())
{
    DLT_REGISTER_CONTEXT(mDBHandleContext, "dbhc", "Database Handle Context");
    DLT_REGISTER_INJECTION_CALLBACK( mDBHandleContext, 0xfff, DLT_Callback_DBHandler );
    DLT_LOG( mDBHandleContext, DLT_LOG_INFO, DLT_STRING( "DB Handler Constructor" ));

    init();
}


DBHandler::~DBHandler()
{
    DLT_UNREGISTER_CONTEXT(mDBHandleContext);
#ifdef __CDL_GUI_MODE__
    AbstractCDLViewerDataModel::finalize();
#endif
}


void DBHandler::flushCallBackDelegate(std::string _domain)
{
    DLT_LOG( mDBHandleContext, DLT_LOG_INFO, DLT_STRING( "transaction delegate, domain : " ), DLT_STRING( QString::fromStdString( _domain ).toLocal8Bit().data() ) );
    flushInstantly( _domain );
}


void DBHandler::init()
{
#ifdef __CDL_GUI_MODE__
    connect( this, SIGNAL(signalSetTableData(QString,QString,QString,QString,QString,QString,QString)),
             this, SLOT(setTableData(QString,QString,QString,QString,QString,QString,QString)));
#endif
}


void DBHandler::storeData(std::string _domain, std::string _subDomain, std::string _id, ClientAPIRemoteTypes::CDLData _data)
{
    QString _qDomain = QString::fromStdString( _domain );
    QString _qSubDomain = QString::fromStdString( _subDomain );


    int _dbIdx = findDatabaseInfoIdx( _qDomain );

    if ( ! openDB( m_databaseInfoList.at(_dbIdx).db ) )
    {
        DLT_LOG( mDBHandleContext, DLT_LOG_WARN, DLT_STRING( "database open fail. return." ) );
        return;
    }


    QString _table = findTable( m_databaseInfoList.at(_dbIdx).db, _qSubDomain );



    QString _time = getGenerationTime( m_databaseInfoList.at(_dbIdx).db );
    if( _time == "" )
    {
        DLT_LOG( mDBHandleContext, DLT_LOG_WARN, DLT_STRING( "time generation fail. return." ) );
        return;
    }


    QString _dataID = QString::fromStdString( _id );


    QString _requester = getRequester();


    parsedCDLData_t _parsedData = ParsingCDLData( _data );


    DLT_LOG( mDBHandleContext, DLT_LOG_INFO, DLT_STRING( QString("domain: %1, subDomain: %2, dataID: %3, dataType: %4, dataValue: %5")
                                                          .arg(_qDomain)
                                                          .arg( _qSubDomain )
                                                          .arg( _dataID )
                                                          .arg( _parsedData.dataType )
                                                          .arg( _parsedData.dataValue ).toLocal8Bit().data() ) );
    QString _query = queryInsertCardata( _table, _time, _requester, _qDomain, _qSubDomain, _dataID, _parsedData.dataType, _parsedData.dataValue );

#ifdef __CDL_GUI_MODE__
    emit signalSetTableData( _time, _requester, _qDomain, _qSubDomain, _dataID, _parsedData.dataType, _parsedData.dataValue );
#endif

    m_databaseInfoList[_dbIdx].transactionBuffer.push_back( _query );


    flushQueryList( m_databaseInfoList.at(_dbIdx).db, m_databaseInfoList[_dbIdx].transactionBuffer );


    closeDB( m_databaseInfoList.at(_dbIdx).db );
}


int DBHandler::findDatabaseInfoIdx(QString _domain)
{
    QStringList _conns = QSqlDatabase::connectionNames();

    if ( _conns.contains( _domain ) )
    {
        for( int i = 0 ; i < m_databaseInfoList.size() ; i++ )
        {
            if ( m_databaseInfoList.at(i).db.connectionName() == _domain )
            {
                return i;
            }
        }
    }
    else
    {
        QSqlDatabase _database;
        _database = QSqlDatabase::addDatabase( kDATABASE_DRIVER, _domain);
        _database.setDatabaseName( _domain + kFILE_NAME_EXTENSION_MARK );

        m_databaseInfoList.push_back( databaseInfo_t( _database, QStringList()) );
        return m_databaseInfoList.size() -1;
    }
    return -1;
}


QString DBHandler::findTable(QSqlDatabase _currentDatabase, QString _subDomain)
{
    QStringList tables = _currentDatabase.tables( );

    for( int i = 0 ; i < tables.size() ; i++ )
    {
        if( tables.at(i) == _subDomain )
        {
            return tables.at(i);
        }
    }

    DLT_LOG( mDBHandleContext, DLT_LOG_DEBUG, DLT_STRING( "table not found" ) );

    return createTable( _currentDatabase, _subDomain );
}


DBHandler::parsedCDLData_t DBHandler::ParsingCDLData(ClientAPIRemoteTypes::CDLData _data)
{
    parsedCDLData_t retVal;

    if(_data.isType<int16_t>())
    {
        retVal.dataType = "int16_t";
        int16_t i16 = _data.get<int16_t>();
        retVal.dataValue = QString::number(i16);
    }
    else if(_data.isType<uint16_t>())
    {
        retVal.dataType = "uint16_t";
        int16_t ui16 = _data.get<uint16_t>();
        retVal.dataValue = QString::number(ui16);
    }
    else if(_data.isType<bool>())
    {
        retVal.dataType = "bool";
        int16_t b = _data.get<bool>();
        retVal.dataValue = b ? "1" : "0";
    }
    else if(_data.isType<uint32_t>())
    {
        retVal.dataType = "uint32_t";
        int16_t ui32 = _data.get<uint32_t>();
        retVal.dataValue = QString::number(ui32 );
    }
    else if(_data.isType<std::string>())
    {
        retVal.dataType = "std::string";
        std::string stdStr = _data.get<std::string>();
        retVal.dataValue = QString::fromStdString(stdStr);
    }
    else
    {
        retVal.dataType = "unknown";
        retVal.dataValue = "unknown";
    }
    return retVal;
}


QString DBHandler::getGenerationTime(QSqlDatabase _currentDatabase)
{
    QString query = "SELECT strftime('%Y-%m-%d %H:%M:%f','now')";
    QSqlQuery l_query = QSqlQuery( query, _currentDatabase );
    l_query.exec();
    while( l_query.next() )
    {
        return l_query.value(0).toString();
    }
    QDateTime now = QDateTime::currentDateTime();
    QString ret_dateTime = QString("%1-%2-%3 %4:%5:%6")
            .arg( now.date().year() )
            .arg( now.date().month() )
            .arg( now.date().day() )
            .arg( now.time().hour() )
            .arg( now.time().minute() )
            .arg( now.time().second() );

    return ret_dateTime;
}


QString DBHandler::getRequester()
{
    return kDEFAULT_REQUESTER;
}


QString DBHandler::queryInsertCardata(QString _table, QString _generateTime, QString _requester, QString _domain, QString _subDomain, QString _dataID, QString _dataType, QString _dataValue)
{
    QString _query = "INSERT INTO " + _table +
            " (time_stamp, requester, domain, sub_domain, data_id, data_type, data_value) " +
            " VALUES ( " +
            wrapQuoteMark(_generateTime) + ", "+
            wrapQuoteMark(_requester) + ", " +
            wrapQuoteMark(_domain) + ", " +
            wrapQuoteMark(_subDomain) + ", " +
            wrapQuoteMark(_dataID) + ", " +
            wrapQuoteMark(_dataType) + ", " +
            wrapQuoteMark(_dataValue) +
            ")";

    DLT_LOG( mDBHandleContext, DLT_LOG_DEBUG, DLT_STRING( _query.toLocal8Bit().data() ) );

    return _query;
}


void DBHandler::flushQueryList(QSqlDatabase _currentDatabase, QStringList &_buffer, bool _vismajor)
{
    if( _buffer.size() < kTRANSACTION_SIZE && !_vismajor) return;

    DLT_LOG( mDBHandleContext, DLT_LOG_INFO, DLT_STRING( "transaction size : " ), DLT_INT( _buffer.size() ) );

    if(_currentDatabase.transaction())
    {
        QSqlQuery _query(_currentDatabase);

        for(int i = 0 ; i < _buffer.size() ; i++)
        {
            _query.exec( _buffer.at(i) );

            if( _query.lastError().isValid() )
            {
                if ( _query.lastError().number() == QSqlError::TransactionError)
                {
                    DLT_LOG( mDBHandleContext, DLT_LOG_WARN, DLT_STRING( "transaction Error, rollback. return." ) );
                    _currentDatabase.rollback();
                    return;
                }
            }
        }
        _currentDatabase.commit();
        _buffer.clear();
    }
}

void DBHandler::flushInstantly(std::string _domain)
{
    QString _qDomain = QString::fromStdString( _domain );

    int _dbIdx = findDatabaseInfoIdx( _qDomain );

    if ( ! openDB(( m_databaseInfoList.at( _dbIdx ).db )) )
    {
        DLT_LOG( mDBHandleContext, DLT_LOG_WARN, DLT_STRING( "database open fail. return." ) );
        return;
    }

    DLT_LOG( mDBHandleContext, DLT_LOG_INFO, DLT_STRING( "flush instantly" ) );

    flushQueryList( m_databaseInfoList.at( _dbIdx ).db, m_databaseInfoList[ _dbIdx ].transactionBuffer, true );

    closeDB( m_databaseInfoList.at( _dbIdx ).db );
}


bool DBHandler::openDB(QSqlDatabase _currentDatabase)
{
    if ( !_currentDatabase.isOpen() )
    {
        if( _currentDatabase.open() )
        {
            dbConnectionCount++;
            DLT_LOG( mDBHandleContext, DLT_LOG_DEBUG, DLT_STRING( "success database open, connection size : " ), DLT_INT( dbConnectionCount ) );
            return true;
        }
        else
        {
            DLT_LOG( mDBHandleContext, DLT_LOG_DEBUG, DLT_STRING( "fail database open" ) );
            return false;
        }
    }
    else
    {
        dbConnectionCount++;
        DLT_LOG( mDBHandleContext, DLT_LOG_DEBUG, DLT_STRING( "success database open, connection size : " ), DLT_INT( dbConnectionCount ) );
        return true;
    }
}


void DBHandler::closeDB(QSqlDatabase _currentDatabase)
{
    dbConnectionCount--;
    DLT_LOG( mDBHandleContext, DLT_LOG_DEBUG, DLT_STRING( "database close, connection size : " ), DLT_INT( dbConnectionCount ) );
    _currentDatabase.close();
}


QString DBHandler::createTable( QSqlDatabase _currentDatabase, QString _subDomain )
{
    DLT_LOG( mDBHandleContext, DLT_LOG_DEBUG, DLT_STRING( "create table " ), DLT_STRING( _subDomain.toLocal8Bit().data()) );

    QString _query = "CREATE TABLE " + _subDomain + "(" +
            "time_stamp DATETIME, " +
            "requester VARCHAR(50), " +
            "domain VARCHAR(50), " +
            "sub_domain VARCHAR(50), " +
            "data_id VARCHAR(50), " +
            "data_type VARCHAR(30), " +
            "data_value VARCHAR(50) "
            ")";
    DLT_LOG( mDBHandleContext, DLT_LOG_INFO, DLT_STRING( _query.toLocal8Bit().data()) );

    QSqlQuery l_query = QSqlQuery( _query, _currentDatabase );
    l_query.exec();
    return _subDomain;
}


int DLT_Callback_DBHandler( u_int32_t serviceId, void *data, u_int32_t length )
{
    if ( data == NULL || length == 0 )
    {
        DLT_LOG( DBHandler::instance()->mDBHandleContext, DLT_LOG_INFO, DLT_STRING("invalid command"));

        return -1;
    }

    QStringList list = QString::fromUtf8( (const char*)data ).split( "," );

    if ( list.size() > 0 )
    {
        if ( list[0] == "help" )
        {
            DLT_LOG( DBHandler::instance()->mDBHandleContext, DLT_LOG_INFO, DLT_STRING("(flush,domain) do transaction "));
        }
        else if( list[0] == "flush" )
        {
            DBHandler::instance()->flushCallBackDelegate( list[1].toStdString() );
        }
        else if ( list[0] == "view")
        {
            DBHandler::instance()->storeData("ASDAS","weg23t","234", static_cast<int16_t>(213));
        }
        else
        {
            DLT_LOG( DBHandler::instance()->mDBHandleContext, DLT_LOG_INFO, DLT_STRING("invalid command. please type \"help\""));
        }
    }
    return 0;
}
