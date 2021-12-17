#ifndef ROBOTINFO_H
#define ROBOTINFO_H

#include <QWidget>

namespace Ui {
class RobotInfo;
}

class RobotInfo : public QWidget
{
    Q_OBJECT

public:
    explicit RobotInfo(QString robotid, QWidget *parent = nullptr);
    ~RobotInfo();

    Ui::RobotInfo *ui;
private slots:
    void changeRobotPositionClicked();
signals:
    void changeRobotPosition();
};

#endif // ROBOTINFO_H
