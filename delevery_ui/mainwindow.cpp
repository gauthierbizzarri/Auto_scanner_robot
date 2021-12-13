#include "mainwindow.h"
#include "LoadingZones.h"
#include "ui_mainwindow.h"
#include "orderchecker.h"
#include "StartZones.h"

#include <colors.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
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
    connect(ui->clbtSend, SIGNAL(clicked(bool)), this, SLOT(checkOrder()));
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
    //send the message: connect(&checker, SIGNAL(validate()), this, SLOT(sendMessage()));
    connect(&checker, SIGNAL(refute(QString, QString)), this, SLOT(fieldInvalid(QString, QString)));
    return checker.check();
}

void MainWindow::fieldInvalid(QString field, QString reason)
{
    QMessageBox::information(this, "Erreur de l'envoi de l'ordre", field+" : "+reason);
}

