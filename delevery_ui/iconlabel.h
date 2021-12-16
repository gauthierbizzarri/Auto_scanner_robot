#ifndef ICONLABEL_H
#define ICONLABEL_H

#include <QLabel>

class IconLabel : public QLabel
{
private:
    QString text;
    QColor color;
    static int iconSize;
public:
    IconLabel(QWidget* parent = nullptr);
    IconLabel(QColor color, QString text, QWidget* parent = nullptr);

    void setText(QString text);
    void setColor(QColor color);
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // ICONLABEL_H
