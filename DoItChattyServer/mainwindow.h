#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <initserver.h>

class QStandardItemModel;

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    string startServer(quint16 port);
    void startServer();
    void addUser(QString nickName);
    void clearUserList();
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_shutdownButton_clicked();

private:
    Ui::MainWindow *ui;
    InitServer *server;
    QStandardItemModel *model;
};

#endif // MAINWINDOW_H
