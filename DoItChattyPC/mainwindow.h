#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tcpserver.h>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void updateText(QString &readContant);
    void filterText(QString);
    void systemMessages(QString msgSystem);
    void setButtonEnabilities(QString set);
    ~MainWindow();

private:
    void setEmoticonMap();
    void setDisconnected();
    void setConnected();
    void setListening();
    void setNotListening();
    QMap<QRegExp, QString> emoticonMap;
    Ui::MainWindow *ui;
    TcpServer *tcpserver;

private slots:
void on_listenButton_clicked();
void on_sendTextButton_clicked();
void on_disconnectButton_clicked();
void on_stopListenButton_clicked();
void on_connectButton_clicked();
void on_changeNickButton_clicked();
};

#endif // MAINWINDOW_H
