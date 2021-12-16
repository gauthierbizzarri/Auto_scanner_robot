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
#include "StateColors.h"
#include "robotbuttonpresshandler.h"
#include "cameracolorhandler.h"
#include "jsonpathmaker.h"
#include "robotpathmqttpayload.h"
#include "objectpathmaker.h"
#include "robotstephandler.h"
#include "camerascanmqttpayload.h"
#include "loadinareacolorhandler.h"
#include "leftrightpathmaker.h"

#include <colors.h>
#include <QMessageBox>
#include <QDebug>
#include <QAbstractItemModel>
#include <QJsonArray>

MainWindow::MainWindow(MQTTManager* manager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setup selectors
    ui->colorSelector->addItem(" --- selectionner une couleur");
    ui->loadingZoneSelector->addItem(" --- selectionner une zone de chargement");
    ui->robotSelector->addItem(" --- selectionner un robot");
    Q_FOREACH(QString c, colors.keys())
    {
        ui->colorSelector->addItem(c);
    }
    ui->robotSelector->addItem("ROBOT3");

    //disable send button until brocker connection
    ui->clbtSend->setDisabled(true);
    ui->clbtSend->setText("en attente de connection ...");
    connect(ui->clbtSend, SIGNAL(clicked(bool)), this, SLOT(checkOrder()));

    //setting base parametters to order history table
    ui->cvHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cvHistory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->cvHistory->setSortingEnabled(false);

    //setting mqtt manager
    this->manager=manager;
    connect(this->manager, SIGNAL(connected()), this, SLOT(openFields()));
    connect(this->manager, SIGNAL(timedout()), this, SLOT(showTimeoutError()));
    manager->connectToHost();

    //setting field model
    fieldModel = new FieldModel();
    connect(fieldModel, SIGNAL(newPath(QString,QList<FieldElement*>)), this, SLOT(sendPath(QString,QList<FieldElement*>)));
    Q_FOREACH(int lz, fieldModel->getLoadings().keys())
    {
        ui->loadingZoneSelector->addItem(QString::number(lz));
    }

    //set field drawer
    ui->widget_2->setModel(fieldModel);

    ui->toolBox->setCurrentIndex(0);

    //set indicators init values
    ui->PackageTransitState->setColor(StateColors::KO);
    ui->orderState->setText("A l'arret");
    ui->orderState->setColor(StateColors::KO);
    ui->connectionState->setColor(StateColors::OK);
    ui->packageColor->setColor(StateColors::UNKNOWN);
    ui->pbRedifRobPos->setProperty("robot", "ROBOT3");
    ui->cbAutocomplete->setChecked(true);

    connect(ui->pbRedifRobPos, SIGNAL(clicked(bool)), ui->widget_2, SLOT(redifineRobotPosition()));
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
    OrderChecker checker(ui->colorSelector->currentText(), ui->robotSelector->currentText(), ui->loadingZoneSelector->currentText().toInt());
    connect(&checker, SIGNAL(validate()), this, SLOT(sendOrder()));
    connect(&checker, SIGNAL(refute(QString,QString)), this, SLOT(fieldInvalid(QString,QString)));
    return checker.check();//check values
}

void MainWindow::sendOrder()
{
    Robot* robot = fieldModel->getRobots().value(ui->robotSelector->currentText());//get selected robot
    if(robot != nullptr)
    {
        if(!robot->isReadyForOrder())//if robot is occupied
        {
            QMessageBox::warning(this, "Robot occupé", "Inpossible de créer un order pour ce robot, il est déjà occupé");
            return;
        }
        FieldElement* start = fieldModel->at(robot->getPosition());//if robot is on a valid position
        if(start != nullptr)
        {
            robot->setReadyForOrder(false);//reserve this robot
            ui->orderState->setText("En attente d'initialisation");
            ui->orderState->setColor(StateColors::WAIT);
            if(fieldModel->getColorsFound().values().contains(ui->colorSelector->currentText()) && ui->cbAutocomplete->isChecked())//set the target accurding to knowledge about the field
            {
                ui->loadingZoneSelector->setCurrentText(QString::number(fieldModel->getColorsFound().key(ui->colorSelector->currentText())));
            }
            robot->setStatus(RobotStatus::TOLOAD);
            robot->setColorToLookFor(ui->colorSelector->currentText());
            fieldModel->setLastLoading(ui->loadingZoneSelector->currentText().toInt());

            //send order for history
            manager->publish(MqttTopic::uiOrder(3), new UiOrderMqttPayload(
                                 ui->colorSelector->currentText(),
                                 ui->loadingZoneSelector->currentText().toInt(),
                                 fieldModel->depositIndex(start),
                                 ui->robotSelector->currentText()));
            ui->orderState->setText("En attente d'initialisation");
            ui->orderState->setColor(StateColors::WAIT);
        }
    }
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

    UiOrderModel* model = new UiOrderModel();//setting history model
    ui->cvHistory->setModel(model);

    //setting up events
    mqttEventManager->addEventListener(MqttTopic::uiOrderTemplate, new UiOrderHandler(model));
    mqttEventManager->addEventListener(MqttTopic::robotButtonTemplate, new RobotButtonPressHandler(ui->orderState, ui->PackageTransitState, ui->packageColor, manager, fieldModel));
    mqttEventManager->addEventListener(MqttTopic::cameraColorTemplate, new CameraColorHandler(ui->packageColor, manager, fieldModel));
    mqttEventManager->addEventListener(MqttTopic::robotStepTemplate, new RobotStepHandler(ui->orderState, fieldModel, ui->widget_2));
    mqttEventManager->addEventListener(MqttTopic::robotStepTemplate, new RobotStepHandler(ui->orderState, fieldModel, ui->widget_2));
    mqttEventManager->addEventListener(MqttTopic::loadingAreaColorTemplate, new LoadinAreaColorHandler({
                                                                                                           ui->loader1,
                                                                                                           ui->loader2,
                                                                                                           ui->loader3,
                                                                                                           ui->loader4
                                                                                                       }, fieldModel));

    EventManager::launch(mqttEventManager);
}

void MainWindow::showTimeoutError()
{
    QMessageBox box(QMessageBox::Critical, "Erreur de noyau", "Une erreur est survenue lors de l'initialisation de l'application. Impossible de se connecter au serveur distant. Veuillez réessayer ultérieurment");
    box.exec();
    //retry ?
}

void MainWindow::appExit()
{
    this->close();
}

void MainWindow::sendPath(QString robotid, QList<FieldElement*> elements)
{
    Robot* robot = fieldModel->getRobots().value(robotid);//get robot
    QJsonObject path = JsonPathMaker(robot->pointing()).create(elements);//get path
    manager->publish(MqttTopic::robotPath(ui->robotSelector->currentText()), new RobotPathMqttPayload(LeftRightPathMaker(robot->pointing()).create(elements)));//send path to robot
    QString pstring = "";
    for(int i = 0; i<path.value("data").toArray().count(); i++)
    {
       pstring+=path.value("data").toArray().at(i).toObject().value("direction").toString();
    }
    ui->orderState->setText("Ordre envoyé");
    if(!fieldModel->followSteps(ui->robotSelector->currentText(), new OrderFollower(ui->robotSelector->currentText(), robot, pstring, ObjectPathMaker(robot->pointing()).create(elements), elements)))
    {
        QMessageBox::warning(this, "Robot indisponible", "Le robot "+ui->robotSelector->currentText()+" suit déjà un order établi. réésayez lorqu'il sera prêt.");
        return;
    }//follow the path of this robot
}

