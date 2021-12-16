#ifndef ROBOT_H
#define ROBOT_H

#include <QColor>
#include <QPainter>
#include <QPoint>
#include <direction.h>

enum RobotStatus{
    TOLOAD, TOANALYSE, TODEPOSIT, BACKTOLOADING, RELOAD
};

class Robot
{
private:
    QPoint pos;
    QPoint start;
    QColor color;
    Direction dir;
    RobotStatus status;
    bool readyForOrder;
    QString carryingColor;
    QString lookingForColor;
public:
    Robot();
    Robot(QPoint ipos, QColor color, Direction dir);
    void moveAt(QPoint p);
    QPoint startedOn();
    QColor getColor();
    QPoint getPosition();
    Direction pointing();
    void setDirection(Direction d);
    void setReadyForOrder(bool ready);
    RobotStatus getStatus();
    void setStatus(RobotStatus s);
    bool isReadyForOrder();
    void setCarryingColor(QString);
    QString getCarriedColor();
    void setColorToLookFor(QString);
    QString getColorToLookFor();
    void draw(QPainter* p);
};

#endif // ROBOT_H
