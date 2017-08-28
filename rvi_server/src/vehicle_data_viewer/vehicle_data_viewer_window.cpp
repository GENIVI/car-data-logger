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

#include "vehicle_data_viewer_window.hpp"
#include "ui_vehicledataviewerwindow.h"
#include "vehicle_data_manager_window.hpp"
#include "data_manager.hpp"

#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QObject>

static VehicleDataViewerWindow * g_vehicle_data_viewer_instance = NULL;

VehicleDataViewerWindow::VehicleDataViewerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VehicleDataViewerWindow), m_speedDataName("Speed"), m_rpmDataName("RPM")
    , m_maxSpeedX(0), m_maxRpmX(0), m_maxSpeedY(0), m_maxRpmY(0), m_preJsonFilePath(""), m_autoRefreshState(true)
{
    ui->setupUi(this);
}

VehicleDataViewerWindow::~VehicleDataViewerWindow()
{
    delete ui;
}

VehicleDataViewerWindow *VehicleDataViewerWindow::getInstance()
{
    if( g_vehicle_data_viewer_instance == NULL )
    {
        g_vehicle_data_viewer_instance = new VehicleDataViewerWindow();
        g_vehicle_data_viewer_instance->init();
    }

    return g_vehicle_data_viewer_instance;
}

void VehicleDataViewerWindow::init()
{
    connect(this, SIGNAL(signalFileDropEventNotify(string)), this, SLOT(drawVehicleDataGraph(string)));
    connect(ui->speedPlot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(mouseDoubleClickEventInSpeedArea(QMouseEvent*)));
    connect(ui->rpmPlot, SIGNAL(mouseDoubleClick(QMouseEvent*)), this, SLOT(mouseDoubleClickEventInRPMArea(QMouseEvent*)));
    connect(DataManager::getInstance(), SIGNAL(signalCompletedTransferData(QString)), this, SLOT(slotCompletedTransferData(QString)));
    connect(VehicleDataManagerWindow::getInstance(), SIGNAL(signalnotifyAutoRefreshState(bool)), this, SLOT(slotAutoRefreshState(bool)));
    connect(VehicleDataManagerWindow::getInstance(), SIGNAL(signalFileListItemDoubleClicked(string)), this, SLOT(drawVehicleDataGraph(string)));

    speedGraphInit();
    rpmGraphInit();

    setAcceptDrops(true);
}

void VehicleDataViewerWindow::speedGraphInit()
{
    QFont legendFont("Courier", 15, QFont::Bold);

    ui->speedPlot->addGraph();
    ui->speedPlot->xAxis->setLabel("Time");
    ui->speedPlot->yAxis->setLabel("Speed");
    ui->speedPlot->xAxis->setLabelFont(legendFont);
    ui->speedPlot->yAxis->setLabelFont(legendFont);
    ui->speedPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
}

void VehicleDataViewerWindow::rpmGraphInit()
{
    QFont legendFont("Courier", 15, QFont::Bold);

    ui->rpmPlot->addGraph();
    ui->rpmPlot->xAxis->setLabel("Time");
    ui->rpmPlot->yAxis->setLabel("RPM");
    ui->rpmPlot->xAxis->setLabelFont(legendFont);
    ui->rpmPlot->yAxis->setLabelFont(legendFont);
    ui->rpmPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
}

property_tree::ptree VehicleDataViewerWindow::read(const string jsonFilePath)
{
    boost::property_tree::ptree jsonDoc;

    try
    {
        boost::property_tree::json_parser::read_json(jsonFilePath, jsonDoc);
    }
    catch( std::exception & e )
    {
        //add that failed to read_json log
        qDebug() << "exception : " << e.what();
    }

    return jsonDoc;
}

void VehicleDataViewerWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void VehicleDataViewerWindow::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void VehicleDataViewerWindow::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

void VehicleDataViewerWindow::dropEvent(QDropEvent *event)
{
    QString filepath;
    QList<QUrl> urls;
    QList<QUrl>::Iterator iter;
    urls = event->mimeData()->urls();

    for( iter = urls.begin(); iter != urls.end(); iter++ )
    {
        filepath = iter->path();
    }

    if( m_preJsonFilePath != filepath )
    {
        m_preJsonFilePath = filepath;
        emit signalFileDropEventNotify(filepath.toUtf8().constData());
    }
    else
    {
        qDebug() << "<< VehicleDataViewerWindow::dropEvent() >> Current JSON file is the same as the previous file";
        qDebug() << filepath;
    }
}

void VehicleDataViewerWindow::mouseDoubleClickEventInSpeedArea(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton )
    {
        setSpeedRange();
        ui->speedPlot->replot();
    }
}

void VehicleDataViewerWindow::mouseDoubleClickEventInRPMArea(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton )
    {
        setRpmRange();
        ui->rpmPlot->replot();
    }
}

void VehicleDataViewerWindow::slotCompletedTransferData(QString jsonFilePath)
{
    if( m_autoRefreshState )
    {
        drawVehicleDataGraph(jsonFilePath.toLocal8Bit().data());
    }
}

void VehicleDataViewerWindow::slotAutoRefreshState(bool state)
{
    m_autoRefreshState = state;
}

void VehicleDataViewerWindow::drawVehicleDataGraph(const string jsonFilePath)
{
    QVector<double> speedTime, speed;
    QVector<double> rpmTime, rpm;

    QVector<QString> speedTimeLabel, rpmTimeLabel;

    if( parseJson(read(jsonFilePath), speedTime, speed, rpmTime, rpm, speedTimeLabel, rpmTimeLabel) )
    {
        m_maxSpeedX = speedTime.size();
        m_maxRpmX = rpmTime.size();

        setTimeLabel(speedTimeLabel, rpmTimeLabel);

        drawGraph(speedTime, speed, rpmTime, rpm, speedTimeLabel, rpmTimeLabel);
    }
    else
    {
        //failed to draw graph
        qDebug() << "<< VehicleDataViewerWindow::drawVehicleDataGraph >> Failed to draw graph";
    }
}
bool VehicleDataViewerWindow::parseJson(property_tree::ptree jsonDoc, QVector<double> &speedX, QVector<double> &speedY, QVector<double> &rpmX, QVector<double> &rpmY, QVector<QString> &speedLabel, QVector<QString> &rpmLable)
{
    int speedIndex = 0;
    int rpmIndex = 0;

    int maxSpeedY = 0;
    int maxRpmY = 0;

    if( !jsonDoc.empty() )
    {
        try
        {
            BOOST_FOREACH( property_tree::ptree::value_type &vt, jsonDoc.get_child("VehicleData") )
            {
                QString id = QString::fromLocal8Bit(vt.second.get<string>("id").c_str());
                QString value = QString::fromLocal8Bit(vt.second.get<string>("value").c_str());

                string timeStampStr = vt.second.get<string>("time_stamp").c_str();

                /* UTC Time Parsing */
                unsigned long timeStamp = boost::lexical_cast<unsigned long>(timeStampStr);

                QDateTime dateTime =QDateTime::fromMSecsSinceEpoch(timeStamp);
                QString dateTimeFormat = dateTime.toString("hh:mm:ss:zzz");

                if( id == "54" )    //rpm
                {
                    rpmIndex++;

                    if( maxRpmY < value.toInt() )
                    {
                        maxRpmY = value.toInt();
                    }

                    rpmX.push_back(rpmIndex);
                    rpmY.push_back(value.toInt());
                    rpmLable.push_back(dateTimeFormat);
                }
                else if( id == "63" )   //speed
                {
                    speedIndex++;

                    if( maxSpeedY < value.toInt() )
                    {
                        maxSpeedY = value.toInt();
                    }

                    speedX.push_back(speedIndex);
                    speedY.push_back(value.toInt());
                    speedLabel.push_back(dateTimeFormat);
                }
            }
        }
        catch( std::exception &e )
        {
            qDebug() << "<< VehicleDataViewerWindow::parseJson >> Error parsing JSON file: "<<e.what();
            return false;
        }
    }
    else
    {
        qDebug() << "<< VehicleDataViewerWindow::parseJson >> JSON file is invalid ( no data, empty )";
        return false;
    }

    qDebug() << "rpm data count : " << rpmIndex;
    qDebug() << "speed data count : " << speedIndex;

    m_maxSpeedY = maxSpeedY;
    m_maxRpmY = maxRpmY;

    return true;
}

void VehicleDataViewerWindow::drawGraph(QVector<double> &speedX, QVector<double> &speedY, QVector<double> &rpmX, QVector<double> &rpmY, QVector<QString> &speedLabel, QVector<QString> &rpmLable)
{
    ui->speedPlot->legend->setVisible(true);
    ui->speedPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);

    ui->rpmPlot->legend->setVisible(true);
    ui->rpmPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);

    speedGraphDraw(speedX, speedY, speedLabel);
    rpmGraphDraw(rpmX, rpmY, rpmLable);
}

void VehicleDataViewerWindow::speedGraphDraw(QVector<double> &x, QVector<double> &y, QVector<QString> &speedLabel)
{
    m_speedTextTicker = QSharedPointer<QCPAxisTickerText>(new QCPAxisTickerText);

    ui->speedPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->speedPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->speedPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    ui->speedPlot->graph(0)->setName(m_speedDataName);

    m_speedTextTicker->addTicks(x, speedLabel);
    ui->speedPlot->xAxis->setTicker(m_speedTextTicker);
    ui->speedPlot->xAxis->setTickLabelRotation(60);
    ui->speedPlot->xAxis->setSubTicks(false);
    ui->speedPlot->xAxis->setTickLength(0, 4);

    setSpeedRange();
    setRpmRange();

    ui->speedPlot->graph(0)->setData(x, y);
    ui->speedPlot->axisRect()->setupFullAxesBox(true);
    ui->speedPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->speedPlot->replot();
}

void VehicleDataViewerWindow::rpmGraphDraw(QVector<double> &x, QVector<double> &y, QVector<QString> &rpmLabel)
{
    m_rpmTextTicker = QSharedPointer<QCPAxisTickerText>(new QCPAxisTickerText);;

    ui->rpmPlot->graph(0)->setPen(QPen(Qt::red));
    ui->rpmPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->rpmPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    ui->rpmPlot->graph(0)->setName(m_rpmDataName);

    m_rpmTextTicker->addTicks(x, rpmLabel);
    ui->rpmPlot->xAxis->setTicker(m_rpmTextTicker);
    ui->rpmPlot->xAxis->setTickLabelRotation(60);
    ui->rpmPlot->xAxis->setSubTicks(false);
    ui->rpmPlot->xAxis->setTickLength(0, 4);

    setSpeedRange();
    setRpmRange();

    ui->rpmPlot->graph(0)->setData(x, y);
    ui->rpmPlot->axisRect()->setupFullAxesBox(true);
    ui->rpmPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->rpmPlot->replot();
}

void VehicleDataViewerWindow::setTimeLabel(QVector<QString> &speedLabel, QVector<QString> &rpmLabel)
{
    for( int i=0; i<speedLabel.size(); i++ )
    {
        if( m_maxSpeedX > 10 )
        {
            if( i%(m_maxSpeedX/10) != 0 )
            {
                speedLabel[i] = "";
            }
        }
    }

    for( int i=0; i<rpmLabel.size(); i++ )
    {
        if( m_maxRpmX > 10 )
        {
            if( i%(m_maxRpmX/10) != 0 )
            {
                rpmLabel[i] = "";
            }
        }
    }
}

void VehicleDataViewerWindow::setSpeedRange()
{
    ui->speedPlot->xAxis->setRange(0, m_maxSpeedX);
    ui->speedPlot->yAxis->setRange(0, 300);
}

void VehicleDataViewerWindow::setRpmRange()
{
    ui->rpmPlot->xAxis->setRange(0, m_maxRpmX);
    ui->rpmPlot->yAxis->setRange(0, 20000);
}
