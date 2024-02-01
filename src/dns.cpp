#include "dns.h"

DNSParser::DNSParser(const char* buffer) {
    Parse(buffer);
}
DNSParser::~DNSParser() = default;

void DNSParser::Parse(const char* buffer) {
    header.id = (buffer[0] << 8) | buffer[1];
    header.qr = (buffer[2] & 0x80) != 0;
    header.opcode = (buffer[2] & 0x78) >> 3;
    header.authoritative_answer = (buffer[2] & 0x04) != 0;
    header.truncated_message = (buffer[2] & 0x02) != 0;
    header.recursion_desired = (buffer[2] & 0x01) != 0;
    header.recursion_available = (buffer[3] & 0x80) != 0;
    header.rescode = static_cast<ResultCode>((buffer[3] & 0x78) >> 3);

    header.questions = (buffer[4] << 8) | buffer[5];
    header.answers = (buffer[6] << 8) | buffer[7];
    header.resource_entries = (buffer[8] << 8) | buffer[9];
    header.authoritative_entries = (buffer[10] << 8) | buffer[11];

    domain.labels.clear();
    uint8_t currentByte = 12;
    while (buffer[currentByte] != 0) {
        int labelLength = buffer[currentByte];
        std::string label = "";
        for (int i = 0; i < labelLength; i++) {
            label += buffer[currentByte + i + 1];
        }
        domain.labels.push_back(label);
        currentByte += labelLength + 1;
    }

    // A response packet
    if (header.qr) {
        NASSERT(checkNextByte(buffer, currentByte, 4, 0x00010001), 0, "Packet smaller than expected");

        uint16_t pointerFlag;
        while (pointerFlag = read_nBytes_As<uint16_t>(buffer, currentByte), pointerFlag == 0xc00c) {
            NASSERT(checkNextByte(buffer, currentByte, 4, 0x00010001), 0, "Packet smaller than expected");

            ip_addr ip;

            int timeout = read_nBytes_As<int>(buffer, currentByte);
            ip.timeOut = timeout;

            uint16_t ip_size = read_nBytes_As<uint16_t>(buffer, currentByte);
            int i;
            FORLT(i, 0, ip_size) {
                ip.octets[i] = buffer[currentByte + i];
            }
            currentByte += ip_size;

            resolvedAddresses.push_back(ip);
        }
    }
}

DnsHeader DNSParser::GetHeader() {
    return header;
}

DomainName DNSParser::GetDomain() {
    return domain;
}

std::vector<ip_addr> DNSParser::GetResolvedAddresses()
{
    return resolvedAddresses;
}
