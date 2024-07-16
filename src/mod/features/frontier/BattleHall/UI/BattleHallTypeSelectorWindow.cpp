#include "exlaunch.hpp"
#include "externals/UnityEngine/Events/UnityAction.h"
#include "externals/Dpr/UI/UIText.h"

namespace BattleHallTypeSelectorWindow {
    bool _OpOpen_d__5$$MoveNext() {
        UnityEngine::Events::UnityAction::Object* onSet;
        Dpr::UI::UIText::Object* rankText;

        onSet = UnityEngine::Events::UnityAction::getClass(UnityEngine::Events::UnityAction::void_TypeInfo)->newInstance();
        rankText->SetFormattedText(onSet, nullptr, nullptr);



    }
}