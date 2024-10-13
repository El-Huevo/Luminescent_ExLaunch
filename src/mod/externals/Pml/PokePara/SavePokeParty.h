#pragma once

#include <cstdint>
#include "externals/il2cpp-api.h"
#include "externals/Pml/PokePara/SerializedPokemonFull.h"
#include "externals/Pml/PokeParty.h"

namespace Pml {
    struct PokeParty;
}

namespace Pml::PokePara {
    struct SavePokeParty : ILStruct<SavePokeParty> {
        struct Fields {
            SerializedPokemonFull::Array* members;
            uint8_t memberCount;
            uint8_t markingIndex;
        };

        static long GetByteCount() {
            long count = 0;
            count += Pml::PokePara::SerializedPokemonFull::GetByteCount()*6;
            count += sizeof(uint8_t)*2;

            return count;
        }

        inline void Serialize_Full(Pml::PokeParty* party) {
            external<void>(0x02055490, this, party);
        }

        inline void Deserialize_Full(Pml::PokeParty* party) {
            external<void>(0x02055730, this, party);
        }

        inline void CreateWorkIfNeed() {
            external<void>(0x02055610, this);
        }

        inline void Clear() {
            external<void>(0x02055990, this);
        }
    };
}

