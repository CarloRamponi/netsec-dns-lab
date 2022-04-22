# netsec-dns-lab

To **start the lab**:
1. compile the attacker's docker image:
  - `cd images/attacker_machine`
  - `sudo docker build -t attacker_image .`
2. go into the laboratory directory:
  - `cd ../../lab`
3. start the lab
  - `kathara lstart --noterminals`

To **connect to a device** you can just type `kathara connect {DEVICE_NAME}`. The available devices are:
- `attacker`: where you have all the tools to perform the attack;
- `victim`: the victim of the attack. Here you will be able to check if the attack was successful;
- `rec_dns`: the recursive DNS the victim will query;
- `authoritative_dns`: the real authoritative DNS for *example.com*;
- `malicious_dns`: the attacker's DNS, set up to be authoritative for *example.com*;
- `root_dns`: the root DNS of this network topology.

Example: `kathara connect attacker`.


To perform the **cache poisoning attack**:
1. On the authoritative DNS device, set delay with: `tc qdisc add dev eth0 root netem delay 2000ms`
2. On the attacker's device run the script: `./exploit-poisoning`
3. On the victim's device, verify that test.example.com resolves to IP 1.1.1.3 with `dig test.example.com`

To perform the **Kaminsky attack**:
1. On the authoritative DNS's device, set delay with: `tc qdisc add dev eth0 root netem delay 2000ms`
2. On the attacker's device run the script: `./exploit`
3. On the victim's device, verify that example.com has ns at 1.1.1.254 with `dig example.com`. Every sub-domain should resolve to IP 1.1.1.3.


**Useful commands**:
- stop the kathara lab (you will lose everything you have done so far): `kathara lclean`
- clear the cache of a DNS: `rndc flush`
- print the cache entries for *example.com*: `rndc dumpdb -cache && grep "example.com" /var/cache/bind/dump.db`
- edit the delay: `tc qdisc change dev eth0 root netem delay 2000ms`
- remove the delay: `tc qdisc del dev eth0 root netem delay 2000ms`


**Browser inside the terminal**:
- use `links` to start it;
- type `g` to start searching for a URL;
- type `q` to exit.
