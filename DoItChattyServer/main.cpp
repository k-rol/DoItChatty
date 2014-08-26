#include "mainwindow.h"
#include <QApplication>
#include <iostream>
//Add CONFIG += console to pro file for console output

using namespace std;

string help()
{
    return "\n"
            "Starts the server automatically on the choosen port,\n"
            "and can be closed with CTRL+C\n"
            "\n"
            "usage: doitchattyserver [/?] [-help] [port] \n"
            "\n"
            "   [/?]       Provides this help.\n"
            "   [-help]    \n"
            "\n"
            "   [port]     Specifies the port the server should be listening to.\n"
            "\n"
            "\n"
            "The port can be anything between 1 and 65535.\n"
            "\n";
}

int main(int argc, char *argv[])
{
    int port = 0;
    int exceed = 65535;
    int thanOne = 1;
    if (argc > 1)
    {
        string str = string(argv[1]);
        port = atoi(argv[1]);
        if (str == "help" || str == "-help" ||str == "/help" || str == "/?" || str == "-?" || str == "?")
        {
            cout << help();
            return 0;
        }
        else if (port < thanOne || port > exceed)
        {
            //cout << "\nError: Port range exceeded. Should be [1 - 65535].\n";
            return 0;
        }
        //port = QString(argv[1]).toInt(&ok);
        //int i = (int)(argv[1] - '0');

        QApplication a(argc, argv);
        MainWindow w;
        w.show();


        //cout << w.startServer(port);
        w.startServer(port);

        return a.exec();
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
