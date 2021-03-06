#include "tcpserver.h"
#include <iostream>
#include <QtNetwork>
#include <QDebug>
#include <ui_mainwindow.h>
#include <mainwindow.h>
#include <qnetworkproxy.h>

using namespace std;

/*
 * Constructor: Instantiates pointers to 0
 */
TcpServer::TcpServer(QObject *parent) : QObject(parent), qTcpServer(0)
{
    qTcpSocket = 0;
    packetSize = 0;
    qDebug() << "TcpServer instance created.";

    QNetworkProxyFactory::setUseSystemConfiguration(true);
}

/*
 * Listen button was pressed and app will be ready to do so
 */
void TcpServer::startListening(int port)
{
    qTcpServer = new QTcpServer(this);
    connect(qTcpServer, SIGNAL(newConnection()),this, SLOT(acceptConnection()));
    qTcpServer->listen(QHostAddress::Any, port);
    qDebug() << "Listening to port " + QString::number(port)+ "...";
    updateUiText("Listening to port " + QString::number(port) + "...");
    setUIButtons(QString("setListening"));
}

/*
 * Outcoming connection starting once Connect button was clicked
 */
void TcpServer::connectToHost(QString &ipAddressHost, int &port)
{
    if (qTcpSocket == NULL || qTcpSocket->state() == QTcpSocket::UnconnectedState)
    {
        qDebug() << "Reaching to Host...";
        updateUiText("Reaching to Host...");
        QHostAddress hostIp = QHostAddress(ipAddressHost);
        qTcpSocket = new QTcpSocket(this);
        connect(qTcpSocket, SIGNAL(connected()),this, SLOT(connectionSignals()));
        qTcpSocket->connectToHost(hostIp, port);

    }
    else
    {
        qTcpSocket->disconnectFromHost();
    }

}

/*
 * Called by the Connected Signal once a connection is being tried
 */
void TcpServer::acceptConnection()
{
    qTcpSocket = qTcpServer->nextPendingConnection();
    qTcpSocket->waitForReadyRead(0);

    connectionSignals();

}

/*
 * Connection Succesfull either incoming or outcoming
 * Connect signals for reading/disconnecting/about to close
 */
void TcpServer::connectionSignals()
{
    qDebug() << "Connected to " + qTcpSocket->peerAddress().toString() + " Succesfully.";
    updateUiText("Connected to " + qTcpSocket->peerAddress().toString() + " Succesfully.");
    setUIButtons(QString("setConnected"));

    qDebug() << qTcpSocket->proxy().hostName();

    connect(qTcpSocket, SIGNAL(readyRead()),this, SLOT(startRead()));
    connect(qTcpSocket, SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(qTcpSocket, SIGNAL(aboutToClose()),this, SLOT(aboutToDisconnect()));
    sendNickName();
}

/*
 * Called by readyRead signal when there are readable bytes in the socket
 */
void TcpServer::startRead()
{

    QDataStream dataStream(qTcpSocket);
    QString readContent;

    bool loop = true;
    while(qTcpSocket->bytesAvailable())
    {
        if (packetSize == 0)
        {
            if (qTcpSocket->bytesAvailable() < (int)sizeof(quint16))
                return;

            dataStream >> packetSize;
        }

        if (qTcpSocket->bytesAvailable() < packetSize)
            return;


        dataStream >> readContent;
        packetSize = 0;
        loop = false;
    }


    qDebug() << readContent;

    if (!IsACommand(readContent))
    {
        MainWindow *instanceMainWindow = static_cast<MainWindow*>(this->parent());

        instanceMainWindow->updateText(trimText(readContent));
    }


}

/*
 * Sends current used username
*/
void TcpServer::sendNickName()
{

    QString wholeText("NICK|");
    wholeText.append(nickName.c_str());

    QByteArray byteArrayText;
    QDataStream dataStream(&byteArrayText, QIODevice::WriteOnly);

    dataStream << quint16(0);
    dataStream << wholeText;
    dataStream.device()->seek(0);
    dataStream << (quint16)(byteArrayText.size() - sizeof(quint16));


    qTcpSocket->write(byteArrayText);


}

/*
 * Updates the UI MainWindow when there are specific system messages
 */
void TcpServer::updateUiText(QString textToSend)
{
    MainWindow *instanceMainWindow = static_cast<MainWindow*>(this->parent());
    instanceMainWindow->systemMessages(textToSend);
}

/*
 * Trim text received before sending it to the UI
 * Removes all kind of spaces
 */
QString TcpServer::trimText(QString &toTrim)
{
    QString trimmedQString = QString(toTrim);

    if (trimmedQString.endsWith("\n"))
    {
        trimmedQString.remove(trimmedQString.length()-1,1);
    }
    else if (trimmedQString.endsWith("\r\n") || trimmedQString.endsWith("\n\r"))
    {
        trimmedQString.remove(trimmedQString.length()-2,2);
    }

    return trimmedQString.trimmed();
}

/*
 * Bool whether it is a system message or not
 */
bool TcpServer::IsACommand(QString &possibleCommand)
{

    QList<QString> commandList;
    commandList << "CMD DISCONNECT";
    commandList << "PING|";

    if (commandList.contains(trimText(possibleCommand)))
    {
        qDebug() << "THERE IS A COMMAND, GUYS!!";
        return true;
    }

    return false;
}

/*
 * Will call method in MainWindow to enable or disable different set of buttons
 */
void TcpServer::setUIButtons(QString set)
{
    MainWindow *instanceMainWindow = static_cast<MainWindow*>(this->parent());
    instanceMainWindow->setButtonEnabilities(set);
}

/*
 * Does Nothing at all.
 */
void TcpServer::nothingreally()
{
    qDebug() << "NothingReally...";
}

/*
 * Writes the text to the socket to be sent to HOST
 */
void TcpServer::writeSomething(string textToSend)
{
    QString wholeText = "TEXT|";
    wholeText.append(textToSend.c_str());

    QByteArray byteArrayText;
    QDataStream dataStream(&byteArrayText, QIODevice::WriteOnly);

    dataStream << quint16(0);
    dataStream << wholeText;
    dataStream.device()->seek(0);
    dataStream << (quint16)(byteArrayText.size() - sizeof(quint16));
    qDebug() << (quint16)(byteArrayText.size() - sizeof(quint16));

    qTcpSocket->write(byteArrayText);
}

/*
 * Stops listening when button is pressed
 */
void TcpServer::stopListening()
{
    if (qTcpServer != 0 && qTcpServer->isListening())
    {
        updateUiText("Stopped Listening");
        setUIButtons(QString("setNotListening"));
        qTcpServer->close();
        qTcpServer = 0;
    }
}

/*
 * Local disconneciton request
 * Will alert peer of the disconection
 */
void TcpServer::disconnectIt()
{
    if (qTcpSocket != 0 && qTcpSocket->isOpen())
    {
        //writeSomething("CMD DISCONNECT");
        updateUiText("Disconnected");
        setUIButtons(QString("setDisconnected"));
        qTcpSocket->close();
        qTcpSocket = 0;
    }
}

/*
 * SLOT called when the socket disconnects
 */
void TcpServer::disconnected()
{
    if (qTcpSocket != 0 && qTcpSocket->isOpen())
    {
        updateUiText("Disconnected");
        setUIButtons(QString("setDisconnected"));
        qTcpSocket->close();
        qTcpSocket = 0;
    }
}

/*
 * SLOT called just before it actually disconnects
 */
void TcpServer::aboutToDisconnect()
{

}

/*
 * Destructor
 */
TcpServer::~TcpServer()
{
//    delete qTcpSocket;
//    qTcpServer->close();
    qDebug() << "TcpServer instance deleted";
}

