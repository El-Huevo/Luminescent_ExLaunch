#include "exlaunch.hpp"
#include "features/frontier/frontier_helpers.h"
#include "features/frontier/frontierIndex.h"
#include "memory/json.h"
#include "memory/string.h"
#include "helpers/fsHelper.h"
#include "externals/Pml/PokeParty.h"
#include "externals/Dpr/Battle/Logic/BATTLE_SETUP_PARAM.h"
#include "externals/Dpr/EvScript/EvDataManager.h"
#include "externals/Pml/PokeParty.h"
#include "externals/Dpr/PokeRegulation.h"
#include "externals/GameManager.h"
#include "externals/PlayerWork.h"
#include "externals/XLSXContent/MapInfo.h"
#include "externals/FieldManager.h"
#include "BattleHallPool.h"
#include "externals/FlagWork.h"
#include "frontier_helpers.h"
#include "externals/Dpr/Battle/Logic/BTL_FIELD_SITUATION.h"
#include "externals/Dpr/Battle/Logic/Setup.h"
#include "externals/Dpr/Battle/Logic/BattleEffectComponentData.h"

using namespace Dpr::Battle::Logic;


void SetupBattleFrontierTrainer(Dpr::Battle::Logic::BATTLE_SETUP_PARAM::Object* battleSetupParam,
                                Pml::PokeParty::Object* playerParty, int32_t rule, int32_t arenaID, int32_t weatherType,
                                int32_t enemy1, Pml::PokeParty::Object* enemy1Party, void* enemy1SealTIDs,
                                int32_t enemy2, Pml::PokeParty::Object* enemy2Party, void* enemy2SealTIDs) {
    system_load_typeinfo(0x3f56);
    battleSetupParam->Clear();

    BTL_FIELD_SITUATION::getClass()->initIfNeeded();
    BTL_FIELD_SITUATION::Object* fieldSituation = Dpr::Battle::Logic::BTL_FIELD_SITUATION::newInstance();
    Setup::BATTLE_SETUP_FIELD_SITUATION_Init(fieldSituation);
    fieldSituation->fields.bgComponent->SetUpBgComponentData(arenaID);

    Setup::BTL_SETUP_BattleInst(battleSetupParam, playerParty,
                                                    enemy1, enemy1Party,
                                                    enemy1SealTIDs,enemy2,
                                                    enemy2Party, enemy2SealTIDs,
                                                    fieldSituation, rule);

    battleSetupParam->fields.btlEffComponent->SetUpBattleEffectComponentData(70, -1, 0,
                                                                             (System::String::Object *) nullptr);


}

static bool EvCmd_FTR_SUB_LOCAL_BTL_CALL(Dpr::EvScript::EvDataManager::Object* __this) {
    Pml::PokeParty::Object* trainerParty = Pml::PokeParty::newInstance();
    auto selectedPoke = BattleHallPool::indexLookup(1, 1);
    Logger::log("[_FTR_SUB_LOCAL_BTL_CALL] Selected Poke.\n");
    trainerParty->AddMember(Frontier::GeneratePokemon(selectedPoke));
    Logger::log("[_FTR_SUB_LOCAL_BTL_CALL] Added to party.\n");
    //PokeRegulation::getClass()->initIfNeeded();
    //PokeRegulation::ModifyLevelPokeParty(trainerParty, 1, 50);
    //Logger::log("[_FTR_SUB_LOCAL_BTL_CALL] Party level modified to 50.\n");

    GameManager::getClass()->initIfNeeded();
    auto mapInfo = GameManager::get_mapInfo();
    Logger::log("[_FTR_SUB_LOCAL_BTL_CALL] Retrieved mapInfo.\n");

    PlayerWork::getClass()->initIfNeeded();
    auto zoneID = PlayerWork::get_zoneID();
    Logger::log("[_FTR_SUB_LOCAL_BTL_CALL] Retrieved zoneID.\n");

    auto battleBG = mapInfo->get_Item(zoneID)->fields.BattleBg;

    auto iVar8 = battleBG->m_Items[0];
    auto battleSetupParam = PlayerWork::get_battleSetupParam();
    SetupBattleFrontierTrainer(battleSetupParam, trainerParty, 0, 40, 0, 32,
                               trainerParty, (void*) nullptr, -1,
                               (Pml::PokeParty::Object*) nullptr, (void*) nullptr);


    __this->fields.Btl_TrainerType1 = 2;

    __this->SetBattleReturn();

    FieldManager::getClass()->initIfNeeded();
    auto backingField = FieldManager::getClass()->static_fields->_Instance_k__BackingField;
    backingField->PreLoadEncEffect(System::String::Create("field/01"));
    backingField->EncountStart(0,0,0);

    __this->fields._isCall_TrainerBtl = true;
    __this->fields._isBattleTowerBtl = true;
    return true;
}

HOOK_DEFINE_REPLACE(BTWR_SUB_LOCAL_BTL_CALL) {
    static bool Callback(Dpr::EvScript::EvDataManager::Object* __this) {
        Logger::log("[EvDataManager] _FTR_SUB_LOCAL_BTL_CALL\n");
        return EvCmd_FTR_SUB_LOCAL_BTL_CALL(__this);
    }
};

HOOK_DEFINE_TRAMPOLINE(SetupTowerTrainer) {
    static void Callback(Dpr::Battle::Logic::BATTLE_SETUP_PARAM::Object* battleSetupParam,
                         Pml::PokeParty::Object* playerParty, int32_t rule, int32_t arenaID, int32_t weatherType,
                         int32_t enemy1, Pml::PokeParty::Object* enemy1Party, void* enemy1SealTIDs,
                         int32_t enemy2, Pml::PokeParty::Object* enemy2Party, void* enemy2SealTIDs, void* lotResult) {
        Orig(battleSetupParam, playerParty, rule, arenaID, weatherType, enemy1, enemy1Party, enemy1SealTIDs,
             enemy2, enemy2Party, enemy2SealTIDs, lotResult);

        Logger::log("[SetupTowerTrainer] Rule: %d, arenaID: %d, weatherType: %d, enemy1: %d, enemy2: %d.\n",
                    rule, arenaID, weatherType, enemy1, enemy2);
    }
};

void exl_battle_hall_main() {
    BTWR_SUB_LOCAL_BTL_CALL::InstallAtOffset(0x02c93f50);
    //SetupTowerTrainer::InstallAtOffset(0x02c3bd00);
}