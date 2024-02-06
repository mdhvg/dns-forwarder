#include "DNSPacket.h"

DNSPacket::DNSPacket(DNS dns) : m_Dns(dns) {
    create();
}

DNSPacket::DNSPacket(UString* buffer) : m_Buffer(buffer) {
    loadBuffer();
}

void DNSPacket::create() {
    uint16_t m_BufferSize = m_Dns.type == DNSPacketType::QUERY ? 12 + m_Dns.domain.size() + 1 + 4 : 12 + m_Dns.domain.size() + 1 + 4 + (m_Dns.ipAddr.size() * 16);
    m_Buffer = new UString(m_BufferSize, 0);

    uint16_t currentOffset = 0;
    copyNBytesToBuffer<uint16_t>(m_Buffer, currentOffset, m_Dns.header.id);

    m_Dns.header.id = m_Dns.type == DNSPacketType::RESPONSE ? 1 : 0;
    uint16_t flag0 = m_Dns.header.qr << 15 |
        m_Dns.header.opcode << 11 |
        m_Dns.header.authoritative_answer << 10 |
        m_Dns.header.truncated_message << 9 |
        m_Dns.header.recursion_desired << 8 |
        m_Dns.header.recursion_available << 7 |
        m_Dns.header.rescode;

    copyNBytesToBuffer<uint16_t>(m_Buffer, currentOffset, flag0);
    copyNBytesToBuffer<uint16_t>(m_Buffer, currentOffset, m_Dns.header.questions);
    copyNBytesToBuffer<uint16_t>(m_Buffer, currentOffset, m_Dns.header.answers);
    copyNBytesToBuffer<uint16_t>(m_Buffer, currentOffset, m_Dns.header.resource_entries);
    copyNBytesToBuffer<uint16_t>(m_Buffer, currentOffset, m_Dns.header.authoritative_entries);

    m_Buffer->copyAt(m_Dns.domain, currentOffset);
    currentOffset += m_Dns.domain.size() + 1;

    copyNBytesToBuffer<uint32_t>(m_Buffer, currentOffset, 0x00010001);

    if (m_Dns.type == DNSPacketType::RESPONSE) {
        for (auto& ip : m_Dns.ipAddr) {
            copyNBytesToBuffer<uint16_t>(m_Buffer, currentOffset, 0xc00c);
            copyNBytesToBuffer<uint32_t>(m_Buffer, currentOffset, 0x00010001);
            copyNBytesToBuffer<uint32_t>(m_Buffer, currentOffset, (uint32_t)ip.timeOut);
            copyNBytesToBuffer<uint16_t>(m_Buffer, currentOffset, (uint16_t)4);
            int i;
            FORLT(i, 0, 4) {
                copyNBytesToBuffer<uint8_t>(m_Buffer, currentOffset, ip.octets[i]);
            }
        }
    }
}

void DNSPacket::loadBuffer() {
    uint16_t currentOffset = 0;
    copyNBytesFromBuffer<uint16_t>(m_Buffer, currentOffset, m_Dns.header.id);

    uint16_t flags;
    copyNBytesFromBuffer<uint16_t>(m_Buffer, currentOffset, flags);
    m_Dns.header.qr = (flags & 0x8000) != 0;
    m_Dns.type = m_Dns.header.qr ? DNSPacketType::RESPONSE : DNSPacketType::QUERY;
    m_Dns.header.opcode = (flags & 0x7800) >> 11;
    m_Dns.header.authoritative_answer = (flags & 0x0400) != 0;
    m_Dns.header.truncated_message = (flags & 0x0200) != 0;
    m_Dns.header.recursion_desired = (flags & 0x0100) != 0;
    m_Dns.header.recursion_available = (flags & 0x0080) != 0;
    m_Dns.header.rescode = static_cast<ResultCode>((flags & 0x000F));

    copyNBytesFromBuffer<uint16_t>(m_Buffer, currentOffset, m_Dns.header.questions);
    copyNBytesFromBuffer<uint16_t>(m_Buffer, currentOffset, m_Dns.header.answers);
    copyNBytesFromBuffer<uint16_t>(m_Buffer, currentOffset, m_Dns.header.resource_entries);
    copyNBytesFromBuffer<uint16_t>(m_Buffer, currentOffset, m_Dns.header.authoritative_entries);

    while ((*m_Buffer)[currentOffset] != 0) {
        m_Dns.domain.push_back(static_cast<char>((*m_Buffer)[currentOffset]));
        currentOffset += 1;
    }
    currentOffset += 4;
    if (m_Dns.header.qr) {
        uint16_t pointerFlag;
        copyNBytesFromBuffer<uint16_t>(m_Buffer, currentOffset, pointerFlag);
        while (pointerFlag == 0xc00c) {
            currentOffset += 4;
            IPAddr ip;
            copyNBytesFromBuffer<uint32_t>(m_Buffer, currentOffset, ip.timeOut);
            currentOffset += 2;
            copyNBytesFromBuffer<uint8_t>(m_Buffer, currentOffset, ip.octets[0]);
            copyNBytesFromBuffer<uint8_t>(m_Buffer, currentOffset, ip.octets[1]);
            copyNBytesFromBuffer<uint8_t>(m_Buffer, currentOffset, ip.octets[2]);
            copyNBytesFromBuffer<uint8_t>(m_Buffer, currentOffset, ip.octets[3]);
            m_Dns.ipAddr.push_back(ip);
        }
    }
    m_BufferSize = currentOffset + 1;
}

int DNSPacket::GetBufferSize()
{
    return m_Buffer->size();
}

DNS DNSPacket::GetDNS() {
    return m_Dns;
}

UString* DNSPacket::GetBuffer() {
    return m_Buffer;
}