#include "downrightfieldelement.h"

DownRightFieldElement::DownRightFieldElement(QPoint pos, FieldElement *down, FieldElement *right)
    :FieldElement(pos,
{
{Direction::DOWN, down},
{Direction::RIGHT, right}
})
{

}

void DownRightFieldElement::paint(QPainter *p)
{
    int x = position.x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    int y = position.y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    int width = FieldElement::size/2;
    int height = FieldElement::thickness;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));

    x = position.x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    y = position.y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    width = FieldElement::thickness;
    height = FieldElement::size/2+FieldElement::thickness/2;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));
}
