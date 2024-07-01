#pragma once
#include "il2cpp-api.h"
#include "System/Action.h"
#include "System/Collections/IEnumerator.h"

struct BattleMatchingManager : ILClass<BattleMatchingManager> {
    void* _battleMatchingUI;
    void* _recruitmentMember;
    void* _selectTeamMember;
    void* _selectRule;
    void* _selectBattleTeam;
    void* _selectPokemon;
    void* _result;
    void* _resume;
    void* _countDownData;
    void* _loadingRecieveData;
    System::Action::Object* _onFinish;
    bool _isError;
    int32_t _ColiseumLeavePoint_k__BackingField;
    bool _dispColiseumLeaveOtherMsg;
    bool _dispedLeaveOtherMsg;
    int32_t _currentState;

    static inline System::Collections::IEnumerator::Object* LoadBattleTowerUI(System::Action::Object* onCompletedLoad) {
        return external<System::Collections::IEnumerator::Object*>(0x01d6c3f0, onCompletedLoad);
    }
};