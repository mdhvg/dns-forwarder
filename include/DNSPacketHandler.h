#ifndef DNSPACKETHANDLER_H
#define DNSPACKETHANDLER_H

#include <string>
#include <cstring>

class DNSPacketHandler {
public:
    DNSPacketHandler(unsigned char* packet, int packetSize);
    ~DNSPacketHandler();

    unsigned char* getPacket();
    int getPacketSize();

public:
    std::string getDomain();
    uint16_t getID();
    void setID(uint16_t id);

private:
    uint16_t domainEndOffset = 0;

private:
    template <class T>
    void setEndian(T* value) {
        if (LITTLE_ENDIAN && sizeof(T) > 1) {
            uint8_t l = 0;
            uint8_t r = sizeof(T) - 1;
            while (l < r) {
                uint8_t temp = ((unsigned char*)value)[l];
                ((unsigned char*)value)[l] = ((unsigned char*)value)[r];
                ((unsigned char*)value)[r] = temp;
                l++;
                r--;
            }
        }
    }
private:
    unsigned char* packet;
    int packetSize;
};

#endif // DNSPACKETHANDLER_H