#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include "fieldelement.h"



class FieldModel
{
private:
    QList<FieldElement*> drawn;
    QList<FieldElement*> deposits;
    QList<FieldElement*> elements;

    FieldElement* elementAt(QPoint p);
public:
    FieldModel();
    void draw(QPainter *p, FieldElement *e);
    void drawAll(QPainter* p);
    void addElement(FieldElement* e);
};

#endif // FIELDMODEL_H
