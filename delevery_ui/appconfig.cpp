#include "appconfig.h"
#include "mqttmanager.h"

#include <QFileInfo>
#include <QFile>

const QString AppConfig::defaultPath = "/robotdelivery/options.txt";

AppConfig::AppConfig()
{
}

AppConfig *AppConfig::fromFile(QString path)
{
    QFile file(path);
    if(!file.exists())
    {
        return AppConfig::defaultConfig();
    }
    file.open(QFile::ReadOnly);
    QString data(file.readAll());
    file.close();
    AppConfig* config = AppConfig::defaultConfig();
    Q_FOREACH(QString option, data.split("\n"))
    {
        if(option.split(":").count() == 2)
        {
            QString optionName = option.split(":")[0];
            QString optionValue = option.split(":")[1];
            if(!optionValue.isEmpty() && !optionName.isEmpty())
            {
                if(optionName == "port")
                {
                    bool ok = false;
                    int portFile = optionName.toInt(&ok);
                    if(ok)
                    {
                        config->mqtt_port = portFile;
                    }
                }
                else if(optionName == "host")
                {
                    config->mqtt_host = (optionValue);
                }
                else if(optionName == "username")
                {
                    config->mqtt_username = (optionValue);
                }
                else if(optionName == "password")
                {
                    config->mqtt_password = (optionValue);
                }
                else if(optionName == "clientid")
                {
                    config->mqtt_clientid = (optionValue);
                }
                else if(optionName == "protocolversion")
                {
                    config->mqtt_protocolversion = (optionValue);
                }
                else if(optionName == "keepalive")
                {
                    bool ok = false;
                    int keepaliveFile = optionName.toInt(&ok);
                    if(ok)
                    {
                        config->mqtt_keepalive = (keepaliveFile);
                    }
                }
            }
        }
    }
    return config;
}

AppConfig *AppConfig::fromFile()
{
    return AppConfig::fromFile(AppConfig::defaultPath);
}

AppConfig *AppConfig::defaultConfig()
{
    AppConfig* conf = new AppConfig();
    conf->mqtt_host = "test.mosquitto.org";
    conf->mqtt_port = 1883;
    conf->mqtt_protocolversion = MQTTManager::defaultProtocol;
    return conf;
}

QString AppConfig::mqttConfigString()
{
    return "port:"+QString::number(mqtt_port)+";host:"+mqtt_host+";username:"+mqtt_username+";password:"+mqtt_password+";clientid:"+mqtt_clientid+";protocolversion:"+mqtt_protocolversion+";keepalive:"+mqtt_keepalive;
}
