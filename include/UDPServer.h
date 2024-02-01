#include "util.h"
#include "Request.h"

#include <string>
#include <queue>
#include <arpa/inet.h>

class UDPServer {
public:
    UDPServer(uint16_t port, std::queue<Request>& requests);

    ~UDPServer();

    void Receive();

    void Respond(Request& request);
private:
    std::queue<Request>& m_Requests;
    uint16_t m_port;
    int m_socket;
    sockaddr_in server_address;
};