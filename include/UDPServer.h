#include "util.h"
#include "DNSPacket.h"
#include "Types.h"

#include <string>
#include <queue>
#include <arpa/inet.h>
#include <utility>

class UDPServer {
public:
    UDPServer(uint16_t port, std::queue<RequestPair>& requests);

    ~UDPServer();

    void Receive();

    void Respond(RequestPair request);
private:
    std::queue<RequestPair>& m_Requests;
    int m_Socket;
    uint16_t m_port;
    sockaddr_in server_address;
};