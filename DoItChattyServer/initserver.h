#ifndef INITSERVER_H
#define INITSERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <ui_mainwindow.h>

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
    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;
    Ui_MainWindow *uiMainWindow;

};

#endif // INITSERVER_H
