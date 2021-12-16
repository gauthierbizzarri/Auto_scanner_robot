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
    void manageDirectionInBetween(int from, int to);
public:
    OrderFollower(QString robotid, Robot* robot, QString path, QList<FieldElement*> steps, QList<FieldElement*> passBy);
    bool toStep(int step);
    int lastStep();
    void draw(QPainter* p);
signals:
    void orderEnd(QString);
};

#endif // ORDERFOLLOWER_H
