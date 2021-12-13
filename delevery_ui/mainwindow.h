#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mqttmanager.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MQTTManager* manager, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MQTTManager* manager;

private slots:
    bool checkOrder();
    void sendOrder();
    void recieveMessage(QMqttMessage message);
    void fieldInvalid(QString field, QString reason);
    void openFields();
    void showTimeoutError();
};
#endif // MAINWINDOW_H
