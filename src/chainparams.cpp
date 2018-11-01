// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "main.h"
#include "crypto/equihash.h"

#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "base58.h"

#include "chainparamsseeds.h"

#include <mutex>
#include "metrics.h"
#include "crypto/equihash.h"
static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, const uint256& nNonce, const std::vector<unsigned char>& nSolution, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 520617983 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nSolution = nSolution;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = genesis.BuildMerkleTree();
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database (and is in any case of zero value).
 *
 * >>> from pyblake2 import blake2s
 * >>> 'Moonroomcash' + blake2s(b'TODO').hexdigest()
 *
 * CBlock(hash=00052461, ver=4, hashPrevBlock=00000000000000, hashMerkleRoot=94c7ae, nTime=1516980000, nBits=1f07ffff, nNonce=6796, vtx=1)
 *   CTransaction(hash=94c7ae, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff071f0104455a6361736830623963346565663862376363343137656535303031653335303039383462366665613335363833613763616331343161303433633432303634383335643334)
 *     CTxOut(nValue=0.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 94c7ae
 */
static CBlock CreateGenesisBlock(uint32_t nTime, const uint256& nNonce, const std::vector<unsigned char>& nSolution, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Moonroomcash27af64c90c1d8592312e4332d7b7b617353ae303d14380fab06c2bff70e08977";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nSolution, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

const arith_uint256 maxUint = UintToArith256(uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        strCurrencyUnits = "MRC";
        consensus.fCoinbaseMustBeProtected = true;
        consensus.nSubsidySlowStartInterval = 5000;
        consensus.nSubsidyHalvingInterval = 657850; // 2.5 years
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 4000;
        consensus.powLimit = uint256S("0007ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nDigishieldAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nDigishieldAveragingWindow);
        consensus.nDigishieldMaxAdjustDown = 32; // 32% adjustment down
        consensus.nDigishieldMaxAdjustUp = 16; // 16% adjustment up
        consensus.nPowTargetSpacing = 2 * 60;
        consensus.zawyLWMAHeight = 125000;
        consensus.nZawyLWMAAveragingWindow = 60;
        /**
         * The message start string should be awesome! ⓩ❤
         */
        pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0xe1;
        pchMessageStart[2] = 0xbe;
        pchMessageStart[3] = 0xd0;
        vAlertPubKey = ParseHex("04025b2cf3a116782a69bb68cb4ae5ba3b7f05069f7139b75573dd28e48f8992d95c118122b618d4943456ad64e7356b0b45b2ef179cbe3d9767a2426662d13d32"); //Zel Technologies
        nDefaultPort = 16225;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 100000;
        eh_epoch_1 = eh200_9;
        eh_epoch_2 = eh144_5;
        eh_epoch_1_endblock = 125110;
        eh_epoch_2_startblock = 125100;


       genesis = CreateGenesisBlock(
            1538630820,
            uint256S("0x00000000000000000000000000000000000000000000000000000000000001ae"),
            ParseHex("0015d4077f93f9ed16c5d32998232f66b5c99d850404ce1785abe3ffd3e35dc92bdcf40512992936a93d03952e082592328eb45b661b35c5c3b386b11e491c3fae43417a7253f9a0db24b42943e14dcc01387b050adb46b12a88f51ae841c0e7410971916a6ed1683f343c637dd0e2e1455933e72170e591a9fe9f734ad10e6971c7220d29148abf713f143f28d3045739fbad26b8a4bd8b5d6fc4f2a005c49060eb0dc83779b8a104cf2dddabca98a79238e2de637f19a29ca716ba2f08431f0e32271f6dfc8714b93e42f4dabf683725c7169786b9ccd3f00328a7c436063e22edbe3597c23728153c27f0d89d52d5e933c315230fae144df8f99c0d260de63def415df55b121069b42dbc90c5d6bcdf1a8f75b5dc22fbcf2b73348fb06aa91a08d15324ca0fd417862d5310fedc64a4134963595ac149b7fa736d04e718071cfb77d8bf3a2e1c5e12832c09fd33d1019191d968b92bb3dd0740b5c07cbaf831af1a7b744392de292babfbf5a6a8e7489abd19e7a22d5f89bc12d7fe28e82bc901bfdef3cf10ac8da6b6a83723462413caecce115803040465411dc7f36ab4cf3652fe0b85f673df5b4879f414b37dc1b211157e6fcf2aa31da45b3a99107678a378530ca4c0b0a91739691ddf0fedb9af55da74af6b92e8527fe04b9ad6651c03fa1ca913419f07d10d2e4e334bcbe855c99188396aad0577da87abcc4a6cc93e234dcdaa212288279f0b6f452e93e0e4ab036f5943e53ba56ace3e7c7e3ec57909d8f1e04ee08b632276b30e61d6bd6d22d8105058119bc974f9ba15efd6241347df4c1d1104c16d086411a4563e57083830f34ef26a4d9b402cdd26d605c22289fd09b3339373a352732ae522410ae099daad272bc697594721fdb56b88f32f6b2fae3e720057a727338d565bb68ea6fd47920352b167b4def5d8fbd7660290fbcc8255d277571882ff4fd35d6ce39a8c097f2beb44db880faeb3c3ef181597dd8c0311669975ed0421eb15a18386b71532b057991698c2c22c5f5d7f226a3d7994610983f109941dbc5ea301d7053a14790840be54ff845c18c02a838eb3c4590d7cf832d3be201027322219497192b7c7166be3b49219169371e01cd36bbf4861b16d834f6367674f955a1777bfac832f06b2de585f996de87e959038ff4f0b1e951f651104bb3286aa9145e5c72dc4afd07f15156512118b681e87bd2d0855fc2141ad23b4263eb9d257ec3dbb2533b8d69112a80841b586a3bed04e3db166dfcf1a7a3ee1bcc4b9105d35c286949b16ee65299e5294760304d7ffb9f59313619a3101dbed4259a64a769faac46a201365e5def50d1c33f6ea23d54b5a475ab9d76d29ca8fed25232c99427b15f42ebeb732147fd5573e55750b35c1172fb5771975ade6f78271987f11fbc803bc33370988f1b12aecb1d5595b220db3c89759a2259479bc245553b38b5da448173f522561029a983405a9a9a94fdd1d6315b563c86ed5168528bfaf816f4193d38700ed7009f907b5de364c5e92e27d3974960f669e673ac97a389e13d8b0c45f1ed293ee5e5d5013dc567ae30aa1706fc8b304ccfad330eff6bc8cf01b2fcf5eaadffb7f4280444078c0283d81a9d27a704d979c72d25de7c5fbe057f4e670c4df1c453b0aef08758f9dbd5615975bd8e19ba6b9640aa055dfd03e29c53d29ead0426fe266b557583d27ab88ca1d9d2c223bd46c399584bb12b1826f91a0fd497f33547f842d1c2600f61079a2a356d429c4c1aa192f8e389db9256d1d852a5f129b017078277ce9725eed7bffd6a641ff239333abdfa3f8b605d9dffd144ace2cf711fd319811b42755178d6a60c55b8af17feac4489c701d6298e762a75dc4a3e0ea06371dcfb159926918bf24"),
            0x1f07ffff, 4, 0);
        consensus.hashGenesisBlock = genesis.GetHash();

         printf("%s\n", consensus.hashGenesisBlock.ToString().c_str());
	 printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        
        assert(consensus.hashGenesisBlock == uint256S("0x000272d593a07f8e7f007b78de1007d8af501d83572025c4f0a5dc450cab3afd"));
        assert(genesis.hashMerkleRoot == uint256S("0x580724d528874c3de0249b10700ad1889900cc5d106a7a5a1c175427a18708f2"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("moonroomcash.tech", "dnsseed.moonroomcash.tech")); // Moonroomcash
        /////vSeeds.push_back(CDNSSeedData("node.zel.cash", "seed.zel.cash")); // Moonroomcash
        ///////vSeeds.push_back(CDNSSeedData("node1.zel.cash", "dns.zel.cash")); // Moonroomcash
        vSeeds.push_back(CDNSSeedData("vps.moonroomcash.online", "dnsseed.moonroomcash.online")); 

        // guarantees the first 2 characters, when base58 encoded, are "M1"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x0B,0x43};
        // guarantees the first 2 characters, when base58 encoded, are "M3"
        base58Prefixes[SCRIPT_ADDRESS]     ={0x0A,0xBD};
        // the first character, when base58 encoded, is "5" or "K" or "L" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0x80};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x88,0xB2,0x1E};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x88,0xAD,0xE4};
        // guarantees the first 2 characters, when base58 encoded, are "zc"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0x9A};
        // guarantees the first 4 characters, when base58 encoded, are "ZiVK"
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAB,0xD3};
        // guarantees the first 2 characters, when base58 encoded, are "SK"
        base58Prefixes[ZCSPENDING_KEY]     = {0xAB,0x36};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, consensus.hashGenesisBlock), //Halep won French Open 2018
            1538630820,     // * UNIX timestamp of last checkpoint block
            0,              // * total number of transactions between genesis and last checkpoint
                            //   (the tx=... number in the SetBestChain debug.log lines)
            1            // * estimated number of transactions per day
                            //   total number of tx / (checkpoint block height / (24 * 24))
        };

    }
};
static CMainParams mainParams;

/**
 * Testnet (v4)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        strCurrencyUnits = "TMRC";
        consensus.fCoinbaseMustBeProtected = true;
        consensus.nSubsidySlowStartInterval = 5000;
        consensus.nSubsidyHalvingInterval = 657850; // 2.5 years
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 400;
        consensus.powLimit = uint256S("07ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nDigishieldAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nDigishieldAveragingWindow);
        consensus.nDigishieldMaxAdjustDown = 32; // 32% adjustment down
        consensus.nDigishieldMaxAdjustUp = 16; // 16% adjustment up
        consensus.nPowTargetSpacing = 2 * 60;
        consensus.zawyLWMAHeight = 500;
        consensus.nZawyLWMAAveragingWindow = 60;
        pchMessageStart[0] = 0xf2;
        pchMessageStart[1] = 0xcd;
        pchMessageStart[2] = 0x63;
        pchMessageStart[3] = 0xbf;
        vAlertPubKey = ParseHex("044b5cb8fd1db34e2d89a93e7becf3fb35dd08a81bb3080484365e567136403fd4a6682a43d8819522ae35394704afa83de1ef069a3104763fd0ebdbdd505a1386"); //Zel Technologies
        nDefaultPort = 26225;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 1000;
        eh_epoch_1 = eh200_9;
        eh_epoch_2 = eh144_5;
        eh_epoch_1_endblock = 610;
        eh_epoch_2_startblock = 600;

        genesis = CreateGenesisBlock(
            1538632470,
            uint256S("0x000000000000000000000000000000000000000000000000000000000000002a"),
            ParseHex("0059a036765996eda2d700f8abb24862709a3ae39824723dc943cae34664b976f03f75bff9bf772e4cad02bbf0fc1651c7acc65af111c4892f9493cbcfa714301f9267cfdebf81d9a60314277fe4e5850b34063f011aa6efcfc06269d02d4135bb488911c9333681c30d6eaf1139145b25e40563d50cbc2105e6f5ff1eb5054a89f2121742e1724690c347b4f1a2095554aa9a10dcf62ebcdaa781c1e734b60356110a79c89578fb03eae29d76caed92d67d80533e8cdad95914cdd9cd324a0bc99992a1f6b9fbd8dfbe6fdf16706c3f7f1204d09ee0b9f32499cfe781e9db7b9cfcec8d506b6305d9454860da0935969c60f405d654d05ff652a00505e707a7b1894b25e47651c55b4c535e01247ca833308b42766ae429eb2650578fbd6d646a4142b824511993dd4468dda06d9371350054ac9b6e730c1b1a76370a1e950ede106528d204f5d6dbbe39dfa4bc0ce900c9e1bba5df1819f6c1224cffd11d2561e3f4b9441259c2241cd8ff874440b583e2c0b29b6ed5df34151cc116772355948126066502edabb4933f4e9d53801f3446c62c49e4a2c78ef2990e6dd57d1bbc9cceb8019e6827e751285dc5bd17598ed3fb9334c97ac4aa16b962d2435fac2bb31e52f31bacfbc988460e17f72404533735e4762b843c46b4f6ca18ea45f1f9b5c835067b36ec5704c8ee0033996d9f1e69e4283abcc30765583f90e02471a3ce208c25410fb1aeaa95cad7150d17e4ff0c385d91f9f4878568211a0f7071f8b324c63e7234d803e19474f26ac248690672ce93baf83acc75019f1802bf1330c41fa16def8157fc4b881c182d728af19511bbe48653791dc29055fef933f39427ce49b41f621d49a185c524ace7f005b98aedffb018a4e1d95448911a4ea0319159bc6490b434c897c33d44df2e289c51fd63743832b0f5f7e215a2f8f4890071570034afcc0fa45063ae7abe90e9a33432846f18ee7a11b3e445078251c7a7e14658c6b731db2c7504149e68ac030aedacdaa498e1df73e938e1d948a00f560369a99a9295b69011f2c060b02e1c915384c70355f8e7f397247d4c9a35152a3a25f321b2f9b77d1b83d19de2e5e92d32ca64bd517011d6f56d9f0e6b0556d55dea3612abd932e0dda216d5d3337f3c85284837f2ccfce7f8a5b541689ecffedd066fafd55f2d017d73eb31a55857b75333e84341e2ee8c9674eac00bfda076664ee371255fc1492810296975823a138d1a7633d6ac6ebb2fcc9324df05f2678e7eb43e1d8b6677ce376a223333ca8bcaa2ae6e7cb7318ab9dac406b5ff10449c59813f0dc298a51b053d0749b5d4823afabce80e99573b5f6d64480d77c26146d6ae5baa12dfeec3ffdd5f3f47e3a8b689462ce6a2755d7ecf156dec8888c933446c2d17377dcaac7fd3423f85860522a92d90899ec7788e14377df0c2d51a80dda82c17336acdc0109df30b6e570c623f0849eacad6ad68070471f97d20f483d542117eb9452e4919da130bd22f52b983850f1c80f0bff4a9f148d621abcff348530bebdeff7949b9351cde14d49563eba5600d3601b21e1ed2c4ac5933c188ee334805f04f5d215f7eb0d313baed0b3a50b40f4604c4c424e308196bf17744555d0c5bc14266d743e35777f7d0ec03bb25797fbc8809a9daebae52fe4399c66a3004eea80f9d01be825634bf731d694d65a2fed333ab527e8b2652b8f2b7b20d09ffe4fa1c21d36332b0dace0ad5c8de595a32e3107cae6eee5814e4d2307469f3faa8f6e9b3780f040b374874cd48d2e76985210301127c91342c2c63891ebf4f1309771f85e74f541a36735a59e113949ff61a2fb27ad5334c91e892127dcf6ccc1228cbd9ddd32917a5b2585a81b90694a71a815d70ce6809bd26d9"),
            0x2007ffff, 4, 0);
        
        consensus.hashGenesisBlock = genesis.GetHash();
     
         printf("%s\n", consensus.hashGenesisBlock.ToString().c_str());
	 printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());

        assert(consensus.hashGenesisBlock == uint256S("0x011ae326d56c0c8260415a9c0d9637d745707954ed03907cc524010e6dac93f6"));
        assert(genesis.hashMerkleRoot == uint256S("0x580724d528874c3de0249b10700ad1889900cc5d106a7a5a1c175427a18708f2"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("vps.testnet.moonroomcash.online", "dnsseedtestnet.moonroomcash.online")); // TheTrunk

        // guarantees the first 2 characters, when base58 encoded, are "m1"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x18,0xC7};
        // guarantees the first 2 characters, when base58 encoded, are "m2"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x18,0xCC};
        // the first character, when base58 encoded, is "9" or "c" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0xEF};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x35,0x87,0xCF};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x35,0x83,0x94};
        // guarantees the first 2 characters, when base58 encoded, are "zt"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0xB6};
        // guarantees the first 4 characters, when base58 encoded, are "ZiVt"
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAC,0x0C};
        // guarantees the first 2 characters, when base58 encoded, are "ST"
        base58Prefixes[ZCSPENDING_KEY]     = {0xAC,0x08};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, consensus.hashGenesisBlock),
            1538632470,  // * UNIX timestamp of last checkpoint block
            0,           // * total number of transactions between genesis and last checkpoint
                         //   (the tx=... number in the SetBestChain debug.log lines)
            1          // * estimated number of transactions per day after checkpoint 720 newly mined +30 for txs that users are doing
                         //   total number of tx / (checkpoint block height / (24 * 24))
        };
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test TODO
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        strCurrencyUnits = "REG";
        consensus.fCoinbaseMustBeProtected = false;
        consensus.nSubsidySlowStartInterval = 0;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f");
        consensus.nDigishieldAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nDigishieldAveragingWindow);
        consensus.nDigishieldMaxAdjustDown = 0; // Turn off adjustment down
        consensus.nDigishieldMaxAdjustUp = 0; // Turn off adjustment up
        consensus.nPowTargetSpacing = 2 * 60;
        consensus.zawyLWMAHeight = 1;
        consensus.nZawyLWMAAveragingWindow = 60;

        pchMessageStart[0] = 0xab;
        pchMessageStart[1] = 0xe6;
        pchMessageStart[2] = 0x3d;
        pchMessageStart[3] = 0x5d;
        nDefaultPort = 26226;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 1000;
        eh_epoch_1 = eh48_5;
        eh_epoch_2 = eh48_5;
        eh_epoch_1_endblock = 1;
        eh_epoch_2_startblock = 1;

        genesis = CreateGenesisBlock(
             1538633050,
            uint256S("0000000000000000000000000000000000000000000000000000000000000012"),
            ParseHex("068e4e6cb77fab53e6613f1d918dcf0789d514578ab3b3555e533037e4d430b513dea79d"),
            0x200f0f0f, 4, 0);

        consensus.hashGenesisBlock = genesis.GetHash();
  
 printf("%s\n", consensus.hashGenesisBlock.ToString().c_str());
	 printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());


        assert(consensus.hashGenesisBlock == uint256S("0x011350768b90b59398338712ad2a9aa756a2beae8115421c3b6e82e114074b68"));
        assert(genesis.hashMerkleRoot == uint256S("0x580724d528874c3de0249b10700ad1889900cc5d106a7a5a1c175427a18708f2"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("580724d528874c3de0249b10700ad1889900cc5d106a7a5a1c175427a18708f2")),
            0,
            0,
            0
        };
        // These prefixes are the same as the testnet prefixes
        base58Prefixes[PUBKEY_ADDRESS]     =  {0x18,0xC7};
        base58Prefixes[SCRIPT_ADDRESS]     =  {0x18,0xCC};
        base58Prefixes[SECRET_KEY]         = {0xEF};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x35,0x87,0xCF};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x35,0x83,0x94};
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0xB6};
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAC,0x0C};
        base58Prefixes[ZCSPENDING_KEY]     = {0xAC,0x08};
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);

    // Some python qa rpc tests need to enforce the coinbase consensus rule
    if (network == CBaseChainParams::REGTEST && mapArgs.count("-regtestprotectcoinbase")) {
        regTestParams.SetRegTestCoinbaseMustBeProtected();
    }
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}


// Block height must be >0 and <=last founders reward block height
// Index variable i ranges from 0 - (vFoundersRewardAddress.size()-1)
std::string CChainParams::GetFoundersRewardAddressAtHeight(int nHeight) const {
    int maxHeight = consensus.GetLastFoundersRewardBlockHeight();
    assert(nHeight > 0 && nHeight <= maxHeight);

    size_t addressChangeInterval = (maxHeight + vFoundersRewardAddress.size()) / vFoundersRewardAddress.size();
    size_t i = nHeight / addressChangeInterval;
    return vFoundersRewardAddress[i];
}

// Block height must be >0 and <=last founders reward block height
// The founders reward address is expected to be a multisig (P2SH) address
CScript CChainParams::GetFoundersRewardScriptAtHeight(int nHeight) const {
    assert(nHeight > 0 && nHeight <= consensus.GetLastFoundersRewardBlockHeight());

    CBitcoinAddress address(GetFoundersRewardAddressAtHeight(nHeight).c_str());
    assert(address.IsValid());
    assert(address.IsScript());
    CScriptID scriptID = boost::get<CScriptID>(address.Get()); // Get() returns a boost variant
    CScript script = CScript() << OP_HASH160 << ToByteVector(scriptID) << OP_EQUAL;
    return script;
}

std::string CChainParams::GetFoundersRewardAddressAtIndex(int i) const {
    assert(i >= 0 && i < vFoundersRewardAddress.size());
    return vFoundersRewardAddress[i];
}

int validEHparameterList(EHparameters *ehparams, unsigned long blockheight, const CChainParams& params){
    //if in overlap period, there will be two valid solutions, else 1.
    //The upcoming version of EH is preferred so will always be first element
    //returns number of elements in list
    if(blockheight>=params.eh_epoch_2_start() && blockheight>params.eh_epoch_1_end()){
        ehparams[0]=params.eh_epoch_2_params();
        return 1;
    }
    if(blockheight<params.eh_epoch_2_start()){
        ehparams[0]=params.eh_epoch_1_params();
        return 1;
    }
    ehparams[0]=params.eh_epoch_2_params();
    ehparams[1]=params.eh_epoch_1_params();
    return 2;
}
