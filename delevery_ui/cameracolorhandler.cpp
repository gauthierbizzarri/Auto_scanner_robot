#include "cameracolorhandler.h"
#include "colors.h"
#include "StateColors.h"
#include "mqttmanager.h"
#include "loadingareacolormqttpayload.h"

CameraColorHandler::CameraColorHandler(IconLabel *packet, MQTTManager* manager, FieldModel *model)
{
    this->packet = packet;
    this->model=model;
    this->manager=manager;
}

void CameraColorHandler::handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta)
{
    if(!dataEmpty
            && data.contains("robot") //robot is present in json data
            && data.contains("color") //color is present in json data
            && !meta.isEmpty() //data is not empty
            && meta.contains("camid") //meta data contains the camera id (extracted from topic)
            && model->getCameras().contains(meta.value("camid").toInt()) //the referenced camera ids references this camera
            && model->getRobots().keys().contains(data.value("robot").toString().toUpper()) //the referenced robot exists
            && model->getRobots().value(data.value("robot").toString().toUpper())->getLastLoading() != -1) //check if the loading area target was set
    {
        if(model->getColors().contains(data.value("color").toString().toLower()) && model->getRobots().contains(data.value("robot").toString().toUpper())
                && model->getRobots().value(data.value("robot").toString().toUpper())->getStatus() == RobotStatus::TOANALYSE)
        {
            packet->setColor(model->getColors().value(data.value("color").toString().toLower()));
            packet->setText(data.value("color").toString().toLower());
            Robot *robot = model->getRobots().value(data.value("robot").toString().toUpper());
            robot->setCarryingColor(data.value("color").toString().toLower());
            model->ColorFound(robot->getLastLoading(), data.value("color").toString().toLower());

            //publish for everyone on the field that the discovered color is at this position
            manager->publish(MqttTopic::loadingAreaColor(robot->getLastLoading()), new LoadingAreaColorMqttPayload(data.value("color").toString().toLower()));
        }
    }
}
