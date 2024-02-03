#include "Resolver.h"

#include <iostream>
#include <memory>
#include <ios>
#include <fstream>

int main() {
    std::unique_ptr<Resolver> resolver = std::make_unique<Resolver>();
    resolver->Start();





    // char* fileName = "query_packet";
    // std::ifstream file(fileName, std::ios::binary);

    // if (!file.is_open()) {
    //     std::cout << "Failed to open file: " << fileName << std::endl;
    //     return 1;
    // }

    // char* buffer = new char[512];

    // file.read(buffer, 512);

    // DNSPacket parser(buffer);
    // DnsHeader m_Header = parser.GetHeader();
    // // print all params
    // std::cout << "ID: " << m_Header.id << std::endl;
    // std::cout << "QR: " << m_Header.qr << std::endl;
    // std::cout << "OPCODE: " << int(m_Header.opcode) << std::endl;
    // std::cout << "AA: " << m_Header.authoritative_answer << std::endl;
    // std::cout << "TC: " << m_Header.truncated_message << std::endl;
    // std::cout << "RD: " << m_Header.recursion_desired << std::endl;
    // std::cout << "RA: " << m_Header.recursion_available << std::endl;
    // std::cout << "RCODE: " << m_Header.rescode << std::endl;
    // std::cout << "QDCOUNT: " << m_Header.questions << std::endl;
    // std::cout << "ANCOUNT: " << m_Header.answers << std::endl;
    // std::cout << "NSCOUNT: " << m_Header.resource_entries << std::endl;
    // std::cout << "ARCOUNT: " << m_Header.authoritative_entries << std::endl;

    // DNSDomainName m_Domain = parser.GetDomain();
    // std::cout << "Domain: ";
    // for (auto label : m_Domain.labels) {
    //     std::cout << label << " ";
    // }
    // std::cout << std::endl;
    // UDPClient client("1.1.1.1", 53);
    // char* response = new char[512];
    // client.Send(buffer, 512, response, 512);
    // char* outFile = "response_packet";
    // std::ofstream out(outFile, std::ios::binary);

    // if (!out.is_open()) {
    //     std::cout << "Failed to open file: " << outFile << std::endl;
    //     return 1;
    // }

    // out.write(response, 512);
    // out.close();

    // delete[] buffer;
    // DNSPacket parser(response);
    // DnsHeader m_Header = parser.GetHeader();
    // // print all params
    // std::cout << "ID: " << m_Header.id << std::endl;
    // std::cout << "QR: " << m_Header.qr << std::endl;
    // std::cout << "OPCODE: " << int(m_Header.opcode) << std::endl;
    // std::cout << "AA: " << m_Header.authoritative_answer << std::endl;
    // std::cout << "TC: " << m_Header.truncated_message << std::endl;
    // std::cout << "RD: " << m_Header.recursion_desired << std::endl;
    // std::cout << "RA: " << m_Header.recursion_available << std::endl;
    // std::cout << "RCODE: " << m_Header.rescode << std::endl;
    // std::cout << "QDCOUNT: " << m_Header.questions << std::endl;
    // std::cout << "ANCOUNT: " << m_Header.answers << std::endl;
    // std::cout << "NSCOUNT: " << m_Header.resource_entries << std::endl;
    // std::cout << "ARCOUNT: " << m_Header.authoritative_entries << std::endl;

    // DNSDomainName m_Domain = parser.GetDomain();
    // std::cout << "Domain: ";
    // for (auto label : m_Domain.labels) {
    //     std::cout << label << " ";
    // }
    // std::cout << std::endl;

    // for (auto ip : parser.GetResolvedAddresses()) {
    //     std::cout << "IP: ";
    //     for (int i = 0; i < 4; i++) {
    //         std::cout << int(ip.octets[i]);
    //         if (i != 3) {
    //             std::cout << ".";
    //         }
    //     }
    //     std::cout << std::endl;
    // }

    // UDPServer server(1053);
    // char* recvBuffer = new char[512];
    // server.Receive(recvBuffer, 512, sendBuffer, 512);

    // char* outFile = "query_packet";
    // std::ofstream out(outFile, std::ios::binary);
    // NASSERT(out.is_open(), false, "Failed to open file: ");
    // out.write(recvBuffer, 512);
    // out.close();
}