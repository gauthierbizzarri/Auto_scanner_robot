#include "fielddraw.h"

#include <QMouseEvent>
#include <QMessageBox>

FieldDraw::FieldDraw(QWidget *parent) : QWidget(parent)
{
    robotPositionRedifined = false;
}

void FieldDraw::setModel(FieldModel *model)
{
    this->model=model;
    connect(model, SIGNAL(changed()), this, SLOT(update()));
}

void FieldDraw::redifineRobotPosition()
{
    QWidget* w = (QWidget*)sender();
    moveRobotId = w->property("robot").toString();
    if(model->follower(moveRobotId) == nullptr)
    {
        moveRobotSender = w;
        w->setDisabled(true);
        robotPositionRedifined = true;
    }
    else
    {
        QMessageBox::warning(this, "Déplacement du robot", "Le robot "+moveRobotId+" ne peu pas être déplacé car il est occupế");
    }
}

void FieldDraw::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    model->drawAll(&painter);
}

void FieldDraw::resizeEvent(QResizeEvent *event)
{
    update();
}

void FieldDraw::mouseReleaseEvent(QMouseEvent *event)
{
    if(robotPositionRedifined)
    {
        int x = (int)(event->pos().x()/FieldElement::size);
        int y = (int)(event->pos().y()/FieldElement::size);
        if(model->getDeposits().values().contains(model->at(QPoint(x, y))) && model->moveRobot(moveRobotId, QPoint(x, y)))
        {
            model->getRobots().value(moveRobotId)->setStatus(RobotStatus::TOLOAD);
            robotPositionRedifined = false;
            moveRobotSender->setDisabled(false);
        }
        else
        {
            QMessageBox::warning(this, "Déplacement du robot "+moveRobotId, "Impossible de déplacer ce robot ici");
        }
    }
}
