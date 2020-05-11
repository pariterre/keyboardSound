#include "MainWindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    if (mainWindow.isOkay()){
        mainWindow.show();
        return app.exec();
    } else {
        return 1;
    }
}
