#pragma once
#include <map>
#include "types.h"
#include <string>
#include "memory/json.h"

struct PokemonTypeInfo {
    std::string primaryType;
    std::string secondaryType;
};

extern std::map<int32_t, PokemonTypeInfo> pokemonTypeMap;

const PokemonTypeInfo& getTypeInfo(int32_t monsNo);

void loadTypeMapping();


