#include "datagenerator.h"

/*
 * << Data Infomation >>
 *
 * 8 - string / enum(unknown, fwd, rwd, awd)
 *
 * 55 - int / 0 ~ 100
 * 57 - int / 0 ~ 2000
 * 58 - int / 0 ~ 3000
 * 59 - int / -250 ~ 250
 * 973 - int
 *
 * 70 - unsigned int
 * 948 - unsigned int
 * 955 - unsigned int
 * 975 - unsigned int
 * 976 - unsigned int
 * 977 - unsigned int
 *
 * 957 - float
 *
 * 970 - bool
 *
 */
DataGenerator::DataGenerator(QObject *parent)
    :QObject(parent), m_timer(NULL)
{
    m_signalIdList << 8 << 55 <<  57 <<  58 <<  59 <<  973 <<  70
                   <<  948 <<  955 <<  975 <<  976 <<  977 <<  957 <<  970;
    m_stingDataList << "unknown" <<  "fwd" <<  "rwd" <<  "awd" <<  "invalid1" << "invalid2";

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(storeData()));

    start();
}

DataGenerator::~DataGenerator()
{
    free(m_result.data);
}

void DataGenerator::start()
{
    m_handle = vsi_initialize();

    m_result.domainId = 0;
    m_result.data = (char*)malloc( 1024 );

    m_timer->start(600);
}

void DataGenerator::stop()
{
    if ( m_timer != NULL && m_timer->isActive() )
    {
        m_timer->stop();
    }

    delete m_timer;

    vsi_destroy(m_handle);
}

void DataGenerator::storeData()
{
    qDebug() << "==================== << store Data >> ====================";

    for( int i=0; i<4; i++)
    {
        int index = rand() % CONFIGURATION_DATA_COUNT;
        int signalId = m_signalIdList[index];

        qDebug() << "1. signalID : " << signalId;

        //string type
        if( signalId == 8 )
        {
            int randNum = rand() % STRING_DATA_COUNT;

            qDebug() << "2. data : " << randNum;

            QByteArray temp = m_stingDataList.at(randNum).toLatin1();
            m_result.signalId = signalId;
            m_result.data = temp.data();
            m_result.dataLength = strlen(m_result.data)+1;
            vsi_fire_signal(m_handle, &m_result);
        }
        //boolean type
        else if( signalId == 970 )
        {
            int data = (rand() % 2);
            qDebug() << "2. data : " << data;

            m_result.signalId = signalId;
            memcpy(m_result.data, &data, sizeof(int));
            m_result.dataLength = sizeof(int);
            vsi_fire_signal(m_handle, &m_result);
        }
        //float type
        else if( signalId == 957 )
        {
            float data = (rand() % 450)/(float)4;   //to make a float type
            qDebug() << "2. data : " << data;

            m_result.signalId = signalId;
            memcpy(m_result.data, &data, sizeof(float));
            m_result.dataLength = sizeof(float);
            vsi_fire_signal(m_handle, &m_result);
        }
        //unsigned int type
        else if( signalId == 70 || signalId == 948 || signalId == 955  || signalId == 975
                  || signalId == 976 || signalId == 977)
        {
            int data = (rand() % 101);
            qDebug() << "2. data : " << data;

            m_result.signalId = signalId;
            memcpy(m_result.data, &data, sizeof(int));
            m_result.dataLength = sizeof(int);
            vsi_fire_signal(m_handle, &m_result);
        }
        //int type
        else
        {
            int data = (rand() % 3251) - 250;
            qDebug() << "2. data : " << data;

            m_result.signalId = signalId;
            memcpy(m_result.data, &data, sizeof(int));
            m_result.dataLength = sizeof(int);
            vsi_fire_signal(m_handle, &m_result);
        }
    }
}
