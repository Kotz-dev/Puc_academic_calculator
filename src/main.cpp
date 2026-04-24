#include <QApplication>
#include <GlobalAccess.h>
#include "windows/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
        MainWindow mainWindow;
        GLOBAL_::main = &mainWindow;
        mainWindow.show();
       return QApplication::exec();
}