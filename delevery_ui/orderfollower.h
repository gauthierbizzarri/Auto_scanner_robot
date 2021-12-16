#ifndef ORDERFOLLOWER_H
#define ORDERFOLLOWER_H

#include "fieldelement.h"
#include "robot.h"


/**
 * @brief The OrderFollower class
 * Class used to follow the real time evolution of a robot's journey
 */
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
    /**
     * @brief manageDirectionInBetween
     * Manages directional heading of the robot in between steps
     * @param from
     * @param to
     */
    void manageDirectionInBetween(int from, int to);
public:
    OrderFollower(QString robotid, Robot* robot, QString path, QList<FieldElement*> steps, QList<FieldElement*> passBy);
    /**
     * @brief toStep
     * Make the robot go to step step
     * @param step
     * @return
     */
    bool toStep(int step);

    /**
     * @brief lastStep
     * Retrun the step id of the last step
     * @return
     */
    int lastStep();

    /**
     * @brief draw
     * Draw a path using the given painter object
     * @param p
     */
    void draw(QPainter* p);
signals:
    void orderEnd(QString);
};

#endif // ORDERFOLLOWER_H
