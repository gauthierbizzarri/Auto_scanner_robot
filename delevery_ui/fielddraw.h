#ifndef FIELDDRAW_H
#define FIELDDRAW_H

#include "fieldmodel.h"

#include <QWidget>

/**
 * @brief The FieldDraw class
 * Class used to handle the drawing of the field
 */
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

    /**
     * @brief setModel
     * Sets the field model to draw with
     * @param model
     */
    void setModel(FieldModel* model);
public slots:
    /**
     * @brief redifineRobotPosition
     * Handle the click event activation for robot position change
     */
    void redifineRobotPosition();
signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // FIELDDRAW_H
