#include "config.h"
#include "mqttmanager.h"
#include "ui_config.h"
#include "appconfig.h"

#include <QMessageBox>
#include <QProcess>

config::config(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::config)
{
    ui->setupUi(this);
    Q_FOREACH(QString proto, MQTTManager::admitedProtocols.keys())
    {
        ui->protocolversion->addItem(proto);
    }

    //populate field from a config
    AppConfig* config = AppConfig::fromFile();
    ui->clientid->setText(config->mqtt_clientid);
    ui->host->setText(config->mqtt_host);
    ui->keepalive->setValue(config->mqtt_keepalive);
    ui->password->setText(config->mqtt_password);
    ui->port->setValue(config->mqtt_port);
    ui->protocolversion->setCurrentText(config->mqtt_protocolversion);
    ui->username->setText(config->mqtt_username);

    connect(ui->pbSave, SIGNAL(clicked(bool)), this, SLOT(saveOptions()));
}

config::~config()
{
    delete ui;
}

void config::saveOptions()
{
    //generate a config object from fields
    AppConfig* config = AppConfig::empty();
    config->mqtt_clientid = ui->clientid->text();
    config->mqtt_host = ui->host->text();
    config->mqtt_keepalive = ui->keepalive->value();
    config->mqtt_password = ui->password->text();
    config->mqtt_port = ui->port->value();
    config->mqtt_protocolversion = ui->protocolversion->currentText();
    config->mqtt_username = ui->username->text();
    config->toFile();
    delete config;

    QMessageBox box(QMessageBox::Warning, "Application des modifications", "Les modifications ne seront appliquées qu'après redémarrage de l'applications.",
                    QMessageBox::StandardButtons(QMessageBox::StandardButton::Apply));
    box.exec();
}
