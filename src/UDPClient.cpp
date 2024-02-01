#include "UDPClient.h"

#include <unistd.h>

UDPClient::UDPClient(const std::string ip, uint16_t port) : m_remote_ip(ip), m_remote_port(port) {
    m_socket = socket(AF_INET, SOCK_DGRAM, 0);
    NASSERT(m_socket, -1, "Client: Socket failed to initialize");

    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_remote_port);
    addr.sin_addr.s_addr = inet_addr(m_remote_ip.c_str());
}

UDPClient::~UDPClient() {
    close(m_socket);
}

void UDPClient::Send(const char* buffer, int size, const char* response_buffer, int response_size) {
    int sent = sendto(m_socket, buffer, size, 0, (sockaddr*)&addr, sizeof(addr));
    NASSERT(sent, -1, "Send failed");

    NASSERT(response_buffer, nullptr, "Client: Response buffer is null");
    int received = recvfrom(m_socket, (char*)response_buffer, response_size, 0, nullptr, nullptr);
    NASSERT(received, -1, "Receive failed");
}