#include "downleftfieldelement.h"
#include "fieldmodel.h"
#include "tdownfieldelement.h"
#include "tleftfieldelement.h"
#include "trightfieldelement.h"
#include "tupfieldelement.h"

FieldElement *FieldModel::elementAt(QPoint p)
{
    Q_FOREACH(FieldElement* f, elements)
    {
        if(f->getPosition() == p)
        {
            return f;
        }
    }
    return nullptr;
}

FieldModel::FieldModel()
{
    FieldElement* downleft1 = new DownLeftFieldElement(QPoint(0, 0));
    deposits.append(downleft1);
    elements.append(downleft1);

    addElement(new TUpFieldElement(QPoint(0, 1)));
    addElement(new TDownFieldElement(QPoint(1, 1)));
    addElement(new TLeftFieldElement(QPoint(2, 1)));
    addElement(new TRightFieldElement(QPoint(2, 2)));
    addElement(new DownLeftFieldElement(QPoint(3, 2)));
}

void FieldModel::draw(QPainter *p, FieldElement *e)
{
    e->paint(p);
}

void FieldModel::drawAll(QPainter *p)
{
    Q_FOREACH(FieldElement* e, elements)
    {
        e->paint(p);
    }
}

void FieldModel::addElement(FieldElement *e)
{
    QPoint p = e->getPosition();
    QPoint up = p;
    up.setY(up.y()-1);
    QPoint down = p;
    down.setY(down.y()+1);
    QPoint left = p;
    left.setX(left.x()-1);
    QPoint right = p;
    right.setX(right.x()+1);
    FieldElement* upE = elementAt(up);
    FieldElement* downE = elementAt(down);
    FieldElement* leftE = elementAt(left);
    FieldElement* rightE = elementAt(right);
    Q_FOREACH(Direction d, e->canGoTo())
    {
        switch(d)
        {
        case UP:
            if(upE != nullptr && upE->canGoTo().contains(Direction::DOWN))
            {
                e->addToward(Direction::UP, upE);
                upE->addToward(Direction::DOWN, e);
            }
            break;
        case DOWN:
            if(downE != nullptr && downE->canGoTo().contains(Direction::UP))
            {
                e->addToward(Direction::DOWN, downE);
                downE->addToward(Direction::UP, e);
            }
            break;
        case LEFT:
            if(leftE != nullptr && leftE->canGoTo().contains(Direction::RIGHT))
            {
                e->addToward(Direction::LEFT, leftE);
                leftE->addToward(Direction::RIGHT, e);
            }
            break;
        case RIGHT:
            if(rightE != nullptr && rightE->canGoTo().contains(Direction::LEFT))
            {
                e->addToward(Direction::RIGHT, rightE);
                rightE->addToward(Direction::LEFT, e);
            }
            break;
        }
    }
    elements.append(e);
}
