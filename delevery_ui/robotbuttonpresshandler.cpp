#include "robotbuttonpresshandler.h"
#include "StateColors.h"
#include "jsonpathmaker.h"
#include "objectpathmaker.h"
#include "robotpathmqttpayload.h"

#include <QJsonArray>

RobotButtonPressHandler::RobotButtonPressHandler(IconLabel *order, IconLabel* package, IconLabel *color, MQTTManager* manager, FieldModel* field)
{
    this->order=order;
    this->package=package;
    this->field = field;
    this->color = color;
    this->manager=manager;
}

void RobotButtonPressHandler::handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta)
{
    if(!dataEmpty && data.contains("package") && !meta.isEmpty() && meta.contains("robotid") && field->getRobots().keys().contains(meta.value("robotid").toString().toUpper()))
    {
        order->setText("En attente d'ordre");
        order->setColor(StateColors::WAIT);
        field->getRobots().value(meta.value("robotid").toString().toUpper())->setReadyForOrder(true);
        if(data.value("package").toBool())
        {
            package->setText("Colis sur le robot");
            package->setColor(StateColors::OK);

            color->setColor(StateColors::UNKNOWN);
            color->setText("Inconnue");
        }
        else
        {
            package->setText("Non");
            package->setColor(StateColors::KO);
        }
        Robot* robot = field->getRobots().value(meta.value("robotid").toString().toUpper());
        if(robot->getStatus() == RobotStatus::TOANALYSE)
        {
            QList<FieldElement*> elements = field->getPath(robot->pointing(), field->at(robot->getPosition()), field->getAnalyse(0));
            QJsonObject path = JsonPathMaker(robot->pointing()).create(elements);
            QString pstring = "";
            for(int i = 0; i<path.value("data").toArray().count(); i++)
            {
               pstring+=path.value("data").toArray().at(i).toObject().value("direction").toString();
            }
            if(!field->followSteps(meta.value("robotid").toString().toUpper(), new OrderFollower(meta.value("robotid").toString().toUpper(), robot, pstring, ObjectPathMaker(robot->pointing()).create(elements), elements)))
            {
                return;
            }
            manager->publish(MqttTopic::robotPath(meta.value("robotid").toString().toUpper()), new RobotPathMqttPayload(path));
        }
        else if(robot->getStatus() == RobotStatus::TOLOAD && field->getLastLoading() != -1)
        {

            QList<FieldElement*> elements = field->getPath(robot->pointing(), field->at(robot->getPosition()), field->getLoading(field->getLastLoading()));
            field->setLastLoading((field->getLastLoading()+1)%field->getLoadings().count());
            QJsonObject path = JsonPathMaker(robot->pointing()).create(elements);
            QString pstring = "";
            for(int i = 0; i<path.value("data").toArray().count(); i++)
            {
               pstring+=path.value("data").toArray().at(i).toObject().value("direction").toString();
            }
            if(!field->followSteps(meta.value("robotid").toString().toUpper(), new OrderFollower(meta.value("robotid").toString().toUpper(), robot, pstring, ObjectPathMaker(robot->pointing()).create(elements), elements)))
            {
                return;
            }
            manager->publish(MqttTopic::robotPath(meta.value("robotid").toString().toUpper()), new RobotPathMqttPayload(path));
        }
    }
}
