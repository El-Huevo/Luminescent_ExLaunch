#pragma once
#include "externals/il2cpp-api.h"
#include "UIWindow.h"
#include "externals/UnityEngine/GameObject.h"
#include "externals/System/Action.h"
#include "externals/System/String.h"
#include "externals/UnityEngine/Vector2.h"
#include "externals/Pml/PokePara/PokemonParam.h"
#include "externals/Dpr/UI/PokemonStatusWindow.h"
#include "externals/Dpr/UI/ContextMenuWindow.h"
#include "externals/Dpr/UI/UIBattleMatchingTeamSelect.h"
#include "externals/Dpr/UI/Cursor.h"

namespace Dpr::UI {
    struct UIBattleMatchingPokemonSelect : ILClass<UIBattleMatchingPokemonSelect> {
        struct Fields : UIWindow::Fields {
            void* _timer;
            void* _teamPlate;
            void* _pokemonParty;
            void* _pokemonItems;
            UnityEngine::RectTransform::Object* _decide;
            Dpr::UI::Cursor::Object* _cursor;
            Dpr::UI::PokemonStatusWindow::Object* _pokemonStatusUI;
            Dpr::UI::UIBattleMatchingTeamSelect::Object* _teamSelectUI;
            Dpr::UI::ContextMenuWindow::Object* _contextMenu;
            System::Action::Object* _onDecide;
            System::Action::Object* _onCancel;
            System::Action::Object* _onUpdateTimer;
            bool _isBattleTower;
            bool _decideFade;
            bool _isOpeningStatus;
            bool _isOpeningTeam;
            int32_t _currentIndex;
            int32_t _maxIndex;
            int32_t _requiredNumMin;
            int32_t _requiredNumMax;
            void* _joinIndexList;
            bool _isOpeningMessage;
            void* _msgWindow;
            UnityEngine::Vector2::Object MSG_WINDOW_ANCHOR_POS;
        };

        static_assert(offsetof(Fields, MSG_WINDOW_ANCHOR_POS) == 0xf0);
    };
}
