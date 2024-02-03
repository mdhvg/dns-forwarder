#include "DNSPacket.h"

DNSPacket::DNSPacket(std::string buffer) : m_Buffer(buffer) {
    Load();
}

DNSPacket::DNSPacket(uint16_t id,
    std::string domain,
    std::vector<ResponseIPAddress> resolvedAddresses = {},
    DNSPacketType type = DNSPacketType::QUERY) : m_Domain(domain),
    m_ResolvedAddresses(resolvedAddresses),
    m_Type(type) {
    m_Header.id = id;
    Create();
}

void DNSPacket::Load() {
    m_Header.id = ((uint16_t)(m_Buffer[0] << 8)) | ((uint16_t)m_Buffer[1]);
    m_Header.qr = (m_Buffer[2] & 0x80);
    m_Header.opcode = (m_Buffer[2] & 0x78) >> 3;
    m_Header.authoritative_answer = (m_Buffer[2] & 0x04) != 0;
    m_Header.truncated_message = (m_Buffer[2] & 0x02) != 0;
    m_Header.recursion_desired = (m_Buffer[2] & 0x01) != 0;
    m_Header.recursion_available = (m_Buffer[3] & 0x80) != 0;
    m_Header.rescode = static_cast<ResultCode>((m_Buffer[3] & 0x78) >> 3);

    m_Header.questions = (m_Buffer[4] << 8) | m_Buffer[5];
    m_Header.answers = (m_Buffer[6] << 8) | m_Buffer[7];
    m_Header.resource_entries = (m_Buffer[8] << 8) | m_Buffer[9];
    m_Header.authoritative_entries = (m_Buffer[10] << 8) | m_Buffer[11];

    uint16_t currentByte = 12;
    m_Domain.clear();
    while (m_Buffer[currentByte] != 0) {
        m_Domain.push_back(static_cast<char>(m_Buffer[currentByte]));
        currentByte += 1;
    }

    this->m_Type = m_Header.qr ? DNSPacketType::RESPONSE : DNSPacketType::QUERY;

    // A response packet
    if (m_Header.qr) {
        NASSERT(checkNextByte(m_Buffer, currentByte, 4, 0x00010001), 0, "Packet smaller than expected");

        uint16_t pointerFlag;
        while (pointerFlag = readNBytesAs<uint16_t>(m_Buffer, currentByte), pointerFlag == 0xc00c) {
            NASSERT(checkNextByte(m_Buffer, currentByte, 4, 0x00010001), 0, "Packet smaller than expected");

            ResponseIPAddress ip;

            uint32_t timeout = readNBytesAs<uint32_t>(m_Buffer, currentByte);
            ip.timeOut = timeout;

            uint16_t ip_size = readNBytesAs<uint16_t>(m_Buffer, currentByte);
            int i;
            FORLT(i, 0, ip_size) {
                ip.octets[i] = m_Buffer[currentByte + i];
            }
            currentByte += ip_size;

            m_ResolvedAddresses.push_back(ip);
        }
    }
}

void DNSPacket::Create()
{
    m_Buffer.clear();

    // appendNBytesAs<uint16_t>(m_Buffer, m_Header.id);

    m_Header.qr = m_Type == DNSPacketType::RESPONSE ? 1 : 0;

    uint32_t flags0 = m_Header.id << 16 |
        (m_Header.qr) << 15 |
        1 << 8;
    uint32_t flags1 = m_ResolvedAddresses.size();
    uint32_t flags2 = 0;

    appendNBytesAs<uint32_t>(m_Buffer, flags0);
    appendNBytesAs<uint32_t>(m_Buffer, flags1);
    appendNBytesAs<uint32_t>(m_Buffer, flags2);

    m_Buffer.append(m_Domain);
    m_Buffer.push_back(0);

    appendNBytesAs<uint32_t>(m_Buffer, 0x00010001);

    for (auto& ipAddr : m_ResolvedAddresses) {
        appendNBytesAs<uint16_t>(m_Buffer, 0xc00c);
        appendNBytesAs<uint32_t>(m_Buffer, 0x00010001);
        appendNBytesAs<uint32_t>(m_Buffer, ipAddr.timeOut);
        appendNBytesAs<uint16_t>(m_Buffer, 4);
        int i;
        FORLT(i, 0, 4) {
            m_Buffer.push_back(ipAddr.octets[i]);
        }

    }
}

// void DNSPacket::PackIntoBuffer()
// {
//     char* buffer = new char[512] {0};
//     uint16_t currentOffset = 0;
//     writeNBytesAs<uint16_t>(buffer, currentOffset, m_Header.id);
//     uint8_t flags = (m_Header.qr != 0) << 7 |
//         m_Header.opcode << 3 |
//         (m_Header.authoritative_answer != 0) << 2 |
//         (m_Header.truncated_message != 0) << 1 |
//         (m_Header.recursion_desired != 0);
//     writeNBytesAs<uint8_t>(buffer, currentOffset, flags);
//     flags = (m_Header.recursion_available != 0) << 7 |
//         m_Header.rescode;
//     writeNBytesAs<uint8_t>(buffer, currentOffset, flags);
//     writeNBytesAs<uint16_t>(buffer, currentOffset, m_Header.questions);
//     writeNBytesAs<uint16_t>(buffer, currentOffset, m_Header.answers);
//     writeNBytesAs<uint16_t>(buffer, currentOffset, m_Header.resource_entries);
//     writeNBytesAs<uint16_t>(buffer, currentOffset, m_Header.authoritative_entries);

//     NASSERT(m_Domain.size(), 0, "DNSPacket: Domain name is empty");
//     int i;
//     FORLT(i, 0, m_Domain.size()) {
//         writeNBytesAs<uint8_t>(buffer, currentOffset, m_Domain[i]);
//     }
//     currentOffset += 1;
//     writeNBytesAs<uint32_t>(buffer, currentOffset, 0x00010001);

//     if (m_Type == DNSPacketType::RESPONSE) {
//         NASSERT(m_ResolvedAddresses.size(), 0, "DNSPacket: No resolved addresses");
//         for (auto& ip : m_ResolvedAddresses) {
//             int i;
//             writeNBytesAs<uint16_t>(buffer, currentOffset, 0xc00c);
//             writeNBytesAs<uint32_t>(buffer, currentOffset, 0x00010001);
//             writeNBytesAs<uint32_t>(buffer, currentOffset, ip.timeOut);
//             writeNBytesAs<uint16_t>(buffer, currentOffset, 4);
//             FORLT(i, 0, 4) {
//                 writeNBytesAs<uint8_t>(buffer, currentOffset, ip.octets[i]);
//             }
//         }
//     }
//     m_Buffer = buffer;
// }

void DNSPacket::SetResponseIPAddress(std::vector<ResponseIPAddress>& addresses)
{
    m_Buffer.clear();
    m_Type = DNSPacketType::RESPONSE;
    m_ResolvedAddresses = addresses;
    char* buffer = new char[512] {0};
    uint16_t currentOffset = 0;
    writeNBytesAs<uint16_t>(buffer, currentOffset, m_Header.id);
    uint8_t flags = (m_Header.qr != 0) << 7 |
        m_Header.opcode << 3 |
        (m_Header.authoritative_answer != 0) << 2 |
        (m_Header.truncated_message != 0) << 1 |
        (m_Header.recursion_desired != 0);
    writeNBytesAs<uint8_t>(buffer, currentOffset, flags);
    flags = (m_Header.recursion_available != 0) << 7 |
        m_Header.rescode;
    writeNBytesAs<uint8_t>(buffer, currentOffset, flags);
    writeNBytesAs<uint16_t>(buffer, currentOffset, m_Header.questions);
    writeNBytesAs<uint16_t>(buffer, currentOffset, m_Header.answers);
    writeNBytesAs<uint16_t>(buffer, currentOffset, m_Header.resource_entries);
    writeNBytesAs<uint16_t>(buffer, currentOffset, m_Header.authoritative_entries);

    NASSERT(m_Domain.size(), 0, "DNSPacket: Domain name is empty");
    int i;
    FORLT(i, 0, m_Domain.size()) {
        writeNBytesAs<uint8_t>(buffer, currentOffset, m_Domain[i]);
    }
    currentOffset += 1;
    writeNBytesAs<uint32_t>(buffer, currentOffset, 0x00010001);

    if (m_Type == DNSPacketType::RESPONSE) {
        NASSERT(m_ResolvedAddresses.size(), 0, "DNSPacket: No resolved addresses");
        for (auto& ip : m_ResolvedAddresses) {
            int i;
            writeNBytesAs<uint16_t>(buffer, currentOffset, 0xc00c);
            writeNBytesAs<uint32_t>(buffer, currentOffset, 0x00010001);
            writeNBytesAs<uint32_t>(buffer, currentOffset, ip.timeOut);
            writeNBytesAs<uint16_t>(buffer, currentOffset, 4);
            FORLT(i, 0, 4) {
                writeNBytesAs<uint8_t>(buffer, currentOffset, ip.octets[i]);
            }
        }
    }
    m_Buffer = buffer;
}

std::vector<ResponseIPAddress> DNSPacket::GetResponseIPAddress()
{
    return m_ResolvedAddresses;
}

std::string DNSPacket::GetDomain() {
    return m_Domain;
}

std::vector<ResponseIPAddress> DNSPacket::GetResolvedAddresses()
{
    return m_ResolvedAddresses;
}

DNSPacketType DNSPacket::GetType()
{
    return m_Type;
}

void DNSPacket::SetBuffer(std::string buffer)
{
    m_Buffer = buffer;
    m_Header.qr = (m_Buffer[2] & 0x80);
    m_Header.opcode = (m_Buffer[2] & 0x78) >> 3;
    m_Header.authoritative_answer = (m_Buffer[2] & 0x04) != 0;
    m_Header.truncated_message = (m_Buffer[2] & 0x02) != 0;
    m_Header.recursion_desired = (m_Buffer[2] & 0x01) != 0;
    m_Header.recursion_available = (m_Buffer[3] & 0x80) != 0;
    m_Header.rescode = static_cast<ResultCode>((m_Buffer[3] & 0x78) >> 3);

    m_Header.questions = (m_Buffer[4] << 8) | m_Buffer[5];
    m_Header.answers = (m_Buffer[6] << 8) | m_Buffer[7];
    m_Header.resource_entries = (m_Buffer[8] << 8) | m_Buffer[9];
    m_Header.authoritative_entries = (m_Buffer[10] << 8) | m_Buffer[11];

    uint16_t currentByte = 12;
    m_Domain.clear();
    while (m_Buffer[currentByte] != 0) {
        m_Domain.push_back(static_cast<char>(m_Buffer[currentByte]));
        currentByte += 1;
    }

    this->m_Type = m_Header.qr ? DNSPacketType::RESPONSE : DNSPacketType::QUERY;

    if (m_Header.qr) {
        NASSERT(checkNextByte(m_Buffer, currentByte, 4, 0x00010001), 0, "Packet smaller than expected");

        uint16_t pointerFlag;
        while (pointerFlag = readNBytesAs<uint16_t>(m_Buffer, currentByte), pointerFlag == 0xc00c) {
            NASSERT(checkNextByte(m_Buffer, currentByte, 4, 0x00010001), 0, "Packet smaller than expected");

            ResponseIPAddress ip;

            uint32_t timeout = readNBytesAs<uint32_t>(m_Buffer, currentByte);
            ip.timeOut = timeout;

            uint16_t ip_size = readNBytesAs<uint16_t>(m_Buffer, currentByte);
            int i;
            FORLT(i, 0, ip_size) {
                ip.octets[i] = m_Buffer[currentByte + i];
            }
            currentByte += ip_size;

            m_ResolvedAddresses.push_back(ip);
        }
    }
}

std::string& DNSPacket::GetBuffer()
{
    return m_Buffer;
}

int DNSPacket::GetBufferSize()
{
    return 512;
}

uint16_t DNSPacket::GetID()
{
    return m_Header.id;
}

void DNSPacket::SetID(uint16_t id)
{
    m_Header.id = id;
    uint16_t currentByte = 0;
    writeNBytesAs<uint16_t>(m_Buffer, currentByte, m_Header.id);
}