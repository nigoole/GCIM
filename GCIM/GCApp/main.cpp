#include "mainwindow.h"
#include "myapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // init app config
    MyApp::init(a);

    MainWindow w;
    w.resize(QSize(280, 700));
    w.show();

    return a.exec();
}
