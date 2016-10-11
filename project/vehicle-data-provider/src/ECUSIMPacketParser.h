//#ifndef ECUSIMPACKETPARSER_H
//#define ECUSIMPACKETPARSER_H

//#include <QObject>
//#include <dlt.h>

//namespace ECUSIM
//{

//class PacketParser : public QObject
//{
//    Q_OBJECT

//public:
//    static PacketParser * instance();
//    ~PacketParser();

//private:
//    PacketParser();

//public:
//    void setManualFuelLevel(quint16 fuelLevel);
//    DltContext & context();

//public slots:
//    void packetReceived(quint16 id, QByteArray packet);

//private:
//    void decodePacket(QByteArray & packet);
//    quint16 decodeVehicleSpeed(QByteArray & packet);
//    quint16 decodeEngineSpeed(QByteArray & packet);

//signals:
//    void notifyECUDataParsed(quint16 vehicleSpeed, quint16 EngineSpeed, quint16 fuelLevel);

//private:
//    DLT_DECLARE_CONTEXT(mContext)

//    quint16 mVehicleSpeed;
//    quint16 mEngineSpeed;
//    quint16 mFuelLevel;
//};

//}

//#endif // ECUSIMPACKETPARSER_H
