#ifndef COLORS_H
#define COLORS_H

#include <QColor>
#include <QString>
#include <QMap>


static const QMap<QString, QColor> colors{
    {"green", QColor(0, 255, 0)},
    {"yellow", QColor(255, 255, 0)},
    {"blue", QColor(0, 0, 255)},
    {"red", QColor(255, 0, 0)}
}; //map representing the packages colors

#endif // COLORS_H
