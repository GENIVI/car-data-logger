//#ifndef OBDHANDLER
//#define OBDHANDLER

//#include <QThread>
//#include <QByteArray>
//#include <QDebug>
//#include <dlt.h>
//#include "OBDDefine.h"


//namespace OBD
//{

//class PortHandler : public QThread
//{
//    Q_OBJECT

//private:
//    PortHandler();
//public:
//    ~PortHandler();

//public:
//    static PortHandler * instance();

//public:
//    void writeData(OBD::Source source, OBD::Target target, OBD::MainID mainID, OBD::SubID subID, QByteArray data);
//    void closeConnection();
//    static int getPacketStartPos(QByteArray & buffer);
//    static int getPacketEndPos(QByteArray & buffer);

//signals:
//    void packetReceived(QByteArray packet);

//private:
//    void initPort();
//    int extractPacket(QByteArray & buffer);

//protected:
//    virtual void run();

//private:
//    int mSocket;
//    QByteArray mBuffer;

//    DLT_DECLARE_CONTEXT(mContext)
//};




//class PacketEncoder
//{
//public:
//    template<typename T>
//    static QByteArray addValue(QByteArray des, T value);

//    template<typename T>
//    static QByteArray addValueByteOrder(QByteArray des, T value);

//    static QByteArray encodePacket(QByteArray src);
//    static char calculateCheckSum(QByteArray & src);
//};


//class PacketDecoder
//{
//public:
//    template<typename T>
//    static T getValue(QByteArray src, int position);

//    template<typename T>
//    static T getValueByteOrder(QByteArray src, int position);

//    static QByteArray decodePacket(QByteArray src);
//    static bool calculateCheckSum(QByteArray & src);
//};


//template<typename T>
//QByteArray PacketEncoder::addValue(QByteArray des, T value)
//{
//    // 12 34 56 78 -> 12 34 56 78

//    for (int i = 0; i < sizeof(T); i++)
//    {
//        int shift = ((sizeof(T) - 1) - i) * 8;

//        des.push_back( static_cast<char>(value >> shift & 0xFF ) );
//    }

//    return des;
//}

//template<typename T>
//QByteArray PacketEncoder::addValueByteOrder(QByteArray des, T value)
//{
//    // 12 34 56 78 -> 78 56 34 12

//    for (int i = 0; i < sizeof(T); i++)
//    {
//        des.push_back( static_cast<char>(value & 0xFF) );

//        value = value >> 8;
//    }

//    return des;
//}

//template<typename T>
//T PacketDecoder::getValue(QByteArray src, int position)
//{
//    // 12 34 56 78 -> 12 34 56 78

//    T value = 0;

//    memcpy(&value, src.data() + position, sizeof(T));

//#if 0
//    if ( src.size() >= position + sizeof(T) )
//    {
//        for (int i = 0; i < sizeof(T); i++)
//        {
//            if ( i > 0 )
//            {
//                value = value << 8;
//            }

//            value |= src.at(position + i) & 0xFF;
//        }
//    }
//#endif

//    return value;
//}

//template<typename T>
//T PacketDecoder::getValueByteOrder(QByteArray src, int position)
//{
//    // 12 34 56 78 -> 78 56 34 12

//    T value = 0;

//    if ( src.size() >= position + sizeof(T) )
//    {
//        for (int i = 0; i < sizeof(T); i++)
//        {
//            value |= (src.at(position + i) & 0xFF) << (((sizeof(T) - 1) - i) * 8);
//        }
//    }

//    return value;
//}

//}

//#endif // OBDHANDLER

