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
 * \file CDLDataModel.cpp
*/

#include "CDLDataModel.h"

AbstractCDLViewerDataModel * g_AbstractCDLViewerDataModel = nullptr;

AbstractCDLViewerDataModel *AbstractCDLViewerDataModel::instance()
{
    if(g_AbstractCDLViewerDataModel == nullptr)
    {
        g_AbstractCDLViewerDataModel = new AbstractCDLViewerDataModel;
    }
    return g_AbstractCDLViewerDataModel;
}

void AbstractCDLViewerDataModel::finalize()
{
    if ( g_AbstractCDLViewerDataModel != nullptr )
    {
        delete g_AbstractCDLViewerDataModel;
        g_AbstractCDLViewerDataModel = nullptr;
    }
}

QHash<qint32, QByteArray> AbstractCDLViewerDataModel::roleNames() const
{
    QHash<qint32, QByteArray> roles;
    roles[MR_TIME] = "time";
    roles[MR_REQUESTER] = "requester";
    roles[MR_DOMAIN] = "domain";
    roles[MR_SUBDOMAIN] = "subDomain";
    roles[MR_DATAID] = "dataID";
    roles[MR_DATATYPE] = "dataType";
    roles[MR_DATAVALUE] = "dataValue";

    return roles;
}

qint32 AbstractCDLViewerDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_cdlViewerDataList.count();
}

bool AbstractCDLViewerDataModel::indexIsValid(const QModelIndex &index) const
{
    return index.isValid() && index.row() < rowCount() && index.row() > -1;
}

QModelIndex AbstractCDLViewerDataModel::index(qint32 row, qint32 column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return createIndex(row, column, quintptr(0));
}

QVariant AbstractCDLViewerDataModel::data(const QModelIndex &index, qint32 role) const
{
    if (!indexIsValid(index))
        return QVariant();

    const CDLViewerData &m_cdlViewerData = m_cdlViewerDataList[index.row()];
    switch (role)
    {
    case MR_TIME:
        return m_cdlViewerData.time();
    case MR_REQUESTER:
        return m_cdlViewerData.requester();
    case MR_DOMAIN:
        return m_cdlViewerData.domain();
    case MR_SUBDOMAIN:
        return m_cdlViewerData.subDomain();
    case MR_DATAID:
        return m_cdlViewerData.dataID();
    case MR_DATATYPE:
        return m_cdlViewerData.dataType();
    case MR_DATAVALUE:
        return m_cdlViewerData.dataValue();
    default:
        break;
    }
    return QVariant();
}

bool AbstractCDLViewerDataModel::setData(const QModelIndex &index, const QVariant &value, qint32 role)
{
    if (indexIsValid(index))
    {
        switch (role)
        {
        case MR_TIME:
            m_cdlViewerDataList[index.row()].setTime(value.toString());
            break;
        case MR_REQUESTER:
            m_cdlViewerDataList[index.row()].setRequester(value.toString());
            break;
        case MR_DOMAIN:
            m_cdlViewerDataList[index.row()].setDomain(value.toString());
            break;
        case MR_SUBDOMAIN:
            m_cdlViewerDataList[index.row()].setSubDomain(value.toString());
            break;
        case MR_DATAID:
            m_cdlViewerDataList[index.row()].setDataID(value.toString());
            break;
        case MR_DATATYPE:
            m_cdlViewerDataList[index.row()].setDataType(value.toString());
            break;
        case MR_DATAVALUE:
            m_cdlViewerDataList[index.row()].setDataValue(value.toString());
            break;
        default:
            break;
        }
        return true;
    }
    return false;
}

bool AbstractCDLViewerDataModel::removeRows(qint32 row, qint32 count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    while (count--)
    {
        m_cdlViewerDataList.removeAt(row);
    }
    endRemoveRows();
    return true;
}

void AbstractCDLViewerDataModel::addData(const CDLViewerData &data)
{
    if( m_cdlViewerDataList.size() >= 10000 )
    {
        removeRows(0,1000);
    }

    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_cdlViewerDataList.append(data);
    endInsertRows();

    emit showLastRow();
}

void AbstractCDLViewerDataModel::setData(quint32 index, const CDLViewerData &data)
{
    if (static_cast<quint32>(m_cdlViewerDataList.size()) > index)
    {
        m_cdlViewerDataList.replace(index, data);
    }
    else
    {
    }
}

void AbstractCDLViewerDataModel::updateList()
{
    m_top = createIndex(0, 0, quintptr(0));
    m_bottom = createIndex(m_cdlViewerDataList.count(), 0, quintptr(0));
    emit dataChanged(m_top, m_bottom);
}

CDLViewerData AbstractCDLViewerDataModel::getCDLViewerData(qint32 index)
{
    if (index >= 0 && m_cdlViewerDataList.size() > index)
    {
        return m_cdlViewerDataList.at(index);
    }
    else
    {
        return CDLViewerData();
    }
}

QString AbstractCDLViewerDataModel::getTime(qint32 index)
{
    if (index >= 0 && m_cdlViewerDataList.size() > index)
    {
        return m_cdlViewerDataList.at(index).time();
    }
    else
    {
        return "";
    }
}

QString AbstractCDLViewerDataModel::getRequester(qint32 index)
{
    if (index >= 0 && m_cdlViewerDataList.size() > index)
    {
        return m_cdlViewerDataList.at(index).requester();
    }
    else
    {
        return "";
    }
}

QString AbstractCDLViewerDataModel::getDomain(qint32 index)
{
    if (index >= 0 && m_cdlViewerDataList.size() > index)
    {
        return m_cdlViewerDataList.at(index).domain();
    }
    else
    {
        return "";
    }
}

QString AbstractCDLViewerDataModel::getSubDomain(qint32 index)
{
    if (index >= 0 && m_cdlViewerDataList.size() > index)
    {
        return m_cdlViewerDataList.at(index).subDomain();
    }
    else
    {
        return "";
    }
}

QString AbstractCDLViewerDataModel::getDataID(qint32 index)
{
    if (index >= 0 && m_cdlViewerDataList.size() > index)
    {
        return m_cdlViewerDataList.at(index).dataID();
    }
    else
    {
        return "";
    }
}

QString AbstractCDLViewerDataModel::getDataType(qint32 index)
{
    if (index >= 0 && m_cdlViewerDataList.size() > index)
    {
        return m_cdlViewerDataList.at(index).dataType();
    }
    else
    {
        return "";
    }
}

QString AbstractCDLViewerDataModel::getDataValue(qint32 index)
{
    if (index >= 0 && m_cdlViewerDataList.size() > index)
    {
        return m_cdlViewerDataList.at(index).dataValue();
    }
    else
    {
        return "";
    }
}

void AbstractCDLViewerDataModel::addListItem()
{
    addData(CDLViewerData("2016-04-06 14:56:54.760","SOME_IP_VEHICLE_DATA","vehicledata","runningstatus","speedometer","uint16_t","32"));
}

AbstractCDLViewerDataModel::AbstractCDLViewerDataModel(QObject *parent) : QAbstractListModel(parent)
  , m_cdlViewerDataList()
  , m_top()
  , m_bottom()
{
}
