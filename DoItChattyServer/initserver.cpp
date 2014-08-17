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

    //connectionMap = new QMap<QTcpSocket*, string>; //no need??

}

/*
 * Listen to the given port waiting for connections
*/
void InitServer::startServer(int port)
{
    tcpserver = new QTcpServer(this);
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
 * Called by the newConnection() signal form QTcpServer, will instantiate the connection
*/
void InitServer::acceptConnection()
{
    QTcpServer *listened = static_cast<QTcpServer*>(sender());
    QTcpSocket *client = listened->nextPendingConnection();

    connect(client,SIGNAL(readyRead()),this,SLOT(readIncoming()));

    client->write("Connected");

    connect(client,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(client,SIGNAL(aboutToClose()),this,SLOT(aboutToDisconnect()));

}

/*
 * Adds a socket(new client) to the QMap
*/
void InitServer::addConnection(QTcpSocket *client)
{
    connectionMap.insert(client, "first");

    updateUserList();
}

/*
 * Updates the user list and number of
*/
void InitServer::updateUserList()
{

}

/*
 * Removes a socket(new client) to the QMap
*/
void InitServer::removeConnection(QTcpSocket *client)
{
    connectionMap.remove(client);
    updateUserList();
}

/*
 * Called when there is something received by the socket ready to be read
*/
void InitServer::readIncoming()
{
    QTcpSocket *client = static_cast<QTcpSocket*>(sender());
    QByteArray readContent = client->readAll();
    qDebug() << readContent;

    QString stringContent = QString(readContent).split();

    if (commandList.contains(readContent))
    {
        qDebug() << "THERE IS A COMMAND, GUYS!!";

    }

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
    QTcpSocket *client = static_cast<QTcpSocket*>(sender());
    removeConnection(client);
}

/*
 * Destructor
*/
InitServer::~InitServer()
{
    qDebug() << "InitServer has been gargabe collected.";
}
