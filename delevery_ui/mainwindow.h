#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "eventmanager.h"
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
    EventManager* mqttEventManager;

private slots:
    bool checkOrder();
    void sendOrder();
    void fieldInvalid(QString field, QString reason);
    void openFields();
    void showTimeoutError();
    void appExit();
};
#endif // MAINWINDOW_H
