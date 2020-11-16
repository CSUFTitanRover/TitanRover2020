#include "onecamera.h"
#include "ui_onecamera.h"

#include <QPushButton>
#include <QDebug>


oneCamera::oneCamera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::oneCamera)
{
    ui->setupUi(this);

    QRadioButton* qualityLowButton = ui->lowQualityButton;
    qualityLowButton->setChecked(true);
    QRadioButton* qualityMediumButton = ui->mediumQualityButton;
    QRadioButton* qualityHighButton = ui->highQualityButton;

    QObject::connect(qualityLowButton, &QRadioButton::clicked, this, &oneCamera::qualityButtonClicked);
    QObject::connect(qualityMediumButton, &QRadioButton::clicked, this, &oneCamera::qualityButtonClicked);
    QObject::connect(qualityHighButton, &QRadioButton::clicked, this, &oneCamera::qualityButtonClicked);

    QPushButton* popupButton = ui->popNewScreenButton;
    QObject::connect(popupButton, &QPushButton::clicked, this, &oneCamera::popupButtonClicked);

    QPushButton* pauseButton = ui->pauseButton;
    QObject::connect(pauseButton, &QPushButton::clicked, this, &oneCamera::pauseButtonClicked);
}

oneCamera::~oneCamera()
{
    delete ui;
}

void oneCamera::pauseButtonClicked(){
    emit requestPause(m_currentCamera);
}

void oneCamera::isPopup() {
    delete ui->verticalLayout;
    delete ui->highQualityButton;
    delete ui->mediumQualityButton;
    delete ui->pauseButton;
    delete ui->popNewScreenButton;
    delete ui->lowQualityButton;
}

void oneCamera::popupButtonClicked() {
    emit requestPopup(m_id);
}

void oneCamera::qualityButtonClicked() {
    int quality;
    if(ui->lowQualityButton->isChecked()) {
        quality = 0;
    } else if(ui->mediumQualityButton->isChecked()) {
        quality = 1;
    } else if (ui->highQualityButton->isChecked()) {
        quality = 2;
    }

    emit qualityChanged(m_id, m_currentCamera, quality);
}

void oneCamera::drawFrame(cv::Mat frame){
//    qDebug() << frame.cols << " " << frame.rows;
    // Set the color table (used to translate colour indexes to qRgb values)
    QVector<QRgb> colorTable;
    for (int i=0; i<256; i++)
        colorTable.push_back(qRgb(i,i,i));
    // Create QImage with same dimensions as input Mat
    QImage img(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    img.setColorTable(colorTable);

    ui->cameraPic->setPixmap(
                QPixmap::fromImage(img).scaled(
                    ui->cameraPic->size(),
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation));
}
