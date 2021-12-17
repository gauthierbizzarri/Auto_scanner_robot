#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "eventmanager.h"
#include "fieldmodel.h"
#include "mqttmanager.h"
#include "pathmaker.h"
#include "robotinfo.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 * Main application window
 */
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
    QMap<QString, RobotInfo*> robotInfos;

private slots:
    /**
     * @brief checkOrder
     * verify if an order is valid
     * @return
     */
    bool checkOrder();

    /**
     * @brief sendOrder
     * Sends an order on process
     */
    void sendOrder();

    /**
     * @brief fieldInvalid
     * Manage order fields invlalidity
     * @param field
     * @param reason
     */
    void fieldInvalid(QString field, QString reason);

    /**
     * @brief openFields
     * Open order sending
     */
    void openFields();

    /**
     * @brief showTimeoutError
     * Display a timeout error
     */
    void showTimeoutError();

    /**
     * @brief appExit
     * Close this window
     */
    void appExit();

    /**
     * @brief sendPath
     * Sends a path composed of elements to robot
     * @param robotid
     * @param elements
     */
    void sendPath(QString robotid, QList<FieldElement*> elements);
};
#endif // MAINWINDOW_H
