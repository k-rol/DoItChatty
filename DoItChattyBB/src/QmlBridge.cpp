/*
 * QmlBridge.cpp
 *
 *  Created on: Aug 24, 2014
 *      Author: CaroL
 */

#include <src/QmlBridge.h>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/controls/button.h>
#include <bb/cascades/controls/textarea.h>

using namespace bb::cascades;

QmlBridge::QmlBridge(QObject *parent) : QObject(parent), myRoot(0)
{
    tcpServer = new TcpServer(this);
    //emit setDisconnected();
}

void QmlBridge::setQml(AbstractPane *root)
{
    myRoot = root;

}

void QmlBridge::updateText(QString readContent)
{
    QRegExp reg(":\\)");
    if (readContent.count(reg) >= 1)
    {

        int regCount = readContent.count(reg);

        /*
        ui->chatTextbox->append(readContent);
        ui->chatTextbox->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->chatTextbox->moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);

        for (int i = 0; i < regCount; ++i) {
            QTextCursor cursor(ui->chatTextbox->document()->find(reg,ui->chatTextbox->textCursor()));
            if (!cursor.isNull())
            {
                cursor.insertHtml("<img src=\":/emoticon/smile.png\" >");

            }
        }
        */
    }
    else
        {
            //ui->chatTextbox->append(readContent);
        }
}

void QmlBridge::systemMessages(QString textToSend)
{
    //ui->chatTextbox->append(msgSystem); //signal or qinvokable

    TextArea *myTextArea = myRoot->findChild<TextArea*>("chatTextBox");
    myTextArea->setText(textToSend);
}

void QmlBridge::on_sendTextButton_clicked(QString textToSend)
{
    tcpServer->writeSomething(textToSend.toStdString());
    //ui->sendTextBox->clear(); //to be done from QML
}

void QmlBridge::setButtonEnabilities(QString set)
{
    if (set == "setDisconnected") {
        setDisconnected();
    }
    else if (set == "setConnected") {
        setConnected();
    }
    else {
        qDebug() << "SetButton command not recognized.";
    }
}

/*
 * Set all buttons to reflect a Disconnected state
*/
void QmlBridge::setDisconnected()
{
    /*
    //ui->disconnectButton->setEnabled(false);
    ui->sendTextButton->setEnabled(false);
    ui->connectButton->setEnabled(true);
    ui->portTextBox->setEnabled(true);
    ui->ipAddressTextBox->setEnabled(true);
    */
}

/*
 * Set all buttons to reflect a Connected state
*/
void QmlBridge::setConnected()
{
    /*
    ui->disconnectButton->setEnabled(true);
    ui->sendTextButton->setEnabled(true);
    ui->connectButton->setEnabled(false);
    ui->portTextBox->setEnabled(false);
    ui->ipAddressTextBox->setEnabled(false);
    */
}

void QmlBridge::on_disconnectButton_clicked()
{
    tcpServer->disconnectIt();
}

void QmlBridge::on_connectButton_clicked(QString nickName)
{
    //timer to put in there in case it doesnt connect*******
    QString ipAddress = "54.191.14.76";
    int port = 51345;
    tcpServer->nickName = nickName.toStdString();
    tcpServer->connectToHost(ipAddress, port);

}

void QmlBridge::on_changeNickButton_clicked(QString nickName)
{
    tcpServer->nickName = nickName.toStdString();
    tcpServer->sendNickName();
}

void QmlBridge::setUIButtons(QString set)
{
    Button *myButton = myRoot->findChild<Button*>("myButton");
    myButton->setText("Fuck yeah");
}

QmlBridge::~QmlBridge()
{
    // TODO Auto-generated destructor stub
}

