#include "mainwindow.h"
#include <QApplication>
#include <iostream>

using namespace std;

string help()
{
    return ;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    quint16 port = 0;
    bool startListening = false;
    bool ok = false;

    if (argc > 0)
    {
        port = QString(argv[0]).toInt(&ok);
    }
    if (!ok)
    {
        port = 51345;
    }

    w.show();
    cout << w.startServer(port, startListening);

    return a.exec();
}
