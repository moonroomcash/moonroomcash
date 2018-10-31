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
cd
mkdir .moonroomcash
echo "rpcuser=username" >> ~/.moonroomcash/moonroomcash.conf
echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=178.128.104.155" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=173.249.16.174" >> ~/.moonroomcash/moonroomcash.conf

```

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
