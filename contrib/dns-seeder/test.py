import socket

seeders = [
    'odexseed.mempool.pw',
    'odexseed1.odexcrypto.com',
    'odexseed2.odexcrypto.com',
    'odexseed3.odexcrypto.com',
    'odexseed4.odexcrypto.com',
    'odexseed5.odexcrypto.com',
    'odexseed1.odexcrypto.site',
    'odexseed2.odexcrypto.site',
    'odexseed3.odexcrypto.site',
    'odexseed4.odexcrypto.site',
    'odexseed5.odexcrypto.site'
]

for seeder in seeders:
    try:
        ais = socket.getaddrinfo(seeder, 0)
    except socket.gaierror:
        ais = []
    
    # Prevent duplicates, need to update to check
    # for ports, can have multiple nodes on 1 ip.
    addrs = []
    for a in ais:
        addr = a[4][0]
        if addrs.count(addr) == 0:
            addrs.append(addr)
    
    print(seeder + ' = ' + str(len(addrs)))
