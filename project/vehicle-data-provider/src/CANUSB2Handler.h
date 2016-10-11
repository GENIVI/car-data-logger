//#ifndef CANUSB2HANDLER_H
//#define CANUSB2HANDLER_H

//#include <QtSerialPort/QSerialPort>
//#include <QObject>

//#include <dlt.h>

//namespace CANUSB2{

//class PortHandler : public QObject
//{
//    Q_OBJECT

//public:
//    static PortHandler * instance();
//    ~PortHandler();

//private:
//    PortHandler();

//public:
//    void openPort();
//    void closePort();
//    void initPort();

//public slots:
//    void readData();

//signals:
//    void packetReceived(quint16 id, QByteArray packet);

//private:
//    bool extractPacket();
//    int getPacketStartPos(QByteArray & buffer);
//    int getPacketEndPos(QByteArray & buffer);

//    void notifyPacket(QByteArray & packet);
//    quint16 getID(QByteArray & packet);
//    QByteArray convertStringToValue(QByteArray & packet);
//    QByteArray swapByteOrder(QByteArray packet);

//    quint16 getValue(char byte);

//    QString toStringChar(QByteArray & packet);
//    QString toStringInt(QByteArray & packet);

//private:
//    QSerialPort * mPort;
//    QByteArray mBuffer;

//private:
//    DLT_DECLARE_CONTEXT(mContext)
//};

//}

//#endif // CANUSB2HANDLER_H
