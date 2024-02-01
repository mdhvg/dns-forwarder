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
    void Send(const char* buffer, int size, const char* response_buffer, int response_size);

    /**
     * @brief Gets the IP address of the remote server.
     * @return The IP address of the remote server.
     */
    std::string GetRemoteIP() const { return m_remote_ip; }

    /**
     * @brief Gets the port number of the remote server.
     * @return The port number of the remote server.
     */
    uint16_t GetRemotePort() const { return m_remote_port; }

private:
    std::string m_remote_ip; ///< The IP address of the remote server.
    uint16_t m_remote_port; ///< The port number of the remote server.
    int m_socket; ///< The socket descriptor.
    sockaddr_in addr; ///< The address structure.
};