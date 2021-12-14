#include "eventlistener.h"
#include "eventmanager.h"

#include <QThread>

EventManager::EventManager()
{
    closed = false;
}

void EventManager::addEventListener(QString reference, EventListener* handler)
{
    listeners.insert(reference, handler);
}

void EventManager::launch(EventManager *manager)
{
    QThread* thread = new QThread();
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(manager, SIGNAL(exited()), thread, SLOT(quit()));
    connect(thread, SIGNAL(started()), manager, SLOT(process()));
    connect(manager, SIGNAL(exited()), manager, SLOT(deleteLater()));
    manager->moveToThread(thread);
    thread->start();
}

void EventManager::close()
{
    closed=true;
}
