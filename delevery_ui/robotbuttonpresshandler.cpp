#include "robotbuttonpresshandler.h"
#include "StateColors.h"
#include "jsonpathmaker.h"
#include "objectpathmaker.h"
#include "robotpathmqttpayload.h"
#include "camerascanmqttpayload.h"
#include "leftrightpathmaker.h"

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
        Robot* robot = field->getRobots().value(meta.value("robotid").toString().toUpper());
        if(robot->getStatus() == RobotStatus::TOANALYSE && data.value("package").toBool())//if robot is going on analyse and has a package
        {
            //alert the user about this robot status
            package->setText("Colis sur le robot");
            package->setColor(StateColors::OK);

            color->setColor(StateColors::UNKNOWN);
            color->setText("Inconnue");

            //manage path to analyse
            srand(time(0));
            QList<FieldElement*> elements = field->getPath(field->at(robot->getPosition()), field->getAnalyse(rand()%field->getAnalyses().count()));
            QJsonObject path = JsonPathMaker(robot->pointing()).create(elements);
            QString pstring = "";
            for(int i = 0; i<path.value("data").toArray().count(); i++)
            {
               pstring+=path.value("data").toArray().at(i).toObject().value("direction").toString();
            }
            //add a follower
            if(!field->followSteps(meta.value("robotid").toString().toUpper(), new OrderFollower(meta.value("robotid").toString().toUpper(), robot, pstring, ObjectPathMaker(robot->pointing()).create(elements), elements)))
            {
                return;
            }
            //send path to robot
            manager->publish(MqttTopic::robotPath(meta.value("robotid").toString().toUpper()), new RobotPathMqttPayload(LeftRightPathMaker(robot->pointing()).create(elements)));
            //activating camera
            manager->publish(MqttTopic::cameraScan(3), new CameraScanMqttPayload(meta.value("robotid").toString().toUpper()));
        }
        else if(robot->getStatus() == RobotStatus::RELOAD && field->getLastLoading() != -1 && !data.value("package").toBool()) //if robot is going to reload its package and has no package
        {
            //inform user about this robot status
            package->setText("Non");
            package->setColor(StateColors::KO);

            color->setColor(StateColors::UNKNOWN);
            color->setText("Inconnue");

            //get the appropriate loading area (some may have been discovered)
            int loadingid = field->getLastLoading();
            if(field->getColorsFound().values().contains(robot->getColorToLookFor()))
            {
                loadingid = field->getColorsFound().key(robot->getColorToLookFor());
            }
            //managing path
            QList<FieldElement*> elements = field->getPath(field->at(robot->getPosition()), field->getLoading(loadingid));
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
            //sending path to robot
            manager->publish(MqttTopic::robotPath(meta.value("robotid").toString().toUpper()), new RobotPathMqttPayload(LeftRightPathMaker(robot->pointing()).create(elements)));
        }
        else if(robot->getStatus() == RobotStatus::TOLOAD && field->getLastLoading() != -1 && !data.value("package").toBool()) //if robot is going to a loading area, has its target set up and has no package
        {
            //inform the user about this robot state
            package->setText("Non");
            package->setColor(StateColors::KO);

            color->setColor(StateColors::UNKNOWN);
            color->setText("Inconnue");

            //managing path
            QList<FieldElement*> elements = field->getPath(field->at(robot->getPosition()), field->getLoading(field->getLastLoading()));
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
            //send path to robot
            manager->publish(MqttTopic::robotPath(meta.value("robotid").toString().toUpper()), new RobotPathMqttPayload(LeftRightPathMaker(robot->pointing()).create(elements)));
        }
        else if(robot->getStatus() == RobotStatus::TOLOAD && field->getLastLoading() == -1 && !data.value("package").toBool()) //if robot is going to loading area, its target loading area has been reset and it has no package
        {
            //reset the robot state to a new one
            package->setText("Non");
            package->setColor(StateColors::KO);

            color->setColor(StateColors::UNKNOWN);
            color->setText("Inconnue");
            robot->setCarryingColor("");
        }
    }
}
