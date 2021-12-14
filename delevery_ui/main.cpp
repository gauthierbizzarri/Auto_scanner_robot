#include "appconfig.h"
#include "mainwindow.h"

#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MQTTManager* manager = new MQTTManager(&a);
    manager->configureFromConfigString(AppConfig::fromFile()->mqttConfigString());

    MainWindow w(manager);
    w.show();
   return a.exec();
}
