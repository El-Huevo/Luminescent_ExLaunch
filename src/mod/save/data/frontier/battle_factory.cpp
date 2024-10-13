#include "helpers/fsHelper.h"
#include "save/save.h"


long FactorySaveData::GetByteCount() const {
    long count = 0;
    count += sizeof(int32_t);
    count += sizeof(FactoryLevel);
    count += sizeof(int32_t);
    count += Pml::PokePara::SavePokeParty::Object::GetByteCount() * 2;

    return count;
}


int32_t FactorySaveData::getRound() const {
    return currentRound;
}

FrontierRound FactorySaveData::getNowRound() const {
    return static_cast<FrontierRound>(currentRound % ROUND_COUNT);
}

void FactorySaveData::SerializePokeParty(Pml::PokeParty::Object* party, bool isPlayer) {
    system_load_typeinfo(0x6abb);
    system_load_typeinfo(0x6b0c);
    system_load_typeinfo(0x6baf);
    system_load_typeinfo(0x3f92);

    if (isPlayer) {
        party->SerializeFull(&currentTeam);
    }

    else {
        lastEnemyTeam.Serialize_Full(party);
    }

}

void FactorySaveData::DeserializePokeParty(Pml::PokeParty::Object* party, bool isPlayer) {
    system_load_typeinfo(0x6ab9);

    if (isPlayer) {
        party->DeserializeFull(&currentTeam);
    }

    else {
        lastEnemyTeam.Deserialize_Full(party);
    }
}

long FactorySaveData::FromBytes(char* buffer, long buffer_size, long index) {
    if (buffer_size >= GetByteCount() + index) {
        memcpy(&currentRound, (void*)(buffer + index), sizeof(int32_t));
        index += sizeof(int32_t);

        memcpy(&factoryLevel, (void*)(buffer + index), sizeof(FactoryLevel));
        index += sizeof(FactoryLevel);

        memcpy(&currentStreakTrades, (void*)(buffer + index), sizeof(int32_t));
        index += sizeof(int32_t);

        for (uint64_t i = 0; i < 2; i++) {
            auto pokeParams = (Pml::PokePara::SerializedPokemonFull::Array*)system_array_new(
                    Pml::PokePara::SerializedPokemonFull_array_TypeInfo(), 6);
            for (uint64_t j = 0; j < 6; j++)
            {
                void* pokeData = (void*)(buffer+index);
                auto pokeByteArray = (System::Byte_array*)system_array_new(
                        System::Byte_array_TypeInfo(),
                        Pml::PokePara::SerializedPokemonFull::GetByteCount());
                memcpy(pokeByteArray->m_Items, pokeData, Pml::PokePara::SerializedPokemonFull::GetByteCount());
                pokeParams->m_Items[j].fields.buffer = pokeByteArray;
                pokeParams->m_Items[j].CreateWorkIfNeed();
                index += Pml::PokePara::SerializedPokemonFull::GetByteCount();
            }
            auto target = (i == 0) ? currentTeam.fields.members : lastEnemyTeam.fields.members;

            memcpy(&target, (void*)pokeParams, Pml::PokePara::SerializedPokemonFull::GetByteCount()*6);

            auto memberCount = (i == 0) ? currentTeam.fields.memberCount : lastEnemyTeam.fields.memberCount;
            memcpy(&memberCount, (void*)(buffer+index), sizeof(uint8_t));
            index+= sizeof(uint8_t);

            auto markingIndex = (i == 0) ? currentTeam.fields.markingIndex : lastEnemyTeam.fields.markingIndex;
            memcpy(&markingIndex, (void*)(buffer+index), sizeof(uint8_t));
            index+= sizeof(uint8_t);

        }
        return index;
    }
    return index + FactorySaveData::GetByteCount();
}

long FactorySaveData::ToBytes(char* buffer, long index) {

    memcpy((void*)(buffer+index), &currentRound, sizeof(int32_t));
    index += sizeof(int32_t);

    memcpy((void*)(buffer+index), &factoryLevel, sizeof(FactoryLevel));
    index += sizeof(FactoryLevel);

    memcpy((void*)(buffer+index), &currentStreakTrades, sizeof(int32_t));
    index += sizeof(int32_t);

    Logger::log("[ToBytes] Beginning loop.\n");
    for (uint64_t i=0; i<2; i++)
    {
        auto serializedPoke = (i == 0) ?
                currentTeam.fields.members : lastEnemyTeam.fields.members;

        for (uint64_t j=0; j<6; j++)
        {
            Logger::log("[ToBytes] Pokemon %d.\n", j);
            auto pokeByteArray = serializedPoke->m_Items[j].fields.buffer;
            void* pokeData = (void*)(buffer+index);
            memcpy(pokeData, (void*)pokeByteArray->m_Items, Pml::PokePara::SerializedPokemonFull::GetByteCount());
            index += Pml::PokePara::SerializedPokemonFull::GetByteCount();
        }

        auto memberCount = (i == 0) ? currentTeam.fields.memberCount : lastEnemyTeam.fields.memberCount;
        memcpy((void*)(buffer+index), &memberCount, sizeof(uint8_t));
        index+= sizeof(uint8_t);

        auto markingIndex = (i == 0) ? currentTeam.fields.markingIndex : lastEnemyTeam.fields.markingIndex;
        memcpy((void*)(buffer+index), &markingIndex, sizeof(uint8_t));
        index+= sizeof(uint8_t);
    }

    Logger::log("[ToBytes - Battle Factory] Serialization complete.\n");

    return index;
}

void FactorySaveData::Clear() {
    currentRound = 0;
    factoryLevel = FactoryLevel::NOT_SET;
    currentStreakTrades = 0;
    currentTeam.Clear();
    lastEnemyTeam.Clear();
}

void loadFactoryData(bool isBackup)
{
    if (!isBackup && FsHelper::isFileExist(getCustomSaveData()->battleFactory.fileName))
    {
        long actualSize = FsHelper::getFileSize(getCustomSaveData()->battleFactory.fileName);
        long expectedSize = getCustomSaveData()->battleFactory.GetByteCount();
        long size = std::max(actualSize, expectedSize);
        FsHelper::LoadData data {
                .path = getCustomSaveData()->battleFactory.fileName,
                .alignment = 0x1000,
                .bufSize = size,
        };
        getCustomSaveData()->battleFactory.Clear();
        FsHelper::loadFileFromPath(data);
        getCustomSaveData()->battleFactory.FromBytes((char*)data.buffer, actualSize, 0);
        Logger::log("Loaded Lumi_Battle_Factory!\n");
    }
    else if (FsHelper::isFileExist(getCustomSaveData()->battleFactory.backupFileName))
    {
        long actualSize = FsHelper::getFileSize(getCustomSaveData()->battleFactory.backupFileName);
        long expectedSize = getCustomSaveData()->battleFactory.GetByteCount();
        long size = std::max(actualSize, expectedSize);
        FsHelper::LoadData data {
                .path = getCustomSaveData()->battleFactory.backupFileName,
                .alignment = 0x1000,
                .bufSize = size,
        };
        getCustomSaveData()->battleFactory.Clear();
        FsHelper::loadFileFromPath(data);
        getCustomSaveData()->battleFactory.FromBytes((char*)data.buffer, actualSize, 0);
        Logger::log("Loaded Lumi_Battle_Factory_BK!\n");
    }
}

void saveFactoryData(bool isMain, bool isBackup) {
    char buffer[getCustomSaveData()->battleFactory.GetByteCount()];
    getCustomSaveData()->battleFactory.ToBytes((char*)buffer, 0);

    if (isMain) {
        FsHelper::writeFileToPath(buffer, sizeof(buffer), getCustomSaveData()->battleFactory.fileName);
    }
    if (isBackup)
        FsHelper::writeFileToPath(buffer, sizeof(buffer), getCustomSaveData()->battleFactory.backupFileName);
}