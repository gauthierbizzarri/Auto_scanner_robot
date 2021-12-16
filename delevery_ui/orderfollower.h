#ifndef ORDERFOLLOWER_H
#define ORDERFOLLOWER_H

#include "fieldelement.h"
#include "robot.h"



class OrderFollower : public QObject
{
    Q_OBJECT
protected:
    QList<FieldElement*> steps;
    QList<FieldElement*> passBy;
    Robot* robot;
    QString robotid;
    int lastIndex;
    QString path;
public:
    OrderFollower(QString robotid, Robot* robot, QString path, QList<FieldElement*> steps, QList<FieldElement*> passBy);
    void toStep(int step);
    int lastStep();
    void draw(QPainter* p);
    bool isDone();
signals:
    void orderEnd(QString);
};

#endif // ORDERFOLLOWER_H
