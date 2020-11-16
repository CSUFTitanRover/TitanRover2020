/*
 * client.c -- a stream socket client demo
 * g++ berk_client.cpp ../packetdefinitions.cpp ../socketfunctions.cpp -o berkcli -lpthread `pkg-config --cflags --libs opencv`
 */

#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <random>
#include <cmath>

#include "opencv2/opencv.hpp"
#include "../packetdefinitions.hpp"
#include "../socketfunctions.hpp"

#define MAXIMUM_BACKOFF 32000

// function declarations
void tcpListener(int tcpSockFd);
void videoStreamWriter();

// global variables
ConfigurationPacket currentConfig;
char *g_hostPort;
char *g_hostIp;

std::mutex m_connected;
std::condition_variable condVar_connected;
bool g_connected = false;

std::mutex m_paused;
std::condition_variable condVar_paused;
bool g_paused = false;

// vars for thread synchronization
std::mutex m_configuration;
std::condition_variable condVar_configuration;
bool haveNewConfig = false;

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        fprintf(stderr, "usage: ./client cameraId hostname port\n");
        exit(1);
    }

    g_hostIp = argv[2];

    //setup random number generator for exponential backoff
    std::random_device rd;
    std::ranlux24 rl24(rd());
    std::uniform_int_distribution<int> dist(1, 1000);
    int tcpSockFd;
    int connectionAttemptCount = 0;
    int waitTime = 0;

    // std::this_thread::sleep_for(std::chrono::seconds(1));

    ConnectionPacket connPack;
    memset(connPack.cameraId, '\0', sizeof(connPack.cameraId));
    strcpy(connPack.cameraId, argv[1]);

    for (;;)
    {
        if (-1 == (tcpSockFd = connectTcpSocketFd(argv[2], argv[3])))
        {
            std::cout << "TCP SOCKET FD" << tcpSockFd << std::endl;
            if (waitTime > MAXIMUM_BACKOFF)
            {
                waitTime = MAXIMUM_BACKOFF + dist(rl24);
            }
            else
            {
                waitTime = static_cast<int>(std::pow(2, connectionAttemptCount)) * 1000 + dist(rl24);
            }

            std::cout << "waiting before retry... " << waitTime << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
            ++connectionAttemptCount;
        }
        else
        {
            std::cout << "TCP SOCKET FD" << tcpSockFd << std::endl;
            connectionAttemptCount = 0;
            g_connected = true;

            // start configuration listener
            std::thread(tcpListener, tcpSockFd).detach();

            // Give thread time to start, then send Id
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            // Send user ID
            send(tcpSockFd, &connPack, sizeof(connPack), 0);

            //
            // block until disconnected
            //
            std::cout << "g_connected " << g_connected << std::endl;
            {
                // Wait until we lose our connection
                std::unique_lock<std::mutex> lk(m_connected);
                condVar_connected.wait(lk, [] { return !g_connected; });
            }
            std::cout << "==== DISCONNECTED ====" << std::endl;
        }
    }
}

void tcpListener(int tcpSockFd)
{

    int recv_bytes;
    int tempIndex = 0;
    int messageIndex = 0;
    uint8_t remainingBytes = 0;
    int bytesToCopy = 0;
    const int buflen = 2000000;
    uint8_t buf[buflen];
    uint8_t tempBuf[buflen];
    bool messageComplete = false;

    for (;;) // infinite loop
    {
        std::cout << "waiting for new configuration" << std::endl;
        // get the incoming configuration data
        while (!messageComplete)
        {
            // get the incoming bytes
            std::cout << "tempIndex = " << tempIndex << std::endl;
            recv_bytes = recv(tcpSockFd, &tempBuf[tempIndex], PACK_SIZE, 0);
            if (recv_bytes == -1 || recv_bytes == 0)
            {
                //
                // after disconnecting, change ready to false
                //
                std::cout << "DISCONNECTING..." << std::endl;
                {
                    std::lock_guard<std::mutex> lk(m_connected);
                    g_connected = false;
                }

                condVar_connected.notify_all();

                std::cout << "exiting tcp listener" << std::endl;
                close(tcpSockFd);
                return;
            }

            if (tempBuf[tempIndex] == '%' && tempBuf[tempIndex + 1] == '%')
            {
                tempIndex = tempIndex + 2;

                {
                    std::lock_guard<std::mutex> lk(m_paused);
                    g_paused = !g_paused;
                }

                condVar_paused.notify_all();

                std::cout << "toggling g_paused: " << g_paused << std::endl;
                continue;
            }

            std::cout << "received " << recv_bytes << " bytes" << std::endl;

            // If starting a new message
            if (remainingBytes == 0)
            {
                // move the message indexer to the start of message
                messageIndex = 0;

                // get the message length and reduce receieved bytes by 1
                remainingBytes = tempBuf[tempIndex];

                recv_bytes--;

                // increment the tempIndex to the next byte
                tempIndex++;
            }
            printf("%hhu\n", remainingBytes);

            // if remainingBytes <= recv_bytes, we have
            // two messages smooshed together.
            if (remainingBytes <= recv_bytes)
            {
                // get the rest of the message
                bytesToCopy = remainingBytes;
            }
            // if recv_bytes is less than remainingBytes
            // the message is split
            else if (recv_bytes < remainingBytes)
            {
                // copy the rest of the temp buffer over
                bytesToCopy = recv_bytes;
            }

            // copy the temp buffer into the message buffer
            memcpy(&buf[messageIndex], &tempBuf[tempIndex], bytesToCopy);
            // update index into message buffer
            messageIndex = messageIndex + bytesToCopy;
            // slide the data from the middle of the temp buffer back to the front
            memcpy(tempBuf, &tempBuf[tempIndex], recv_bytes - bytesToCopy);
            tempIndex = recv_bytes - bytesToCopy;
            remainingBytes = remainingBytes - bytesToCopy;

            if (remainingBytes == 0)
            {
                messageComplete = true;
            }
        }
        // tempIndex = 0;

        // make sure we are in the correct state to accept a new configuration
        if (haveNewConfig == false)
        {
            messageComplete =  false;
            haveNewConfig = true;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));

            currentConfig = ConfigurationPacket::deserialize(buf);
            std::cout << "deserialize " << currentConfig.targetPort << std::endl;
            printf("new configuration: device: %s port: %s FPS:%hhu QUAL:%hhu X:%hu Y:%hu\n",
                   currentConfig.device.c_str(),
                   currentConfig.targetPort.c_str(),
                   currentConfig.fps,
                   currentConfig.quality,
                   currentConfig.resolutionX,
                   currentConfig.resolutionY);

            std::thread(videoStreamWriter).detach();
        }
    }
}

void videoStreamWriter()
{
    cv::VideoCapture vidCap;
    cv::Mat frame;
    std::vector<int> compression_params;
    std::vector<uchar> encoded;

    unsigned int numPacks;
    unsigned int numBytes;
    int bytesPerFrame;

    int udpSockFd = connectUdpSocketFd(g_hostIp, currentConfig.targetPort.c_str());

    std::cout << "begin streaming" << std::endl;

    for (;;)
    {

        if (std::isdigit(currentConfig.device[0]))
        {
            vidCap.open(currentConfig.device[0] - '0');
        }
        else
        {
            vidCap.open(currentConfig.device);
        }

        if (!vidCap.isOpened())
        {
            std::cout << "failed to open device" << std::endl;
            exit(EXIT_FAILURE);
        }

        vidCap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));

        vidCap.set(cv::CAP_PROP_FRAME_WIDTH, currentConfig.resolutionX);
        vidCap.set(cv::CAP_PROP_FRAME_HEIGHT, currentConfig.resolutionY);

        compression_params.clear();
        compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
        compression_params.push_back(currentConfig.quality);

        // reset haveNewConfig to false
        haveNewConfig = false;

        // main loop for broadcasting frames
        for (;;)
        {
            {
                // Wait until we lose our connection
                std::unique_lock<std::mutex> lk(m_paused);
                condVar_paused.wait(lk, [] { return !g_paused; });
            }

            bytesPerFrame = 0;
            // std::cout << "streamingloop" << std::endl;
            // get a video frame from the camera
            vidCap >> frame;

            // if it's empty go back to the start of the loop
            if (frame.empty())
                continue;

            // change formatting from BRG to RGB when opening images outside of openCV
            cv::cvtColor(frame, frame, CV_BGR2RGB);

            // use opencv to encode and compress the frame as a jpg
            cv::imencode(".jpg", frame, encoded, compression_params);

            // get the number of packets that need to be sent of the line
            numBytes = encoded.size();
            numPacks = (numBytes / PACK_SIZE) + 1;

            // send initial int that says how many more packets need to be read
            send(udpSockFd, &numBytes, sizeof(numBytes), MSG_NOSIGNAL);
            // udpSocket.send_to(asio::buffer(&numBytes, sizeof(numBytes)), remote_endpoint);

            for (int i = 0; i < numPacks; i++)
            {
                // bytesPerFrame += udpSocket.send_to(asio::buffer(&encoded[i * PACK_SIZE], PACK_SIZE), remote_endpoint);
                bytesPerFrame = send(udpSockFd, &encoded[i * PACK_SIZE], PACK_SIZE, MSG_NOSIGNAL);
            }

            // display bytes recieved and reset count to 0
            // printf("bytes sent : %i\n", bytesPerFrame);

            // at the end...
            if (haveNewConfig)
            {
                std::cout << "new config available" << std::endl;
                break;
            }

            if (!g_connected || haveNewConfig)
            {
                close(udpSockFd);
                vidCap.release();
                break;
            }

            // sleep for an appropriate amount of time to send out the desired FPS
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / currentConfig.fps));
        }

        if (!g_connected || haveNewConfig)
        {
            break;
        }
    }
    std::cout << "stopping stream" << std::endl;
}