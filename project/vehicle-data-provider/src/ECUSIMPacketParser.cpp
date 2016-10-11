//#include "ECUSIMPacketParser.h"
//#include "CANUSB2Handler.h"
//#include "OBDDefine.h"

//namespace ECUSIM
//{

//#define CAN_ID_ECU      0x0100

//int CallBackFunction( u_int32_t serviceId, void *data, u_int32_t length );

//PacketParser * g_ecu_sim_packet_parser_instance = NULL;

//PacketParser * PacketParser::instance()
//{
//    if ( g_ecu_sim_packet_parser_instance == NULL )
//    {
//        g_ecu_sim_packet_parser_instance = new PacketParser;
//    }

//    return g_ecu_sim_packet_parser_instance;
//}

//PacketParser::~PacketParser()
//{
//    DLT_UNREGISTER_CONTEXT(mContext);
//}

//PacketParser::PacketParser()
//{
//    DLT_REGISTER_CONTEXT_LL_TS(mContext, "esdp", "ECU Simulator Data Parser", DLT_LOG_DEBUG, DLT_TRACE_STATUS_OFF);
//    DLT_REGISTER_INJECTION_CALLBACK( mContext, 0xfff, CallBackFunction );

//    mVehicleSpeed = 0;
//    mEngineSpeed = 0;
//    mFuelLevel = 50;

//    connect(CANUSB2::PortHandler::instance(), SIGNAL(packetReceived(quint16,QByteArray)), this, SLOT(packetReceived(quint16,QByteArray)));
//}

//void PacketParser::setManualFuelLevel(quint16 fuelLevel)
//{
//    mFuelLevel = fuelLevel;

//    emit notifyECUDataParsed(0,
//                             0,
//                             mFuelLevel);
//}

//DltContext & PacketParser::context()
//{
//    return mContext;
//}

//void PacketParser::packetReceived(quint16 id, QByteArray packet)
//{
//    if ( id ==  CAN_ID_ECU )
//    {
//        decodePacket(packet);
//    }
//}

//void PacketParser::decodePacket(QByteArray & packet)
//{
//    emit notifyECUDataParsed(decodeVehicleSpeed(packet),
//                             decodeEngineSpeed(packet),
//                             mFuelLevel);
//}

//quint16 PacketParser::decodeVehicleSpeed(QByteArray & packet)
//{
//    quint16 raw_speed = 0;

//#if 0
//    raw_speed = (packet[2] & 0xFF) << 8;
//    raw_speed |= (packet[3] & 0xFF);
//#else
//    raw_speed = (packet[4] & 0xFF) << 8;
//    raw_speed |= (packet[5] & 0xFF);
//#endif

//    quint16 speed = (double)raw_speed / ((double)0x0FFF / (double)200);

//    if ( speed < 2 )
//    {
//        speed = mVehicleSpeed = 0;
//    }
//    else if ( abs(mVehicleSpeed - speed) < 2 )
//    {
//        speed = mVehicleSpeed;
//    }
//    else
//    {
//        mVehicleSpeed = speed;
//    }

//    return speed;
//}

//quint16 PacketParser::decodeEngineSpeed(QByteArray & packet)
//{
//    quint16 raw_rpm = 0;

//#if 0
//    raw_rpm = (packet[0] & 0xFF) << 8;
//    raw_rpm |= (packet[1] & 0xFF);
//#else
//    raw_rpm = (packet[2] & 0xFF) << 8;
//    raw_rpm |= (packet[3] & 0xFF);
//#endif

//    quint16 rpm = (double)raw_rpm / ((double)0x0FFF / (double)8000);

//    if ( rpm < 30 )
//    {
//        rpm = mEngineSpeed = 0;
//    }
//    else if ( abs(mEngineSpeed - rpm) < 30 )
//    {
//        rpm = mEngineSpeed;
//    }
//    else
//    {
//        mEngineSpeed = rpm;
//    }

//    return rpm;
//}

//int CallBackFunction( u_int32_t serviceId, void *data, u_int32_t length )
//{
//    Q_UNUSED(serviceId);

//    DLT_LOG( PacketParser::instance()->context(), DLT_LOG_DEBUG, DLT_STRING( "Call Back" ) );

//    if ( data == NULL || length == 0 )
//    {
//        DLT_LOG( PacketParser::instance()->context(), DLT_LOG_DEBUG, DLT_STRING( "invalid command" ) );
//    }

//    QStringList list = QString::fromUtf8( (const char*)data ).split( "," );

//    if ( list.size() > 0 )
//    {
//        if ( list [0] == "help" )
//        {
//            DLT_LOG( PacketParser::instance()->context(), DLT_LOG_DEBUG, DLT_STRING( "available command list" ) );
//            DLT_LOG( PacketParser::instance()->context(), DLT_LOG_DEBUG, DLT_STRING( "> fuel, (0~100)%" ) );
//        }
//        else if ( list [0] == "fuel" )
//        {
//            DLT_LOG( PacketParser::instance()->context(), DLT_LOG_DEBUG, DLT_STRING( "fuel : "), DLT_STRING( list[1].toLocal8Bit() ));
//            PacketParser::instance()->setManualFuelLevel( list[1].toInt() );
//        }
//    }

//    return 0;
//}


//}
