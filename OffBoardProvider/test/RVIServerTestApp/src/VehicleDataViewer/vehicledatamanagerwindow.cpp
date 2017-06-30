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

#include "vehicledatamanagerwindow.h"
#include "ui_vehicledatamanagerwindow.h"
#include "datamanager.h"
#include <QDebug>
static VehicleDataManagerWindow * g_vehicle_data_manager_instance = NULL;

VehicleDataManagerWindow::VehicleDataManagerWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::VehicleDataManagerWindow)
    ,m_autoRefresh(true)
{
    ui->setupUi(this);
}

VehicleDataManagerWindow::~VehicleDataManagerWindow()
{
    delete ui;
}

VehicleDataManagerWindow *VehicleDataManagerWindow::getInstance()
{
    if( g_vehicle_data_manager_instance == NULL )
    {
        g_vehicle_data_manager_instance = new VehicleDataManagerWindow();
        g_vehicle_data_manager_instance->init();
    }

    return g_vehicle_data_manager_instance;
}

void VehicleDataManagerWindow::init()
{
    connect(DataManager::getInstance(), SIGNAL(signalTransferCurrentFileIndex(int,int)), this, SLOT(slotTransferFileIndex(int,int)));
    connect(DataManager::getInstance(), SIGNAL(signalCompletedStoreFile(QString)), this, SLOT(slotCompletedStoreFile(QString)));
    connect(DataManager::getInstance(), SIGNAL(signalFinishTransfer()), this, SLOT(slotFinishTransfer()));
    connect(ui->autoRefreshCheckBox, SIGNAL(clicked(bool)), this, SLOT(slotAutoRefreshChanged(bool)));
    connect(ui->fileListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotFileListItemDoubleCliecked(QListWidgetItem*)));

    initVehicleDataManagerWindow();
}

void VehicleDataManagerWindow::initVehicleDataManagerWindow()
{
    // Data Transfer - Custom ProgressBar
    setCustomProgressBar();
    ui->autoRefreshCheckBox->setChecked(m_autoRefresh);

    QString fileIndexStr = createTransferFileIndexText(0, 0);
    ui->fileIndexLabel->setText(fileIndexStr);

    emit signalnotifyAutoRefreshState(m_autoRefresh);
}

QString VehicleDataManagerWindow::createTransferFileIndexText(int curIndex, int totalIndex)
{
    QString fileIndexStr;
    fileIndexStr = QString( "( %0 / %1 )" ).arg(QString::number(curIndex)).arg(QString::number(totalIndex));

    return fileIndexStr;
}

void VehicleDataManagerWindow::slotTransferFileIndex(int currentIndex, int totalIndex)
{
    QString fileIndexStr;
    int value=0;

    if( totalIndex == 0 )
    {
        return;
    }

    fileIndexStr = createTransferFileIndexText(currentIndex, totalIndex);
    value = ( (double)(currentIndex)/totalIndex )*100;

    ui->fileIndexLabel->setText(fileIndexStr);
    ui->transferFileProgressBar->setValue(value);
}

void VehicleDataManagerWindow::slotCompletedStoreFile(QString filePath)
{
    if( filePath == "" )
    {
        return;
    }

    ui->fileListWidget->addItem(filePath);
}

void VehicleDataManagerWindow::slotFinishTransfer()
{
    QString fileIndexStr;

    fileIndexStr = createTransferFileIndexText(0, 0);

    ui->fileIndexLabel->setText(fileIndexStr);
    ui->transferFileProgressBar->setValue(0);
}

void VehicleDataManagerWindow::slotAutoRefreshChanged(bool autoRefresh)
{
    m_autoRefresh = autoRefresh;

    emit signalnotifyAutoRefreshState(autoRefresh);
}

void VehicleDataManagerWindow::slotFileListItemDoubleCliecked(QListWidgetItem *item)
{
    if( item != NULL && !m_autoRefresh )
    {
        emit signalFileListItemDoubleClicked(item->text().toLocal8Bit().data());
    }
}

void VehicleDataManagerWindow::setCustomProgressBar()
{
    QString progressStyleSheet;

    progressStyleSheet += "QProgressBar{"
                          "border: 2px solid grey;"
                          "border-radius: 5px;"
                          "text-align: center"
                          "}";

    progressStyleSheet += "QProgressBar::chunk {"
                          "background-color: green;"
                          "width: 10px;"
                          "margin: 0.5px;"
                          "}";

    ui->transferFileProgressBar->setStyleSheet(progressStyleSheet);
}
