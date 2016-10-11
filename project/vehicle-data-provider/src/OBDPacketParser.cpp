//#include "OBDPacketParser.h"
//#include "OBDHandler.h"
//#include "OBDConnectionManager.h"

//#include <QtEndian>

//#include <QDebug>
//#include <QMutexLocker>


//#include <QMap>

//namespace OBD
//{

//PacketParser * g_obd_packet_parser_instance = NULL;

//int CallBackFunction( u_int32_t serviceId, void *data, u_int32_t length );

//PacketParser::PacketParser()
//{
//    DLT_REGISTER_CONTEXT(mContext, "obdp", "OBD Packet Parser");
////    DLT_REGISTER_CONTEXT_LL_TS(mContext, "obdp", "OBD Packet Parser", DLT_LOG_DEBUG, DLT_TRACE_STATUS_OFF);
//    DLT_REGISTER_INJECTION_CALLBACK( mContext, 0xfff, CallBackFunction );

//    connect(OBD::PortHandler::instance(), SIGNAL(packetReceived(QByteArray)), this, SLOT(packetReceived(QByteArray)));

//    mDecodePacketCallback = NULL;
//    temp_fuel_level = 50;
//}

//PacketParser::~PacketParser()
//{

//}

//PacketParser * PacketParser::instance()
//{
//    if ( g_obd_packet_parser_instance == NULL )
//    {
//        g_obd_packet_parser_instance = new PacketParser;
//    }

//    return g_obd_packet_parser_instance;
//}

//void PacketParser::packetReceived(QByteArray packet)
//{
//    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("new packet received : "), DLT_RAW(packet.data(), packet.size()));

//    QMutexLocker locker(&mMutex);

//    if ( mDecodePacketCallback != NULL )
//    {
//        mDecodePacketCallback(packet);
//    }
//    else
//    {
//        DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("Packet Parser state is UNKNOWN!! ignore packet"));
//    }
//}

//void PacketParser::setDecodeConnectionState()
//{
//    mDecodePacketCallback = std::bind(&PacketParser::decodePacketForConnection, this, std::placeholders::_1);
//}

//void PacketParser::setDecodeDataState()
//{
//    mDecodePacketCallback = std::bind(&PacketParser::decodePacketForData, this, std::placeholders::_1);
//}

//void PacketParser::decodePacketForConnection(const QByteArray & packet)
//{
//    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("decode packet for connection"));

//    if ( packet.at(MAIN_ID_POS) == ID_FIRMWARE_BLUETOOTH && packet.at(SUB_ID_POS) == SID_FIRMWARE_BLUETOOTH_SW_PIN_CODE )
//    {
//        emit signalRequestPINCode();
//    }

//    if ( packet.at(MAIN_ID_POS) == ID_REQUEST_SENSOR_DATA && packet.at(SUB_ID_POS) == SID_REQUEST_SENSOR_DATA_SELECT_ITEM )
//    {
//        emit signalResponseSelectSensorData();
//    }

//    if ( packet.at(MAIN_ID_POS) == ID_REQUEST_SENSOR_DATA && packet.at(SUB_ID_POS) == SID_REQUEST_SENSOR_DATA_BROADCASTING )
//    {
//        emit signalResponseSetBroadcastSensorData();
//    }
//}

//void PacketParser::decodePacketForData(const QByteArray & packet)
//{
//    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("decode packet for data"));
//    // deocde packet

//    QByteArray _packet_body;
//    QByteArray _packet_body_length;

//    if ( packet.at( MAIN_ID_POS ) == ID_REQUEST_SENSOR_DATA)
//    {
//        if ( packet.at( SUB_ID_POS ) == SID_REQUEST_SENSOR_DATA_BROADCASTING)
//        {
//            _packet_body_length = packet.mid( LENGTH_POS, 2 );

//            bool ok;
//            int length = _packet_body_length.toHex().toInt( &ok, 16 );
//            QVector<float> mSNSData;

//            _packet_body = packet.mid( DATA_POS, length );

//            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING("received packet = [SENSOR] [BROADCAST] ["), DLT_INT( length  ), DLT_STRING("Byte]") );
//            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_RAW(_packet_body.data(), length) );

//            mSNSData.clear();

//            for( int i = 0 ; i < _packet_body.size() ; i++)
//            {
//                if ( _packet_body[i] == (char)TYPEFLOAT )
//                {
//                    float _float = PacketDecoder::getValue<float>(_packet_body, i+1);

//                    // TO BE REMOVED
//                    if( (SensorIDIndex)(i/5) == SENSOR_IDX_FLI )
//                    {
//                        mSNSData.insert( (SensorIDIndex) (i/5), temp_fuel_level );
//                    }
//                    // ~ TO BE REMOVED
//                    else
//                    {
//                        mSNSData.insert( (SensorIDIndex) (i/5), _float );
//                    }

//                    i += FLOAT_SIZE;
//                }
//                else
//                {
//                    DLT_LOG( mContext, DLT_LOG_WARN, DLT_STRING( "inappropriate sensor broadcasting data" ) );
//                    mSNSData.clear();
//                }
//            }

//            if(mSNSData.size() == SENSOR_IDX_CMV+1)
//                emit notifySensorDataParsed(mSNSData);
//        }
//        else
//        {
//            DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING( "sensor data, not broadcast.. pass..." ) );
//        }
//    }
//    else
//    {
//        DLT_LOG( mContext, DLT_LOG_DEBUG, DLT_STRING( "unused data.. pass..." ) );
//    }
//}

//int CallBackFunction( u_int32_t serviceId, void *data, u_int32_t length )
//{
//    Q_UNUSED(serviceId);

//    DLT_LOG( PacketParser::instance()->mContext, DLT_LOG_DEBUG, DLT_STRING( "Call Back" ) );

//    if ( data == NULL || length == 0 )
//    {
//        DLT_LOG( PacketParser::instance()->mContext, DLT_LOG_DEBUG, DLT_STRING( "invalid command" ) );
//    }

//    QStringList list = QString::fromUtf8( (const char*)data ).split( "," );

//    if ( list.size() > 0 )
//    {
//        if ( list [0] == "help" )
//        {
//            DLT_LOG( PacketParser::instance()->mContext, DLT_LOG_DEBUG, DLT_STRING( "available command list" ) );
//            DLT_LOG( PacketParser::instance()->mContext, DLT_LOG_DEBUG, DLT_STRING( "> fuel, (0~100)%" ) );
//        }
//        else if ( list [0] == "fuel" )
//        {
//            DLT_LOG( PacketParser::instance()->mContext, DLT_LOG_DEBUG, DLT_STRING( "fuel : "), DLT_STRING( list[1].toLocal8Bit() ));
//            PacketParser::instance()->temp_fuel_level = list[1].toFloat();
//        }
//    }

//    return 0;
//}



//}
