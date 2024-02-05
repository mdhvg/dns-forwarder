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
    while (true) {
        if (!m_Requests.empty()) {
            RequestPair request = m_Requests.front();
            printf("Resolver: Processing request from - %s of size - %d\n", request.first.addressString, request.second.size());
            m_Requests.pop();

            UString respBuffer = resolveRequest(request.second);

            m_Server->Respond(std::make_pair(request.first, respBuffer));
        }
    }
}

UString Resolver::resolveRequest(UString* request)
{
    DNSPacket reqPacket(*request);
    std::string reqDomain = reqPacket.GetDNS().domain;
    DNS resDNS;
    if (m_Cache.find(reqDomain) != m_Cache.end()) {
        printf("Resolver: Cache hit for domain - %s\n", reqDomain.c_str());
        resDNS = m_Cache[reqDomain];
    }
    else {
        printf("Resolver: Cache miss for domain - %s\n", reqDomain.c_str());
        UDPClient client(m_ClientResolveServer, m_ClientPort);
        UString resp;
        client.Send(request, resp);
        DNSPacket respPacket(resp);
        printf("Resolver: Received packet ID %d and Response packet ID %d\n", reqPacket.GetDNS().header.id, respPacket.GetDNS().header.id);
        resDNS = respPacket.GetDNS();
        m_Cache[reqDomain] = resDNS;
    }
    resDNS.header.id = reqPacket.GetDNS().header.id;
    DNSPacket resPacket(resDNS);
    return resPacket.GetBuffer();
}