#pragma once
#include "externals/il2cpp-api.h"

struct FactorySaveData {
    static constexpr const char *fileName = "SaveData:/Lumi_Battle_Factory.bin";
    static constexpr const char *backupFileName = "SaveData:/Lumi_Battle_Factory_BK.bin";

    int32_t currentRound;
    FactoryLevel factoryLevel;
    int32_t currentStreakTrades;
    Pml::PokePara::SavePokeParty::Object currentTeam;
    Pml::PokePara::SavePokeParty::Object lastEnemyTeam;


    [[nodiscard]] long GetByteCount() const;

    long FromBytes(char* buffer, long buffer_size, long index);

    long ToBytes(char* buffer, long index);

    void Clear();

    [[nodiscard]] int32_t getRound() const;

    [[nodiscard]] FrontierRound getNowRound() const;

    void SerializePokeParty(Pml::PokeParty::Object* party, bool isPlayer = true);

    void DeserializePokeParty(Pml::PokeParty::Object* party, bool isPlayer = true);
};

void loadFactoryData(bool isBackup);

void saveFactoryData(bool isMain, bool isBackup);