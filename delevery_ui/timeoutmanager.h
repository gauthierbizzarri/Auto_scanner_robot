#ifndef TIMEOUTMANAGER_H
#define TIMEOUTMANAGER_H

#include <QObject>


/**
 * @brief The TimeoutManager class
 * Class managing timeout counter in a separate thread
 */
class TimeoutManager : public QObject
{
    Q_OBJECT
private:
    int timeout;
    bool aborted;
public:
    bool timeoutReached;
    TimeoutManager(int time = 2);
    static void launch(TimeoutManager* manager);
public slots:
    void process();
    void abort();
signals:
    void timedout();
    void exitAborted();
};

#endif // TIMEOUTMANAGER_H
