/********************************************************************************
** Form generated from reading UI file 'onecamera.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONECAMERA_H
#define UI_ONECAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_oneCamera
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *cameraPic;
    QVBoxLayout *verticalLayout;
    QPushButton *popNewScreenButton;
    QPushButton *pauseButton;
    QRadioButton *highQualityButton;
    QRadioButton *mediumQualityButton;
    QRadioButton *lowQualityButton;

    void setupUi(QWidget *oneCamera)
    {
        if (oneCamera->objectName().isEmpty())
            oneCamera->setObjectName(QString::fromUtf8("oneCamera"));
        oneCamera->resize(726, 502);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(oneCamera->sizePolicy().hasHeightForWidth());
        oneCamera->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(238, 238, 236, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(246, 246, 245, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(119, 119, 118, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(159, 159, 157, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush6(QColor(255, 255, 220, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush7(QColor(0, 0, 0, 128));
        brush7.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush7);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        QBrush brush8(QColor(0, 0, 0, 128));
        brush8.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush8);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush9(QColor(0, 0, 0, 128));
        brush9.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush9);
#endif
        oneCamera->setPalette(palette);
        oneCamera->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(oneCamera);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        cameraPic = new QLabel(oneCamera);
        cameraPic->setObjectName(QString::fromUtf8("cameraPic"));
        cameraPic->setEnabled(true);
        sizePolicy.setHeightForWidth(cameraPic->sizePolicy().hasHeightForWidth());
        cameraPic->setSizePolicy(sizePolicy);
        cameraPic->setMinimumSize(QSize(0, 0));
        cameraPic->setStyleSheet(QString::fromUtf8(""));
        cameraPic->setAlignment(Qt::AlignCenter);
        cameraPic->setWordWrap(false);

        horizontalLayout->addWidget(cameraPic);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        popNewScreenButton = new QPushButton(oneCamera);
        popNewScreenButton->setObjectName(QString::fromUtf8("popNewScreenButton"));

        verticalLayout->addWidget(popNewScreenButton);

        pauseButton = new QPushButton(oneCamera);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pauseButton->sizePolicy().hasHeightForWidth());
        pauseButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(pauseButton);

        highQualityButton = new QRadioButton(oneCamera);
        highQualityButton->setObjectName(QString::fromUtf8("highQualityButton"));

        verticalLayout->addWidget(highQualityButton);

        mediumQualityButton = new QRadioButton(oneCamera);
        mediumQualityButton->setObjectName(QString::fromUtf8("mediumQualityButton"));

        verticalLayout->addWidget(mediumQualityButton);

        lowQualityButton = new QRadioButton(oneCamera);
        lowQualityButton->setObjectName(QString::fromUtf8("lowQualityButton"));

        verticalLayout->addWidget(lowQualityButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(oneCamera);

        QMetaObject::connectSlotsByName(oneCamera);
    } // setupUi

    void retranslateUi(QWidget *oneCamera)
    {
        oneCamera->setWindowTitle(QApplication::translate("oneCamera", "Form", nullptr));
        cameraPic->setText(QApplication::translate("oneCamera", "test text", nullptr));
        popNewScreenButton->setText(QApplication::translate("oneCamera", "Pop Up", nullptr));
        pauseButton->setText(QApplication::translate("oneCamera", "Pause", nullptr));
        highQualityButton->setText(QApplication::translate("oneCamera", "High", nullptr));
        mediumQualityButton->setText(QApplication::translate("oneCamera", "Medium", nullptr));
        lowQualityButton->setText(QApplication::translate("oneCamera", "Low", nullptr));
    } // retranslateUi

};

namespace Ui {
    class oneCamera: public Ui_oneCamera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONECAMERA_H
