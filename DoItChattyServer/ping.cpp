#include "ping.h"

Ping::Ping(QObject *parent) :
    QObject(parent)
{
    pingTimer.setInterval(5000); //300000 is 5min
}

/*
 *
*/
void Ping::startPingTimer()
{
    pingTimer.start();
}


void Ping::responseTimerTimeOut()
{

}

void Ping::pingTimerTimeOut()
{

}

void Ping::comparePingResponses()
{

}

void Ping::kickPingNoResponse()
{

}
