//#ifndef OBDPACKETPARSER
//#define OBDPACKETPARSER

//#include <functional>
//#include <QObject>
//#include <QMutex>
//#include <dlt.h>
//#include "OBDDefine.h"


//using namespace std;

//namespace OBD
//{

//class PacketParser : public QObject
//{
//    Q_OBJECT

//    typedef std::function<void(const QByteArray &)> DecodePacketCallback;

//private:
//    PacketParser();

//public:
//    ~PacketParser();

//public:
//    static PacketParser * instance();

//public:
//    void setDecodeConnectionState();
//    void setDecodeDataState();

//public slots:
//    void packetReceived(QByteArray packet);

//signals:
//    void signalRequestPINCode();
//    void signalResponseSelectSensorData();
//    void signalResponseSetBroadcastSensorData();

//    void notifySensorDataParsed(QVector<float> data);

//private:
//    void decodePacketForConnection(const QByteArray & packet);
//    void decodePacketForData(const QByteArray & packet);

//private:
//    DecodePacketCallback mDecodePacketCallback;
//    QMutex mMutex;

//public:
//    DLT_DECLARE_CONTEXT(mContext)
//    float temp_fuel_level;
//};

//}


//#endif // OBDPACKETPARSER

