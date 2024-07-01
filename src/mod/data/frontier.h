#pragma once

enum Facility : int32_t {
    BATTLE_TOWER,
    BATTLE_FACTORY,
    BATTLE_ARCADE,
    BATTLE_CASTLE,
    BATTLE_HALL,
    FACILITY_COUNT
};

enum Rank : int32_t {
    RANK_1,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_COUNT
};

enum Group : int32_t {
    GROUP_1,
    GROUP_2,
    GROUP_3,
    GROUP_4,
    GROUP_COUNT
};

enum HallRound : int32_t {
    ROUND_1,
    ROUND_2,
    ROUND_3,
    ROUND_4,
    ROUND_5,
    ROUND_6,
    ROUND_7,
    ROUND_8,
    ROUND_9,
    ROUND_10,
    ROUND_COUNT
};

extern const char* frontierFolderPath;

