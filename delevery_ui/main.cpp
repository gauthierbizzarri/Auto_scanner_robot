#include "appconfig.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MQTTManager* manager = new MQTTManager(&a);
    manager->configureFromConfigString(AppConfig::fromFile()->mqttConfigString());

    MainWindow w(manager);
    w.setWindowTitle("NOZAMA");
    w.setWindowIcon(QIcon(QDir::homePath()+"/robotdelivery/icon.png"));
    w.show();
   return a.exec();
}
