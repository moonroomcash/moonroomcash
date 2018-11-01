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
addnode=178.128.104.155
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

4. Run a Moonroomcash RPC Command
```
./src/moonroomcashd --daemon(when daemon=1)
 Moonroomcash Server Starting
./src/moonroomcash-cli getinfo 
Returns an object containing various state info.
./src/moonroomcash-cli help
user will get all rpc commands of moonroomcash
./src/moonroomcash-cli stop
Moonroomcash server stopping
./src/moonroomcash-cli getnewwadress
will get a (T-address)  start with M1
 ./src/moonroomcash-cli z_getnewaddress
will get a (z-address) start with z
./src/moonroomcash-cli z_validateaddress "zaddress"
check address is validate or not
./src/moonroomcash-cli validateaddress "t-address"
check t-address is validate or not
./src/moonroomcash-cli getwalletinfo
get various  wallet state info
./src/moonroomcash-cli listaddressgroupings
Lists groups of addresses which have had their common ownership
made public by common use as inputs or as the resulting change
in past transactions
./src/moonroomcash-cli z_listaddresses
Returns the list of Sprout and Sapling shielded addresses belonging to the wallet.
./src/moonroomcash-cli z_sendmany "fromaddress" '[{"address": "toaddress" ,"amount": xxx}]'
Send multiple times. Amounts are double-precision floating point numbers.
Change generated from a taddr flows to a new taddr address, while change generated from a zaddr returns to itself.
When sending coinbase UTXOs to a zaddr, change is not allowed. The entire value of the UTXO(s) must be consumed.
Before Sapling activates, the maximum number of zaddr outputs is 54 due to transaction size limits
1. "fromaddress"          The taddr or zaddr to send the funds from.
2. "amount"              An array of json objects representing the amounts to send.
3. "toaddress"           The address is a taddr or zaddr
Result:
"operationid"          (string) An operationid to pass to z_getoperationstatus to get the result of the operation.
./src/moonroomcash-cli z_getoperationstatus (["operationid", ... ]) 
Result:
"    [object, ...]"      (array) A list of JSON objects
./src/moonroomcash-cli z_getoperationresult (["operationid", ... ]) 
Result:
"    [object, ...]"      (array) A list of JSON objects
./src/moonroomcash-cli listunspent
Returns array of unspent transaction outputs
./src/moonroomcash-cli listtransactions
Returns array of  transaction outputs in account
./src/moonroomcash-cli "moonroomcashaddress"
Returns the balance of a moonroomcashaddress (taddr or zaddr) belonging to the node’s wallet.
./src/moonroomcash-cli getbalance
Returns the node's total available balance
./src/moonroomcash-cli z_gettotalbalance 
Return the total amount  of moonroomcash (both t-address and z-address) stored in the node’s wallet.
Result:
{
  "transparent": xxxxx,     (numeric) the total balance of transparent funds
  "private": xxxxx,         (numeric) the total balance of private funds (in both Sprout and Sapling addresses)
  "total": xxxxx,           (numeric) the total balance of both transparent and private funds
}
./src/moonroomcash-cli getblock "blockhash" 
get serialized, hex-encoded data for the block
./src/moonroomcash-cli getblockchaininfo
Returns an object containing various state info regarding block chain processing. 
./src/moonroomcash-cli getpeerinfo
Returns data about each connected network node as a json array of objects.
./src/moonroomcash-cli getmempoolinfo
Returns details on the active state of the TX memory pool.

Result:
{
  "size": xxxxx                (numeric) Current tx count
  "bytes": xxxxx               (numeric) Sum of all tx sizes
  "usage": xxxxx               (numeric) Total memory usage for the mempool
}
 ./src/moonroomcash-cli  getdifficulty

Returns the proof-of-work difficulty as a multiple of the minimum difficulty
./src/moonroomcash-cli setgenerate true -1
Set 'generate' true to turn generation on
Generation is limited to 'genproclimit' processors, -1 is unlimited.
See the getgenerate call for the current setting.
./src/moonroomcash-cli setgenerate false
false to turn generation off.
./src/moonroomcash-cli dumpprivkey "t-addr"
Reveals the private key corresponding to 't-addr'.
./src/moonroomcash-cli backupwallet "/root/ws/moonroomcash-wallet-back-up"
give The full path of the destination file
./src/moonroomcash-cli encryptwallet "passphrase" 
WARNING: encryptwallet is disabled.
To enable it, restart zcashd with the -experimentalfeatures and
-developerencryptwallet commandline options, or add these two lines
to the moonroomcash.conf file:

experimentalfeatures=1
developerencryptwallet=1

Encrypts the wallet with 'passphrase'. This is for first time encryption.
./src/moonroomcash-cli dumpwallet "filename"
Dumps taddr wallet keys in a human-readable format.
./src/moonroomcash-cli gettransaction "txid"
Get detailed information about in-wallet transaction <txid>
./src/moonroomcash-cli importaddress "address"
Adds an address or script (in hex) that can be watched as if it were in your wallet but cannot be used to spend.
./src/moonroomcash-cli mportprivkey "moonroomcashprivkey"
Adds a private key (as returned by dumpprivkey) to your wallet.
./src/moonroomcash-cli  importwallet "filename" 
Imports taddr keys from a wallet dump file (see dumpwallet).
./src/moonroomcash-cli z_importkey "zkey"
Adds a zkey (as returned by z_exportkey) to your wallet.
./src/moonroomcash-cli z_importviewingkey "vkey"
Adds a viewing key (as returned by z_exportviewingkey) to your wallet.
./src/moonroomcash-cli z_importwallet "filename"
Imports taddr and zaddr keys from a wallet export file (see z_exportwallet).
./src/moonroomcash-cli z_exportkey "zaddr"
Reveals the zkey corresponding to 'zaddr'.
./src/moonroomcash-cli z_exportviewingkey "zaddr"
Reveals the viewing key corresponding to 'zaddr'.
./src/moonroomcash-cli z_exportwallet "filename"
Exports all wallet keys, for taddr and zaddr, in a human-readable format.
./src/moonroomcash-cli z_listunspent
Results are an array of Objects
./src/moonroomcash-cli z_listoperationids
Returns the list of operation ids currently known to the wallet.
```
 
