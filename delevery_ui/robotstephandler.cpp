#include "robotstephandler.h"
#include "StateColors.h"

RobotStepHandler::RobotStepHandler(IconLabel *order, FieldModel *model, FieldDraw *draw)
{
    this->order=order;
    this->model=model;
    this->draw = draw;
}

void RobotStepHandler::handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta)
{
    if(!dataEmpty && data.contains("status") &&
            meta.contains("robotid") &&
            model->getRobots().contains(meta.value("robotid").toString().toUpper()) &&
            model->follower(meta.value("robotid").toString().toUpper()) != nullptr)
    {
        OrderFollower* follower = model->follower(meta.value("robotid").toString().toUpper());
        //a robot must stop when it arrives at a loading area or a deposit area
        bool stopState = model->getRobots().value(meta.value("robotid").toString().toUpper())->getStatus() == RobotStatus::TOLOAD
                || model->getRobots().value(meta.value("robotid").toString().toUpper())->getStatus() == RobotStatus::TODEPOSIT
                || model->getRobots().value(meta.value("robotid").toString().toUpper())->getStatus() == RobotStatus::BACKTOLOADING
                || model->getRobots().value(meta.value("robotid").toString().toUpper())->getStatus() == RobotStatus::RELOAD;
        bool continues = follower->toStep(data.value("status").toInt());
        if(continues)
        {
            //set robot working indicator
            order->setText("Ordre en cours d'execution");
            order->setColor(StateColors::OK);
        }
        else
        {
            if(stopState)
                customSlot();
        }
        draw->update();
    }
}

void RobotStepHandler::customSlot()
{
    //set robot stoped indicator
    order->setText("A l'arret");
    order->setColor(StateColors::KO);
}
