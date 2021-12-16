#ifndef FIELDDRAW_H
#define FIELDDRAW_H

#include "fieldmodel.h"

#include <QWidget>

class FieldDraw : public QWidget
{
    Q_OBJECT
private:
    FieldModel* model;

    bool robotPositionRedifined;
    QString moveRobotId;
    QWidget* moveRobotSender;
public:
    explicit FieldDraw(QWidget *parent = nullptr);
    void setModel(FieldModel* model);
public slots:
    void redifineRobotPosition();
signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // FIELDDRAW_H
