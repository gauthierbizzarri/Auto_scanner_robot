#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "eventmanager.h"
#include "fieldmodel.h"
#include "mqttmanager.h"
#include "pathmaker.h"

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
    FieldModel* fieldModel;
    PathMaker<QList<FieldElement*>, QJsonObject>* pathMaker;

private slots:
    bool checkOrder();
    void sendOrder();
    void fieldInvalid(QString field, QString reason);
    void openFields();
    void showTimeoutError();
    void appExit();
    void sendPath(QString robotid, QList<FieldElement*> elements);
};
#endif // MAINWINDOW_H
