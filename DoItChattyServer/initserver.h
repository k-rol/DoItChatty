#ifndef INITSERVER_H
#define INITSERVER_H

#include <QObject>
#include <QMap>

class QTcpSocket;
class QTcpServer;
class MainWindow;

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
    void removeConnection(QTcpSocket *client);
    void updateUserList();
    void makeCommandList();
    void sendTextToAll(QString textToSend);
    //invokeMethod methods
    Q_INVOKABLE void textChatMethod(QTcpSocket *client, QString testToSend);
    Q_INVOKABLE void nickChatMethod(QTcpSocket *client, QString nickName);
    //End invokeMethod methods

    QString GetRandomString() const;
    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;
    MainWindow *mainWindow;
    QMap<QTcpSocket*, QString> connectionMap;
    QList<QString> commandList;

};

#endif // INITSERVER_H
