#ifndef FIELDDRAW_H
#define FIELDDRAW_H

#include "fieldmodel.h"

#include <QWidget>

class FieldDraw : public QWidget
{
    Q_OBJECT
private:
    FieldModel* model;
public:
    explicit FieldDraw(QWidget *parent = nullptr);
    void setModel(FieldModel* model);

signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // FIELDDRAW_H
