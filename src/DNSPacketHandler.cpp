#include "DNSPacketHandler.h"

DNSPacketHandler::DNSPacketHandler(unsigned char* packet, int packetSize) :
    packetSize(packetSize) {
    this->packet = new unsigned char[packetSize];
    memmove(this->packet, packet, packetSize);
};

DNSPacketHandler::~DNSPacketHandler() {
    delete[] packet;
}

unsigned char* DNSPacketHandler::getPacket() {
    return packet;
}

int DNSPacketHandler::getPacketSize() {
    return packetSize;
}

std::string DNSPacketHandler::getDomain() {
    uint16_t currentOffset = 12;
    std::string domain;
    while (packet[currentOffset] != 0) {
        domain.push_back(packet[currentOffset]);
        currentOffset++;
    }
    domainEndOffset = currentOffset;
    return domain;
}

uint16_t DNSPacketHandler::getID() {
    uint16_t id = 0;
    memmove(&id, &packet[0], sizeof(uint16_t));
    setEndian(&id);
    return id;
}

void DNSPacketHandler::setID(uint16_t id) {
    setEndian(&id);
    memmove(&packet[0], &id, sizeof(uint16_t));
}