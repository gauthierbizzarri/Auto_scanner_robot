#ifndef STATECOLORS_H
#define STATECOLORS_H

#include <QColor>

/**
 * @brief The StateColors class
 * Class storing the different colors and states of a robot indicator
 */
class StateColors
{
public:
    static QColor OK;
    static QColor KO;
    static QColor WAIT;
    static QColor UNKNOWN;
};

#endif // STATECOLORS_H
