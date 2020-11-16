/*
 * g++ berk_server.cpp -o berkserv -lpthread `pkg-config --cflags --libs opencv`
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h> // for memset
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
// #include <signal.h>

// Data structures
#include <vector>
#include <set>
#include <map>

// Thread management
#include <thread>
#include <chrono>

// OpenCV
#include "opencv2/opencv.hpp"

// JSON
#include "json.hpp"

// Networking
#include "../packetdefinitions.hpp"
#include "../socketfunctions.hpp"

std::set<int> socketFds;
std::map<int, std::thread> socketToThreadMap;

std::map<std::string, int> idToSocketMap;
std::vector<std::thread> videoStreamListeners(4);

nlohmann::json configJSON;

void tcpConnectionListener(char const *port);
void videoStreamListener(std::string port, int id);

void sendConfiguration(int socketFd, uint8_t *configurationBuffer, uint16_t numPacks);
void sendHeartbeat();

int main(void)
{
    // Get handle for config file
    std::ifstream i("config.json");
    // Read data into json object
    i >> configJSON;
    // close file stream
    i.close();

    for (int i = 0, port = 23456; i < videoStreamListeners.size(); port++, i++)
    {
        videoStreamListeners[i] = std::thread(videoStreamListener, std::to_string(port), i);
    }

    std::thread tcpConnectionListenerThread(tcpConnectionListener,
                                            configJSON["connPort"].get<std::string>().c_str());
    tcpConnectionListenerThread.join();

    return 0;
}

void sendConfiguration(int socketFd, uint8_t *configurationBuffer, uint8_t numPacks)
{
    int result;
    std::cout << "sending configuration..." << std::endl;
    std::cout << sizeof(numPacks) << std::endl;
    result = send(socketFd, &numPacks, sizeof(numPacks), MSG_NOSIGNAL);
    if (result == -1)
    {
        perror("send");
    }

    printf("%hhu\n", numPacks);
    result = send(socketFd, configurationBuffer, numPacks, MSG_NOSIGNAL);
    if (result == -1)
    {
        perror("send");
    }
}

void tcpConnectionListener(char const *port)
{
    int sockfd, new_fd; // listen on sock_fd, new connection on new_fd
    int recv_bytes;
    char s[INET6_ADDRSTRLEN];
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;

    ConnectionPacket connPack;

    sockfd = bindTcpSocketFd(port);
    printf("server: waiting for connections...\n");

    for (;;)
    { // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);

        // Verify their information in the config file
        recv_bytes = recv(new_fd, &connPack, CONN_PACK_SIZE, 0);

        if (recv_bytes == CONN_PACK_SIZE)
        {
            std::cout << connPack.cameraId << " has connected." << std::endl;
            ConfigurationPacket defaultConfigPacket = {
                configJSON["devices"][connPack.cameraId]["device"].get<std::string>(),
                configJSON["devices"][connPack.cameraId]["targetPort"].get<std::string>(),
                configJSON["devices"][connPack.cameraId]["fps"].get<uint8_t>(),
                configJSON["devices"][connPack.cameraId]["quality"].get<uint8_t>(),
                configJSON["devices"][connPack.cameraId]["resolutionX"].get<uint16_t>(),
                configJSON["devices"][connPack.cameraId]["resolutionY"].get<uint16_t>(),
            };

            idToSocketMap[std::string(connPack.cameraId)] = new_fd;

            uint8_t numPacks;
            uint8_t *serializedConfigPack = ConfigurationPacket::serialize(defaultConfigPacket, numPacks);

            sendConfiguration(new_fd, serializedConfigPack, numPacks);

            delete serializedConfigPack;
        }
    }
}

void sendHeartbeat()
{
    for (;;)
    {
        if (!idToSocketMap.empty())
        {
            for (auto it = std::begin(idToSocketMap); it != std::end(idToSocketMap); ++it)
            {
                printf("Sending messages to %s.\n", it->first.c_str());
                int result = send(it->second, "Hello, world!", 13, MSG_NOSIGNAL); //MSG_NOSIGNAL
                if (result == -1 || result == 0)
                {
                    perror("send");
                    printf("Camera %s has disconnected", it->first.c_str());
                    idToSocketMap.erase(it->first);
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void videoStreamListener(std::string port, int id)
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

    udpSock = bindUdpSocketFd(port.c_str());
    std::cout << "Listening for video on UDP port " << port << std::endl;

    while (true)
    {
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        frameBytes = 0;
        // the do-while below is in charge of finding a packet that is a single int
        // We then get that int, which presents the number of packets needed to get
        // the complete image.
        // If it gets data or misses data, it will continue to throw away messages
        // until it finds another int, which is the start of a new image.

        do
        {
            recv_bytes = recvfrom(udpSock, buffer, buflen, 0, NULL, NULL);
            bytesPerSecond += recv_bytes;
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
        if (frame.size().width == 0)
        {
            std::cerr << "decode failure" << std::endl;
            continue;
        }

        // Draws the frame on screen. Will be replaced with UI code
        cv::imshow("recv", frame);
        cv::waitKey(1);

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        if (duration >= 1000)
        {
            // std::cout << "bytes per second: " << (double)bytesPerSecond / 1000.0 / 1000.0 << "mB/s" << std::endl;
            duration = 0;
            bytesPerSecond = 0;
        }
    }

    delete buffer;
}