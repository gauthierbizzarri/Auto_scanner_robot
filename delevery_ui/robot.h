#ifndef ROBOT_H
#define ROBOT_H

#include <QColor>
#include <QPainter>
#include <QPoint>
#include <direction.h>

/**
 * @brief The RobotStatus enum
 * informs about the robot advancement in its research of the package
 * TOLOAD : the robot is aiming to its first targeted loading area
 * TOANALYSE : the robot is aiming for one of the analyse area (distributed randomly)
 * TODEPOSIT : the robot is aiming for its deposit attributed space to deliver the package
 * BACKTOLOADING : the robot is aiming back to a loading area where he picked a whong package
 * RELOAD : the robot is aiming for the next loading area to pisk its new package
 */
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
    int lastLoading;
public:
    Robot();
    Robot(QPoint ipos, QColor color, Direction dir);

    /**
     * @brief moveAt
     * Move the robot at the indicated position
     * @param p
     */
    void moveAt(QPoint p);

    /**
     * @brief startedOn
     * Get the start position of the robot
     * @return
     */
    QPoint startedOn();

    /**
     * @brief egtLastLoading
     * @return the last loading area id this robot targeted
     */
    int getLastLoading();

    /**
     * @brief setLastLoading
     * Set the last loading area of this robot
     * @param v
     */
    void setLastLoading(int v);

    /**
     * @brief setStartPoint
     * Set the start point of the robot to p
     * @param p
     */
    void setStartPoint(QPoint p);

    /**
     * @brief getColor
     * @return The robot color
     */
    QColor getColor();

    /**
     * @brief getPosition
     * @return The robot position
     */
    QPoint getPosition();

    /**
     * @brief pointing
     * @return The robot aiming direction
     */
    Direction pointing();

    /**
     * @brief setDirection
     * Set the robot aiming direction
     * @param d
     */
    void setDirection(Direction d);

    /**
     * @brief setReadyForOrder
     * Say the robot it can accept a new order, or reserve it
     * @param ready
     */
    void setReadyForOrder(bool ready);

    /**
     * @brief getStatus
     * @return The robot status
     * @see RobotStatus
     */
    RobotStatus getStatus();

    /**
     * @brief setStatus
     * set the robot status
     * @see RobotStatus
     * @param s
     */
    void setStatus(RobotStatus s);

    /**
     * @brief isReadyForOrder
     * Ask the robot if it can accept a new order
     * @return
     */
    bool isReadyForOrder();

    /**
     * @brief setCarryingColor
     * Set the robot's carrying packet color
     */
    void setCarryingColor(QString);

    /**
     * @brief getCarriedColor
     * @return The color of the packet the robot is carrying, empty if unknown
     */
    QString getCarriedColor();

    /**
     * @brief setColorToLookFor
     * Say to the robot which color of package he has to find
     */
    void setColorToLookFor(QString);

    /**
     * @brief getColorToLookFor
     * @return The package's color the robot is looking for
     */
    QString getColorToLookFor();

    /**
     * @brief draw
     * Draw the robot user the given painter object
     * @param p
     */
    void draw(QPainter* p);
};

#endif // ROBOT_H
