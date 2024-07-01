#include "exlaunch.hpp"
#include "data/typeMapping.h"
#include "memory/json.h"
#include "helpers/fsHelper.h"
#include <string>
#include "features/frontier/battle hall/BattleHallPool.h"
#include "data/frontier.h"


const PokemonTypeInfo& getTypeInfo(int32_t monsNo) {
    static PokemonTypeInfo unknownType = {"Unknown", ""};
    auto it = pokemonTypeMap.find(monsNo);
    if (it != pokemonTypeMap.end()) {
        return it->second;
    }
    // Return default types if not found
    return unknownType;
}


void loadTypeMapping() {
    nn::string frontierFilePath(frontierFolderPath);
    frontierFilePath.append("/hall_type_list.json");
    nn::json j = FsHelper::loadJsonFileFromPath(frontierFilePath.c_str());

    if (j != nullptr && !j.is_discarded()){
        for (const auto& item : j.items()) {
            int32_t monsNo = std::stoi(static_cast<const std::string>(item.key()));
            PokemonTypeInfo typeInfo;
            typeInfo.primaryType = item.value().at("primaryType").get<std::string>();
            typeInfo.secondaryType = item.value().at("secondaryType").get<std::string>();
            pokemonTypeMap[monsNo] = typeInfo;
        }
    }
    else {
        Logger::log("Error when parsing !\n");
    }
}
