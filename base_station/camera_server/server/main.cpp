// Application Imports
#include "mainwindow.h"
#include <QApplication>

// Metatype imports
#include "../packetdefinitions.hpp"
#include "opencv2/opencv.hpp"

Q_DECLARE_METATYPE(cv::Mat)
Q_DECLARE_METATYPE(ConfigurationPacket)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<cv::Mat>();
    qRegisterMetaType<ConfigurationPacket>();

    MainWindow mainWindow;

    mainWindow.show();
    return a.exec();
}
