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
    RANK_1 = 0,
    RANK_2 = 1,
    RANK_3 = 2,
    RANK_4 = 3,
    RANK_5 = 4,
    RANK_6 = 5,
    RANK_7 = 6,
    RANK_8 = 7,
    RANK_9 = 8,
    RANK_10 = 9,
    RANK_COUNT = 10
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

enum TypeSelectorIndex : int32_t {
    NORMAL,
    FIRE,
    WATER,
    ELECTRIC,
    GRASS,
    ICE,
    FIGHTING,
    POISON,
    GROUND,
    FLYING,
    PSYCHIC,
    BUG,
    ROCK,
    GHOST,
    DRAGON,
    DARK,
    SUMMARY,
    STEEL,
    FAIRY,
    MATRON,
    INDEX_COUNT
};


extern const char* frontierFolderPath;

