#ifndef LEFTRIGHTPATHMAKER_H
#define LEFTRIGHTPATHMAKER_H

#include "fieldelement.h"
#include "pathmaker.h"



class LeftRightPathMaker : PathMaker<QList<FieldElement*>, QJsonObject>
{
private:
    Direction init;
public:
    LeftRightPathMaker(Direction init);

    // PathMaker interface
public:
    QJsonObject create(QList<FieldElement*> in);
};

#endif // LEFTRIGHTPATHMAKER_H
