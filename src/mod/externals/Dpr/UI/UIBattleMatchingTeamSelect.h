#pragma once
#include "externals/il2cpp-api.h"
#include "UIWindow.h"
#include "externals/UnityEngine/GameObject.h"
#include "externals/System/Action.h"
#include "externals/System/String.h"
#include "externals/UnityEngine/Vector2.h"
#include "externals/Pml/PokePara/PokemonParam.h"

namespace Dpr::UI {
    struct UIBattleMatchingTeamSelect : ILClass<UIBattleMatchingTeamSelect> {
        struct Fields : UIWindow::Fields {
            void* _timer;
            void* _teamPlates;
            void* _objArrows;
            void* _boxWindow;
            System::Action::Object* _onDecide;
            System::Action::Object* _onCancel;
            int32_t _currentState;
            bool _cancelFade;
            bool _closed;
            bool _isServerError;
            void* _illegalList;
            int32_t _currentIndex;
            void* _msgWindow;
            float _closingProgressTime;
            System::String::Array* YESNO_CONTEXTMENU_LABELS;
            UnityEngine::Vector2::Object MSG_WINDOW_ANCHOR_POS;
            bool _isActiveKeyGuide_k__BackingField;
        };

        struct _c__DisplayClass60_0 : ILClass<_c__DisplayClass60_0> {
            struct Fields {
                UIBattleMatchingTeamSelect::Object* __4__this;
                Pml::PokePara::PokemonParam::Array* pokemonParams;
            };
        };

        inline Pml::PokePara::PokemonParam::Array* CreateModifyLevelParty(
                Pml::PokePara::PokemonParam::Array** pokemonParams) {
            return external<Pml::PokePara::PokemonParam::Array*>(0x01bf3010, this, pokemonParams);
        }
    };
}
