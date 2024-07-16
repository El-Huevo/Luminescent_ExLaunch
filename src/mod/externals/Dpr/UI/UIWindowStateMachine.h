#pragma once
#include "externals/il2cpp-api.h"
#include "externals/UnityEngine/StateMachineBehaviour.h"

namespace Dpr::UI {
    struct UIWindowStateMachine : ILClass<UIWindowStateMachine, 0x04c63270> {
        struct Fields : UnityEngine::StateMachineBehaviour::Fields {

        };

        struct StaticFields {
            int32_t animParamConnectId;
            int32_t animParamStateId;
            int32_t animStateVoid;
            int32_t animStateOpened;
        };
    };
}