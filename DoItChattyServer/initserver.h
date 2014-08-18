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
    void textChatMethod(QTcpSocket *client, QString testToSend);
    void nickChatMethod(QTcpSocket *client, QString nickName);


private:
    void addConnection(QTcpSocket *client);
    void removeConnection(QTcpSocket *client);
    void updateUserList();
    void makeCommandList();
    QString GetRandomString() const;
    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;
    MainWindow *mainWindow;
    QMap<QTcpSocket*, string> connectionMap;
    QList<QString> commandList;

};

#endif // INITSERVER_H
