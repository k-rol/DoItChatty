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
void QBiMap::insert(QTcpSocket *client, QString nickName)
{
    mapBySocket.insert(client, nickName);
    mapByUser.insert(nickName, client);
}

/*
 * Del map to both QMap when given the socket only
*/
bool QBiMap::remove(QTcpSocket *client)
{

    QString nickName;
    nickName = mapBySocket.value(client);
    int s = mapBySocket.remove(client);
    int n = mapByUser.remove(nickName);

    if (s == 0 || n == 0)
    {
        return false;
    }

    return true;
}

/*
 * Del map to both QMap when given the nickName only
*/
bool QBiMap::remove(QString nickName)
{
    QTcpSocket *client;
    client = mapByUser.value(nickName);
    int s = mapBySocket.remove(client);
    int n = mapByUser.remove(nickName);


    if (s == 0 || n == 0)
    {
        return false;
    }

    return true;
}

/*
 * Returns bool wether the QTcpSocket key already exist
*/
bool QBiMap::containsValue(QTcpSocket *client)
{
    if (mapBySocket.contains(client))
    {
        return true;
    }
    else return false;
}

/*
 * Returns bool wether the QString key already exist
*/
bool QBiMap::containsValue(QString nickName)
{
    if (mapByUser.contains(nickName))
    {
        return true;
    }
    else return false;
}

/*
 * Return QString with the nickName found in client
*/
QString QBiMap::value(QTcpSocket *client)
{
    QString nickName = mapBySocket.value(client);
    return nickName;
}

/*
 * Return QTcpSocket with the client socket found with the nickName
*/
QTcpSocket* QBiMap::value(QString nickName)
{
    QTcpSocket *client = mapByUser.value(nickName);
    return client;
}

/*
 * Returns a QStringList of the list of QString (nickName)
*/
QStringList QBiMap::listQString()
{
    QStringList nicknameList;
    foreach (QString nickName, mapByUser.keys()) {
        nicknameList.append(nickName);
    }
    return nicknameList;
}

/*
 * Returns QList of QTcpSocket of all of them
*/
QList<QTcpSocket*> QBiMap::listSocket()
{
    QList<QTcpSocket*> clientList;
    foreach (QTcpSocket* client, mapBySocket.keys()) {
        clientList.append(client);
    }
    return clientList;
}

/*
 *
*/
int QBiMap::count()
{
    int count = mapBySocket.count();

    return count;
}
