#include "util.h"

#include <vector>
#include <iostream>
#include <string>

enum ResultCode {
    NOERROR,
    FORMERR,
    SERVFAIL,
    NXDOMAIN,
    NOTIMP,
    REFUSED
};

struct ResponseIPAddress {
    uint8_t octets[4] = { 0, 0, 0, 0 }; /**< Array of octets representing the IP address. */
    uint16_t timeOut = 0; /**< Timeout value for the IP address. */
};

struct DNSDomainName {
    std::vector<std::string> labels;
};

struct DnsHeader {
    uint16_t id; // 16 bits

    bool qr;                   // 1 bit
    uint8_t opcode;                 // 4 bits
    bool authoritative_answer; // 1 bit
    bool truncated_message;    // 1 bit
    bool recursion_desired;    // 1 bit
    bool recursion_available; // 1 bit
    // Z 3 bits reserved
    ResultCode rescode;       // 4 bits

    uint16_t questions;             // 16 bits
    uint16_t answers;               // 16 bits
    uint16_t resource_entries;      // 16 bits
    uint16_t authoritative_entries; // 16 bits
};

/**
 * @brief The DNSParser class is responsible for parsing DNS packets.
 *
 * It provides methods to parse the DNS packet, retrieve the header, domain name,
 * and resolved addresses from the packet.
 */
class DNSParser {
public:
    /**
     * @brief Constructs a DNSParser object with the given buffer.
     *
     * @param buffer The buffer containing the DNS packet.
     */
    DNSParser(const char* buffer);

    /**
     * @brief Destroys the DNSParser object.
     */
    ~DNSParser();

    /**
     * @brief Parses the DNS packet.
     *
     * @param buffer The buffer containing the DNS packet.
     */
    void Parse(const char* buffer);

    /**
     * @brief Retrieves the DNS header.
     *
     * @return The DNS header.
     */
    DnsHeader GetHeader();

    /**
     * @brief Retrieves the domain name.
     *
     * @return The domain name.
     */
    DNSDomainName GetDomain();

    /**
     * @brief Retrieves the list of resolved addresses in the packet.
     *
     * @return The list of resolved addresses.
     */
    std::vector<ResponseIPAddress> GetResolvedAddresses();

private:
    /**
     * @brief Checks if the next byte in the buffer matches the given pattern.
     *
     * @param buffer The buffer containing the DNS packet.
     * @param currentOffset The current offset in the buffer.
     * @param size The size of the pattern to match.
     * @param pattern The pattern to match.
     * @return True if the next byte matches the pattern, false otherwise. Moves the `currentOffset` by `size` if the next byte matches the pattern.
     */
    inline bool checkNextByte(const char* buffer, uint8_t& currentOffset, uint8_t size, int pattern) {
        int next = 0;
        int i;
        FOREQ(i, 1, size) {
            next <<= 8;
            next |= buffer[currentOffset + i];
        }
        currentOffset += size;
        return next == pattern;
    }

    /**
     * @brief Reads n bytes from the buffer and converts them to the specified type.
     *
     * @tparam T The type to convert the bytes to.
     * @param buffer The buffer containing the DNS packet.
     * @param currentOffset The current offset in the buffer.
     * @return The converted value.
     */
    template <class T>
    inline T read_nBytes_As(const char* buffer, uint8_t& currentOffset) {
        T result = 0;
        int i;
        FOREQ(i, 1, sizeof(T)) {
            result <<= 8;
            result |= buffer[currentOffset + i];
        }
        currentOffset += sizeof(T);
        return result;
    }

private:
    DnsHeader header;                           // The DNS header
    DNSDomainName domain;                          // The domain name
    std::vector<ResponseIPAddress> resolvedAddresses;      // List of resolved addresses in the packet
};