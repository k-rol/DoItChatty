#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include "QmlBridge.h"

using namespace std;

class QTcpServer;
class QTcpSocket;

class MainWindow;

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = 0);
    void startListening(int port);
    void connectToHost(QString &ipAddressHost, int &port);
    void writeSomething(string textToSend);
    void sendNickName();
    void disconnectIt();
    void stopListening();
    string nickName;
    virtual ~TcpServer();

private slots:
    void acceptConnection();
    void connectionSignals();
    void startRead();
    void disconnected();
    void nothingreally();
    void aboutToDisconnect();

private:
    void setUIButtons(QString set);
    QString trimText(QString &toTrim);
    bool IsACommand(QString &possibleCommand);
    void updateUiText(QString textToSend);
    QTcpServer *qTcpServer;
    QTcpSocket *qTcpSocket;
    quint16 packetSize;

    MainWindow *mainWindow;

};

#endif // TCPSERVER_H
