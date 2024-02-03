#include "util.h"

#include <string>
#include <arpa/inet.h>

/**
 * @class UDPClient
 * @brief Represents a UDP client for sending and receiving data over UDP.
 */
class UDPClient {
public:
    /**
     * @brief Constructs a UDPClient object with the specified IP address and port.
     * @param ip The IP address of the remote server.
     * @param port The port number of the remote server.
     */
    UDPClient(std::string ip, uint16_t port);

    /**
     * @brief Destroys the UDPClient object.
     */
    ~UDPClient();

    /**
     * @brief Sends data to the remote server and receives the response.
     * @param buffer The buffer containing the data to be sent.
     * @param size The size of the data to be sent.
     * @param response_buffer The buffer to store the response received from the server.
     * @param response_size The size of the response buffer.
     */
    void Send(std::string& reqBuffer, std::string& recvBuffer);

    /**
     * @brief Gets the IP address of the remote server.
     * @return The IP address of the remote server.
     */
    std::string GetRemoteIP() const { return m_RemoteIP; }

    /**
     * @brief Gets the port number of the remote server.
     * @return The port number of the remote server.
     */
    uint16_t GetRemotePort() const { return m_RemotePort; }

private:
    std::string m_RemoteIP; ///< The IP address of the remote server.
    uint16_t m_RemotePort; ///< The port number of the remote server.
    int m_Socket; ///< The socket descriptor.
    sockaddr_in m_RemoteAddr; ///< The address structure.
};