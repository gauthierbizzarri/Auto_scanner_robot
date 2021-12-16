#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QString>
#include <QCoreApplication>

/**
 * @brief The AppConfig class
 * Class representing all the application configurations
 */
class AppConfig
{
private:
    AppConfig();
public:
    static const QString defaultPath; //default config file path
    /**
     * @brief fromFile
     * Load an application config object from a file
     * @param path
     * @return
     */
    static AppConfig* fromFile(QString path);

    /**
     * @brief fromFile
     * Load an application config object from default file
     * @return
     */
    static AppConfig* fromFile();

    /**
     * @brief empty
     * Load an empty application config object
     * @return
     */
    static AppConfig *empty();

    /**
     * @brief defaultConfig
     * Load default config
     * @return
     */
    static AppConfig *defaultConfig();

    /**
     * @brief toFile
     * Print this object to the default file
     */
    void toFile();

    /**
     * @brief mqttConfigString
     * Extract the config string fot MQTT
     * @return
     */
    QString mqttConfigString();

    int mqtt_port;
    QString mqtt_host;
    QString mqtt_username;
    QString mqtt_password;
    QString mqtt_clientid;
    QString mqtt_protocolversion;
    int mqtt_keepalive;
};

#endif // APPCONFIG_H
