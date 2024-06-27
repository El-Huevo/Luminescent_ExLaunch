
#include <random>
#include "BattleHallPool.h"
#include "externals/FlagWork.h"
#include "externals/FlagWork_Enums.h"
#include "save/save.h"


static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::mt19937 rng(seed);

const char* frontierFolderPath = "rom:/Data/ExtraData/Frontier";

namespace BattleHallPool {
    nn::string appendJsonPath(const nn::string& path) {
        nn::string frontierFilePath(frontierFolderPath);
        frontierFilePath.append(path);
        return frontierFilePath;
    }

    frontierIndex indexLookup(int32_t monsNo, Group groupNo) {
        nn::json j = FsHelper::loadJsonFileFromPath(
                appendJsonPath("/Group_" + nn::to_string(groupNo + 1) + ".json").c_str());

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

    Group calculateGroup(Rank rank) {
        Group groupNo;
        std::uniform_int_distribution<int32_t> distribution(1, 2);
        int32_t randNo = distribution(rng);
        switch (rank) {
            case (RANK_1) ... (RANK_2): {
                groupNo = GROUP_1;
                break;
            }
            case (RANK_3) ... (RANK_5): {
                groupNo = (randNo == 1) ? GROUP_1 : GROUP_2;
                break;
            }
            case (RANK_6) ... (RANK_8): {
                groupNo = (randNo == 1) ? GROUP_2 : GROUP_3;
                break;
            }
            case (RANK_9) ... (RANK_10): {
                groupNo = (randNo == 1) ? GROUP_3 : GROUP_4;
                break;
            }
            default: {
                groupNo = GROUP_1;
                break;
            }
        }
        Logger::log("[HallPoke] Current Group: %d\n", groupNo + 1);
        return groupNo;
    }

    uint16_t calculateEnemyLvl(Rank rank) {
        int32_t pLvl = 50; // Todo Dynamic Lvl
        double lvlBase = pLvl - (3 * sqrt(pLvl));
        int32_t currentTypeRank = rank + 1;
        double types = 17;
        double increment = sqrt(pLvl) / 5;
        double oLvlCalc = lvlBase + (types / 2) + (currentTypeRank - 1) * increment;
        return (uint16_t) fmin(pLvl, round(oLvlCalc));
    }

    int32_t rankIVLookup(Rank rank) {
        const int32_t rankIVs[] = {0, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26};

        if (rank >= RANK_1 && rank <= RANK_10) {
            return rankIVs[rank];
        }

        else {
            return rankIVs[RANK_1]; // Returns 0 IVs if out of range.
        }
    }

    bool duplicateCheck(PoolManager* poolManager, int32_t monsNo, int32_t typeIndex) {
        auto typeList = poolManager->getBlackListedMons(typeIndex);
        for (const auto& blacklistedMonsNo : typeList) {
            if (blacklistedMonsNo == monsNo) {
                return true;
            }
        }
        return false;
    }

    nn::vector<int32_t> getTypeMapping(const nn::string& type) {
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

    nn::vector<int32_t> getTypePool(const nn::string& type, Group groupNo) {
        nn::json j = FsHelper::loadJsonFileFromPath(
                appendJsonPath("/Group_" + nn::to_string(groupNo + 1) + ".json").c_str());

        nn::vector<int32_t> result;
        if (j != nullptr && !j.is_discarded()) {
            nn::vector<int32_t> typeMapping = getTypeMapping(type);
            for (const auto& item : j) {
                int32_t monsNo = item["monsNo"];
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

}

