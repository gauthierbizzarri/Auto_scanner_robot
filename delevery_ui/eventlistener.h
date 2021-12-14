#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <QJsonObject>
#include <QString>
#include <QVariant>



class EventListener
{
public:
    EventListener(){

    };
    virtual void handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta) = 0;
};

#endif // EVENTLISTENER_H
