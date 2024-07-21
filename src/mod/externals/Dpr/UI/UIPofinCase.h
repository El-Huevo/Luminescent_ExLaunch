#pragma once
#include "externals/il2cpp-api.h"
#include "externals/Dpr/UI/UIWindow.h"
#include "externals/Dpr/UI/Cursor.h"
#include "externals/Dpr/UI/UIText.h"
#include "externals/UnityEngine/GameObject.h"
#include "externals/Pml/PokePara/PokemonParam.h"
#include "externals/Dpr/Message/MessageMsgFile.h"
#include "externals/UnityEngine/Coroutine.h"

namespace Dpr::UI {
    struct UIPofinCase : ILClass<UIPofinCase> {
        struct __c__DisplayClass42_0_ : ILClass<__c__DisplayClass42_0_, 0x04c62fc8> {
            struct Fields {
                UIPofinCase::Object* __4__this;
                System::Action::Object* onComplete;
            };

            static inline StaticILMethod<0x04c807c0, Dpr::UI::UIWindow> Method$$__OpenPokemonStatusWindow__b__0;

            inline void ctor() {
                external<void>(0x01a17cf0, this);
            }
        };
        struct Fields : UIWindow::Fields {
            void* categorySelector;
            void* tasteLump;
            void* scrollView;
            Dpr::UI::Cursor::Object* cursor;
            Dpr::UI::UIText::Object* subText;
            UnityEngine::GameObject::Object* noDataTextObject;
            UnityEngine::GameObject::Array* noDataDisableObjects;
            Pml::PokePara::PokemonParam::Object* selectedPokemonParam;
            void* onResultCallback;
            void* poffinResultDatas;
            void* poffinDatas;
            int32_t selectedIndex;
            int32_t selectedPartyIndex;
            float scrollPos;
            void* currentItemButton;
            Dpr::Message::MessageMsgFile::Object* poffinMainMsgFile;
            UnityEngine::Coroutine::Object* removeNewIconCoroutine;
            void* poffin3DModel;
            void* conditionParam;
        };
    };
}
