#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QString>
#include <QCoreApplication>


class AppConfig
{
private:
    AppConfig();
public:
    static QString defaultPath;
    static AppConfig* fromFile(QString path);
    static AppConfig* fromFile();
    static AppConfig *defaultConfig();

    QString mqttConfigString();

    int mqtt_port;
    QString mqtt_host;
    QString mqtt_username;
    QString mqtt_password;
    QString mqtt_clientid;
    QString mqtt_protocolversion;
    int mqtt_keepalive;
};

QString AppConfig::defaultPath = QCoreApplication::applicationDirPath()+"options.txt";

#endif // APPCONFIG_H
