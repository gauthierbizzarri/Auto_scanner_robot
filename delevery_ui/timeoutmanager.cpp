#include "timeoutmanager.h"

#include <QThread>
#include <QTime>

TimeoutManager::TimeoutManager(int time)
{
    timeout = time;
    aborted = false;
    timeoutReached = false;
}

void TimeoutManager::launch(TimeoutManager* timeout)
{
    QThread* thread = new QThread();
    connect(timeout, SIGNAL(timedout()), thread, SLOT(quit()));
    connect(timeout, SIGNAL(exitAborted()), thread, SLOT(quit()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), timeout, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), timeout, SLOT(process()));
    timeout->moveToThread(thread);
    thread->start();
}

void TimeoutManager::process()
{
    QTime time = QTime::currentTime();
    while((QTime::currentTime().second()-time.second()) < timeout && !aborted);
    if(!aborted)
    {
        timeoutReached = true;
        emit timedout();
    }
    else
    {
        emit exitAborted();
    }
}

void TimeoutManager::abort()
{
    aborted = true;
}
