#include "udp_server.h"

#include <unistd.h>

UDPServer::UDPServer(uint16_t port) : m_port(port) {
    m_socket = socket(AF_INET, SOCK_DGRAM, 0);
    NASSERT(m_socket, -1, "Server: Socket failed to initialize");

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(m_port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    int bound = bind(m_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    NASSERT(bound, -1, "Server: Failed to bind socket");
}

UDPServer::~UDPServer() {
    close(m_socket);
}

void UDPServer::Receive(char* buffer, int size) {
    bool recv = false;
    while (!recv) {
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int received = recvfrom(m_socket, buffer, size, 0, (sockaddr*)&client_addr, &client_addr_len);
        NASSERT(received, -1, "Receive failed");
        recv = true;
    }
}

void UDPServer::Respond(int request_id, const char* response_buffer, int response_size) {
    NASSERT(response_buffer, nullptr, "Server: Response buffer is null");
    int sent = sendto(m_socket, response_buffer, response_size, 0, (sockaddr*)&server_address, sizeof(server_address));
    NASSERT(sent, -1, "Respond failed");
}