#ifndef INITSERVER_H
#define INITSERVER_H

#include <QObject>
#include <QMap>
#include <qbimap.h>
#include "ping.h"

class QTcpSocket;
class QTcpServer;
class MainWindow;
class QBiMap;
class Ping;

//using namespace QBiMap;
using namespace std;

class InitServer : public QObject
{
    Q_OBJECT
public:
    explicit InitServer(QObject *parent = 0);
    void startServer(int port);
    void stopServer(QString message);
    virtual ~InitServer();

signals:


public slots:

private slots:
    void acceptConnection();
    void readIncoming();
    void disconnected();
    void aboutToDisconnect();


private:
    void addConnection(QTcpSocket *client, QString nickName);
    void removeConnection(QTcpSocket *client);
    void updateUserList();
    void makeCommandList();
    void sendTextToAll(QString textToSend);
    void sendSystemMsgToAll(QString textToSend);
    void sendSystemMsgToOne(QString textToSend, QTcpSocket *client);
    //invokeMethod methods
    Q_INVOKABLE void textChatMethod(QTcpSocket *client, QString testToSend);
    Q_INVOKABLE void nickChatMethod(QTcpSocket *client, QString nickName);
    //End invokeMethod methods

    QString GetRandomString() const;
    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;
    MainWindow *mainWindow;
    QMap<QTcpSocket*, QString> connectionMap;
    QBiMap connectionBiMap;
    QList<QString> commandList;
    Ping ping;
    quint16 packetSize;

};

#endif // INITSERVER_H
