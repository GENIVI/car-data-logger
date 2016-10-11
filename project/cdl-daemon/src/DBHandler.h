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
 * \file DBHandler.h
*/

#ifndef DBHANDLER
#define DBHANDLER

#include "com/ivis/CDL/ClientAPIRemoteStubDefault.hpp"

#include <QVector>
#include <QSqlDatabase>

#ifdef __CDL_GUI_MODE__
#include <QQmlContext>
#include "cdldatamodel.h"
#else
#include <QObject>
#endif

#include "dlt.h"

#include <iostream>
using namespace std;

using namespace v1::com::ivis::CDL;

class DBHandler : public QObject
{
    Q_OBJECT
public:
    static DBHandler* instance();
    static void finalize();

public:
    void storeData(std::string _domain, std::string _subDomain, std::string _id, ClientAPIRemoteTypes::CDLData _data);

private:
    typedef struct DatabaseInfo{
        QSqlDatabase db;
        QStringList transactionBuffer;
        DatabaseInfo(){
            db = QSqlDatabase();
            transactionBuffer = QStringList();
        }
        DatabaseInfo(QSqlDatabase _db, QStringList _buffer = QStringList()){
            db = _db;
            transactionBuffer = _buffer;
        }
    }databaseInfo_t;

    typedef struct ParsedCDLData{
        QString dataType;
        QString dataValue;
        ParsedCDLData(){
            dataType = QString();
            dataValue= QString();
        }
    }parsedCDLData_t;

    QVector<databaseInfo_t> m_databaseInfoList;
    static int dbConnectionCount;

    static const QString kDATABASE_DRIVER;
    static const QString kDOMAIN_DATABASE_VEHICLE_DATA;
    static const QString kFILE_NAME_EXTENSION_MARK;
    static const QString kDEFAULT_REQUESTER;
    static const int kTRANSACTION_SIZE = 100;

private:
    void init();


    /**
     * @brief findDatabase by domain. if not found, create the database file name of "domain"
     * @param _domain
     * @return QSqlDatabase name of "damain"
     */
    int findDatabaseInfoIdx( QString _domain );

    /**
     * @brief findTable by subdomain. if not found, create the database table name of "domain"
     * @param _currentDatabase
     * @param _subDomain
     * @return table name
     */
    QString findTable( QSqlDatabase _currentDatabase, QString _subDomain );


    /**
     * @brief ParsingCDLData
     * @param _data. source data.
     * @return type and value
     */
    parsedCDLData_t ParsingCDLData( ClientAPIRemoteTypes::CDLData _data );

    /**
     * @brief getGenerationTime
     * @return current system time.
     */
    QString getGenerationTime(QSqlDatabase _currentDatabase);

    /**
     * @brief getRequester
     * @return IVIS. (to be defined)
     */
    QString getRequester();

    /**
     * @brief queryInsertCardata. make insert query. using argments.
     * @return INSERT Query
     */
    QString queryInsertCardata( QString _table, QString _generateTime, QString _requester, QString _domain, QString _subDomain, QString _dataID, QString _dataType, QString _dataValue );

    /**
     * @brief flushQueryList. do transaction
     */
    void flushQueryList(QSqlDatabase _currentDatabase, QStringList& _buffer, bool _vismajor = false);

    void flushInstantly(std::string _domain);


    bool openDB( QSqlDatabase _currentDatabase );
    void closeDB( QSqlDatabase _currentDatabase );

    QString createTable( QSqlDatabase _currentDatabase, QString _subDomain );

    template <typename T>
    static inline QString wrapQuoteMark(T arg)
    {
        return QString("\"%1\"").arg(arg);
    }

private:
    explicit DBHandler(QObject* parent=0);
    ~DBHandler();
    Q_DISABLE_COPY(DBHandler)

public:
    DLT_DECLARE_CONTEXT(mDBHandleContext)
    void flushCallBackDelegate(std::string _domain);



public:
#ifdef __CDL_GUI_MODE__
    QQmlContext * aa;
    void setContext(QQmlContext * a)
    {
        aa = a;
        aa->setContextProperty("CDLDataModel", QVariant::fromValue(AbstractCDLViewerDataModel::instance()));
    }

signals:
    void signalSetTableData( QString _time, QString _requester, QString _qDomain,QString _qSubDomain, QString _dataID, QString _dataType, QString _dataValue );

private slots:
    void setTableData( QString _time, QString _requester, QString _qDomain,QString _qSubDomain, QString _dataID, QString _dataType, QString _dataValue )
    {
        AbstractCDLViewerDataModel::instance()->addData( CDLViewerData(_time, _requester, _qDomain,_qSubDomain, _dataID, _dataType, _dataValue)  );
    }
#endif
};
#endif // DBHANDLER





























