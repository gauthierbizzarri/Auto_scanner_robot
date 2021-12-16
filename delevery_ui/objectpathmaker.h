#ifndef OBJECTPATHMAKER_H
#define OBJECTPATHMAKER_H

#include "fieldelement.h"
#include "pathmaker.h"

/**
 * @brief The ObjectPathMaker class
 * Path maker extracting only intersection elements to create its path
 */
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
