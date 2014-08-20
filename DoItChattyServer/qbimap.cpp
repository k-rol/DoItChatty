#include "qbimap.h"
#include <QTcpSocket>
#include <QStringList>

QBiMap::QBiMap(QObject *parent) :
    QObject(parent)
{
}

/*
 * Add map to both QMap
*/
void QBiMap::addConnection(QTcpSocket *client, QString nickName)
{
    connectionMapBySocket.insert(client, nickName);
    connectionMapByUser.insert(nickName, client);
}

/*
 * Del map to both QMap when given the socket only
*/
bool QBiMap::delConnection(QTcpSocket *client)
{

    QString nickName;
    nickName = connectionMapBySocket.value(client);
    int s = connectionMapBySocket.remove(client);
    int n = connectionMapByUser.remove(nickName);

    if (s == 0 || n == 0)
    {
        return false;
    }

    return true;
}

/*
 * Del map to both QMap when given the nickName only
*/
bool QBiMap::delConnection(QString nickName)
{
    QTcpSocket *client;
    client = connectionMapByUser.value(nickName);
    int s = connectionMapBySocket.remove(client);
    int n = connectionMapByUser.remove(nickName);


    if (s == 0 || n == 0)
    {
        return false;
    }

    return true;
}

/*
 * Returns bool wether the QTcpSocket key already exist
*/
bool QBiMap::containsConnection(QTcpSocket *client)
{
    if (connectionMapBySocket.contains(client))
    {
        return true;
    }
    else return false;
}

/*
 * Returns bool wether the QString key already exist
*/
bool QBiMap::containsConnection(QString nickName)
{
    if (connectionMapByUser.contains(nickName))
    {
        return true;
    }
    else return false;
}

/*
 * Return QString with the nickName found in client
*/
QString QBiMap::getConnection(QTcpSocket *client)
{
    QString nickName = connectionMapBySocket.value(client);
    return nickName;
}

/*
 * Return QTcpSocket with the client socket found with the nickName
*/
QTcpSocket* QBiMap::getConnection(QString nickName)
{
    QTcpSocket *client = connectionMapByUser.value(nickName);
    return client;
}

/*
 * Returns a QStringList of the list of QString (nickName)
*/
QStringList QBiMap::listStringConnections()
{
    QStringList ha;
    return ha;
}

/*
 *
*/
int QBiMap::countConnection()
{
    int count = connectionMapBySocket.count();

    return count;
}
