#include "util.h"

#include <string>
#include <arpa/inet.h>

/**
 * @brief The UDPServer class represents a UDP server that listens on a specified port.
 */
class UDPServer {
public:
    /**
     * @brief Constructs a UDPServer object with the specified port.
     * @param port The port number to listen on.
     */
    UDPServer(uint16_t port);

    /**
     * @brief Destroys the UDPServer object.
     */
    ~UDPServer();

    /**
     * @brief Receives data from a client and sends a response.
     * @param buffer The buffer to store the received data.
     * @param size The size of the buffer.
     */
    void Receive(char* buffer, int size);

    void Respond(int request_id, const char* response_buffer, int response_size);

private:
    uint16_t m_port; ///< The port number to listen on.
    int m_socket; ///< The socket file descriptor.
    sockaddr_in server_address; ///< The server address structure.

};