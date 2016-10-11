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
 * \file gaugearea.cpp
*/

#include "GaugeArea.h"
#include <QPainter>
#include <QDir>

GaugeArea::GaugeArea(QQuickItem *parent) : QQuickPaintedItem(parent)
    , m_startAngle(0)
    , m_endAngle(0)
    , m_myUrl("")
    , m_myImage(QImage())
    , m_type(GT_RPM)
    , m_calculateX(0)
    , m_calculateY(0)
    , m_imageX(0)
    , m_imageY(0)
{
    this->setRenderTarget(QQuickPaintedItem::FramebufferObject);
}

void GaugeArea::paint(QPainter *painter)
{
    painter->setPen(Qt::NoPen);

    QPainterPath path = QPainterPath();
    path.moveTo(QPointF(311, 311));
    path.arcTo(QRectF(0, 0, 622, 622), m_calculateX + m_startAngle, m_calculateY - m_endAngle);
    painter->setClipPath(path);

    painter->drawImage(QPoint(m_imageX, m_imageY), m_myImage);
}

double GaugeArea::startAngle() const
{
    return m_startAngle;
}

void GaugeArea::setStartAngle(double startAngle)
{
    m_startAngle = startAngle;
}

double GaugeArea::endAngle() const
{
    return m_endAngle;
}

void GaugeArea::setEndAngle(double endAngle)
{
    m_endAngle = endAngle;
    update();
}

QString GaugeArea::myUrl() const
{
    return m_myUrl;
}

void GaugeArea::setMyUrl(const QString &myUrl)
{
    m_myUrl = myUrl;
    if (m_myUrl.size() > 3)
    {
        m_myUrl = m_myUrl.remove(0, 3);
        m_myImage = QImage(m_myUrl);
    }
}

QImage GaugeArea::myImage() const
{
    return m_myImage;
}

void GaugeArea::setMyImage(const QImage &myImage)
{
    m_myImage = myImage;
}

int GaugeArea::type() const
{
    return m_type;
}

void GaugeArea::setType(int type)
{
    m_type = type;

    if (m_type == GT_RPM)
    {
        m_calculateX = -30;
        m_calculateY = -120;

        m_imageX = 0;
        m_imageY = 71 + 103;
    }
    else if (m_type == GT_FUEL)
    {
        m_calculateX = -150;
        m_calculateY = 120;

        m_imageX = 622 - 67;
        m_imageY = 71 + 103;
    }
    else
    {

    }
}
