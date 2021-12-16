#ifndef JSONPATHMAKER_H
#define JSONPATHMAKER_H

#include "pathmaker.h"
#include "fieldelement.h"

#include <QList>

class JsonPathMaker : public PathMaker<QList<FieldElement*>, QJsonObject>
{
private:
    Direction init;
public:
    JsonPathMaker(Direction init);

    // PathMaker interface
public:
    QJsonObject create(QList<FieldElement*> in);
};

#endif // JSONPATHMAKER_H
