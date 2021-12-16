#include "iconlabel.h"
#include <QPainterPath>
#include <QPainter>

#include "StateColors.h"

int IconLabel::iconSize = 15;

IconLabel::IconLabel(QWidget* parent) : QLabel(parent)
{
    color = StateColors::UNKNOWN;
    text = "sampleText";
}

IconLabel::IconLabel(QColor color, QString text, QWidget* parent) : QLabel(parent)
{
    this->color = color;
    this->text = text;
}

void IconLabel::setText(QString text)
{
    this->text = text;
    update();
}

void IconLabel::setColor(QColor color)
{
    this->color = color;
    update();
}

void IconLabel::paintEvent(QPaintEvent *event)
{
    int spacing = height()/2-iconSize/2;
    // creating circle clip area
    QPainterPath path;
    path.addEllipse(spacing, spacing, iconSize, iconSize);

    QPainter painter(this);

    // filling rounded area if needed
    painter.fillPath(path, color);
    QPainterPath textPath;
    QFont font("comic-sans");
    int maxHeight = QFontMetrics(font).height()/2+(height()/2)+10>iconSize+spacing*2
            ? QFontMetrics(font).height()/2+(height()/2)+10
            : iconSize+spacing*2;
    setFixedHeight(maxHeight);
    textPath.addText(iconSize+spacing*3, QFontMetrics(font).height()/2+(height()/2), font, text);
    painter.fillPath(textPath, QBrush(QColor(0,0, 0)));

    setFixedWidth(textPath.boundingRect().width()+spacing*5+iconSize);
    painter.end();
}
