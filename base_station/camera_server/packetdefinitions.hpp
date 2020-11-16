#ifndef PACKETDEFINITIONS_H
#define PACKETDEFINITIONS_H

// typedef uint8_t byte;
#include <vector>
#include <string>
#include <iostream>

#define PACK_SIZE 4096
#define CONN_PACK_SIZE 26

class ConfigurationPacket
{
public:
    std::string device;
    std::string targetPort;
    uint8_t fps;
    uint8_t quality;
    uint16_t resolutionX;
    uint16_t resolutionY;

    static uint8_t *serialize(ConfigurationPacket &packet, uint8_t &numPacks);
    static ConfigurationPacket deserialize(uint8_t *buffer);
};


struct ConnectionPacket
{
    char cameraId[CONN_PACK_SIZE];
};


#endif // A_H
