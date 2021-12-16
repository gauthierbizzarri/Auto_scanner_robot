#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <QJsonObject>
#include <QString>
#include <QVariant>


/**
 * @brief The EventListener class
 * Base class used to listen to events (act basically like a lambda)
 */
class EventListener : public QObject
{
    Q_OBJECT
public:
    EventListener(){

    };
public slots:
    /**
     * @brief customSlot
     * Slot used to perform some sided signal actions
     */
    virtual void customSlot(){};
    /**
     * @brief handle
     * Handles the event it describes
     * @param data the fondamenta data of the event
     * @param dataEmpty is the data empty
     * @param meta some meta data (you can put anything you want here)
     */
    virtual void handle(QJsonObject data, bool dataEmpty, QMap<QString, QVariant> meta) = 0;
};

#endif // EVENTLISTENER_H
