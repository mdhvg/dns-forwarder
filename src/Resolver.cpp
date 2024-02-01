#include "Resolver.h"

Resolver* Resolver::s_Instance = nullptr;

Resolver::Resolver(uint16_t serverPort, uint16_t clientPort, std::string resolveServer) :
    m_clientPort(clientPort), m_clientResolveServer(resolveServer)
{
    ASSERT(s_Instance, nullptr, "Resolver: Instance already exists");
    s_Instance = this;
    m_Server = std::make_unique<UDPServer>(serverPort, m_requests);
}

void Resolver::Start()
{
    m_ServerThread = std::thread(&UDPServer::Receive, m_Server.get());
    while (true) {
        if (!m_requests.empty()) {
            printf("Resolver: Processing request\n");
            Request request = m_requests.front();
            printf("Resolver: Processing request from - %s\n", request.addressString);
            m_requests.pop();
            std::unique_ptr<UDPClient> client = std::make_unique<UDPClient>(m_clientResolveServer, m_clientPort);
            client->Send(request.queryBuffer, sizeof(request.queryBuffer), request.responseBuffer, sizeof(request.responseBuffer));
            m_Server->Respond(request);
        }
    }
}