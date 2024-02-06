#ifndef DNSPACKET_H
#define DNSPACKET_H

#include "util.h"
#include "Types.h"
#include "UString.h"

#include <vector>
#include <iostream>
#include <string>

class DNSPacket {
public:
    DNSPacket(DNS);
    DNSPacket(UString* buffer);
    ~DNSPacket() = default;

    int GetBufferSize();
    DNS GetDNS();
    UString* GetBuffer();
private:
    void loadBuffer();
    void create();

private:
    template <class T>
    inline void copyNBytesToBuffer(UString* buffer, uint16_t& currentOffset, T value) {
        memmove(&(*buffer)[currentOffset], &value, sizeof(T));
        if (LITTLE_ENDIAN) {
            if (sizeof(T) > 1) {
                uint8_t l = 0;
                uint8_t r = sizeof(T) - 1;
                while (l < r) {
                    uint8_t temp = (*buffer)[currentOffset + l];
                    (*buffer)[currentOffset + l] = (*buffer)[currentOffset + r];
                    (*buffer)[currentOffset + r] = temp;
                    l++;
                    r--;
                }
            }
        }
    }

    template <class T>
    inline void copyNBytesFromBuffer(UString* buffer, uint16_t& currentOffset, T& value) {
        unsigned char* temp = new unsigned char[sizeof(T)];
        memmove(temp, &((*buffer)[currentOffset]), sizeof(T));
        if (LITTLE_ENDIAN) {
            if (sizeof(T) > 1) {
                uint8_t l = 0;
                uint8_t r = sizeof(T) - 1;
                while (l < r) {
                    uint8_t t = temp[l];
                    temp[l] = temp[r];
                    temp[r] = t;
                    l++;
                    r--;
                }
            }
        }
        memmove(&value, temp, sizeof(T));
        delete[] temp;
        currentOffset += sizeof(T);
    }

private:
    DNS m_Dns;
    UString* m_Buffer;
    int m_BufferSize = m_Buffer->size();
};

#endif // DNSPACKET_H