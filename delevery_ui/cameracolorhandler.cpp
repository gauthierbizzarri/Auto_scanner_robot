#include "cameracolorhandler.h"
#include "colors.h"

#include <cameraids.h>

CameraColorHandler::CameraColorHandler(IconLabel *packet, FieldModel *model)
{
    this->packet = packet;
    this->model=model;
}

void CameraColorHandler::handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta)
{
    if(!dataEmpty
            && data.contains("robot")
            && data.contains("color")
            && !meta.isEmpty()
            && meta.contains("camid")
            && cameraIds.contains(meta.value("camid").toInt())
            && model->getRobots().keys().contains(data.value("robot").toString().toUpper()))
    {
        if(colors.contains(data.value("color").toString().toLower()) && model->getRobots().contains(data.value("robot").toString().toUpper()))
        {
            packet->setColor(colors.value(data.value("color").toString().toLower()));
            packet->setText(data.value("color").toString().toLower());
            Robot *robot = model->getRobots().value(data.value("robot").toString().toUpper());
            robot->setCarryingColor(data.value("color").toString().toLower());
        }
    }
}
