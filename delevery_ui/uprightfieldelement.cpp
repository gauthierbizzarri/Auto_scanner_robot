#include "uprightfieldelement.h"

UpRightFieldElement::UpRightFieldElement(QPoint pos, FieldElement *up, FieldElement *right)
    :FieldElement(pos,
{
{Direction::UP, up},
{Direction::RIGHT, right}
})
{

}

void UpRightFieldElement::paint(QPainter *p)
{
    int x = position.x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    int y = position.y()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    int width = FieldElement::size/2+FieldElement::thickness/2;
    int height = FieldElement::thickness;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));

    x = position.x()*FieldElement::size+FieldElement::size/2-FieldElement::thickness/2;
    y = position.y()*FieldElement::size;
    width = FieldElement::thickness;
    height = FieldElement::size/2+FieldElement::thickness/2;
    p->fillRect(x, y, width, height, QBrush(QColor(0, 0, 0)));
}
