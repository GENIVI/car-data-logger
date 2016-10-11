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
 * \file MainWindow.h
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QQuickView>

class QQmlContext;

class MainWindow : public QQuickView
{
public:


    explicit MainWindow(QWindow *parent = Q_NULLPTR);
    ~MainWindow();

public:
    void init();
    void initContextProperty();

private:
    void initQmlRegisterType();

public:
    QQmlContext *m_context;
};

#endif // MAINWINDOW_H
