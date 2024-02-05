#include "UDPServer.h"
#include "UDPClient.h"
#include "DNSPacket.h"
#include "Request.h"

#include <memory>
#include <queue>
#include <thread>
#include <vector>
#include <unordered_map>
#include <utility>

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
    UString resolveRequest(UString* request);
private:
    std::queue<RequestPair> m_Requests;
    std::thread m_ServerThread;
    std::thread m_ResolverThread;
    std::unique_ptr<UDPServer> m_Server;
    std::vector<std::unique_ptr<UDPClient>> m_Clients;
    std::string m_ClientResolveServer;
    uint16_t m_ClientPort;
    std::unordered_map<std::string, DNS> m_Cache;
private:
    static Resolver* s_Instance;
};