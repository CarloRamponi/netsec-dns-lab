$TTL   60000
@               IN      SOA     example.com.    ns.attacker.com. (
                        2006031201 ; serial
                        28800 ; refresh
                        14400 ; retry
                        3600000 ; expire
                        0 ; negative cache ttl
                        )

@       IN      NS    ns.attacker.com.

@       IN      A     1.1.1.3
www     IN      A     1.1.1.3
ns      IN      A     1.1.1.254
*       IN      A     1.1.1.3
