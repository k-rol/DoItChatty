#include "initserver.h"
#include <iostream>
#include <QtNetwork>
#include <QDebug>
#include <ui_mainwindow.h>
#include <mainwindow.h>

/*
 * Constructor that only set the uiMainWindow pointer
*/
InitServer::InitServer(QObject *parent) :
    QObject(parent), tcpserver(0), tcpsocket(0)
{
    qDebug() << "InitServer Instance Started.";

    mainWindow = static_cast<MainWindow*>(this->parent());

}

/*
 * Listen to the given port waiting for connections
*/
void InitServer::startServer(int port)
{
    tcpserver->listen(QHostAddress::Any, port);

    connect(tcpserver,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
}

/*
 *
*/
void InitServer::stopServer(QString message)
{
    tcpserver->close();
}

/*
 * Called by the newConnection() signal form QTcpServer, will instantiate the connec
*/
void InitServer::acceptConnection()
{
    tcpsocket = static_cast<QTcpSocket*>(sender());

    connect(tcpsocket,SIGNAL(readyRead()),this,SLOT(readIncoming()));
    connect(tcpsocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(tcpsocket,SIGNAL(aboutToClose()),this,SLOT(aboutToDisconnect()));
}

/*
 * Called when there is something received by the socket ready to be read
*/
void InitServer::readIncoming()
{
    QTcpSocket *client = static_cast<QTcpSocket*>(sender());
    QByteArray readContent = client->readAll();

}

/*
 * Called by aboutToClose() signal just before disconnecting a socket
*/
void InitServer::aboutToDisconnect()
{

}

/*
 * Called by the disconnected() signal from a socket
*/
void InitServer::disconnected()
{

}

/*
 * Destructor
*/
InitServer::~InitServer()
{
    qDebug() << "InitServer has been gargabe collected.";
}
