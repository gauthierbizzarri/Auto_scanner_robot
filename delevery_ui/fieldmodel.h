#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include "fieldelement.h"
#include "orderfollower.h"
#include "robot.h"

#include <QJsonObject>

class FieldModel : public QObject
{
    Q_OBJECT
private:
    QList<FieldElement*> drawn;
    QMap<int, FieldElement*> deposits;
    QMap<int, FieldElement*> loadings;
    QList<FieldElement*> analyse;
    QList<FieldElement*> elements;
    QMap<QString, OrderFollower*> orderFollowers;

    QMap<QString, Robot*> robots;

    int lastLoading;
public:
    FieldModel();
    void draw(QPainter *p, FieldElement *e);
    void drawAll(QPainter* p);
    void addElement(FieldElement* e);
    void addDeposit(FieldElement* e, int index);
    void addLoading(FieldElement* e, int index);
    FieldElement* getLoading(int index);
    const QMap<int, FieldElement*> getLoadings();
    FieldElement *getDeposit(int index);
    const QMap<int, FieldElement*> getDeposits();
    int depositIndex(FieldElement* e);
    FieldElement* getAnalyse(int index);
    void addAnalyse(FieldElement* e);
    FieldElement *at(QPoint pos);
    bool moveRobot(QString robotId, QPoint pos);
    QMap<QString, Robot*> getRobots();
    bool followSteps(QString robotid, OrderFollower *follower);
    OrderFollower *follower(QString robotid);
    QList<FieldElement*> getPath(Direction init, FieldElement* from, FieldElement* to);
    void setLastLoading(int v);
    int getLastLoading();
signals:
    void changed();
    void newPath(QString robotid, QList<FieldElement*> elements);
private slots:
    void setRobotAvailable(QString robot);
};

#endif // FIELDMODEL_H
