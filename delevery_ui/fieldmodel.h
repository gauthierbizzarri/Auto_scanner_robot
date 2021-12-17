#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include "fieldelement.h"
#include "orderfollower.h"
#include "robot.h"

#include <QJsonObject>

/**
 * @brief The FieldModel class
 * The class keeping and manipulating all data about field
 * One class to keep them all
 */
class FieldModel : public QObject
{
    Q_OBJECT
private:
    QMap<int, FieldElement*> deposits;
    QMap<int, FieldElement*> loadings;
    QList<FieldElement*> analyse;
    QList<FieldElement*> elements;
    QMap<QString, OrderFollower*> orderFollowers;
    QList<int> cameras;
    QMap<QString, QColor> colors;

    QMap<QString, Robot*> robots;
    QMap<int, QString> colorsFound;
public:
    FieldModel();

    /**
     * @brief draw
     * Draws one element with the given painter object
     * @param p
     * @param e
     */
    void draw(QPainter *p, FieldElement *e);

    /**
     * @brief drawAll
     * Draw all elements using the given painter object
     * @param p
     */
    void drawAll(QPainter* p);

    /**
     * @brief addElement
     * Add an element to the field
     * @param e
     */
    void addElement(FieldElement* e);

    /**
     * @brief addDeposit
     * Add an element tagged as deposit to the field
     * @param e
     * @param index
     */
    void addDeposit(FieldElement* e, int index);

    /**
     * @brief addLoading
     * Add an element tagged as loading area to the field
     * @param e
     * @param index
     */
    void addLoading(FieldElement* e, int index);

    /**
     * @brief addColor
     * Add a new packages color
     * @param colot
     * @param value
     */
    void addColor(QString colot, QColor value);

    /**
     * @brief getCameras
     * @return A list of camera ids
     */
    const QList<int> getCameras();

    /**
     * @brief getColors
     * @return The mqp of the package colors
     */
    const QMap<QString, QColor> getColors();

    /**
     * @brief getLoading
     * @param index
     * @return The loading area element indexed by index
     */
    FieldElement* getLoading(int index);

    /**
     * @brief getLoadings
     * @return All the loading elements
     */
    const QMap<int, FieldElement*> getLoadings();

    /**
     * @brief getDeposit
     * @param index
     * @return Return the deposit element indexed by index
     */
    FieldElement *getDeposit(int index);

    /**
     * @brief getDeposits
     * @return All the deposits elements
     */
    const QMap<int, FieldElement*> getDeposits();

    /**
     * @brief depositIndex
     * @param e
     * @return Gets the deposit index of an element, or -1 if the element is not a deposit one
     */
    int depositIndex(FieldElement* e);

    /**
     * @brief getAnalyse
     * @param index
     * @return The analyse element indexed by index
     */
    FieldElement* getAnalyse(int index);

    /**
     * @brief addAnalyse
     * Add an element taged as analyse to the field
     * @param e
     */
    void addAnalyse(FieldElement* e);

    /**
     * @brief getAnalyses
     * @return all analyses elements
     */
    const QList<FieldElement*> getAnalyses();

    /**
     * @brief at
     * @param pos
     * @return An element at a position pos
     */
    FieldElement *at(QPoint pos);

    /**
     * @brief moveRobot
     * Moves the robot index by robotid to position pos
     * @param robotId
     * @param pos
     * @return
     */
    bool moveRobot(QString robotId, QPoint pos);

    /**
     * @brief getRobots
     * @return All robots
     */
    const QMap<QString, Robot*> getRobots();

    /**
     * @brief addRobot
     * Add a new robot
     * @param id
     * @param r
     */
    void addRobot(QString id, Robot* r);

    /**
     * @brief followSteps
     * Make the field model follow a ribot indexed by robotid using the follower
     * @param robotid
     * @param follower
     * @return
     */
    bool followSteps(QString robotid, OrderFollower *follower);

    /**
     * @brief follower
     * @param robotid
     * @return The follower of a robot indexed by robotid (if any)
     */
    OrderFollower *follower(QString robotid);

    /**
     * @brief getPath
     * @param from
     * @param to
     * @return The path from the from element to the to element
     * Usage of A* algorithme
     */
    const QList<FieldElement*> getPath(FieldElement* from, FieldElement* to);

    /**
     * @brief ColorFound
     * Tag a color as found on the loading area element indexed by v (if any)
     * @param loading
     * @param color
     */
    void ColorFound(int loading, QString color);

    /**
     * @brief getColorsFound
     * @return A map of loading area index and colors name
     */
    const QMap<int, QString> getColorsFound();
signals:
    void changed();
    void newPath(QString robotid, QList<FieldElement*> elements);
private slots:
    /**
     * @brief setRobotAvailable
     * Change the robot state to make it available to another process part
     * @param robot
     */
    void setRobotAvailable(QString robot);
};

#endif // FIELDMODEL_H
