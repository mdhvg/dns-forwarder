#include "Resolver.h"

#include <iostream>
#include <memory>
#include <ios>
#include <fstream>

int main() {
    std::unique_ptr<Resolver> resolver = std::make_unique<Resolver>();
    resolver->Start();





    // const char* fileName = "query_packet";
    // std::ifstream file(fileName, std::ios::binary);

    // if (!file.is_open()) {
    //     std::cout << "Failed to open file: " << fileName << std::endl;
    //     return 1;
    // }

    // char* buffer = new char[512];

    // file.read(buffer, 512);

    // DNSParser parser(buffer);
    // DnsHeader header = parser.GetHeader();
    // // print all params
    // std::cout << "ID: " << header.id << std::endl;
    // std::cout << "QR: " << header.qr << std::endl;
    // std::cout << "OPCODE: " << int(header.opcode) << std::endl;
    // std::cout << "AA: " << header.authoritative_answer << std::endl;
    // std::cout << "TC: " << header.truncated_message << std::endl;
    // std::cout << "RD: " << header.recursion_desired << std::endl;
    // std::cout << "RA: " << header.recursion_available << std::endl;
    // std::cout << "RCODE: " << header.rescode << std::endl;
    // std::cout << "QDCOUNT: " << header.questions << std::endl;
    // std::cout << "ANCOUNT: " << header.answers << std::endl;
    // std::cout << "NSCOUNT: " << header.resource_entries << std::endl;
    // std::cout << "ARCOUNT: " << header.authoritative_entries << std::endl;

    // DNSDomainName domain = parser.GetDomain();
    // std::cout << "Domain: ";
    // for (auto label : domain.labels) {
    //     std::cout << label << " ";
    // }
    // std::cout << std::endl;
    // UDPClient client("1.1.1.1", 53);
    // char* response = new char[512];
    // client.Send(buffer, 512, response, 512);
    // const char* outFile = "response_packet";
    // std::ofstream out(outFile, std::ios::binary);

    // if (!out.is_open()) {
    //     std::cout << "Failed to open file: " << outFile << std::endl;
    //     return 1;
    // }

    // out.write(response, 512);
    // out.close();

    // delete[] buffer;
    // DNSParser parser(response);
    // DnsHeader header = parser.GetHeader();
    // // print all params
    // std::cout << "ID: " << header.id << std::endl;
    // std::cout << "QR: " << header.qr << std::endl;
    // std::cout << "OPCODE: " << int(header.opcode) << std::endl;
    // std::cout << "AA: " << header.authoritative_answer << std::endl;
    // std::cout << "TC: " << header.truncated_message << std::endl;
    // std::cout << "RD: " << header.recursion_desired << std::endl;
    // std::cout << "RA: " << header.recursion_available << std::endl;
    // std::cout << "RCODE: " << header.rescode << std::endl;
    // std::cout << "QDCOUNT: " << header.questions << std::endl;
    // std::cout << "ANCOUNT: " << header.answers << std::endl;
    // std::cout << "NSCOUNT: " << header.resource_entries << std::endl;
    // std::cout << "ARCOUNT: " << header.authoritative_entries << std::endl;

    // DNSDomainName domain = parser.GetDomain();
    // std::cout << "Domain: ";
    // for (auto label : domain.labels) {
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

    // const char* outFile = "query_packet";
    // std::ofstream out(outFile, std::ios::binary);
    // NASSERT(out.is_open(), false, "Failed to open file: ");
    // out.write(recvBuffer, 512);
    // out.close();
}