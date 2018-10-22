# Moonroomcash 1.1.0
INNOVATIVE  INTMRCLIGENT  INSPIRING

Moonroomcash is a fork of 1.0.14 Zcash aiming to provide decentralised development platform via ZelNodes and ZelTreZ.

POW asic resistant with Equihash (144,5) also known as Zhash with personalisation string ZelProof. 

To speed up synchronisation you can also download our blockchain (state Fri 6. 7. 2018) at https://drive.google.com/file/d/1Vn8HWau24wjTtUc9QZU2stliKevaEFx1/view?usp=sharing (pw: moonroomcash).

## Install and run from APT
```
echo 'deb https://moonroomcash.github.io/aptrepo/ all main' | sudo tee --append /etc/apt/sources.list.d/moonroomcash.list
gpg --keyserver keyserver.ubuntu.com --recv 69FAF6DE41B8AC51
gpg --export 69FAF6DE41B8AC51| sudo apt-key add -

sudo apt-get update
sudo apt-get install moonroomcash
```
This installs moonroomcashd, moonroomcash-cli, moonroomcash-tx and fetch-params

#### Run Moonroomcash 
1. Create moonroomcash.conf file
```
cd
mkdir .moonroomcash
echo "rpcuser=username" >> ~/.moonroomcash/moonroomcash.conf
echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=node.zel.cash" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=explorer.zel.cash" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=explorer2.zel.cash" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=explorer.moonroomcash.online" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=node-eu.moonroomcash.com" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=node-uk.moonroomcash.com" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=node-asia.moonroomcash.com" >> ~/.moonroomcash/moonroomcash.conf
```

2. Fetch keys
```
fetch-params
```

3. Run a Moonroomcash node
```
moonroomcashd
```

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
echo "addnode=node.zel.cash" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=explorer.zel.cash" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=explorer2.zel.cash" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=explorer.moonroomcash.online" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=node-eu.moonroomcash.com" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=node-uk.moonroomcash.com" >> ~/.moonroomcash/moonroomcash.conf
echo "addnode=node-asia.moonroomcash.com" >> ~/.moonroomcash/moonroomcash.conf
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


## Build for Windows 64Bit (Ubuntu 16.04 Tested)
1. Get dependencies
```
sudo apt-get update
sudo apt-get install \
      build-essential pkg-config libc6-dev m4 g++-multilib \
      autoconf libtool ncurses-dev unzip git python curl \
      zlib1g-dev wget bsdmainutils automake cmake mingw-w64
```

2. Configure to use POSIX variant
```
sudo update-alternatives --config x86_64-w64-mingw32-gcc
sudo update-alternatives --config x86_64-w64-mingw32-g++
```

3. Install rust by running following script
```
curl https://sh.rustup.rs -sSf | sh
source ~/.cargo/env
rustup install stable-x86_64-unknown-linux-gnu
rustup install stable-x86_64-pc-windows-gnu
rustup target add x86_64-pc-windows-gnu
echo "[target.x86_64-pc-windows-gnu]" >> ~/.cargo/config
echo "linker = \"/usr/bin/x86_64-w64-mingw32-gcc\"" >> ~/.cargo/config
source ~/.cargo/env
```

4. Compile for windows
```
# pull
git clone https://github.com/moonroomcash/moonroomcash.git
cd moonroomcash
# Build
./zcutil/build-win.sh -j$(nproc)
```
This will create moonroomcashd.exe moonroomcash-cli.exe and moonroomcash-tx.exe in src directory.