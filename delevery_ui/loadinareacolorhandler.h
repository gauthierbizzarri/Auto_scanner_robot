#ifndef LOADINAREACOLORHANDLER_H
#define LOADINAREACOLORHANDLER_H

#include "eventlistener.h"
#include "fieldmodel.h"
#include "iconlabel.h"


/**
 * @brief The LoadinAreaColorHandler class
 * Class used to handle the arrival of informations about the field from other robots and cameras (collaborative exploring)
 */
class LoadinAreaColorHandler : public EventListener
{
private:
     FieldModel *model;
     QList<IconLabel*> loadings;
public:
    LoadinAreaColorHandler(QList<IconLabel*> loadings, FieldModel* model);

    // EventListener interface
public:
    void handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta);
};

#endif // LOADINAREACOLORHANDLER_H
