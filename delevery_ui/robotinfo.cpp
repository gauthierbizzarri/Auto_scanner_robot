#include "StateColors.h"
#include "robotinfo.h"
#include "ui_robotinfo.h"

RobotInfo::RobotInfo(QString robotid, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RobotInfo)
{
    ui->setupUi(this);


    //set indicators init values
    ui->packageState->setColor(StateColors::KO);
    ui->robotState->setText("A l'arret");
    ui->robotState->setColor(StateColors::KO);
    ui->connectionState->setColor(StateColors::OK);
    ui->packageState->setColor(StateColors::UNKNOWN);
    this->setProperty("robot", robotid);
    connect(ui->pbMoveRobot, SIGNAL(clicked(bool)), this, SLOT(changeRobotPositionClicked()));
}

RobotInfo::~RobotInfo()
{
    delete ui;
}

void RobotInfo::changeRobotPositionClicked()
{
    emit changeRobotPosition();
}
