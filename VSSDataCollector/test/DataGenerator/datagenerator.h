#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

extern "C"
{
    #include <vsi.h>
}

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QList>
#include <cstdlib>
#include <iostream>

#define CONFIGURATION_DATA_COUNT 14
#define STRING_DATA_COUNT 6

using namespace std;

class DataGenerator : public QObject
{
    Q_OBJECT
public:
    explicit DataGenerator(QObject *parent = 0);
    virtual ~DataGenerator();

public:
    void start();
    void stop();

private slots:
    void storeData();

private:
    QTimer *m_timer;
    QList<int> m_signalIdList;
    QList<QString> m_stingDataList;
    vsi_handle m_handle;
    vsi_result m_result;
};

#endif // DATAGENERATOR_H
