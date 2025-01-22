#include "mainwindow.h"

#include <QApplication>

#include "test/test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    test_fs_init();

    w.show();
    return a.exec();
}
