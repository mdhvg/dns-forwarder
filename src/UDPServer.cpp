#include "UDPServer.h"

#include <unistd.h>

UDPServer::UDPServer(uint16_t port, std::queue<Request>& m_requests) : m_port(port), m_Requests(m_requests) {
    m_socket = socket(AF_INET, SOCK_DGRAM, 0);
    NASSERT(m_socket, -1, "Server: Socket failed to initialize");

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(m_port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    int bound = bind(m_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    printf("Server: Listening on port %d\n", m_port);
    NASSERT(bound, -1, "Server: Failed to bind socket");
}

UDPServer::~UDPServer() {
    close(m_socket);
}

void UDPServer::Receive() {
    while (true) {
        Request request;
        int received = recvfrom(
            m_socket,
            request.queryBuffer,
            sizeof(request.queryBuffer),
            0,
            request.addressPointer,
            &request.addressSize
        );
        printf("Server: Received %d bytes from %s:%d\n", received, inet_ntoa(request.address.sin_addr), ntohs(request.address.sin_port));
        NASSERT(received, -1, "Receive failed");
        m_Requests.push(request);
    }
}

void UDPServer::Respond(Request& request) {
    NASSERT(request.responseBuffer, nullptr, "Server: Response buffer is null");
    int sent = sendto(
        m_socket,
        request.responseBuffer,
        sizeof(request.responseBuffer),
        0,
        request.addressPointer,
        request.addressSize
    );
    NASSERT(sent, -1, "Respond failed");
}