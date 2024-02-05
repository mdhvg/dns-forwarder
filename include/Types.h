#ifndef TYPES_H
#define TYPES_H

#include "Request.h"
#include "UString.h"

#include <utility>
#include <string>
#include <vector>

typedef std::pair<Request, UString*> RequestPair;

enum ResultCode {
	NOERROR,
	FORMERR,
	SERVFAIL,
	NXDOMAIN,
	NOTIMP,
	REFUSED
};

enum DNSPacketType {
	QUERY, RESPONSE
};

struct IPAddr {
	// TODO: Change this to sockaddr_in m_Type
	uint8_t octets[4] = { 0, 0, 0, 0 };
	uint32_t timeOut = 0;
};

typedef std::vector<IPAddr> IPAddrList;

struct DnsHeader {
	uint16_t id = -1;                           // 16 bits

	bool qr = 0;                                // 1 bit
	uint8_t opcode = 0;                         // 4 bits
	bool authoritative_answer = 0;				// 1 bit
	bool truncated_message = 0;		            // 1 bit
	bool recursion_desired = 0;					// 1 bit
	bool recursion_available = 0;	            // 1 bit
	// Z 3 bits reserved
	ResultCode rescode = ResultCode::NOERROR;	// 4 bits

	uint16_t questions = 0;						// 16 bits
	uint16_t answers = 0;		                // 16 bits
	uint16_t resource_entries = 0;				// 16 bits
	uint16_t authoritative_entries = 0;			// 16 bits
};

struct DNS {
	DnsHeader header;
	std::string domain;
	IPAddrList ipAddr;
	DNSPacketType type;
};

#endif // TYPES_H