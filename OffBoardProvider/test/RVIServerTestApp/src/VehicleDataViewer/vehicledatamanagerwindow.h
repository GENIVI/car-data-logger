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

#ifndef VEHICLEDATAMANAGERWINDOW_H
#define VEHICLEDATAMANAGERWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <string>

using namespace std;

namespace Ui{
class VehicleDataManagerWindow;
}

class VehicleDataManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VehicleDataManagerWindow(QWidget *parent=0);
    ~VehicleDataManagerWindow();

public:
    static VehicleDataManagerWindow * getInstance();

signals:
    void signalnotifyAutoRefreshState(bool state);
    void signalFileListItemDoubleClicked(string filePath);

private slots:
    void slotTransferFileIndex(int currentIndex, int totalIndex);
    void slotCompletedStoreFile(QString filePath);
    void slotFinishTransfer();
    void slotAutoRefreshChanged(bool autoRefresh);
    void slotFileListItemDoubleCliecked(QListWidgetItem * item);

private:
    void init();
    void initVehicleDataManagerWindow();
    void setCustomProgressBar();
    QString createTransferFileIndexText(int curIndex, int totalIndex);

private:
    Ui::VehicleDataManagerWindow * ui;
    bool m_autoRefresh;
};

#endif // VEHICLEDATAMANAGERWINDOW_H
