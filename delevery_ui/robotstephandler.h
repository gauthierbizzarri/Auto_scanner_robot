#ifndef ROBOTSTEPHANDLER_H
#define ROBOTSTEPHANDLER_H

#include "eventlistener.h"
#include "fielddraw.h"
#include "fieldmodel.h"
#include "iconlabel.h"


/**
 * @brief The RobotStepHandler class
 * Handle the step forward of a robot in a part of its journey
 */
class RobotStepHandler : public EventListener
{
private:
    FieldModel* model;
    IconLabel* order;
    FieldDraw* draw;
public:
    RobotStepHandler(IconLabel* order, FieldModel* model, FieldDraw* draw);

    // EventListener interface
public slots:
    void handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta);
    void customSlot();
};

#endif // ROBOTSTEPHANDLER_H
