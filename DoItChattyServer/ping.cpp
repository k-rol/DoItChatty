#include "ping.h"
#include "qbimap.h"
#include <qtcpsocket.h>

Ping::Ping(QObject *parent, QBiMap *connections) :
    QObject(parent)
{
    pingTimer = new QTimer(this);
    pingTimer->setInterval(300000); //300000 is 5min
    clientMap = connections;
}

/*
 * Starts the timer to ping each client every x msec
*/
void Ping::startPingTimer()
{
    qDebug() << "ping timer started...";
    pingTimer->start();
    connect(pingTimer,SIGNAL(timeout()),this,SLOT(pingTimerTimeOut()));
}

/*
 *
*/
void Ping::pingTimerTimeOut()
{
    QList<QTcpSocket*> allClientsSockets;

    allClientsSockets = clientMap->listSocket();
    //allClientsNickNames = clientMap->listQString();
    qDebug() << "!ping timeout!";
    foreach (QTcpSocket *client, allClientsSockets) {
        client->write("PING|");
        qDebug() << "PING|";
    }
}

/*
 *
*/
void Ping::responseTimerTimeOut()
{

}

/*
 *
*/
void Ping::comparePingResponses()
{

}

/*
 *
*/
void Ping::kickPingNoResponse()
{

}

Ping::~Ping()
{
    qDebug() << "Ping destroyed";
}
