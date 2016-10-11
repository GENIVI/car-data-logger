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
 * \file GaugeArea.h
*/

#ifndef GAUGEAREA_H
#define GAUGEAREA_H

#include <QQuickPaintedItem>
#include <QImage>

class GaugeArea : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(double  startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(double  endAngle   READ endAngle   WRITE setEndAngle)
    Q_PROPERTY(QString myUrl      READ myUrl      WRITE setMyUrl)
    Q_PROPERTY(QImage  myImage    READ myImage    WRITE setMyImage)
    Q_PROPERTY(int     type       READ type       WRITE setType)

public:
    GaugeArea(QQuickItem *parent = 0);

    enum GaugeType {
        GT_RPM,
        GT_FUEL
    };
    Q_ENUM(GaugeType)

    void paint(QPainter *painter);

    double startAngle() const;
    void setStartAngle(double startAngle);

    double endAngle() const;
    void setEndAngle(double endAngle);

    QString myUrl() const;
    void setMyUrl(const QString &myUrl);

    QImage myImage() const;
    void setMyImage(const QImage &myImage);

    int type() const;
    void setType(int type);

private:
    double m_startAngle;
    double m_endAngle;
    QString m_myUrl;
    QImage m_myImage;
    int m_type;
    int m_calculateX;
    int m_calculateY;
    int m_imageX;
    int m_imageY;

};

#endif // GAUGEAREA_H
