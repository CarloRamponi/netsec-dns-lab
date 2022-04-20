$TTL   60000
@               IN      SOA     example.com.    ns.example.com. (
                        2006031201 ; serial
                        28800 ; refresh
                        14400 ; retry
                        1 ; expire
                        0 ; negative cache ttl
                        )

@   1       IN      NS    ns.example.com.

@   1       IN      A     2.2.2.2
www 1       IN      A     2.2.2.2
ns  1       IN      A     2.2.2.254
foo 1       IN      A     2.2.2.2
bar 1       IN      A     2.2.2.3
*   1       IN      A     2.2.2.2