#ifndef OBJECTPATHMAKER_H
#define OBJECTPATHMAKER_H

#include "fieldelement.h"
#include "pathmaker.h"

class ObjectPathMaker : PathMaker<QList<FieldElement*>, QList<FieldElement*>>
{
private:
    Direction init;
public:
    ObjectPathMaker(Direction dir);

    // PathMaker interface
public:
    QList<FieldElement*> create(QList<FieldElement*> in);
};

#endif // OBJECTPATHMAKER_H
