#ifndef TCPIPASTM_H
#define TCPIPASTM_H

#include <QObject>
#include <QTcpSocket>
//#include <QTimer>
//#include <QByteArray>


class tcpipastm : public QObject
{
    Q_OBJECT
public:
    explicit tcpipastm(QObject *parent = 0);
//    void sendToServer(QString &);
//    void highASTM(QString &, QString, QString, QString, QString, QString, int, QString, int);
//    void connectToServer();
//    void disconnectToServer();
    void writeFrame(const QByteArray &);
    QString getDataReceived();


signals:
//    void signalState();
    void signalReceivedRepositories();
    void signalReceivedRepositoriesUP();
    void signalReceivedRepositoriesDOWN();

public slots:

private slots:
//   void stateASTM();
   void slotReadyRead();
//   void timeOutTimerTcpip();

private:
//    bool checkComand(quint8);
//    void transmittingFrame();
    //void writeFrame(const QByteArray &);
//    quint8 createCheckSum(const QByteArray &);
    void writeComand(quint8);
//    void changeToNeutralTransmit();


private:
    QTcpSocket *socket;
    QString data_received;
//    enum statesProtocolTcpIp{
//        NEUTRAL,
//        ESTABLISHMENT,
//        TRANSFER,
//        TRANSMIT,
//        RECEIVE,
//        TERMINATION
//    };
//    statesProtocolTcpIp stateProtocolTcpIp;
//    QTimer *timer_tcpip;
//    QByteArray arr_receivedData;
//    QByteArray arr_dataToSend;
//    int frame_number;
//    int nak_count;
//    bool add_frame_transmitting;
};
#endif // TCPIPASTM_H
