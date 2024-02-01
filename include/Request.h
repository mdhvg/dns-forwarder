#ifndef REQUEST_H
#define REQUEST_H

#include <arpa/inet.h>

struct Request {
    sockaddr_in address;
    sockaddr* addressPointer = (sockaddr*)&address;
    socklen_t addressSize = sizeof(address);
    const char* addressString = inet_ntop(AF_INET, &address.sin_addr, new char[INET_ADDRSTRLEN], INET_ADDRSTRLEN);

    u_int16_t packetId = 0;

    char queryBuffer[512] = { 0 };
    char responseBuffer[512] = { 0 };
};

#endif // REQUEST_H