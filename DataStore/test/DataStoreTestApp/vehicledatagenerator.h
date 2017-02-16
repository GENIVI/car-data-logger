#ifndef VEHICLEDATAGENERATOR_H
#define VEHICLEDATAGENERATOR_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QTimer>
#include <string>

#include <storemanager.h>

using namespace std;

class vehicleDataGenerator : public QObject
{
    Q_OBJECT

public:
    explicit vehicleDataGenerator(QObject *parent = 0);
    virtual ~vehicleDataGenerator();

    void init();

private:
    void nameDataFormatinit();
    void typeDataFormatInit();
    void unitDataFormatInit();
    void startTimer();

private slots:
    void insertData();

private:
    StoreManager * m_storeManager_instance;
    QTimer * m_timer;
    QList<string> m_nameList;
    QList<string> m_typeList;
    QList<string> m_unitList;

    int m_count;
};

#endif // VEHICLEDATAGENERATOR_H
