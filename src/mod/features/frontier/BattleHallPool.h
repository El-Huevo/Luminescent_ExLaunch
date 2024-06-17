#pragma once
#include "externals/il2cpp-api.h"
#include "features/frontier/frontierIndex.h"
#include "data/typeMapping.h"
#include "helpers/fsHelper.h"
#include "data/utils.h"
#include "save/save.h"

class BattleHallPool {
private:
    nn::json jsonData;

    [[nodiscard]] static HallSaveData* getHallSaveData() {
        return &getCustomSaveData()->battleHall;
    }

public:
    explicit BattleHallPool();

    static frontierIndex indexLookup(int32_t monsNo, int32_t group);

    static int32_t calculateBST(int32_t rank);

    static int8_t calculateEnemyLvl(int32_t rank);
};

