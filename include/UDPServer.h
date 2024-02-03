#include "util.h"
#include "Request.h"
#include "DNSPacket.h"

#include <string>
#include <queue>
#include <arpa/inet.h>
#include <utility>

typedef std::pair<Request, std::string> RequestPair;

class UDPServer {
public:
    UDPServer(uint16_t port, std::queue<RequestPair>& requests);

    ~UDPServer();

    void Receive();

    void Respond(RequestPair request);
private:
    std::queue<RequestPair>& m_Requests;
    uint16_t m_port;
    int m_Socket;
    sockaddr_in server_address;
};