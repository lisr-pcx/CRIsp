/********************************************************************************
** Form generated from reading UI file 'mainpage.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINPAGE_H
#define UI_MAINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainPage
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QToolBox *tb_UserMode;
    QWidget *EncryptMode;
    QVBoxLayout *verticalLayout;
    QLabel *lbl_Mode;
    QGridLayout *gridLayout;
    QLabel *lbl_Data;
    QLabel *lbl_IV;
    QPushButton *pb_LoadIV;
    QLabel *lbl_Key;
    QPushButton *pb_LoadKey;
    QPushButton *pb_LoadData;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_Encrypt;
    QSpacerItem *horizontalSpacer_4;
    QWidget *DecryptMode;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainPage)
    {
        if (MainPage->objectName().isEmpty())
            MainPage->setObjectName("MainPage");
        MainPage->resize(600, 300);
        centralwidget = new QWidget(MainPage);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tb_UserMode = new QToolBox(centralwidget);
        tb_UserMode->setObjectName("tb_UserMode");
        EncryptMode = new QWidget();
        EncryptMode->setObjectName("EncryptMode");
        EncryptMode->setGeometry(QRect(0, 0, 582, 179));
        verticalLayout = new QVBoxLayout(EncryptMode);
        verticalLayout->setObjectName("verticalLayout");
        lbl_Mode = new QLabel(EncryptMode);
        lbl_Mode->setObjectName("lbl_Mode");

        verticalLayout->addWidget(lbl_Mode);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        lbl_Data = new QLabel(EncryptMode);
        lbl_Data->setObjectName("lbl_Data");
        lbl_Data->setScaledContents(false);

        gridLayout->addWidget(lbl_Data, 0, 0, 1, 2);

        lbl_IV = new QLabel(EncryptMode);
        lbl_IV->setObjectName("lbl_IV");

        gridLayout->addWidget(lbl_IV, 2, 0, 1, 1);

        pb_LoadIV = new QPushButton(EncryptMode);
        pb_LoadIV->setObjectName("pb_LoadIV");

        gridLayout->addWidget(pb_LoadIV, 2, 3, 1, 1);

        lbl_Key = new QLabel(EncryptMode);
        lbl_Key->setObjectName("lbl_Key");

        gridLayout->addWidget(lbl_Key, 1, 0, 1, 1);

        pb_LoadKey = new QPushButton(EncryptMode);
        pb_LoadKey->setObjectName("pb_LoadKey");

        gridLayout->addWidget(pb_LoadKey, 1, 3, 1, 1);

        pb_LoadData = new QPushButton(EncryptMode);
        pb_LoadData->setObjectName("pb_LoadData");

        gridLayout->addWidget(pb_LoadData, 0, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(198, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(198, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 1, 1, 2);

        horizontalSpacer = new QSpacerItem(178, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pb_Encrypt = new QPushButton(EncryptMode);
        pb_Encrypt->setObjectName("pb_Encrypt");

        horizontalLayout_2->addWidget(pb_Encrypt);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        tb_UserMode->addItem(EncryptMode, QString::fromUtf8("Encrypt"));
        DecryptMode = new QWidget();
        DecryptMode->setObjectName("DecryptMode");
        DecryptMode->setGeometry(QRect(0, 0, 582, 179));
        tb_UserMode->addItem(DecryptMode, QString::fromUtf8("Decrypt"));

        verticalLayout_2->addWidget(tb_UserMode);

        MainPage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainPage);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 600, 22));
        MainPage->setMenuBar(menubar);
        statusbar = new QStatusBar(MainPage);
        statusbar->setObjectName("statusbar");
        MainPage->setStatusBar(statusbar);

        retranslateUi(MainPage);

        tb_UserMode->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainPage);
    } // setupUi

    void retranslateUi(QMainWindow *MainPage)
    {
        MainPage->setWindowTitle(QCoreApplication::translate("MainPage", "MainPage", nullptr));
        lbl_Mode->setText(QCoreApplication::translate("MainPage", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:700;\">AES-256 CBC</span></p></body></html>", nullptr));
        lbl_Data->setText(QCoreApplication::translate("MainPage", "data information", nullptr));
        lbl_IV->setText(QCoreApplication::translate("MainPage", "IV information", nullptr));
        pb_LoadIV->setText(QCoreApplication::translate("MainPage", "LOAD IV", nullptr));
        lbl_Key->setText(QCoreApplication::translate("MainPage", "key information", nullptr));
        pb_LoadKey->setText(QCoreApplication::translate("MainPage", "LOAD KEY", nullptr));
        pb_LoadData->setText(QCoreApplication::translate("MainPage", "LOAD DATA", nullptr));
        pb_Encrypt->setText(QCoreApplication::translate("MainPage", "ENCRYPT", nullptr));
        tb_UserMode->setItemText(tb_UserMode->indexOf(EncryptMode), QCoreApplication::translate("MainPage", "Encrypt", nullptr));
        tb_UserMode->setItemText(tb_UserMode->indexOf(DecryptMode), QCoreApplication::translate("MainPage", "Decrypt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainPage: public Ui_MainPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINPAGE_H
