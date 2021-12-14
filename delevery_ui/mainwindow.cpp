#include "mainwindow.h"
#include "LoadingZones.h"
#include "ui_mainwindow.h"
#include "orderchecker.h"
#include "StartZones.h"
#include "uiordermqttpayload.h"
#include "eventmanager.h"
#include "mqttmessageeventmanager.h"
#include "uiorderhandler.h"
#include "uiordermodel.h"

#include <colors.h>
#include <QMessageBox>
#include <QDebug>
#include <QAbstractItemModel>

MainWindow::MainWindow(MQTTManager* manager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->colorSelector->addItem(" --- selectionner une couleur");
    ui->loadingZoneSelector->addItem(" --- selectionner une zone de largage");
    ui->robotSelector->addItem(" --- selectionner un robot");
    ui->startSelector->addItem(" --- selectionner un point de dépot");
    Q_FOREACH(QString c, colors.keys())
    {
        ui->colorSelector->addItem(c);
    }
    Q_FOREACH(int lz, loadingZones)
    {
        ui->loadingZoneSelector->addItem(QString::number(lz));
    }
    Q_FOREACH(int sz, startZones)
    {
        ui->startSelector->addItem(QString::number(sz));
    }
    ui->robotSelector->addItem("ROBOT3");
    ui->clbtSend->setDisabled(true);
    ui->clbtSend->setText("en attente de connection ...");
    connect(ui->clbtSend, SIGNAL(clicked(bool)), this, SLOT(checkOrder()));

    ui->cvHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cvHistory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->cvHistory->setSortingEnabled(false);
    this->manager=manager;
    connect(this->manager, SIGNAL(connected()), this, SLOT(openFields()));
    connect(this->manager, SIGNAL(timedout()), this, SLOT(showTimeoutError()));
    manager->connectToHost();
    ui->widget_2->setModel(new FieldModel());

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(appExit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkOrder()
{
    if(ui->colorSelector->currentIndex() <= 0)
    {
        fieldInvalid("couleur", "une valeur doit être définie");
        return false;
    }
    if(ui->loadingZoneSelector->currentIndex() <= 0)
    {
        fieldInvalid("zone de chargement", "une valeur doit être définie");
        return false;
    }
    if(ui->robotSelector->currentIndex() <= 0)
    {
        fieldInvalid("robot", "une valeur doit être définie");
        return false;
    }
    if(ui->startSelector->currentIndex() <= 0)
    {
        fieldInvalid("zone de dépot", "une valeur doit être définie");
        return false;
    }
    OrderChecker checker(ui->colorSelector->currentText(), ui->robotSelector->currentText(), ui->loadingZoneSelector->currentText().toInt());
    connect(&checker, SIGNAL(validate()), this, SLOT(sendOrder()));
    connect(&checker, SIGNAL(refute(QString, QString)), this, SLOT(fieldInvalid(QString, QString)));
    return checker.check();
}

void MainWindow::sendOrder()
{
    manager->publish(MqttTopic::uiOrder(3), new UiOrderMqttPayload(
                         ui->colorSelector->currentText(),
                         ui->loadingZoneSelector->currentText().toInt(),
                         ui->startSelector->currentText().toInt(),
                         ui->robotSelector->currentText()));
}

void MainWindow::fieldInvalid(QString field, QString reason)
{
    QMessageBox::information(this, "Erreur de l'envoi de l'ordre", field+" : "+reason);
}

void MainWindow::openFields()
{
    ui->clbtSend->setEnabled(true);
    ui->clbtSend->setText("Envoyer");
    mqttEventManager = new MqttMessageEventManager(this->manager);

    UiOrderModel* model = new UiOrderModel();
    ui->cvHistory->setModel(model);

    mqttEventManager->addEventListener(MqttTopic::uiOrderTemplate, new UiOrderHandler(model));

    EventManager::launch(mqttEventManager);
}

void MainWindow::showTimeoutError()
{
    QMessageBox box(QMessageBox::Critical, "Erreur de noyau", "Une erreur est survenue lors de l'initialisation de l'application. Impossible de se connecter au serveur distant. Veuillez réessayer ultérieurment");
    box.exec();
    this->close();
}

void MainWindow::appExit()
{
    this->close();
}

