#include "helpers/fsHelper.h"
#include "save/save.h"
#include "externals/UnityEngine/JsonUtility.h"
#include "features/frontier/BattleFactory/BattleFactoryPool.h"

int32_t FactorySaveData::getRound() const {
    return currentRound;
}

FrontierRound FactorySaveData::getNowRound() const {
    return static_cast<FrontierRound>(currentRound % ROUND_COUNT);
}

void FactorySaveData::SerializePokeParty(Pml::PokeParty::Object* party, bool isPlayer) {
    system_load_typeinfo(0x6abb);
    isPlayer ? party->SerializeFull(&currentTeam) : party->SerializeFull(&lastEnemyTeam);
}

void FactorySaveData::DeserializePokeParty(Pml::PokeParty::Object* party, bool isPlayer) {
    system_load_typeinfo(0x6ab9);
    isPlayer ? party->DeserializeFull(&currentTeam) : party->DeserializeFull(&lastEnemyTeam);
}

nn::json FactorySaveData::PartyToJson(Pml::PokePara::SavePokeParty::Object party) {
    nn::json partyObject = nn::json::object();
    nn::json membersArray = nn::json::array();
    for (uint64_t i = 0; i < party.fields.memberCount; i++) {
        nn::json membersObject = nn::json::object();
        nn::json bufferJson = nn::json::array();
        for (int j = 0; j < party.fields.members->m_Items[i].fields.buffer->max_length; j++) {
            bufferJson.push_back(party.fields.members->m_Items[i].fields.buffer->m_Items[j]);
        }

        membersObject["buffer"] = bufferJson;
        membersArray.push_back(membersObject);
    }

    partyObject = {
            {"members", membersArray},
            {"memberCount", party.fields.memberCount},
            {"markingIndex", party.fields.markingIndex}
    };

    return partyObject;
}

void FactorySaveData::Clear() {
    currentRound = 0;
    factoryLevel = FactoryLevel::NOT_SET;
    currentStreakTrades = 0;
    currentTeam.Clear();
    lastEnemyTeam.Clear();
}

nn::json FactorySaveData::ToJson() const {
    return {
            {"factory", {
                    {"currentRound", currentRound},
                    {"factoryLevel", static_cast<int32_t>(factoryLevel)},
                    {"currentStreakTrades", currentStreakTrades},
                    {"currentTeam", PartyToJson(currentTeam)},
                    {"lastEnemyTeam", 0}
            }}
    };
}

void FactorySaveData::FromJson(const nn::json &factory) {
    Clear();
    currentRound = factory["currentRound"].get<int32_t>();
    factoryLevel = static_cast<FactoryLevel>(factory["factoryLevel"].get<int32_t>());
    currentStreakTrades = factory["currentStreakTrades"].get<int32_t>();
    currentTeam = {};
    lastEnemyTeam = {};
}

void FactorySaveData::GenerateSixRentalMons() {
    Pml::PokeParty::Object* genParty = Pml::PokeParty::newInstance();
    auto& save = getCustomSaveData()->battleFactory;
    frontierIndex selectedPoke;
    std::mt19937 rng = BattleFactoryPool::getRNG();
    FrontierSet currentSet = BattleFactoryPool::GetCurrentSet();
    int32_t IV = BattleFactoryPool::IVLookup(currentSet);
    auto distribution = BattleFactoryPool::GetDistributionRange(OPEN_LEVEL, currentSet,
                                                                static_cast<FrontierRound>(save.currentRound));

    int index = distribution(rng);

    for (int32_t i = 0; i < 6; i++) {
        Logger::log("[_FTR_SUB_LOCAL_BTL_CALL] Entering clause check %d.\n", i);
        while (BattleFactoryPool::ClausesCheck(BattleFactoryPool::IndexLookup(index, GROUP_2))) {
            index = distribution(rng);
        }
        auto pp = Frontier::GeneratePokemon(
                BattleFactoryPool::IndexLookup(index, GROUP_2), IV, 100);
        int32_t monsNo = pp->fields.m_accessor->GetMonsNo();
        Logger::log("[_FTR_SUB_LOCAL_BTL_CALL] Generated Pokemon = %d | %s.\n", monsNo, SPECIES[monsNo]);
        genParty->AddMember(pp);
        index = distribution(rng);
    }

    rentalParty = genParty;
}

void loadFactory(bool isBackup) {

    if (!isBackup && FsHelper::isFileExist(CustomSaveData::mainSaveName)) {
        nn::json jData = FsHelper::loadJsonFileFromPath(CustomSaveData::mainSaveName);
        if (jData.contains("lumi") && jData["lumi"].contains("factory")) {
            getCustomSaveData()->battleFactory.FromJson(jData["lumi"]["factory"]);
            Logger::log("Loaded Lumi_Factory!\n");
        }
    }

    else if (FsHelper::isFileExist(CustomSaveData::backupSaveName)) {
        nn::json jData = FsHelper::loadJsonFileFromPath(CustomSaveData::backupSaveName);
        if (jData.contains("lumi") && jData["lumi"].contains("factory")) {
            getCustomSaveData()->battleFactory.FromJson(jData["lumi"]["factory"]);
            Logger::log("Loaded Lumi_Factory_BK!\n");
        }
    }
}

nn::json saveFactory() {
    return getCustomSaveData()->battleFactory.ToJson();
}