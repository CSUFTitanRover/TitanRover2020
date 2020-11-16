/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "onecamera.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QComboBox *singleCameraCB;
    QComboBox *configurationCB;
    QHBoxLayout *horizontalLayout_5;
    oneCamera *cameraOne;
    oneCamera *cameraTwo;
    QHBoxLayout *horizontalLayout_4;
    oneCamera *cameraThree;
    oneCamera *cameraFour;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1151, 618);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 9, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setSizeConstraint(QLayout::SetMinimumSize);
        singleCameraCB = new QComboBox(centralwidget);
        singleCameraCB->addItem(QString());
        singleCameraCB->setObjectName(QString::fromUtf8("singleCameraCB"));

        horizontalLayout_6->addWidget(singleCameraCB);

        configurationCB = new QComboBox(centralwidget);
        configurationCB->addItem(QString());
        configurationCB->setObjectName(QString::fromUtf8("configurationCB"));

        horizontalLayout_6->addWidget(configurationCB);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetNoConstraint);
        cameraOne = new oneCamera(centralwidget);
        cameraOne->setObjectName(QString::fromUtf8("cameraOne"));

        horizontalLayout_5->addWidget(cameraOne);

        cameraTwo = new oneCamera(centralwidget);
        cameraTwo->setObjectName(QString::fromUtf8("cameraTwo"));

        horizontalLayout_5->addWidget(cameraTwo);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetNoConstraint);
        cameraThree = new oneCamera(centralwidget);
        cameraThree->setObjectName(QString::fromUtf8("cameraThree"));

        horizontalLayout_4->addWidget(cameraThree);

        cameraFour = new oneCamera(centralwidget);
        cameraFour->setObjectName(QString::fromUtf8("cameraFour"));

        horizontalLayout_4->addWidget(cameraFour);


        verticalLayout->addLayout(horizontalLayout_4);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "UiCamera", nullptr));
        singleCameraCB->setItemText(0, QApplication::translate("MainWindow", "Select Camera...", nullptr));

        configurationCB->setItemText(0, QApplication::translate("MainWindow", "Select Configuration...", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
