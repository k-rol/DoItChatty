/*
 * QmlBridge.h
 *
 *  Created on: Aug 24, 2014
 *      Author: CaroL
 */

#ifndef QMLBRIDGE_H_
#define QMLBRIDGE_H_
#include <QObject>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/controls/textarea.h>
#include <bb/cascades/controls/textfield.h>
#include <bb/cascades/controls/button.h>
#include "tcpserver.h"

using namespace bb::cascades;

class TcpServer;



class QmlBridge: public QObject
{
    Q_OBJECT
public:
    QmlBridge(QObject *parent = 0);
    void setQml(AbstractPane *root);
    void updateText(QString readContent);
    void systemMessages(QString textToSend);
    Q_INVOKABLE void setButtonEnabilities(QString set);
    Q_INVOKABLE void setUIButtons(QString set);
    Q_INVOKABLE void on_sendTextButton_clicked(QString textToSend);
    Q_INVOKABLE void on_disconnectButton_clicked();
    Q_INVOKABLE void on_connectButton_clicked(QString nickName);
    Q_INVOKABLE void on_changeNickButton_clicked(QString nickName);
    virtual ~QmlBridge();

private:
    void checkFocus();
    void setDisconnected();
    void setConnected();
    AbstractPane *myRoot;
    TextArea *myTextArea;
    TextField *mySendTextField;
    TextField *myNickTextField;
    Button *nickButton;
    Button *connectButton;
    Button *sendButton;
    TcpServer *tcpServer;

    /*
private slots:

    */
};

#endif /* QMLBRIDGE_H_ */
