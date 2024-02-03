#include "UDPClient.h"

#include <unistd.h>

UDPClient::UDPClient(const std::string ip, uint16_t port) : m_RemoteIP(ip), m_RemotePort(port) {
    m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
    NASSERT(m_Socket, -1, "Client: Socket failed to initialize");

    m_RemoteAddr.sin_family = AF_INET;
    m_RemoteAddr.sin_port = htons(m_RemotePort);
    m_RemoteAddr.sin_addr.s_addr = inet_addr(m_RemoteIP.c_str());
}

UDPClient::~UDPClient() {
    close(m_Socket);
}

void UDPClient::Send(std::string& reqBuffer, std::string& recvBuffer) {
    int sent = sendto(m_Socket, reqBuffer.data(), reqBuffer.size(), 0, (sockaddr*)&m_RemoteAddr, sizeof(m_RemoteAddr));
    NASSERT(sent, -1, "Send failed");

    char* temp = new char[512];
    int received = recvfrom(m_Socket,
        temp,
        512,
        0,
        nullptr,
        nullptr);
    NASSERT(received, -1, "Receive failed");
    recvBuffer.append(temp, received);
    delete[] temp;
}