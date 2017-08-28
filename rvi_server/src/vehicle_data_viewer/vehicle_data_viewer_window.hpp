/*
* Copyright (C) 2017, IVIS
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
* \author Seok-Heum Choi <seokheum.choi@ivisolution.com>
*
* \copyright Copyright (c) 2017, IVIS \n
* License MPL-2.0: Mozilla Public License version 2.0 http://mozilla.org/MPL/2.0/.
*
*/

#ifndef VEHICLEDATAVIEWERWINDOW_H
#define VEHICLEDATAVIEWERWINDOW_H

#include "qcustomplot.h"

#include <QMainWindow>
#include <string>
#include <boost/property_tree/ptree.hpp>

using namespace std;
using namespace boost;

namespace Ui {
class VehicleDataViewerWindow;
}

class VehicleDataViewerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VehicleDataViewerWindow(QWidget *parent = 0);
    virtual ~VehicleDataViewerWindow();

    static VehicleDataViewerWindow * getInstance();

protected:
    void dragEnterEvent(QDragEnterEvent * event);
    void dragLeaveEvent(QDragLeaveEvent * event);
    void dragMoveEvent(QDragMoveEvent * event);
    void dropEvent(QDropEvent * event);

signals:
    void signalFileDropEventNotify(const string jsonFilePath);

private slots:
    void drawVehicleDataGraph(const string jsonFilePath);
    void mouseDoubleClickEventInSpeedArea(QMouseEvent *event);
    void mouseDoubleClickEventInRPMArea(QMouseEvent *event);

    void slotCompletedTransferData(QString jsonFilePath);
    void slotAutoRefreshState(bool state);

private:
    void init();
    void speedGraphInit();
    void rpmGraphInit();
    property_tree::ptree read(const string jsonFilePath);
    bool parseJson(property_tree::ptree jsonDoc, QVector<double> &x, QVector<double> &y, QVector<double> &rpmX, QVector<double> &rpmY, QVector<QString> &speedLabel, QVector<QString> &rpmLable);
    void drawGraph(QVector<double> &speedX, QVector<double> &speedY, QVector<double> &rpmX, QVector<double> &rpmY, QVector<QString> &speedLabel, QVector<QString> &rpmLable);
    void speedGraphDraw(QVector<double> & x, QVector<double> & y, QVector<QString> &speedLabel);
    void rpmGraphDraw(QVector<double> & x, QVector<double> & y, QVector<QString> &rpmLabel);
    void setTimeLabel(QVector<QString> &speedLabel, QVector<QString> &rpmLabel);
    void setSpeedRange();
    void setRpmRange();

private:
    Ui::VehicleDataViewerWindow *ui;
    QString m_speedDataName;
    QString m_rpmDataName;
    QSharedPointer<QCPAxisTickerText> m_speedTextTicker;
    QSharedPointer<QCPAxisTickerText> m_rpmTextTicker;

    int m_maxSpeedX;
    int m_maxRpmX;
    int m_maxSpeedY;
    int m_maxRpmY;
    QString m_preJsonFilePath;
    bool m_autoRefreshState;
};

#endif // VEHICLEDATAVIEWERWINDOW_H
