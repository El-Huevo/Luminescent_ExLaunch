#pragma once
#include "externals/il2cpp-api.h"
#include "features/frontier/frontierIndex.h"
#include "data/typeMapping.h"
#include "helpers/fsHelper.h"
#include "data/utils.h"
#include "data/frontier.h"

struct BattleHallPool {

    static nn::vector<int32_t> getTypeMapping(const nn::string& type);

    static nn::vector<int32_t> getTypePool(const nn::string& type, Group groupNo);

    static void updateTypePool(const nn::string& type, int32_t group, const nn::vector<int32_t>& pool);

    static frontierIndex indexLookup(int32_t monsNo, Group groupNo);

    static int32_t calculateBST(int32_t rank);

    static int8_t calculateEnemyLvl(int32_t rank);
};
