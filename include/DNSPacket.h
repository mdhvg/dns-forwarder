#ifndef DNSPACKET_H
#define DNSPACKET_H

#include "util.h"

#include <vector>
#include <iostream>
#include <string>

enum ResultCode {
    NOERROR,
    FORMERR,
    SERVFAIL,
    NXDOMAIN,
    NOTIMP,
    REFUSED
};

enum DNSPacketType {
    QUERY, RESPONSE
};

struct ResponseIPAddress {
    // TODO: Change this to sockaddr_in m_Type
    uint8_t octets[4] = { 0, 0, 0, 0 };
    uint32_t timeOut = 0;
};

struct DnsHeader {
    uint16_t id; // 16 bits

    bool qr;                   // 1 bit
    uint8_t opcode;                 // 4 bits
    bool authoritative_answer; // 1 bit
    bool truncated_message;    // 1 bit
    bool recursion_desired;    // 1 bit
    bool recursion_available; // 1 bit
    // Z 3 bits reserved
    ResultCode rescode;       // 4 bits

    uint16_t questions;             // 16 bits
    uint16_t answers;               // 16 bits
    uint16_t resource_entries;      // 16 bits
    uint16_t authoritative_entries; // 16 bits
};

class DNSPacket {
public:
    DNSPacket() = default;
    DNSPacket(std::string buffer);
    DNSPacket(uint16_t id, std::string domain, std::vector<ResponseIPAddress> resolvedAddresses, DNSPacketType type);
    ~DNSPacket() = default;


    void SetResponseIPAddress(std::vector<ResponseIPAddress>& addresses);
    std::vector<ResponseIPAddress> GetResponseIPAddress();

    std::string GetDomain();
    std::vector<ResponseIPAddress> GetResolvedAddresses();
    DNSPacketType GetType();
    std::string& GetBuffer();
    void SetBuffer(std::string buffer);
    int GetBufferSize();
    uint16_t GetID();
    void SetID(uint16_t id);

public:
    DnsHeader m_Header;

private:
    void Load();
    void Create();

private:
    inline bool checkNextByte(std::string buffer, uint16_t& currentOffset, uint8_t size, int pattern) {
        int next = 0;
        int i;
        FOREQ(i, 1, size) {
            next <<= 8;
            next |= buffer[currentOffset + i];
        }
        currentOffset += size;
        return next == pattern;
    }

    template <class T>
    inline T readNBytesAs(std::string buffer, uint16_t& currentOffset) {
        T result = 0;
        int i;
        FOREQ(i, 1, sizeof(T)) {
            result <<= 8;
            result |= buffer[currentOffset + i];
        }
        currentOffset += sizeof(T);
        return result;
    }

    template <class T>
    inline void writeNBytesAs(std::string buffer, uint16_t& currentOffset, T value) {
        int i;
        FORLT(i, 0, sizeof(T)) {
            buffer[currentOffset] = (value >> ((sizeof(T) - i - 1) * 8));
            currentOffset += 1;
        }
    }

    template <class T>
    inline void appendNBytesAs(std::string& buffer, T value) {
        int i;
        FORLT(i, 0, sizeof(T)) {
            buffer.push_back((value >> ((sizeof(T) - i - 1) * 8)));
        }
    }

private:
    std::string m_Domain = "";
    std::vector<ResponseIPAddress> m_ResolvedAddresses;
    DNSPacketType m_Type;
    std::string m_Buffer;
    int m_BufferSize = m_Buffer.size();
};

#endif // DNSPACKET_H