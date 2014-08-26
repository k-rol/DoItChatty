#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpserver.h"
#include <QDebug>
#include <QTcpSocket>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpserver = new TcpServer(this);
    setDisconnected();
    setNotListening();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::filterText(QString &readContent)
{
    //ui->chatTextbox->insertHtml(textDoc->toHtml());
}

void MainWindow::updateText(QString &readContent)
{
    QRegExp reg(":\\)");
    if (readContent.count(reg) >= 1)
    {

        int regCount = readContent.count(reg);

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
    }
    else
        {
            ui->chatTextbox->append(readContent);
        }
}

void MainWindow::insertEmoticon(QString emoString)
{
    //ui->chatTextbox->insertHtml(readContent); <img src='\smile.png'> <img src=\":/smile.png\"> <img src=":/emoticon/smile.png" />
}

void MainWindow::systemMessages(QString msgSystem)
{
    ui->chatTextbox->append(msgSystem);
    //ui->chatTextbox->appendPlainText(msgSystem);
}

void MainWindow::on_listenButton_clicked()
{
    tcpserver->startListening(ui->portTextBox->text().toInt());
}

void MainWindow::on_sendTextButton_clicked()
{

    /*
    string nickName = "" + ui->nickTextBox->text().toStdString() + "";
    string textToSend = ui->sendTextBox->text().toStdString() + "";
    string wholeText = nickName+textToSend;
    tcpserver->writeSomething(wholeText);

    QString textToAdd = wholeText.c_str();

    if (textToAdd.endsWith("\n") || textToAdd.endsWith("\r\n"))
    {
        textToAdd.remove(textToAdd.length()-1,1);
    }

    //ui->chatTextbox->appendPlainText(textToAdd.trimmed());

    */
    tcpserver->writeSomething(ui->sendTextBox->text().toStdString());
    ui->sendTextBox->clear();

}

/*
 *
*/
void MainWindow::setButtonEnabilities(QString set)
{
    if (set == "setDisconnected") {
        setDisconnected();
    }
    else if (set == "setConnected") {
        setConnected();
    }
    else if (set == "setListening") {
        setListening();
    }
    else if (set == "setNotListening") {
        setNotListening();
    }
    else {
        qDebug() << "SetButton command not recognized.";
    }
}

/*
 * Set all buttons to reflect a Disconnected state
*/
void MainWindow::setDisconnected()
{
    //ui->disconnectButton->setEnabled(false);
    ui->sendTextButton->setEnabled(false);
    ui->connectButton->setEnabled(true);
    ui->portTextBox->setEnabled(true);
    ui->ipAddressTextBox->setEnabled(true);
}

/*
 * Set all buttons to reflect a Connected state
*/
void MainWindow::setConnected()
{
    ui->disconnectButton->setEnabled(true);
    ui->sendTextButton->setEnabled(true);
    ui->connectButton->setEnabled(false);
    ui->portTextBox->setEnabled(false);
    ui->ipAddressTextBox->setEnabled(false);
}

/*
 * Set all buttons to reflect a Listening state
*/
void MainWindow::setListening()
{
    ui->listenButton->setEnabled(false);
    ui->stopListenButton->setEnabled(true);
    ui->portTextBox->setEnabled(false);
    ui->ipAddressTextBox->setEnabled(false);
}

/*
 * Set all buttons to reflect a Not Listening state
*/
void MainWindow::setNotListening()
{
    ui->listenButton->setEnabled(true);
    ui->stopListenButton->setEnabled(false);
    ui->portTextBox->setEnabled(true);
    ui->ipAddressTextBox->setEnabled(true);
}

void MainWindow::on_disconnectButton_clicked()
{
    tcpserver->disconnectIt();
}

void MainWindow::on_stopListenButton_clicked()
{
    tcpserver->stopListening();
}

void MainWindow::on_connectButton_clicked()
{
    //timer to put in there in case it doesnt connect*******

    QString ipAddress = ui->ipAddressTextBox->text();
    int port = ui->portTextBox->text().toInt();
    tcpserver->nickName = ui->nickTextBox->text().toStdString();
    tcpserver->connectToHost(ipAddress, port);
}

void MainWindow::on_changeNickButton_clicked()
{
    tcpserver->nickName = ui->nickTextBox->text().toStdString();
    tcpserver->sendNickName();
}
