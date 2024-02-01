#include "UDPServer.h"
#include "UDPClient.h"
#include "DNSParser.h"
#include "Request.h"

#include <memory>
#include <queue>
#include <thread>
#include <vector>

#define DEFAULT_SERVER 3053

class Resolver {
public:
    Resolver(const Resolver&) = delete;
    Resolver& operator=(const Resolver&) = delete;
public:
    Resolver(uint16_t serverPort = DEFAULT_SERVER, uint16_t clientPort = 53, std::string clientResolveServer = "1.1.1.1");
    ~Resolver() = default;

    void Start();
public:
    inline static Resolver& Get() { return *s_Instance; }

private:
    std::queue<Request> m_requests;
    std::thread m_ServerThread;
    std::thread m_ResolverThread;
    std::unique_ptr<UDPServer> m_Server;
    std::vector<std::unique_ptr<UDPClient>> m_Clients;
    std::string m_clientResolveServer;
    uint16_t m_clientPort;
private:
    static Resolver* s_Instance;
};