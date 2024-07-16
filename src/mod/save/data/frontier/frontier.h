#pragma once
#include "externals/il2cpp-api.h"
#include "data/types.h"
#include "data/frontier.h"
#include "data/utils.h"
#include "features/frontier/BattleHall/BattleHallPool.h"
#include "externals/FlagWork_Enums.h"
#include "externals/FlagWork.h"
#include "features/frontier/BattleHall/PoolManager.h"

struct HallSaveData {
    static constexpr const char *fileName = "SaveData:/Lumi_Battle_Hall.bin";
    static constexpr const char *backupFileName = "SaveData:/Lumi_Battle_Hall_BK.bin";

    Rank currentRank[TYPE_COUNT]{};
    int32_t currentRound;
    int32_t streakPokePID;
    BattleHallPool::PoolManager poolManager;
//    bool silverSealObtained; //ToDo
//    bool goldSealObtained; //ToDo

    long GetByteCount() const;

    long FromBytes(char* buffer, long buffer_size, long index);

    long ToBytes(char* buffer, long index);

    void setRank(const char* type, Rank rank);

    Rank getRank(const char* type);

    void Clear();

    [[nodiscard]] int32_t getRound() const;

    [[nodiscard]] HallRound getNowRound() const;

    nn::vector<std::pair<const char*, Rank>> getAllTypeRanks();

};

void loadHallData(bool isBackup);

void saveHallData(bool isMain, bool isBackup);