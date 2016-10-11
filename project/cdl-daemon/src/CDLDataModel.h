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
 * \file CDLDataModel.h
*/

#ifndef CDLDATAMODEL
#define CDLDATAMODEL

#include <QAbstractListModel>
#include <QObject>

class CDLViewerData
{
public:
//    CDLViewerData();
    CDLViewerData(QString time="", QString requester="", QString domain="", QString subDomain="", QString dataID="", QString dataType="", QString dataValue="")
        : m_time(time), m_requester(requester), m_domain(domain), m_subDomain(subDomain), m_dataID(dataID), m_dataType(dataType), m_dataValue(dataValue)
    {}
    QString time() const        { return m_time; }
    QString requester() const   { return m_requester; }
    QString domain() const      { return m_domain; }
    QString subDomain() const   { return m_subDomain; }
    QString dataID() const      { return m_dataID; }
    QString dataType() const    { return m_dataType; }
    QString dataValue() const   { return m_dataValue; }

    void setTime(QString time)
    {
        if (m_time == time) return;
        m_time = time;
    }

    void setRequester(QString requester)
    {
        if (m_requester == requester) return;
        m_requester = requester;
    }

    void setDomain(QString domain)
    {
        if (m_domain == domain) return;
        m_domain = domain;
    }

    void setSubDomain(QString subDomain)
    {
        if (m_subDomain == subDomain) return;
        m_subDomain = subDomain;
    }

    void setDataID(QString dataID)
    {
        if (m_dataID == dataID) return;
        m_dataID = dataID;
    }

    void setDataType(QString dataType)
    {
        if (m_dataType == dataType) return;
        m_dataType = dataType;
    }

    void setDataValue(QString dataValue)
    {
        if (m_dataValue == dataValue) return;
        m_dataValue = dataValue;
    }

private:
    QString m_time;
    QString m_requester;
    QString m_domain;
    QString m_subDomain;
    QString m_dataID;
    QString m_dataType;
    QString m_dataValue;
};

class AbstractCDLViewerDataModel : public QAbstractListModel{
    Q_OBJECT
public:
    static AbstractCDLViewerDataModel* instance();
    static void finalize();

    enum ModelRoles {
        MR_TIME = 0,
        MR_REQUESTER,
        MR_DOMAIN,
        MR_SUBDOMAIN,
        MR_DATAID,
        MR_DATATYPE,
        MR_DATAVALUE,
    };

public:
    QHash<qint32, QByteArray> roleNames() const;

    qint32 rowCount(const QModelIndex & parent = QModelIndex()) const;

    bool indexIsValid(const QModelIndex & index) const;

    QModelIndex index(qint32 row, qint32 column, const QModelIndex &parent) const;

    QVariant data(const QModelIndex & index, qint32 role = Qt::DisplayRole) const;

    bool setData(const QModelIndex & index, const QVariant & value, qint32 role = Qt::EditRole);

    bool removeRows(qint32 row, qint32 count, const QModelIndex &parent = QModelIndex());

    void addData(const CDLViewerData &data);

    void setData(quint32 index, const CDLViewerData &data);

    void updateList();

    CDLViewerData getCDLViewerData(qint32 index);

    Q_INVOKABLE QString getTime(qint32 index);
    Q_INVOKABLE QString getRequester(qint32 index);
    Q_INVOKABLE QString getDomain(qint32 index);
    Q_INVOKABLE QString getSubDomain(qint32 index);
    Q_INVOKABLE QString getDataID(qint32 index);
    Q_INVOKABLE QString getDataType(qint32 index);
    Q_INVOKABLE QString getDataValue(qint32 index);

    Q_INVOKABLE void addListItem();

signals:
    void showLastRow();


private:
    explicit AbstractCDLViewerDataModel(QObject *parent = Q_NULLPTR);

    QVector<CDLViewerData> m_cdlViewerDataList;

    QModelIndex m_top;
    QModelIndex m_bottom;
};

#endif // CDLDATAMODEL

