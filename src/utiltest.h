// Copyright (c) 2016 The Zcash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "wallet/wallet.h"
#include "moonroomcash/JoinSplit.hpp"
#include "moonroomcash/Note.hpp"
#include "moonroomcash/NoteEncryption.hpp"

CWalletTx GetValidReceive(ZCJoinSplit& params,
                          const libmoonroomcash::SpendingKey& sk, CAmount value,
                          bool randomInputs);
libmoonroomcash::Note GetNote(ZCJoinSplit& params,
                       const libmoonroomcash::SpendingKey& sk,
                       const CTransaction& tx, size_t js, size_t n);
CWalletTx GetValidSpend(ZCJoinSplit& params,
                        const libmoonroomcash::SpendingKey& sk,
                        const libmoonroomcash::Note& note, CAmount value);
