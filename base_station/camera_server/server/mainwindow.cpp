#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"
#include "tcplistenerthread.h"

#include <QDebug>

#include <vector>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPushButton>
#include "videolistenerthread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tcpListener = new TcpListenerThread();
    tcpListener->setPort(12345);
    tcpListener->setId(1);
    tcpListener->start();

    QObject::connect(tcpListener, &TcpListenerThread::deviceConnected, this, &MainWindow::addDevice);
    QObject::connect(tcpListener, &TcpListenerThread::deviceDisconnected, this, &MainWindow::removeDevice);

    videoListenerThreads = new std::vector<VideoListenerThread*>();
    cameras = new std::vector<oneCamera*>{
            ui->cameraOne,
            ui->cameraTwo,
            ui->cameraThree,
            ui->cameraFour
    };

    for(int i = 0; i < 4; i++) {
        VideoListenerThread *videoListener = new VideoListenerThread();
        videoListener->setPort(23456+i);
        videoListener->setId(i);
        videoListener->start();
        videoListenerThreads->push_back(videoListener);
        cameras->at(i)->setViewIndex(i);
        QObject::connect(cameras->at(i), &oneCamera::requestPopup, this, &MainWindow::createPopupWindow);
        QObject::connect(cameras->at(i), &oneCamera::qualityChanged, this, &MainWindow::getConfiguration);
        QObject::connect(cameras->at(i), &oneCamera::requestPause, tcpListener, &TcpListenerThread::sendPause);
        QObject::connect(videoListener, &VideoListenerThread::frameCompleted, cameras->at(i), &oneCamera::drawFrame);
    }

    QComboBox* singleCameraComboBox = ui->singleCameraCB;
    QComboBox* configurationComboBox = ui->configurationCB;

    QStandardItemModel* model = dynamic_cast<QStandardItemModel*>( singleCameraComboBox->model() );
    QStandardItem* item = model->item(0, 0);
    item->setEnabled(false);

    model = dynamic_cast<QStandardItemModel*>( configurationComboBox->model() );
    item = model->item(0, 0);
    item->setEnabled(false);

    // Add configurations to combobox
    QJsonObject configurationList = global::configObject["configurations"].toObject();
    configurationComboBox->addItems(configurationList.keys());

    QObject::connect(singleCameraComboBox, QOverload<const QString&>::of(&QComboBox::activated), this, &MainWindow::setCamera);
    QObject::connect(configurationComboBox, QOverload<const QString&>::of(&QComboBox::activated), this, &MainWindow::setConfiguration);

    QObject::connect(this, &MainWindow::configurationReady, tcpListener, &TcpListenerThread::sendConfiguration);
}

void MainWindow::handlePause(int viewportIndex) {

}

void MainWindow::getConfiguration(int viewportIndex, QString cameraId, int quality) {
    buildConfiguration(cameraId, viewportIndex, quality);
}

void MainWindow::createPopupWindow(int viewportIndex) {
    oneCamera* popup = new oneCamera();
    popup->isPopup();
    QObject::connect(videoListenerThreads->at(viewportIndex), &VideoListenerThread::frameCompleted, popup, &oneCamera::drawFrame);
    popup->show();
}

void MainWindow::setConfiguration(const QString configurationId) {
    QJsonObject configurationList = global::configObject["configurations"].toObject();
    QJsonArray cameraList = configurationList[configurationId].toArray();

    for(int i = 0; i < cameraList.size(); i++) {
        buildConfiguration(cameraList[i].toString(), i, 0);
    }
}

void MainWindow::setCamera(const QString cameraId) {
    buildConfiguration(cameraId, 0, 0);
}

void MainWindow::buildConfiguration(const QString cameraId, int viewportIndex, int quality) {
    cameras->at(viewportIndex)->setCameraId(cameraId);

    QJsonObject deviceJSON = global::configObject["devices"]
            .toObject()[cameraId]
            .toObject();

    QJsonObject deviceQuality = deviceJSON["quality"]
            .toArray()[quality]
            .toObject();

    qDebug() << deviceQuality["fps"];

    ConfigurationPacket confPack = {
        deviceJSON["device"].toString().toStdString(),
        QString(videoListenerThreads->at(viewportIndex)->getPort()).toStdString(),
        static_cast<u_int8_t>(deviceQuality["fps"].toInt()),
        static_cast<u_int8_t>(deviceQuality["jpgQuality"].toInt()),
        static_cast<u_int16_t>(deviceQuality["resolutionX"].toInt()),
        static_cast<u_int16_t>(deviceQuality["resolutionY"].toInt()),
    };
    qDebug() << confPack.fps;

    emit configurationReady(cameraId, confPack);
}

void MainWindow::addDevice(QString cameraId, int fd) {
    // Only add to the list if it doesn't already exist
    // Might occur on quick reconnects
    if(this->ui->singleCameraCB->findText(cameraId) == -1) {
        this->ui->singleCameraCB->addItem(cameraId);
    }
}

void MainWindow::removeDevice(QString cameraId, int fd) {
    this->ui->singleCameraCB->removeItem(
                this->ui->singleCameraCB->findText(cameraId)
                );
}

MainWindow::~MainWindow()
{
    delete ui;
}
