
#include <random>
#include "BattleHallPool.h"
#include "externals/FlagWork.h"
#include "externals/FlagWork_Enums.h"


static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::mt19937 rng(seed);

const char* frontierFolderPath = "rom:/Data/ExtraData/Frontier";

BattleHallPool::BattleHallPool() {
    loadTypeMapping();  // Load the type mapping from JSON
}

frontierIndex BattleHallPool::indexLookup(int32_t monsNo, int32_t group) {
    nn::string frontierFilePath(frontierFolderPath);

    switch (group) {
        case 1: {
            frontierFilePath.append("/Group_1.json");
            Logger::log("[Frontier] File Path: %s\n", frontierFilePath.c_str());
            break;
        }

        case 2: {
            frontierFilePath.append("/Group_2.json");
            Logger::log("[Frontier] File Path: %s\n", frontierFilePath.c_str());
            break;
        }

        default: {
            break;
        }
    }

    nn::json j = FsHelper::loadJsonFileFromPath(frontierFilePath.c_str());

    if (j != nullptr && !j.is_discarded()) {
        for (const auto& item : j) {
            if (item.at("monsNo").get<int>() == monsNo) {
                return item.get<frontierIndex>();
            }
        }
    }
    else {
        Logger::log("Error when parsing !\n");
    }
}

int32_t BattleHallPool::calculateBST(int32_t rank) {
    int32_t BST;
    std::uniform_int_distribution<int32_t> distribution(1, 2);
    int32_t randNo = distribution(rng);
    switch (rank) {

        case (1) ... (2): {
            BST = 1;
            break;
        }
        case (3) ... (5): {
            BST = (randNo == 1) ? 1 : 2;
            break;
        }
        case (6) ... (8): {
            BST = (randNo == 1) ? 2 : 3;
            break;
        }
        case (9) ... (10): {
            BST = (randNo == 1) ? 3 : 4;
            break;
        }
        default: {
            Logger::log("[HallPoke] Rank %d out of bounds, returning BST = 1\n", rank);
            return 1;
        }
    }
    Logger::log("[HallPoke] Current BST: %d\n", BST);
    return BST;
}

int8_t BattleHallPool::calculateEnemyLvl(int32_t rank) {
    int32_t pLvl = 50; // Todo Dynamic Lvl
    double lvlBase = pLvl - (3 * sqrt(pLvl));
    int32_t currentTypeRank = rank;
    double types = 17;
    double increment = sqrt(pLvl) / 5;
    double oLvlCalc = lvlBase + (types / 2) + (currentTypeRank - 1) * increment;
    return (int8_t) fmin(pLvl, round(oLvlCalc));
}
