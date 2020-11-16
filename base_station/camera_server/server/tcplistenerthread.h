#ifndef TCPLISTENERTHREAD_H
#define TCPLISTENERTHREAD_H

// Networking
#include "../packetdefinitions.hpp"
#include "../socketfunctions.hpp"

#include <QThread>
#include <map>

class TcpListenerThread : public QThread
{
    Q_OBJECT
public:
    void run(void);
    void setPort(int port) {
        m_port = QString::number(port).toStdString();
    }
    void setId(int id) {
        m_id = id;
    }

public slots:
    void sendConfiguration(const QString cameraId, ConfigurationPacket confPack);
    void sendPause(const QString cameraId);
    void sendHeartbeat();

signals:
    void deviceConnected(QString cameraId, int socketFd);
    void deviceDisconnected(QString cameraId, int socketFd);

private:
    std::string m_port;
    int m_id;
    int tcpSocketFD;
    std::map<QString, int> connectedDevices;
};

#endif // TCPLISTENERTHREAD_H
