//#include "OBDConnectionManager.h"
//#include "OBDPacketParser.h"
//#include "OBDHandler.h"

//#include <QTimer>

//int OBD::ConnectionManager::retryCount = 0;

//namespace OBD
//{

//ConnectionManager * g_obd_connection_manager_instance = NULL;

//ConnectionManager::ConnectionManager()
//{
////    DLT_REGISTER_CONTEXT(mContext, "obdc", "OBD Connection Manager");
//    DLT_REGISTER_CONTEXT_LL_TS(mContext, "obdc", "OBD Connection Manager", DLT_LOG_DEBUG, DLT_TRACE_STATUS_OFF);

//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("init connection with OBD"));
//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("change packet parser state to Decode Packet for Connection!!!!"));

//    retryTimer = new QTimer(this);

//    connect(PacketParser::instance(), SIGNAL(signalRequestPINCode()), this, SLOT(requestSetPINCode()));
//    connect(PacketParser::instance(), SIGNAL(signalResponseSelectSensorData()), this, SLOT(requestBroadcastSensorData()));
//    connect(PacketParser::instance(), SIGNAL(signalResponseSetBroadcastSensorData()), this, SLOT(establishConnectionDone()));

//    connect( retryTimer, SIGNAL(timeout()), this, SLOT(requestBroadcastSensorData()) );

//    PacketParser::instance()->setDecodeConnectionState();

//    retryTimer->setInterval( 1000 * 5 );
//    retryTimer->stop();
//}

//ConnectionManager::~ConnectionManager()
//{
//}

//ConnectionManager * ConnectionManager::instance()
//{
//    if ( g_obd_connection_manager_instance == NULL )
//    {
//        g_obd_connection_manager_instance = new ConnectionManager;
//    }

//    return g_obd_connection_manager_instance;
//}

//void ConnectionManager::requestSetPINCode()
//{
//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("request for PIN Code received"));

//    QByteArray data;
//    data.push_back( 0x30 );
//    data.push_back( 0x30 );
//    data.push_back( 0x30 );
//    data.push_back( 0x30 );

//    PortHandler::instance()->writeData(eSOURCE_BT, eTARGET_FIRMWARE, ID_FIRMWARE_BLUETOOTH, SID_FIRMWARE_BLUETOOTH_SW_PIN_CODE, data);

//    QTimer::singleShot(500, this, SLOT(requestSelectSensorData()));
//}

//void ConnectionManager::requestSelectSensorData()
//{
//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("request select monitoring sensor data"));

//    SensorID id_list [] = {SENSOR_ID_CLV,
//                           SENSOR_ID_ECT,
//                           SENSOR_ID_RPM,
//                           SENSOR_ID_SPEED,
//                           SENSOR_ID_IAT,
//                           SENSOR_ID_AFR_MAF,
//                           SENSOR_ID_DWM,
//                           SENSOR_ID_FLI,
//                           SENSOR_ID_CMV};

//    QByteArray data;

//    for (size_t i = 0; i < sizeof(id_list) / sizeof(id_list[0]); i++)
//    {
//        data = PacketEncoder::addValueByteOrder(data, (int)id_list[i]);
//    }

//    PortHandler::instance()->writeData(eSOURCE_BT, eTARGET_DIAGNOSIS, ID_REQUEST_SENSOR_DATA, SID_REQUEST_SENSOR_DATA_SELECT_ITEM, data);
//}

//void ConnectionManager::requestBroadcastSensorData()
//{
//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("request broadcast selected monitoring sensor data"));

//    if ( (retryCount++) > 5 )
//    {
//        DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("request broadcast selected monitoring sensor data fail !!!!"));
//    }

//    SensorID id_list [] = {SENSOR_ID_CLV,
//                           SENSOR_ID_ECT,
//                           SENSOR_ID_RPM,
//                           SENSOR_ID_SPEED,
//                           SENSOR_ID_IAT,
//                           SENSOR_ID_AFR_MAF,
//                           SENSOR_ID_DWM,
//                           SENSOR_ID_FLI,
//                           SENSOR_ID_CMV};

//    QByteArray data;

//    for (size_t i = 0; i < sizeof(id_list) / sizeof(id_list[0]); i++)
//    {
//        data = PacketEncoder::addValueByteOrder(data, (int)id_list[i]);
//    }

//    PortHandler::instance()->writeData(eSOURCE_BT, eTARGET_DIAGNOSIS, ID_REQUEST_SENSOR_DATA, SID_REQUEST_SENSOR_DATA_BROADCASTING, data);

//    retryTimer->start();
//}

//void ConnectionManager::establishConnectionDone()
//{
//    retryTimer->stop();

//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("connection established !!"));
//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("change packet parser state to Decode Packet for Data!!!!"));

//    disconnect(PacketParser::instance(), SIGNAL(signalRequestPINCode()), this, SLOT(requestSetPINCode()));
//    disconnect(PacketParser::instance(), SIGNAL(signalResponseSelectSensorData()), this, SLOT(requestBroadcastSensorData()));
//    disconnect(PacketParser::instance(), SIGNAL(signalResponseSetBroadcastSensorData()), this, SLOT(establishConnectionDone()));

//    PacketParser::instance()->setDecodeDataState();
//}

//void ConnectionManager::prepareCloseConnection()
//{
//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("prepare for close OBD Connection"));

//    SensorID id_list [] = {SENSOR_ID_CLV,
//                           SENSOR_ID_ECT,
//                           SENSOR_ID_RPM,
//                           SENSOR_ID_SPEED,
//                           SENSOR_ID_IAT,
//                           SENSOR_ID_AFR_MAF,
//                           SENSOR_ID_DWM,
//                           SENSOR_ID_FLI,
//                           SENSOR_ID_CMV};

//    QByteArray data;

//    for (size_t i = 0; i < sizeof(id_list) / sizeof(id_list[0]); i++)
//    {
//        data = PacketEncoder::addValueByteOrder(data, (int)id_list[i]);
//    }

//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("stop broadcast sensor data.."));

//    PortHandler::instance()->writeData(eSOURCE_BT, eTARGET_DIAGNOSIS, ID_REQUEST_SENSOR_DATA, SID_REQUEST_SENSOR_DATA_ONCE, data);
//}

//}
