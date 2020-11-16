#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>
#include "onecamera.h"

#include <vector>
#include "videolistenerthread.h"
#include "tcplistenerthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void buildConfiguration(const QString cameraId, int viewIndex, int quality);

    ~MainWindow();

signals:
    void configurationReady(const QString cameraId, ConfigurationPacket confPack);

public slots:
    void addDevice(QString cameraId, int fd);
    void removeDevice(QString cameraId, int fd);
    void setCamera(const QString cameraId);
    void setConfiguration(const QString configurationId);
    void createPopupWindow(int videoListenerIndex);
    void getConfiguration(int viewIndex, QString cameraId, int quality);
    void handlePause(int viewportIndex);

private:
    Ui::MainWindow *ui;
    std::vector<VideoListenerThread*> *videoListenerThreads;
    std::vector<oneCamera*> *cameras;
    TcpListenerThread *tcpListener;
};
#endif // MAINWINDOW
