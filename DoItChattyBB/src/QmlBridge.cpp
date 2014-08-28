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
#include <bb/cascades/controls/textfield.h>

using namespace bb::cascades;

QmlBridge::QmlBridge(QObject *parent) : QObject(parent), myRoot(0), myTextArea(0), mySendTextField(0), myNickTextField(0)
{
    tcpServer = new TcpServer(this);
    //emit setDisconnected();
}

void QmlBridge::setQml(AbstractPane *root)
{
    myRoot = root;
    myTextArea = myRoot->findChild<TextArea*>("chatTextBox");
    mySendTextField = myRoot->findChild<TextField*>("sendTextBox");
    myNickTextField = myRoot->findChild<TextField*>("nickTextBox");

    nickButton = myRoot->findChild<Button*>("nickButton");
    connectButton = myRoot->findChild<Button*>("connectButton");
    sendButton = myRoot->findChild<Button*>("sendButton");

    setDisconnected();
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

    QString text = myTextArea->text() + "\n" + readContent;
    //QString html = myTextArea->text() + "<html><span style='text-decoration:underline'>Cascades</span>is <span style='font-size:xx-large;font-style:italic;color:green'>awesome!</span></html>";
    myTextArea->setText(text);

    //checkFocus();
}

void QmlBridge::checkFocus()
{
    if (myTextArea->isFocused())
    {
        myTextArea->editor()->setCursorPosition(myTextArea->editor()->cursorPosition() + 1);
    }
    else if (myNickTextField->isFocused()) {
        myTextArea->requestFocus();
        //myTextArea->editor()->setCursorPosition(myTextArea->editor()->cursorPosition() + 1);
        myNickTextField->requestFocus();
    }
    else {
        myTextArea->requestFocus();
        myTextArea->editor()->setCursorPosition(myTextArea->editor()->cursorPosition() + 100000);
        mySendTextField->requestFocus();
    }
}

void QmlBridge::systemMessages(QString textToSend)
{
    //ui->chatTextbox->append(msgSystem); //signal or qinvokable

    TextArea *myTextArea = myRoot->findChild<TextArea*>("chatTextBox");
    QString text = myTextArea->text() + "\n" + textToSend;
    myTextArea->setText(text);
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
    nickButton->setEnabled(false);
    connectButton->setText("Connect");
    sendButton->setEnabled(false);
}

/*
 * Set all buttons to reflect a Connected state
*/
void QmlBridge::setConnected()
{
    nickButton->setEnabled(true);
    connectButton->setText("Disconnect");
    sendButton->setEnabled(true);
}

void QmlBridge::on_disconnectButton_clicked()
{
    tcpServer->disconnectIt();
}

void QmlBridge::on_connectButton_clicked(QString nickName)
{
    //timer to put in there in case it doesnt connect*******
    QString ipAddress = "54.191.14.76";
    int port = 443;
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

