
#include "externals/PlayerWork.h"
#include "logger/logger.h"
#include "commands.h"
#include "externals/GameManager.h"
#include "externals/System/Action.h"
#include "externals/BattleMatchingManager.h"
#include "externals/SmartPoint/AssetAssistant/Sequencer.h"
#include "externals/Dpr/BattleMatching/BattleMatchingWork.h"


bool FTR_SUB_SELECT_POKE(Dpr::EvScript::EvDataManager::Object* manager) {
    system_load_typeinfo(0x453f);

    switch (manager->fields._btwrSequence) {
        case 0: {
            MethodInfo* mi = *Dpr::EvScript::EvDataManager::Method$$EvDataManager_BTWR_SUB_SELECT_POKE;
            auto onCompleted = System::Action::getClass(System::Action::void_TypeInfo)->newInstance(
                    manager, mi);

            auto routine = BattleMatchingManager::LoadBattleTowerUI(onCompleted);

            SmartPoint::AssetAssistant::Sequencer::getClass()->initIfNeeded();
            SmartPoint::AssetAssistant::Sequencer::Start(routine);
            break;
        }

        case 2: {
            BattleMatchingWork::getClass()->initIfNeeded();
            auto pokeParams = &BattleMatchingWork::getClass()->static_fields->pokemonParams;
            *pokeParams = nullptr;

            BattleMatchingWork::getClass()->static_fields->battleTeamIndex = -1;
        }


    }


    return true;
}