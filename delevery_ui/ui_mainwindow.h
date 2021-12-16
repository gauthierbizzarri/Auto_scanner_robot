/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "config.h"
#include "fielddraw.h"
#include "iconlabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QToolBox *toolBox;
    QWidget *order;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *robotSelector;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *colorSelector;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *loadingZoneSelector;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QCommandLinkButton *clbtSend;
    QTableView *cvHistory;
    QWidget *page;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    FieldDraw *widget_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QFormLayout *formLayout;
    QLabel *label_5;
    IconLabel *orderState;
    QLabel *label_7;
    IconLabel *connectionState;
    QLabel *label_9;
    IconLabel *PackageTransitState;
    QLabel *label_11;
    IconLabel *packageColor;
    QPushButton *pbRedifRobPos;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_4;
    QWidget *history;
    QVBoxLayout *verticalLayout_2;
    config *widget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1125, 632);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolBox = new QToolBox(centralwidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        order = new QWidget();
        order->setObjectName(QString::fromUtf8("order"));
        order->setGeometry(QRect(0, 0, 1107, 477));
        verticalLayout_3 = new QVBoxLayout(order);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(order);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(150, 50));
        label->setWordWrap(false);
        label->setMargin(50);

        horizontalLayout->addWidget(label);

        robotSelector = new QComboBox(order);
        robotSelector->setObjectName(QString::fromUtf8("robotSelector"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(robotSelector->sizePolicy().hasHeightForWidth());
        robotSelector->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(robotSelector);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(order);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMaximumSize(QSize(150, 50));
        label_2->setMargin(45);

        horizontalLayout_2->addWidget(label_2);

        colorSelector = new QComboBox(order);
        colorSelector->setObjectName(QString::fromUtf8("colorSelector"));

        horizontalLayout_2->addWidget(colorSelector);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(order);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMaximumSize(QSize(150, 50));
        label_3->setMargin(17);

        horizontalLayout_3->addWidget(label_3);

        loadingZoneSelector = new QComboBox(order);
        loadingZoneSelector->setObjectName(QString::fromUtf8("loadingZoneSelector"));

        horizontalLayout_3->addWidget(loadingZoneSelector);

        checkBox = new QCheckBox(order);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setMaximumSize(QSize(230, 16777215));

        horizontalLayout_3->addWidget(checkBox);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        clbtSend = new QCommandLinkButton(order);
        clbtSend->setObjectName(QString::fromUtf8("clbtSend"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(clbtSend->sizePolicy().hasHeightForWidth());
        clbtSend->setSizePolicy(sizePolicy2);
        clbtSend->setMaximumSize(QSize(100, 30));

        horizontalLayout_4->addWidget(clbtSend);


        verticalLayout_3->addLayout(horizontalLayout_4);

        cvHistory = new QTableView(order);
        cvHistory->setObjectName(QString::fromUtf8("cvHistory"));

        verticalLayout_3->addWidget(cvHistory);

        toolBox->addItem(order, QString::fromUtf8("Cr\303\251er un ordre"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 1107, 477));
        horizontalLayout_6 = new QHBoxLayout(page);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        widget_2 = new FieldDraw(page);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy3);
        widget_2->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));

        horizontalLayout_7->addWidget(widget_2);

        groupBox = new QGroupBox(page);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(300, 0));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        orderState = new IconLabel(groupBox);
        orderState->setObjectName(QString::fromUtf8("orderState"));

        formLayout->setWidget(0, QFormLayout::FieldRole, orderState);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_7);

        connectionState = new IconLabel(groupBox);
        connectionState->setObjectName(QString::fromUtf8("connectionState"));

        formLayout->setWidget(1, QFormLayout::FieldRole, connectionState);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_9);

        PackageTransitState = new IconLabel(groupBox);
        PackageTransitState->setObjectName(QString::fromUtf8("PackageTransitState"));

        formLayout->setWidget(2, QFormLayout::FieldRole, PackageTransitState);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_11);

        packageColor = new IconLabel(groupBox);
        packageColor->setObjectName(QString::fromUtf8("packageColor"));

        formLayout->setWidget(3, QFormLayout::FieldRole, packageColor);


        verticalLayout_5->addLayout(formLayout);

        pbRedifRobPos = new QPushButton(groupBox);
        pbRedifRobPos->setObjectName(QString::fromUtf8("pbRedifRobPos"));

        verticalLayout_5->addWidget(pbRedifRobPos);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);


        horizontalLayout_7->addWidget(groupBox);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));

        horizontalLayout_7->addLayout(verticalLayout_4);


        horizontalLayout_6->addLayout(horizontalLayout_7);

        toolBox->addItem(page, QString::fromUtf8("Etat et position du robot"));
        history = new QWidget();
        history->setObjectName(QString::fromUtf8("history"));
        history->setGeometry(QRect(0, 0, 1107, 477));
        verticalLayout_2 = new QVBoxLayout(history);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget = new config(history);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout_2->addWidget(widget);

        toolBox->addItem(history, QString::fromUtf8("Options"));

        verticalLayout->addWidget(toolBox);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1125, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Robot : ", nullptr));
        robotSelector->setCurrentText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Couleur :", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Zone de largage :", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Compl\303\251ter automatiquement", nullptr));
        clbtSend->setText(QCoreApplication::translate("MainWindow", "Envoyer", nullptr));
        toolBox->setItemText(toolBox->indexOf(order), QCoreApplication::translate("MainWindow", "Cr\303\251er un ordre", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Informations du robot", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Etat du robot :", nullptr));
        orderState->setText(QCoreApplication::translate("MainWindow", "En attente d'ordre", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Etat de connection du robot :", nullptr));
        connectionState->setText(QCoreApplication::translate("MainWindow", "Connect\303\251", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Colis en transit :", nullptr));
        PackageTransitState->setText(QCoreApplication::translate("MainWindow", "Non", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Couleur du colis :", nullptr));
        packageColor->setText(QCoreApplication::translate("MainWindow", "inconnue", nullptr));
        pbRedifRobPos->setText(QCoreApplication::translate("MainWindow", "Red\303\251finir position robot (annulera ordres en cours )", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QCoreApplication::translate("MainWindow", "Etat et position du robot", nullptr));
        toolBox->setItemText(toolBox->indexOf(history), QCoreApplication::translate("MainWindow", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
