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
 * \file MainWindow.cpp
*/

#include "../system/HMIModeManager.h"
#include "MainWindow.h"
#include "DATCControl.h"
#include "MusicPlayControl.h"
#include "VideoPlayControl.h"

#include <QQuickView>
#include <QQmlContext>


MainWindow::MainWindow(QWindow *parent)
    : QQuickView(parent), m_context(Q_NULLPTR)

{
    setResizeMode(QQuickView::SizeViewToRootObject);
    setWidth(800);
    setHeight(480);
    setMinimumSize(QSize(800,480));

    setColor(QColor(Qt::transparent));

    m_context = this->rootContext();

    init();

    setSource(QUrl("qrc:/home/HomeMain.qml"));
    this->show();    
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    qDebug("MainWindow Init()");
    initQmlRegisterType();
    initContextProperty();
}

void MainWindow::initQmlRegisterType()
{
//    qmlRegisterType<SetupDefine>("SetupDefine", 1, 0, "SetupDefine");
//    qmlRegisterType<EnumBroswingState>("BroswingStateEnum",1,0,"BroswingState");
}

void MainWindow::initContextProperty()
{

    m_context->setContextProperty("ModeManager", HMIModeManager::instance().data());
    m_context->setContextProperty("DatcControl", DatcControl::instance().data());
    m_context->setContextProperty("VideoControl", VideoPlayControl::instance().data());
    m_context->setContextProperty("MusicControl", MusicPlayControl::instance().data());

    m_context->setContextProperty("MainWindow", this);
}
