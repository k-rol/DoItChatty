#ifndef QBIMAP_H
#define QBIMAP_H

#include <QObject>
#include <QMap>

class QTcpSocket;


class QBiMap : public QObject
{
    Q_OBJECT
public:
    explicit QBiMap(QObject *parent = 0);
    void addConnection(QTcpSocket *client, QString nickName);
    bool delConnection(QTcpSocket *client);
    bool delConnection(QString nickName);
    bool containsConnection(QTcpSocket *client);
    bool containsConnection(QString nickName);
    QString getConnection(QTcpSocket *client);
    QTcpSocket *getConnection(QString nickName);
    QStringList listStringConnections();
    int countConnection();

signals:

public slots:

private:
    QMap<QTcpSocket*, QString> connectionMapBySocket;
    QMap<QString, QTcpSocket*> connectionMapByUser;


};

#endif // BIQMAP_H
