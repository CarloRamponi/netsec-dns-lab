$TTL   60000
@               IN      SOA     example.com.    ns.example.com. (
                        2006031201 ; serial
                        28800 ; refresh
                        14400 ; retry
                        3600000 ; expire
                        0 ; negative cache ttl
                        )

@       IN      NS    ns.example.com.

@       IN      A     2.2.2.2
www     IN      A     2.2.2.2
ns      IN      A     2.2.2.254
foo     IN      A     2.2.2.2
bar     IN      A     2.2.2.3
*       IN      A     2.2.2.2