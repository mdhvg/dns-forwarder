#include "UDPServer.h"

#include <unistd.h>

UDPServer::UDPServer(uint16_t port, std::queue<RequestPair>& requests) : m_port(port), m_Requests(requests) {
    m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
    NASSERT(m_Socket, -1, "Server: Socket failed to initialize");

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(m_port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    NASSERT(bind(m_Socket, (struct sockaddr*)&server_address, sizeof(server_address)),
        -1,
        "Server: Failed to bind socket");
    printf("Server: Listening on port %d\n", m_port);
}

UDPServer::~UDPServer() {
    close(m_Socket);
}

void UDPServer::Receive() {
    while (true) {
        Request request;
        // MIGHT GIVE BUGS
        unsigned char* temp = new unsigned char[512];
        int received = recvfrom(
            m_Socket,
            temp,
            512,
            0,
            request.addressPointer,
            &request.addressSize
        );
        UString* buffer = new UString(temp, received);
        printf("Server: Received %d bytes from %s:%d\n", received, inet_ntoa(request.address.sin_addr), ntohs(request.address.sin_port));
        NASSERT(received, -1, "Receive failed");
        m_Requests.push(std::make_pair(request, buffer));
    }
}

void UDPServer::Respond(RequestPair request) {
    int sent = sendto(
        m_Socket,
        request.second->data(),
        request.second->size(),
        0,
        request.first.addressPointer,
        request.first.addressSize
    );
    NASSERT(sent, -1, "Respond failed");
}