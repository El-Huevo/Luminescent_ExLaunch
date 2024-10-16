#include "helpers/fsHelper.h"
#include "save/save.h"

long HallSaveData::GetByteCount() const {
    long count = 0;
    count += sizeof(Rank) * TYPE_COUNT;
    count += sizeof(int32_t);
    count += sizeof(int32_t);
    count += sizeof(BattleHallPool::PoolManager);
//    count += sizeof(bool) * 2;

    return count;
}

void HallSaveData::setRank(const char* type, Rank rank) {
    int32_t typeIndex = 0;//array_index(TYPES, type);
    currentRank[typeIndex] = rank;
}

Rank HallSaveData::getRank(const char* type) {
    int32_t typeIndex = 0;//array_index(TYPES, type);
    return currentRank[typeIndex];
}

void HallSaveData::Clear() {
    for (auto& rank : currentRank) {
        rank = RANK_1;
    }
    currentRound = 0;
    streakPokePID = -1;
    poolManager.initializeTypeLists();
}


int32_t HallSaveData::getRound() const {
    return currentRound;
}

long HallSaveData::FromBytes(char* buffer, long buffer_size, long index) {
    if (buffer_size >= GetByteCount() + index) {
        memcpy(&currentRank, (void*)(buffer + index), sizeof(Rank) * TYPE_COUNT);
        index += sizeof(Rank) * TYPE_COUNT;

        memcpy(&currentRound, (void*)(buffer + index), sizeof(int32_t));
        index += sizeof(int32_t);

        memcpy(&streakPokePID, (void*)(buffer + index), sizeof(uint32_t));
        index += sizeof(int32_t);

        memcpy(&poolManager, (void*)(buffer + index), sizeof(BattleHallPool::PoolManager));
        index += sizeof(BattleHallPool::PoolManager);

        return index;
    }
    return index + HallSaveData::GetByteCount();
}

long HallSaveData::ToBytes(char* buffer, long index) {
    memcpy((void*)(buffer + index), &currentRank, sizeof(Rank) * TYPE_COUNT);
    index += sizeof(Rank) * TYPE_COUNT;
    memcpy((void*)(buffer + index), &currentRound, sizeof(int32_t));
    index += sizeof(int32_t);
    memcpy((void*)(buffer + index), &streakPokePID, sizeof(int32_t));
    index += sizeof(int32_t);
    memcpy((void*)(buffer + index), &poolManager, sizeof(BattleHallPool::PoolManager));
    index += sizeof(BattleHallPool::PoolManager);
    Logger::log("[Battle Hall] Serialization complete.\n");

    return index;
}

nn::vector<std::pair<const char *, Rank>> HallSaveData::getAllTypeRanks() {
    nn::vector<std::pair<const char *, Rank>> ranks;
    int32_t index = 0;
    for (const auto& rank : currentRank) {
        ranks.emplace_back(TYPES[index], rank);
        ++index;
    }
    return ranks;
}

HallRound HallSaveData::getNowRound() const {
    return static_cast<HallRound>(currentRound % HALL_ROUND_COUNT);
}

void loadHallData(bool isBackup)
{
    if (!isBackup && FsHelper::isFileExist(getCustomSaveData()->battleHall.fileName))
    {
        long actualSize = FsHelper::getFileSize(getCustomSaveData()->battleHall.fileName);
        long expectedSize = getCustomSaveData()->battleHall.GetByteCount();
        long size = std::max(actualSize, expectedSize);
        FsHelper::LoadData data {
                .path = getCustomSaveData()->battleHall.fileName,
                .alignment = 0x1000,
                .bufSize = size,
        };
        FsHelper::loadFileFromPath(data);
        getCustomSaveData()->battleHall.FromBytes((char*)data.buffer, actualSize, 0);
        Logger::log("Loaded Lumi_Battle_Hall!\n");
    }
    else if (FsHelper::isFileExist(getCustomSaveData()->battleHall.backupFileName))
    {
        long actualSize = FsHelper::getFileSize(getCustomSaveData()->battleHall.backupFileName);
        long expectedSize = getCustomSaveData()->battleHall.GetByteCount();
        long size = std::max(actualSize, expectedSize);
        FsHelper::LoadData data {
                .path = getCustomSaveData()->battleHall.backupFileName,
                .alignment = 0x1000,
                .bufSize = size,
        };
        FsHelper::loadFileFromPath(data);
        getCustomSaveData()->battleHall.FromBytes((char*)data.buffer, actualSize, 0);
        Logger::log("Loaded Lumi_Battle_Hall_BK!\n");
    }
}

void saveHallData(bool isMain, bool isBackup) {
    char buffer[getCustomSaveData()->battleHall.GetByteCount()];
    getCustomSaveData()->battleHall.ToBytes((char*)buffer, 0);

    if (isMain) {
        FsHelper::writeFileToPath(buffer, sizeof(buffer), getCustomSaveData()->battleHall.fileName);
        //getCustomSaveData()->battleHall.hallPool->saveState();
    }
    if (isBackup)
        FsHelper::writeFileToPath(buffer, sizeof(buffer), getCustomSaveData()->battleHall.backupFileName);
}
/* Battle Hall ExeFS List */
// Done SaveData structure - [Functional]
// ToDo - Custom SetupTowerTrainer
// ToDo - Custom Script Commands
// ToDo - Pokemon Pool from JSON [Partially Functional]