#include "util.h"
#include "UString.h"

#include <string>
#include <arpa/inet.h>

class UDPClient {
public:
    UDPClient(std::string ip, uint16_t port);
    ~UDPClient();

    void Send(UString& reqBuffer, UString& recvBuffer);

    std::string GetRemoteIP() const { return m_RemoteIP; }
    uint16_t GetRemotePort() const { return m_RemotePort; }

private:
    std::string m_RemoteIP;
    uint16_t m_RemotePort;
    int m_Socket;
    sockaddr_in m_RemoteAddr;
};