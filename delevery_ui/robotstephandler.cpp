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
        if(model->getRobots().value(meta.value("robotid").toString().toUpper())->getStatus() == RobotStatus::TOLOAD
                || model->getRobots().value(meta.value("robotid").toString().toUpper())->getStatus() == RobotStatus::TODEPOSIT)
            connect(follower, SIGNAL(orderEnd(QString)), this, SLOT(followerDone()));
        follower->toStep(data.value("status").toInt());
        disconnect(follower, SIGNAL(orderEnd(QString)), this, SLOT(followerDone()));
        if(!follower->isDone())
        {
            order->setText("Ordre en cours d'execution");
            order->setColor(StateColors::OK);
        }
        draw->update();
    }
}

void RobotStepHandler::followerDone()
{
    order->setText("A l'arret");
    order->setColor(StateColors::KO);
}
