# Moonroomcash 1.0.0
What is Moonroomcash?

Moonroomcash is an implementation of the "Zerocash" protocol. Based on Bitcoin's code, it intends to offer a far higher standard of privacy through a sophisticated zero-knowledge proving scheme that preserves confidentiality of transaction metadata.

This software is the Moonroomcash node and command-line client. It downloads and stores the entire history of Moonroomcash transactions; depending on the speed of your computer and network connection, the synchronization process could take a day or more once the blockchain has reached a significant size.




## Build (Ubuntu 16.04 Tested)
1. Get dependencies
```
sudo apt-get update
sudo apt-get install \
      build-essential pkg-config libc6-dev m4 g++-multilib \
      autoconf libtool ncurses-dev unzip git python \
      zlib1g-dev wget bsdmainutils automake curl
```

2. Build
```
# pull
git clone https://github.com/moonroomcash/moonroomcash.git
cd moonroomcash
# Build
./zcutil/build.sh -j$(nproc)
```

#### Run Moonroomcash 
1. Create moonroomcash.conf file
```
mkdir -p  ~/.moonroomcash
echo "rpcuser=username" >> ~/.moonroomcash/moonroomcash.conf
echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=178.128.104.155" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=173.249.16.174" >> ~/.moonroomcash/moonroomcash.conf
please add those  command  in moonroomcash.conf file to complete moonroomcash.conf
cd ~/.moonroomcash
nano  moonroomcash.conf
listen=1
rpcport=16224
#rpcallowip=10.1.1.34
#rpcallowip=192.168.*.*
#rpcallowip=1.2.3.4/255.255.255.0
rpcallowip=127.0.0.1
rpctimeout=30
gen=1
equihashsolver=tromp
showmetrics=1
 #Use Secure Sockets Layer (also known as TLS or HTTPS) to communicate
# with moonroomcash -server or moonroomcashd
#rpcssl=1
# OpenSSL settings used when rpcssl=1
#rpcsslciphers=TLSv1+HIGH:!SSLv2:!aNULL:!eNULL:!AH:!3DES:@STRENGTH
#rpcsslcertificatechainfile=server.cert
#rpcsslprivatekeyfile=server.pem




2. Fetch keys
```
cd moonroomcash
./zcutil/fetch-params.sh
```

3. Run a Moonroomcash node
```
./src/moonroomcashd 
```

Currently only Linux is officially supported.

Windows version will be available soon.
For license information see the file at  [User-guide for moonroomcash].
[User-guide for moonroomcash]: https://github.com/moonroomcash/moonroomcash/blob/master/doc/user-guide/user-guide.md
