#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "eventlistener.h"

#include <QJsonObject>

class EventManager : public QObject
{
    Q_OBJECT
protected:
    QMap<QString, EventListener*> listeners;
    bool closed;

public:
    EventManager();
    void addEventListener(QString reference, EventListener* handler);
    static void launch(EventManager* manager);
    void close();

public slots:
    virtual void process() = 0;
signals:
    void exited();
};

#endif // EVENTMANAGER_H
