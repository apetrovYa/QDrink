#include <QApplication>
#include "view/mainwindow.h"

int main (int argc, char* argv[])
{
    QApplication app(argc, argv); 
    app.setApplicationName ("QDrink-Freedom");
    app.setApplicationVersion ("1.0.0");
    app.setOrganizationName ("apetrov");
    MainWindow win;
    win.show();
    return app.exec();
}
