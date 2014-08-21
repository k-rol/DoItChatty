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
    void insert(QTcpSocket *client, QString nickName);
    bool remove(QTcpSocket *client);
    bool remove(QString nickName);
    bool containsValue(QTcpSocket *client);
    bool containsValue(QString nickName);
    QString value(QTcpSocket *client);
    QTcpSocket *value(QString nickName);
    QStringList listValue(typename QTcpSocket*);
    QStringList listValue(typename QString);
    int count();

signals:

public slots:

private:
    QMap<QTcpSocket*, QString> mapBySocket;
    QMap<QString, QTcpSocket*> mapByUser;


};

#endif // BIQMAP_H
