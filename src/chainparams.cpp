// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Odex developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
        (0, uint256("0x00000eec3130c1dae85736c987cd2e0443db34bab6c8aad364682a23d6950eaa"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1538006698,// * UNIX timestamp of last checkpoint block
    537501,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
        (0, uint256("0x00000ccb905aef2fbeca647eb7b27782fbacebab25ae16dc96bbedd6237d57a9"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1514516171,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest;
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xac;
        pchMessageStart[1] = 0x1e;
        pchMessageStart[2] = 0x7f;
        pchMessageStart[3] = 0xcf;
	    vAlertPubKey = ParseHex("04579f18934b3cdef394a9999e45506a1935662d0cd4e504d07beb53b8a1bfd78d81bee47e65119318397809420d5320e3c7b2aaae58580db48c38a4e6d4f0f919");
        nDefaultPort = 20149;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Odex starting difficulty is 1 / 2^12
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 90; // Odex: 1.5 minutes
        nTargetSpacingSlowLaunch = 5 * 90;  // Odex: 7.5 minutes (Slow launch - Block 300)
	    nTargetSpacing = 1 * 90; // Odex: 1.5min after block 300
        nLastPOWBlock = 530000;
	    nRampToBlock = 960; // Slow start, ramp linearly to this block
        nMaturity = 66; // 99 Minutes
	    nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
	    nMaxMoneyOut = 21525720 * COIN; // Year 2

        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "ODEX - Launch (12/28/2018)";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04243cdea79e117dba99d89a2da6ed761af43175227d19caaffea72398514962af9701478a69410b8158e190ae36d50a1f7325eba3df9559ad345db0cb72bfe2e2") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1546061079;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();;
        genesis.nNonce = 2091500;

  	    hashGenesisBlock = genesis.GetHash();

        /*
        if(genesis.GetHash() != uint256S("0x"))
        {
              printf("MSearching for genesis block...\n");
              uint256 hashTarget;
              hashTarget.SetCompact(genesis.nBits);
              while(uint256(genesis.GetHash()) > hashTarget)
              {
                  ++genesis.nNonce;
                  if (genesis.nNonce == 0)
                  {
                      printf("Mainnet NONCE WRAPPED, incrementing time");
                      std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
                      ++genesis.nTime;
                  }
                  if (genesis.nNonce % 10000 == 0)
                  {
                      printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                  }
              }
              printf("Mainnet block.nTime = %u \n", genesis.nTime);
              printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
              printf("Mainnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
              printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }
        */

        assert(hashGenesisBlock == uint256("0x00000c495edc842b693f7a1c4e3f512819b5ba62ba1b6a36e288720063984ace"));
        assert(genesis.hashMerkleRoot == uint256("0x58f218876870107a98ad658f229f1e3c724ef6db153acc89fff104feec3c5e97"));

        vSeeds.push_back(CDNSSeedData("149.28.57.251", "149.28.57.251"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 115); // b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 204);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

	    nPoolMaxTransactions = 3;
        strSporkKey = "0453748e298a34e32d760a3d64b7b517c952c10024a4160a3a746d9bce572f85e13ac6d4f518ac110ba807ce19fb657bc2696ca02013290e3fbe517adf09c95787";
        strObfuscationPoolDummyAddress = "bDiJwVuKv9dcKBN4KCfX6UmXbkpqLfzGyf";
        nStartMasternodePayments = 1511092620;

        /** Zerocoin */
        zerocoinModulus = "b2275261dcaa303374af30576c5f676c8c2f1596aae7814f932f08839d442a5b2f7eaac75ffe9481321cbaae1c48703eff"
            "384222885cf9e07e3996fa36d25f0866a7f3834c2457b253b0bbbd0ec23036fcc6c84886cce4d6bcc917ce7fb40d3ffcc12984db02e55e4e"
            "ccd205f7a239fe48ab27ea1124efa0a545ae434876b0b934ebcc54b03375c78bdbb1cde74c8e42048839e191f3986436f757c11d36b60942"
            "f6b88f40acbcd4b36d82890e05b6e508192873dee5be51352e7215fbca7dfe30daac0efd8435426313557b1d193be3fa3be8c3c81f5501e0"
            "52478afcfc1bd1f06ff429ecae3b682faa26bda5bb530fe1eca4d630fadc3b5d15e3d1feeeb161812894d3f17f497bb321c224f5419e30d2"
            "b79511979fa41d24bc78c0aa18e12dc668b164841ce56bc8de5b7386cff2bb314b11094a4ad5661a7fd7b517181f8a999e61ddadc6936262"
            "80b2692bc5b62bd328eb0b4c7d48b98942b0e6037add6568897f41adb825482057ae6224531047eef0cfd8f5510eb64e0610d83a1c7181";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee

        /** Staking Requirements */
        nStakeMinStartProtocol = 70850; // Starting protocol version (ActiveProtocol())
        nStakeMinConfirmations = 475; // Required number of confirmations
        nStakeMinAmount = 100 * COIN; // Minimum required staking amount
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xac;
        pchMessageStart[1] = 0xbd;
        pchMessageStart[2] = 0xef;
        pchMessageStart[3] = 0xca;

	    vAlertPubKey = ParseHex("0479ef3e7bfc6347248a901aca81dd6a9f3acdeb5272f1c831f5147b139a4e1bacaa253541d9ebdfba982fb5cc45df3e34a8e98cdce9329037f009af217bc64ed9");
        nDefaultPort = 21149;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 15; // 30 Seconds
        nTargetSpacing = 1 * 15;  // 30 Seconds
	    nTargetSpacingSlowLaunch = 1 * 15; // Kludgy but don't want to check for testnet each time in GetNextWorkRequired

        nLastPOWBlock = 200;
        nMaturity = 15;
        nMaxMoneyOut = 33284220 * COIN; // 2032 Maximum
        nRampToBlock = 100;

        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1537896086;
        genesis.nNonce = 2385723;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();

        hashGenesisBlock = genesis.GetHash();

        /*
        if(genesis.GetHash() != uint256S("0x"))
        {
              printf("MSearching for genesis block...\n");
              uint256 hashTarget;
              hashTarget.SetCompact(genesis.nBits);
              while(uint256(genesis.GetHash()) > hashTarget)
              {
                  ++genesis.nNonce;
                  if (genesis.nNonce == 0)
                  {
                      printf("Mainnet NONCE WRAPPED, incrementing time");
                      std::cout << std::string("Mainnet NONCE WRAPPED, incrementing time:\n");
                      ++genesis.nTime;
                  }
                  if (genesis.nNonce % 10000 == 0)
                  {
                      printf("Mainnet: nonce %08u: hash = %s \n", genesis.nNonce, genesis.GetHash().ToString().c_str());
                  }
              }
              printf("Mainnet block.nTime = %u \n", genesis.nTime);
              printf("Mainnet block.nNonce = %u \n", genesis.nNonce);
              printf("Mainnet block.hashMerkleRoot: %s\n", genesis.hashMerkleRoot.ToString().c_str());
              printf("Mainnet block.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        }
        */

        assert(hashGenesisBlock == uint256("0x00000ccb905aef2fbeca647eb7b27782fbacebab25ae16dc96bbedd6237d57a9"));
        assert(genesis.hashMerkleRoot == uint256("0x58f218876870107a98ad658f229f1e3c724ef6db153acc89fff104feec3c5e97"));

        vSeeds.push_back(CDNSSeedData("149.28.57.251", "149.28.57.251"));
        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("testnet01.mempool.pw", "testnet01.mempool.pw"));
        //vSeeds.push_back(CDNSSeedData("testnet02.mempool.pw", "testnet02.mempool.pw"));
        //vSeeds.push_back(CDNSSeedData("testnet03.mempool.pw", "testnet03.mempool.pw"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 140); // Testnet odex addresses start with 'T'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet odex script addresses start with '5' or '6'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet odex BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet odex BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet odex BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "048abad405bde958ad46d7eac0a359c80b001c3628cc1437a56420434ae6c2b4f1a18addd35a2e2b3c3bbe35d8b2bb6d387b4df3fac5156f92f8ded76f0cfc7a71";
        strObfuscationPoolDummyAddress = "TUQ57Fbh1crybrDhV6X9SDH95H4oSq4v6p";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        /** Staking Requirements */
        nStakeMinStartProtocol = 70850; // Starting protocol version (ActiveProtocol())
        nStakeMinConfirmations = 30; // Required number of confirmations
        nStakeMinAmount = 500 * COIN; // Minimum required staking amount
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xce;
        pchMessageStart[1] = 0xa3;
        pchMessageStart[2] = 0xfe;
        pchMessageStart[3] = 0xde;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Odex: 1 day
        nTargetSpacing = 1 * 60;        // Odex: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 22149;
//        assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 23149;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
