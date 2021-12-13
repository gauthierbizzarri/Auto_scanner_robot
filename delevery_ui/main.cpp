#include "appconfig.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MQTTManager* manager = new MQTTManager(&a);
    manager->configureFromConfigString(AppConfig::defaultConfig()->mqttConfigString());

    MainWindow w(manager);
    w.show();
    return a.exec();
}
