#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "eventlistener.h"

#include <QJsonObject>

/**
 * @brief The EventManager class
 * Main class for events, managing them in a side thread
 */
class EventManager : public QObject
{
    Q_OBJECT
protected:
    QMap<QString, EventListener*> listeners;
    bool closed;

public:
    EventManager();
    /**
     * @brief addEventListener
     * Add an event listener with its own reference
     * @param reference
     * @param handler
     */
    void addEventListener(QString reference, EventListener* handler);

    /**
     * @brief launch
     * Starts the event processing
     * @param manager The manager to start
     */
    static void launch(EventManager* manager);

    /**
     * @brief close
     * Stops the event processing
     */
    void close();

public slots:
    /**
     * @brief process
     * Main function
     */
    virtual void process() = 0;
signals:
    void exited();
    void handleCalled(QJsonObject, bool, QMap<QString, QVariant>);
};

#endif // EVENTMANAGER_H
