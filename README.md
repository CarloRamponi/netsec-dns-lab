# netsec-dns-lab

To start the lab:
1. `cd lab`
2. `kathara lstart`

To perform cache poisoning:
1. On authoritative DNS device, set delay with: `tc qdisc add dev eth0 root netem delay 1000ms`
2. On attacker device: `./exploit-poisoning`
3. On victim, verify that test.example.com has IP 1.1.1.3 with `dig test.example.com`

To perform Kaminsky attack:
1. On root DNS device, set delay with: `tc qdisc add dev eth0 root netem delay 1000ms`
2. On attacker device: `./exploit`
3. On victim, verify that example.com has ns at 1.1.1.254 with `dig example.com`
