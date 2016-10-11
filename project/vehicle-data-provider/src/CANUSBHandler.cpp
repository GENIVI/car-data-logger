//#include "CANUSBHandler.h"

//#include <QDebug>
//#include <QThread>

//namespace CANUSB {

//#ifdef _TCC_ARM_
//#define DEVICE_NODE	"/dev/HVAC"
//#else
//#define DEVICE_NODE	"/dev/ttyUSB0"
//#endif

//#define PACKET_START    116     // 't'
//#define PACKET_END      13      // '\r'

//#define INVALID_POS     -1

//PortHandler * g_canusb_handler_instance = NULL;

//PortHandler * PortHandler::instance()
//{
//    if ( g_canusb_handler_instance == NULL )
//    {
//        g_canusb_handler_instance = new PortHandler;
//    }

//    return g_canusb_handler_instance;
//}

//PortHandler::~PortHandler()
//{
//}

//PortHandler::PortHandler()
//{
//    DLT_REGISTER_CONTEXT_LL_TS(mContext, "cuh", "CAN2USB Port Handler", DLT_LOG_DEBUG, DLT_TRACE_STATUS_OFF);
//    mPort = NULL;

//    openPort();
//    initPort();
//}

//void PortHandler::openPort()
//{
//    mPort = new QSerialPort;
//    mPort->setPortName(DEVICE_NODE);
//    mPort->setBaudRate(QSerialPort::Baud115200);
//    mPort->setDataBits(QSerialPort::Data8);
//    mPort->setParity(QSerialPort::NoParity);
//    mPort->setStopBits(QSerialPort::OneStop);
//    mPort->setFlowControl(QSerialPort::NoFlowControl);

//    if ( mPort->open(QIODevice::ReadWrite) )
//    {
//        DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("open port success !"));
//    }
//    else
//    {
//        DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("open port failed"));
//        DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("error : "), DLT_STRING( mPort->errorString().toLocal8Bit() ));
//    }

//    connect(mPort, SIGNAL(readyRead()), this, SLOT(readData()));
//}

//void PortHandler::closePort()
//{
//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("send close port command !"));

//    // send close can port command
//    char close_can_command []  = {'C', '\r'};
//    mPort->write(close_can_command, sizeof(close_can_command));
//}

//void PortHandler::initPort()
//{
//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("send clear buffer command !"));

//    // send clear buffer command
//    char clear_buffer_command [] = {'\r', '\r', '\r'};
//    mPort->write(clear_buffer_command, sizeof(clear_buffer_command));

//    QThread::currentThread()->msleep(200);

//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("send setup baud rate command !"));

//    // send set baud rate command
//#if 1
//    char baud_rate_command [] = {'S', '3', '\r'};       // 100 k
//#else
//    char baud_rate_command [] = {'S', '6', '\r'};       // 500 k
//#endif
//    mPort->write(baud_rate_command, sizeof(baud_rate_command));

//    QThread::currentThread()->msleep(200);

//    DLT_LOG(mContext, DLT_LOG_INFO, DLT_STRING("send open port command !"));

//    // send open can port command
//    char open_can_command [] = {'O', '\r'};
//    mPort->write(open_can_command, sizeof(open_can_command));
//}

//void PortHandler::readData()
//{
//    QByteArray data = mPort->readAll();

//    mBuffer.append( data );

//    while ( extractPacket() );
//}

//bool PortHandler::extractPacket()
//{
//    int packet_start_pos = getPacketStartPos(mBuffer);
//    int packet_end_pos = getPacketEndPos(mBuffer);

//    // there is no packet.. clear buffer
//    if ( packet_start_pos == INVALID_POS )
//    {
//        mBuffer.clear();

//        return false;
//    }

//    // incomplete packet.. remove from buffer
//    if ( packet_end_pos != INVALID_POS && packet_start_pos > packet_end_pos )
//    {
//        mBuffer.remove(0, packet_start_pos);

//        return true;
//    }

//    // there is packet.. extact packet from buffer
//    if ( packet_start_pos != INVALID_POS && packet_end_pos != INVALID_POS )
//    {
//        QByteArray packet = mBuffer.mid(packet_start_pos, (packet_end_pos - packet_start_pos) + 1);

//        notifyPacket( packet );

//        mBuffer.remove(0, packet_end_pos + 1);

//        return true;
//    }

//    return false;
//}

//int PortHandler::getPacketStartPos(QByteArray & buffer)
//{
//    for (int i = 0; i < buffer.size(); i++)
//    {
//        if ( buffer.at(i) == PACKET_START )
//        {
//            return i;
//        }
//    }

//    return INVALID_POS;
//}

//int PortHandler::getPacketEndPos(QByteArray & buffer)
//{
//    for (int i = 0; i < buffer.size(); i++)
//    {
//        if ( buffer.at(i) == PACKET_END )
//        {
//            return i;
//        }
//    }

//    return INVALID_POS;
//}

//void PortHandler::notifyPacket(QByteArray & packet)
//{
//    static int count = 0;

//    quint16 id = getID( packet );

//    if ( id == 0x0100 )
//    {
//        if ( count++ == 5 )
//        {
//            count = 0;
//        }
//        else
//        {
//            return;
//        }
//    }

//    QByteArray packet_data = swapByteOrder( convertStringToValue(packet) );

//    emit packetReceived(id, packet_data);
//}

//quint16 PortHandler::getID(QByteArray & packet)
//{
//    quint16 id = 0;

//    id = getValue( packet.at(1) );

//    id = id << 4;

//    id |= getValue( packet.at(2) );

//    id = id << 4;

//    id |= getValue( packet.at(3) );

//    return id;
//}

//quint16 PortHandler::getValue(char byte)
//{
//    switch ( byte )
//    {
//    case '0':       return 0x00;
//    case '1':       return 0x01;
//    case '2':       return 0x02;
//    case '3':       return 0x03;
//    case '4':       return 0x04;
//    case '5':       return 0x05;
//    case '6':       return 0x06;
//    case '7':       return 0x07;
//    case '8':       return 0x08;
//    case '9':       return 0x09;
//    case 'A':       return 0x0A;
//    case 'B':       return 0x0B;
//    case 'C':       return 0x0C;
//    case 'D':       return 0x0D;
//    case 'E':       return 0x0E;
//    case 'F':       return 0x0F;
//    }

//    return 0;
//}

//QByteArray PortHandler::convertStringToValue(QByteArray & packet)
//{
//    QByteArray converted_packet;

//    for (int i = 5; i < packet.size() - 1; i = i + 2)
//    {
//        char byte = (getValue(packet.at(i)) << 4) | getValue(packet.at(i + 1));

//        converted_packet.push_back( byte );
//    }

//    return converted_packet;
//}

//QByteArray PortHandler::swapByteOrder(QByteArray packet)
//{
//    QByteArray swap_packet;

//    for (int i = 0; i < packet.size(); i++)
//    {
//        swap_packet.push_front( packet.at(i) );
//    }

//    return swap_packet;
//}

//QString PortHandler::toStringChar(QByteArray & packet)
//{
//    QString packet_text;
//    for (int i = 0; i < packet.size(); i++)
//    {
//        QString byte = QString("%1 ").arg(packet.at(i));
//        packet_text += byte;
//    }

//    return packet_text;
//}

//QString PortHandler::toStringInt(QByteArray & packet)
//{
//    QString packet_text;
//    for (int i = 0; i < packet.size(); i++)
//    {
//        QString byte;
//        byte.sprintf("%02X ", (unsigned char)packet.at(i) & 0xFF);

//        packet_text += byte;
//    }

//    return packet_text;
//}

//}

