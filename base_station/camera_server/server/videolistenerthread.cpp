// Networking
#include "../packetdefinitions.hpp"
#include "../socketfunctions.hpp"

// OpenCV
#include "opencv2/opencv.hpp"

#include "videolistenerthread.h"
#include <QDebug>

void VideoListenerThread::run()
{
    int udpSock;
    int duration = 0;
    unsigned int bytesPerSecond = 0;
    int recv_bytes = 0;
    unsigned int numPacks;
    unsigned int numBytes;
    unsigned int frameBytes;
    const int buflen = 200000;
    unsigned char *buffer = new unsigned char[buflen];

    udpSock = bindUdpSocketFd(m_port.c_str());
    qDebug() << "Listening for video on UDP port " << m_port.c_str();

    while (true)
    {
//        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        frameBytes = 0;
        // the do-while below is in charge of finding a packet that is a single int
        // We then get that int, which presents the number of packets needed to get
        // the complete image.
        // If it gets data or misses data, it will continue to throw away messages
        // until it finds another int, which is the start of a new image.

        do
        {
            recv_bytes = recvfrom(udpSock, buffer, buflen, 0, nullptr, nullptr);
//            bytesPerSecond += recv_bytes;
        } while (recv_bytes > sizeof(int));

        // treat tempBuf as an int array and get the first element
        numBytes = ((int *)buffer)[0];
        numPacks = (numBytes / PACK_SIZE) + 1;

        for (int i = 0; i < numPacks + 1; i++)
        {
            recv_bytes += recvfrom(udpSock, &buffer[i * PACK_SIZE], PACK_SIZE, MSG_WAITALL, NULL, NULL);
            frameBytes += recv_bytes;
            bytesPerSecond += recv_bytes;
        }

        // display bytes recieved and reset count to 0
        // printf("bytes recieved : %i\n", frameBytes);

        std::vector<unsigned char> rawData(buffer, buffer + numBytes);
        cv::Mat frame = cv::imdecode(rawData, cv::IMREAD_COLOR);
//        if (frame.size().width == 0)
//        {
//            std::cerr << "decode failure" << std::endl;
//            continue;
//        }


        // Draws the frame on screen. Will be replaced with UI code
//        qDebug() << "frame finished";
        emit frameCompleted(frame);

//        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
//        duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
//        if (duration >= 1000)
//        {
//            // std::cout << "bytes per second: " << (double)bytesPerSecond / 1000.0 / 1000.0 << "mB/s" << std::endl;
//            duration = 0;
//            bytesPerSecond = 0;
//        }
    }

    delete[] buffer;
}
