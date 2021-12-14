/********************************************************************************
** Form generated from reading UI file 'config.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_config
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *port;
    QLabel *label_2;
    QLineEdit *host;
    QLabel *label_3;
    QLineEdit *username;
    QLabel *label_4;
    QLineEdit *password;
    QLabel *label_5;
    QLineEdit *clientid;
    QLabel *label_6;
    QComboBox *protocolversion;
    QLabel *label_7;
    QSpinBox *keepalive;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbSave;

    void setupUi(QWidget *config)
    {
        if (config->objectName().isEmpty())
            config->setObjectName(QString::fromUtf8("config"));
        config->resize(1152, 662);
        verticalLayout = new QVBoxLayout(config);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(config);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        port = new QSpinBox(groupBox);
        port->setObjectName(QString::fromUtf8("port"));
        port->setMaximum(65535);

        formLayout->setWidget(0, QFormLayout::FieldRole, port);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        host = new QLineEdit(groupBox);
        host->setObjectName(QString::fromUtf8("host"));

        formLayout->setWidget(1, QFormLayout::FieldRole, host);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        username = new QLineEdit(groupBox);
        username->setObjectName(QString::fromUtf8("username"));

        formLayout->setWidget(2, QFormLayout::FieldRole, username);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        password = new QLineEdit(groupBox);
        password->setObjectName(QString::fromUtf8("password"));
        password->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(3, QFormLayout::FieldRole, password);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        clientid = new QLineEdit(groupBox);
        clientid->setObjectName(QString::fromUtf8("clientid"));

        formLayout->setWidget(4, QFormLayout::FieldRole, clientid);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        protocolversion = new QComboBox(groupBox);
        protocolversion->setObjectName(QString::fromUtf8("protocolversion"));

        formLayout->setWidget(5, QFormLayout::FieldRole, protocolversion);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        keepalive = new QSpinBox(groupBox);
        keepalive->setObjectName(QString::fromUtf8("keepalive"));
        keepalive->setMaximum(500);

        formLayout->setWidget(6, QFormLayout::FieldRole, keepalive);


        verticalLayout_2->addLayout(formLayout);


        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbSave = new QPushButton(config);
        pbSave->setObjectName(QString::fromUtf8("pbSave"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pbSave->sizePolicy().hasHeightForWidth());
        pbSave->setSizePolicy(sizePolicy1);
        pbSave->setMinimumSize(QSize(300, 0));

        horizontalLayout->addWidget(pbSave);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(config);

        QMetaObject::connectSlotsByName(config);
    } // setupUi

    void retranslateUi(QWidget *config)
    {
        config->setWindowTitle(QCoreApplication::translate("config", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("config", "MQTT", nullptr));
        label->setText(QCoreApplication::translate("config", "Port :", nullptr));
        label_2->setText(QCoreApplication::translate("config", "H\303\264te : ", nullptr));
        label_3->setText(QCoreApplication::translate("config", "Nom d'utilisateur (vide si aucun) :", nullptr));
        label_4->setText(QCoreApplication::translate("config", "Mot de passe (vide si aucun) :", nullptr));
        label_5->setText(QCoreApplication::translate("config", "Identifiant client (vide si aucun) :", nullptr));
        label_6->setText(QCoreApplication::translate("config", "Version de protocole :", nullptr));
        label_7->setText(QCoreApplication::translate("config", "Dur\303\251e maximale d'innactivit\303\251 des topics (en s) :", nullptr));
        pbSave->setText(QCoreApplication::translate("config", "Sauvegarder les modifications", nullptr));
    } // retranslateUi

};

namespace Ui {
    class config: public Ui_config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_H
