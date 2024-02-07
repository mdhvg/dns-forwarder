#include "util.h"
#include "DNSPacketHandler.h"

#include <string>
#include <arpa/inet.h>

class UDPClient {
public:
    UDPClient(std::string ip, uint16_t port);
    ~UDPClient();

    DNSPacketHandler* Send(DNSPacketHandler* packet);

private:
    std::string m_RemoteIP;
    uint16_t m_RemotePort;
    int m_Socket;
    sockaddr_in m_RemoteAddr;
};