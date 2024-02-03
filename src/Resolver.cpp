#include "Resolver.h"

Resolver* Resolver::s_Instance = nullptr;

Resolver::Resolver(uint16_t serverPort, uint16_t clientPort, std::string resolveServer) :
    m_ClientPort(clientPort), m_ClientResolveServer(resolveServer)
{
    ASSERT(s_Instance, nullptr, "Resolver: Instance already exists");
    s_Instance = this;
    m_Server = std::make_unique<UDPServer>(serverPort, m_Requests);
}

void Resolver::Start()
{
    m_ServerThread = std::thread(&UDPServer::Receive, m_Server.get());
    std::string recvBuffer;
    while (true) {
        if (!m_Requests.empty()) {
            Request request = m_Requests.front().first;
            std::string reqBuffer = m_Requests.front().second;
            printf("Resolver: Processing request from - %s of size - %d\n", request.addressString, static_cast<int>(reqBuffer.size()));
            m_Requests.pop();

            DNSPacket reqPacket = DNSPacket(reqBuffer);
            if (m_Cache.find(reqPacket.GetDomain()) != m_Cache.end()) {
                printf("Resolver: Cache hit for domain - %s\n", reqPacket.GetDomain().c_str());
                printf("Resolver: Request ID: %d\n", reqPacket.GetID());
                DNSPacket response(reqPacket.GetID(), reqPacket.GetDomain(), m_Cache[reqPacket.GetDomain()], DNSPacketType::RESPONSE);
                m_Server->Respond(std::make_pair(request, response.GetBuffer()));
                continue;
            }

            printf("Resolver: Cache miss for domain - %s\n", reqPacket.GetDomain().c_str());
            UDPClient client(m_ClientResolveServer, m_ClientPort);
            recvBuffer.clear();
            client.Send(reqBuffer, recvBuffer);
            DNSPacket recvPacket = DNSPacket(recvBuffer);
            printf("Resolver: Received packet ID %d and Response packet ID %d\n", reqPacket.GetID(), recvPacket.GetID());
            CopyRsponseID(reqPacket, recvPacket);
            m_Server->Respond(std::make_pair(request, recvPacket.GetBuffer()));
            m_Cache[recvPacket.GetDomain()] = recvPacket.GetResponseIPAddress();
        }
    }
}

void Resolver::CopyRsponseID(DNSPacket& packet, DNSPacket& response)
{
    response.SetID(packet.GetID());
}
