#ifndef VIDEOLISTENERTHREAD_H
#define VIDEOLISTENERTHREAD_H

#include <QThread>

// OpenCV
#include "opencv2/opencv.hpp"

class VideoListenerThread : public QThread
{
    Q_OBJECT
public:
    void run(void);
    const char* getPort() {
        return m_port.c_str();
    }
    void setPort(int port) {
        m_port = QString::number(port).toStdString();
    }
    void setId(int id) {
        m_id = id;
    }

signals:
    void frameCompleted(cv::Mat frame);
private:
    std::string m_port;
    int m_id;
};

#endif // VIDEOLISTENERTHREAD_H
