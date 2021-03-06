#include "initserver.h"
#include <iostream>
#include <QtNetwork>
#include <QDebug>
#include <mainwindow.h>
#include <qbimap.h>
#include "ping.h"


/*
 * Constructor that only set the uiMainWindow pointer
*/
InitServer::InitServer(QObject *parent) :
    QObject(parent), tcpserver(0), tcpsocket(0), connectionBiMap(this), ping(this, &connectionBiMap)
{
    qDebug() << "InitServer Instance Started.";
    packetSize = 0;

    mainWindow = static_cast<MainWindow*>(this->parent());

    makeCommandList();
    //Ping ping = new Ping(this, &connectionBiMap);


}

void InitServer::makeCommandList()
{
    commandList.append("NICK");
    commandList.append("TEXT");
    //commandList.append("PING");
    //commandList.append("");
}

/*
 * Listen to the given port waiting for connections
*/
void InitServer::startServer(int port)
{
    if (tcpserver == 0 || !tcpserver->isListening())
    {
        tcpserver = new QTcpServer(this);
        tcpserver->listen(QHostAddress::Any, port);

        connect(tcpserver,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    }

    ping.startPingTimer();
}

/*
 *
*/
void InitServer::stopServer(QString message)
{
    if (tcpserver != 0 && tcpserver->isListening())
    {
        QList<QTcpSocket*> allclients;

        allclients = connectionBiMap.listSocket();

        foreach (QTcpSocket *client, allclients) {
            //client->write("Server is shutting down.");
            sendSystemMsgToOne("Server is shutting down.", client);
            client->close();
        }
        //send to UI ("Stopped Listening");
        tcpserver->close();
        tcpserver = 0;
    }
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
    QDataStream dataStream(client);
    QString readContent;
    bool loop = true;
    while(client->bytesAvailable())
    {
        if (packetSize == 0)
        {
            if (client->bytesAvailable() < (int)sizeof(quint16))
                return;

            dataStream >> packetSize;
            qDebug() << "PacketSize:";
            qDebug() << packetSize;
        }

        if (client->bytesAvailable() < packetSize)
        {
            qDebug() << QString("bytesAvailable %1 < packetSize %2").arg(QString::number(client->bytesAvailable()),QString::number(packetSize));
            return;
        }


        dataStream >> readContent;
        qDebug() << "readContent:";
        qDebug() << readContent;
        qDebug() << readContent.length();
        loop = false;
        packetSize = 0;
    }



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
            string welcomeString = "User " + nickName.toStdString() + " has joined the conversation.";
            sendTextToAll(welcomeString.c_str());
            addConnection(client,nickName);
            qDebug() << "Socket for " + nickName + " has been added.";

        }
        else
        {
            //client->write("Username already taken.");
            sendSystemMsgToOne("Username already taken.", client);
            client->disconnectFromHost();
        }

    }
    else
    {
        qDebug() << connectionBiMap.containsValue(nickName);
        qDebug() << nickName;
        if (connectionBiMap.containsValue(nickName)) //to change to search all values
        {
            //client->write("Username already taken.");
            sendSystemMsgToOne("Username already taken.", client);
        }
        else
        {
            QString oldNickName = connectionBiMap.value(client);
            connectionBiMap.remove(client);
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
    QByteArray byteArrayText;
    QDataStream dataStream(&byteArrayText, QIODevice::WriteOnly);

    dataStream << quint16(0);
    dataStream << textToSend;
    dataStream.device()->seek(0);
    dataStream << (quint16)(byteArrayText.size() - sizeof(quint16));

    QList<QTcpSocket*> allclients;

    allclients = connectionBiMap.listSocket();

    foreach (QTcpSocket *client, allclients) {
        //client->write(textToSend.toStdString().c_str()); //before dataStream
        client->write(byteArrayText);
    }
}

void InitServer::sendSystemMsgToAll(QString textToSend)
{
    QByteArray byteArrayText;
    QDataStream dataStream(&byteArrayText, QIODevice::WriteOnly);

    dataStream << quint16(0);
    dataStream << textToSend;
    dataStream.device()->seek(0);
    dataStream << (quint16)(byteArrayText.size() - sizeof(quint16));

    QList<QTcpSocket*> allclients;

    allclients = connectionBiMap.listSocket();

    foreach (QTcpSocket *client, allclients) {
        client->write(byteArrayText);
    }

}

void InitServer::sendSystemMsgToOne(QString textToSend, QTcpSocket *client)
{
    QByteArray byteArrayText;
    QDataStream dataStream(&byteArrayText, QIODevice::WriteOnly);

    dataStream << quint16(0);
    dataStream << textToSend;
    dataStream.device()->seek(0);
    dataStream << (quint16)(byteArrayText.size() - sizeof(quint16));

    client->write(byteArrayText);
}

/*
 * Updates the user list on GUI
*/
void InitServer::updateUserList()
{
    QStringList userList;
    userList = connectionBiMap.listQString();

    mainWindow->clearUserList();

    qDebug() << "Users still active:";
    foreach (QString nickName, userList) {
        //qDebug() << nickName;
        mainWindow->addUser(nickName);
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
    updateUserList();
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
