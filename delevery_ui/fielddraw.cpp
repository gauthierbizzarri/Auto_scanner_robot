#include "fielddraw.h"

FieldDraw::FieldDraw(QWidget *parent)
{
}

void FieldDraw::setModel(FieldModel *model)
{
    this->model=model;
}

void FieldDraw::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    model->drawAll(&painter);
}

void FieldDraw::resizeEvent(QResizeEvent *event)
{
    update();
}
