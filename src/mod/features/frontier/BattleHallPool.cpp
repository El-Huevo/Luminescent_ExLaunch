
#include <random>
#include <fstream>
#include "BattleHallPool.h"
#include "externals/FlagWork.h"
#include "externals/FlagWork_Enums.h"
#include "data/frontier.h"


static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::mt19937 rng(seed);

const char* frontierFolderPath = "rom:/Data/ExtraData/Frontier";

frontierIndex BattleHallPool::indexLookup(int32_t monsNo, Group groupNo) {
    nn::string frontierFilePath(frontierFolderPath);

    switch (groupNo) {
        case GROUP_1: {
            frontierFilePath.append("/Group_1.json");
            Logger::log("[Frontier] File Path: %s\n", frontierFilePath.c_str());
            break;
        }

        case GROUP_2: {
            frontierFilePath.append("/Group_2.json");
            Logger::log("[Frontier] File Path: %s\n", frontierFilePath.c_str());
            break;
        }
        case GROUP_3: {
            frontierFilePath.append("/Group_3.json");
            Logger::log("[Frontier] File Path: %s\n", frontierFilePath.c_str());
            break;
        }
        case GROUP_4: {
            frontierFilePath.append("/Group_4.json");
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

nn::string appendJsonPath(const nn::string& path) {
    nn::string frontierFilePath(frontierFolderPath);
    frontierFilePath.append(path);
    return frontierFilePath;
}

nn::vector<int32_t> BattleHallPool::getTypeMapping(const nn::string& type) {
    nn::json j = FsHelper::loadJsonFileFromPath(appendJsonPath("/hall_type_list.json").c_str());

    if (j != nullptr && !j.is_discarded()) {
        if (j.contains(type)) {
            return j[type].get<nn::vector<int32_t>>();
        }
    }

    else {
        Logger::log("Error when parsing !\n");
    }
    return {}; // Return an empty vector if type not found
}

nn::vector<int32_t> BattleHallPool::getTypePool(const nn::string& type, Group groupNo) {
    nn::json j = FsHelper::loadJsonFileFromPath(
            appendJsonPath("/Group_" + nn::to_string(groupNo + 1) + ".json").c_str());

    nn::vector<int32_t> result;
    if (j != nullptr && !j.is_discarded()) {
        nn::vector<int32_t> typeMapping = getTypeMapping(type);
        for (const auto& item : j) {
            int32_t monsNo = item["monsNo"];
            Logger::log("[BHP] Checking monsNo: %d\n", monsNo);
            if (std::find(typeMapping.begin(), typeMapping.end(), monsNo) != typeMapping.end()) {
                Logger::log("[BHP] monsNo %d found in typeMapping.\n", monsNo);
                result.push_back(monsNo);
            }
        }
    }

    else {
        Logger::log("[BHP] Failed to load JSON file or file is discarded.\n");
    }

    return result;
}

void BattleHallPool::updateTypePool(const nn::string& type, int32_t group, const nn::vector<int32_t>& pool) {
    nn::string frontierFilePath(frontierFolderPath);
    frontierFilePath.append("/Group_" + nn::to_string(group + 1) + ".json");
    nn::json j = FsHelper::loadJsonFileFromPath(frontierFilePath.c_str());

    if (j == nullptr || j.is_discarded()) {
        j = nn::json::array(); // Initialize as an empty array if file does not exist
    }

    // Remove existing entries of the monsNos in the pool
    j.erase(std::remove_if(j.begin(), j.end(), [&pool](const nn::json& item) {
        return std::find(pool.begin(), pool.end(), item["monsNo"]) != pool.end();
    }), j.end());

    // Add new entries
    for (const auto& monsNo : pool) {
        nn::json newItem;
        newItem["monsNo"] = monsNo;
        j.push_back(newItem);
    }

    // Write back to file
    nn::string str = j.dump();
    FsHelper::writeFileToPath((void*)str.data(), str.size(), frontierFilePath.c_str());
}

