#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "initserver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new InitServer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{

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

    string portStr = port.toString();
    return "Server has been started on port ";
}

