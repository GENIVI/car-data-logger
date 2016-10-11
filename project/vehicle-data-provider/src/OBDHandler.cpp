//#include <stdio.h>
//#include <unistd.h>

//#include <sys/socket.h>
//#include <bluetooth/bluetooth.h>
//#include <bluetooth/rfcomm.h>

//#include <QDebug>
//#include <QTimer>

//#include <errno.h>

//#include "OBDHandler.h"
//#include "OBDPacketParser.h"


//namespace OBD {

//PortHandler * g_obd_handler_instance = NULL;

//PortHandler::PortHandler()
//{
////    DLT_REGISTER_CONTEXT(mContext, "obdh", "OBD Handler");
//    DLT_REGISTER_CONTEXT_LL_TS(mContext, "obdh", "OBD Handler", DLT_LOG_DEBUG, DLT_TRACE_STATUS_OFF);

//    mSocket = -1;
//}

//void PortHandler::initPort()
//{
//    sockaddr_rc addr;
//    unsigned char default_address[] = "00:18:9A:05:BA:58";
//    const char * obd_address = NULL;

//    char * env_address = getenv("OBD_ADDRESS");

//    if ( env_address )
//    {
//        obd_address = (const char *)env_address;

//        DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("use configured OBD Address ->"), DLT_STRING(obd_address));
//    }
//    else
//    {
//        obd_address = (const char *)default_address;

//        DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("use default OBD Address ->"), DLT_STRING(obd_address));
//    }

//    // allocate a socket
//    mSocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

//    // set the connection parameters (who to connect to)
//    addr.rc_family = AF_BLUETOOTH;
//    addr.rc_channel = (uint8_t) 1;
//    str2ba( obd_address, &addr.rc_bdaddr );

//    // connect to server
//    if ( ::connect(mSocket, (struct sockaddr *)&addr, sizeof(addr)) == 0 )
//    {
//        DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("connect to OBD success!!"));
//    }
//    else
//    {
//        int errNo = errno;

//        if (errNo == EHOSTDOWN)
//        {
//            DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("connect to OBD failed!!"), DLT_STRING("why? -> Host Is Down"));

//        }
//        else if( errNo == EBUSY )
//        {
//            DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("connect to OBD failed!!"), DLT_STRING("why? -> Device or Resource Busy"));
//        }
//        else if (errNo == ETIMEDOUT)
//        {
//            DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("connect to OBD failed!!"), DLT_STRING("why? -> Time Out."));
//        }
//        else
//        {
//            DLT_LOG(mContext, DLT_LOG_WARN, DLT_STRING("connect to OBD failed!!"), DLT_INT32( errNo ));
//        }

//    }
//}

//void PortHandler::closeConnection()
//{
//    if ( mSocket != -1 )
//    {
//        DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("disconnect from ODB"));

//        ::close(mSocket);
//    }
//}

//PortHandler::~PortHandler()
//{

//}

//PortHandler * PortHandler::instance()
//{
//    if ( g_obd_handler_instance == NULL )
//    {
//        g_obd_handler_instance = new PortHandler;
//    }

//    return g_obd_handler_instance;
//}

//void PortHandler::run()
//{
//    char read_buffer[1024] = {0, };

//    initPort();

//    while(1)
//    {
//        int read_size = ::read(mSocket, read_buffer, sizeof(read_buffer));

//        if ( read_size <= 0 )
//        {
//            continue;
//        }

//        // copy read data to buffer
//        for (int i = 0; i < read_size; i++)
//        {
//            mBuffer.push_back( read_buffer[i] );
//        }

//        // extract packet..
//        int extracted_size = extractPacket(mBuffer);

//        if ( extracted_size <= 0 )
//        {
//            // no packet received..
//            continue;
//        }

//        // if packet is extracted, remove extracted packet data from buffer
//        if ( extracted_size == mBuffer.size() )
//        {
//            mBuffer.clear();
//        }
//        else
//        {
//            mBuffer = mBuffer.mid(extracted_size - 1, mBuffer.size() - extracted_size);
//        }
//    }
//}

//int PortHandler::extractPacket(QByteArray & buffer)
//{
//    if ( buffer.size() > 0 )
//    {
//        int packet_start_position = getPacketStartPos(buffer);
//        int packet_end_position = getPacketEndPos(buffer);

//        if ( packet_start_position >= 0 && packet_end_position > 0 )
//        {
//            QByteArray packet;

//            for (int i = packet_start_position; i <= packet_end_position; i++)
//            {
//                packet.push_back( buffer.at(i) );
//            }

//            packet = PacketDecoder::decodePacket(packet);

//            emit packetReceived( packet );

//            return packet_end_position + 1;
//        }
//    }

//    return 0;
//}

//int PortHandler::getPacketStartPos(QByteArray & buffer)
//{
//    for (int i = 0; i < buffer.size(); i++)
//    {
//        if ( buffer.at(i) == STX )
//        {
//            return i;
//        }
//    }

//    return -1;
//}

//int PortHandler::getPacketEndPos(QByteArray & buffer)
//{
//    for (int i = 0; i < buffer.size(); i++)
//    {
//        if ( buffer.at(i) == CR )
//        {
//            return i;
//        }
//    }

//    return -1;
//}

//void PortHandler::writeData(OBD::Source source, OBD::Target target, OBD::MainID mainID, OBD::SubID subID, QByteArray data)
//{
//    QByteArray packet;

//    packet.push_back( STX );
//    packet.push_back( target );
//    packet.push_back( source );
//    packet.push_back( mainID );
//    packet.push_back( subID );

//    // data length
//    packet = PacketEncoder::addValue(packet, (short)data.size());

//    // add data
//    packet.append( data );

//    // check sum
//    packet.push_back( PacketEncoder::calculateCheckSum(packet) );

//    // encode packet for escape char
//    packet = PacketEncoder::encodePacket( packet );

//    // add end of packet
//    packet.push_back( CR );

//    DLT_LOG(mContext, DLT_LOG_DEBUG, DLT_STRING("Wrtie Data : " ), DLT_RAW(packet.data(), packet.size()));

//    ::write(mSocket, packet.data(), packet.size());
//}




//QByteArray PacketEncoder::encodePacket(QByteArray src)
//{
//    QByteArray des;

//    des.push_back( STX );

//    for (int i = 1; i < src.size(); i++)
//    {
//        if ( src.at(i) == STX || src.at(i) == CR || src.at(i) == ESCAPE )
//        {
//            des.push_back( ESCAPE );
//            des.push_back( static_cast<char>(src.at(i) & 0xFF) ^ ESC_COMPLEMENT_VALUE );
//        }
//        else
//        {
//            des.push_back( static_cast<char>(src.at(i) & 0xFF) );
//        }
//    }

//    return des;
//}

//char PacketEncoder::calculateCheckSum(QByteArray & src)
//{
//    char checksum = 0;

//    for (int i = 0; i < src.size(); i++)
//    {
//        checksum += static_cast<char>(src.at(i) & 0xFF);
//    }

//    return checksum;
//}



//QByteArray PacketDecoder::decodePacket(QByteArray src)
//{
//    QByteArray des;

//    des.push_back( src.at(0) );

//    for (int i = 1; i < src.size() - 1; i++)
//    {
//        if ( src.at(i) == ESCAPE )
//        {
//            i++;

//            des.push_back( static_cast<char>(src.at(i) & 0xFF)^ESC_COMPLEMENT_VALUE );
//        }
//        else
//        {
//            des.push_back( static_cast<char>(src.at(i) & 0xFF) );
//        }
//    }

//    des.push_back( static_cast<char>(src.at(src.size() - 1) & 0xFF) );

//    if ( !PacketDecoder::calculateCheckSum(des) )
//    {
//        // checksum error
//        des.clear();
//    }

//    return des;
//}

//bool PacketDecoder::calculateCheckSum(QByteArray & src)
//{
//    char checksum = 0;

//    for (int i = 0; i < src.size() - 2; i++)
//    {
//        checksum += static_cast<char>(src.at(i) & 0xFF);
//    }

//    if ( checksum == static_cast<char>(src.at(src.size() - 2) & 0XFF) )
//    {
//        return true;
//    }

//    return false;
//}

//}
