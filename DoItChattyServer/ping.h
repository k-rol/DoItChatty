#ifndef PING_H
#define PING_H

#include <QObject>
#include <QTimer>

class QTcpSocket;
class QBiMap;

class Ping : public QObject
{
    Q_OBJECT
public:
    explicit Ping(QObject *parent = 0, QBiMap *connections = 0);
    void startPingTimer();
    virtual ~Ping();

signals:

public slots:


private:
    void comparePingResponses();
    void kickPingNoResponse();
    QTimer *pingTimer;
    QBiMap * clientMap;

private slots:
    void pingTimerTimeOut();
    void responseTimerTimeOut();
};

#endif // PING_H
