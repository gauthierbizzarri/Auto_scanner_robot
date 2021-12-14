#ifndef UIORDERHANDLER_H
#define UIORDERHANDLER_H

#include "eventlistener.h"
#include "uiordermodel.h"

#include <QColumnView>

class UiOrderHandler : public EventListener
{
private:
    UiOrderModel* view;
public:
    UiOrderHandler(UiOrderModel *view);

    // EventListener interface
public:
    void handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta);
};

#endif // UIORDERHANDLER_H
