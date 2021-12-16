#ifndef ROBOTSTEPHANDLER_H
#define ROBOTSTEPHANDLER_H

#include "eventlistener.h"
#include "fielddraw.h"
#include "fieldmodel.h"
#include "iconlabel.h"



class RobotStepHandler : public QObject, public EventListener
{
    Q_OBJECT
private:
    FieldModel* model;
    IconLabel* order;
    FieldDraw* draw;
private slots:
    void followerDone();
public:
    RobotStepHandler(IconLabel* order, FieldModel* model, FieldDraw* draw);

    // EventListener interface
public:
    void handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta);
};

#endif // ROBOTSTEPHANDLER_H
