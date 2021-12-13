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
#include <QtWidgets/QColumnView>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QToolBox *toolBox;
    QWidget *order;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QComboBox *startSelector;
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
    QWidget *history;
    QVBoxLayout *verticalLayout_2;
    QColumnView *cvHistory;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 653);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolBox = new QToolBox(centralwidget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        order = new QWidget();
        order->setObjectName(QString::fromUtf8("order"));
        order->setGeometry(QRect(0, 0, 982, 529));
        verticalLayout_3 = new QVBoxLayout(order);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(order);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(150, 55));
        label_4->setMargin(18);

        horizontalLayout_5->addWidget(label_4);

        startSelector = new QComboBox(order);
        startSelector->setObjectName(QString::fromUtf8("startSelector"));

        horizontalLayout_5->addWidget(startSelector);


        verticalLayout_3->addLayout(horizontalLayout_5);

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

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

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

        toolBox->addItem(order, QString::fromUtf8("Cr\303\251er un ordre"));
        history = new QWidget();
        history->setObjectName(QString::fromUtf8("history"));
        history->setGeometry(QRect(0, 0, 982, 529));
        verticalLayout_2 = new QVBoxLayout(history);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        cvHistory = new QColumnView(history);
        cvHistory->setObjectName(QString::fromUtf8("cvHistory"));

        verticalLayout_2->addWidget(cvHistory);

        toolBox->addItem(history, QString::fromUtf8("Historique des ordres"));

        verticalLayout->addWidget(toolBox);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Zone de d\303\251pot :", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Robot : ", nullptr));
        robotSelector->setCurrentText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Couleur :", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Zone de largage :", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Compl\303\251ter automatiquement", nullptr));
        clbtSend->setText(QCoreApplication::translate("MainWindow", "Envoyer", nullptr));
        toolBox->setItemText(toolBox->indexOf(order), QCoreApplication::translate("MainWindow", "Cr\303\251er un ordre", nullptr));
        toolBox->setItemText(toolBox->indexOf(history), QCoreApplication::translate("MainWindow", "Historique des ordres", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
