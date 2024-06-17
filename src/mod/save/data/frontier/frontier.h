#pragma once
#include "externals/il2cpp-api.h"
#include "data/types.h"
#include "data/frontier.h"
#include "data/utils.h"


struct HallSaveData {
    static constexpr const char *fileName = "SaveData:/Lumi_Battle_Hall.bin";
    static constexpr const char *backupFileName = "SaveData:/Lumi_Battle_Hall_BK.bin";

    Rank currentRank[TYPE_COUNT];
    int32_t currentRound;
//    bool silverSealObtained; //ToDo
//    bool goldSealObtained; //ToDo

    long GetByteCount();

    long FromBytes(char* buffer, long buffer_size, long index);

    long ToBytes(char* buffer, long index);

    void setRank(const char* type, Rank rank);

    Rank getRank(const char* type);

    void Clear();

    void setRound(int32_t round = 1);

    [[nodiscard]] int32_t getRound() const;

    nn::vector<std::pair<const char*, Rank>> getAllTypeRanks();

};

void loadHallData(bool isBackup);

void saveHallData(bool isMain, bool isBackup);