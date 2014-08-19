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

    makeCommandList();
}

void InitServer::makeCommandList()
{
    commandList.append("NICK");
    commandList.append("TEXT");
    //commandList.append("ME");
    //commandList.append("");
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
    connectionMap.insert("first", client);

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

    QStringList stringContent = QString(readContent).split("|");

    if (commandList.contains(stringContent.first()))
    {
        string methodToCall = stringContent.first().toLower().toStdString() + "ChatMethod";
        stringContent.removeFirst();
        QString afterCommand = stringContent.join("|");
        client->write(afterCommand.toStdString().c_str());
        //methodToCall.c_str()
        QMetaObject::invokeMethod(this,"textChatMethod",Q_ARG(QTcpSocket, *client),Q_ARG(QString, stringContent.at(1)));


    }
    else
    {

    }


}

void InitServer::textChatMethod(QTcpSocket *client, QString textToSend)
{
    client.write(textToSend.toStdString().c_str());

}

void InitServer::nickChatMethod(QTcpSocket *client, QString nickName)
{
    connectionMap
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

QString InitServer::GetRandomString() const
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 5; // assuming you want random strings of 12 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}

/*
 * Destructor
*/
InitServer::~InitServer()
{
    qDebug() << "InitServer has been gargabe collected.";
}
