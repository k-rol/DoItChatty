#include "initserver.h"
#include <iostream>
#include <QtNetwork>
#include <QDebug>
#include <mainwindow.h>
#include <qbimap.h>


/*
 * Constructor that only set the uiMainWindow pointer
*/
InitServer::InitServer(QObject *parent) :
    QObject(parent), tcpserver(0), tcpsocket(0), connectionBiMap(this)
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
    connect(client,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(client,SIGNAL(aboutToClose()),this,SLOT(aboutToDisconnect()));

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

        QMetaObject::invokeMethod(this,methodToCall.c_str(),Q_ARG(QTcpSocket*, client),Q_ARG(QString, afterCommand));
    }



}

/*
 * Call by invokeMethod when TEXT command is sent, to send normal chat text
*/
void InitServer::textChatMethod(QTcpSocket *client, QString textToSend)
{
    QString nickName = "<" + connectionBiMap.value(client) + "> ";
    QString completeSentence = nickName + textToSend;

    sendTextToAll(completeSentence);

}

/*
 * Call by invokeMethod when NICK command is sent, to map the socket under its nickname
*/
void InitServer::nickChatMethod(QTcpSocket *client, QString nickName)
{

    if (!connectionBiMap.containsValue(client))
    {
        if (!connectionBiMap.containsValue(nickName))
        {
            addConnection(client,nickName);
            qDebug() << "Socket for " + nickName + " has been added.";
            string welcomeString = "User " + nickName.toStdString() + " has joined the conversation.";
            sendTextToAll(welcomeString.c_str());
        }
        else
        {
            client->write("Username already taken.");
            client->disconnectFromHost();
        }

    }
    else
    {
        qDebug() << connectionBiMap.containsValue(nickName);
        qDebug() << nickName;
        if (connectionBiMap.containsValue(nickName)) //to change to search all values
        {
            client->write("Username already taken.");
        }
        else
        {
            QString oldNickName = connectionBiMap.value(client);
            addConnection(client, nickName);
            sendTextToAll("User " + oldNickName + " changed username to " + nickName);

        }
    }

}

/*
 * Sends text to all users
 * Should be using local variable instead of re-iterating each time
 * See updateUserList() below
*/
void InitServer::sendTextToAll(QString textToSend)
{
    QList<QTcpSocket*> allclients;

    allclients = connectionBiMap.listSocket();

    foreach (QTcpSocket *client, allclients) {
        client->write(textToSend.toStdString().c_str());
    }
}

/*
 * Updates the user list and number of usernames
*/
void InitServer::updateUserList()
{
    QStringList userList;
    userList = connectionBiMap.listQString();

    qDebug() << "Users still active:";
    foreach (QString nickName, userList) {
        qDebug() << nickName;
    }

    //update local QList<QString> variable
    //update local QList<QTcpSocket> variable
}

/*
 * Adds a socket(new client) to the QMap
*/
void InitServer::addConnection(QTcpSocket *client, QString nickName)
{
    //bool ok =
    connectionBiMap.insert(client, nickName);
    //qDebug() << ok;
}

/*
 * Removes a socket to the QMap
*/
void InitServer::removeConnection(QTcpSocket *client)
{
    QString nickName = connectionBiMap.value(client);
    if (nickName != NULL)
    {
        sendTextToAll("User " + nickName + " has disconnected.");
    }
    bool ok = connectionBiMap.remove(client);
    qDebug() << ok;
    client->deleteLater();
    updateUserList();
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
   const int randomStringLength = 5; // assuming you want random strings of 5 characters

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
