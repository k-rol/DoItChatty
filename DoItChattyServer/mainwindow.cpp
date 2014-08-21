#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "initserver.h"
#include <iostream>
#include <QStandardItem>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new InitServer(this);

    model = new QStandardItemModel();
    ui->userListView->setModel(model);
}

void MainWindow::on_startButton_clicked()
{
    startServer();
}

void MainWindow::addUser(QString nickName)
{
    QStandardItem* user = new QStandardItem(nickName);
    model->appendRow(user);

}

void MainWindow::clearUserList()
{
    model->clear();
}

void MainWindow::on_shutdownButton_clicked()
{
    server->stopServer("The Server will Shutdown for x Minutes. Thank you.");
}

void MainWindow::startServer()
{

    ui->statusBar->showMessage("Connecting ...");

    server->startServer(ui->portSpinBox->value());

}

string MainWindow::startServer(quint16 port)
{
    ui->statusBar->showMessage("Connecting ...");

    server->startServer(port);

    QString portQStr = QString::number(port);

    return "Server has been started on port " + portQStr.toStdString();
}

MainWindow::~MainWindow()
{
    delete ui;
}
