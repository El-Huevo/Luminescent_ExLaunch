#pragma once

#include "externals/il2cpp-api.h"

#include "externals/UnityEngine/Events/UnityAction.h"
#include "externals/UnityEngine/MonoBehaviour.h"
#include "externals/UnityEngine/Animator.h"
#include "externals/Dpr/UI/UIManager.h"
#include "externals/Dpr/UI/UIInputController.h"
#include "externals/Dpr/MsgWindow/MsgWindow.h"
#include "externals/Dpr/MsgWindow/MsgWindowParam.h"

namespace Dpr::UI {
    // Forward declaration
    struct ContextMenuWindow;

    struct UIWindow : ILClass<UIWindow> {
        struct __c__ : ILClass<__c__, 0x04c63288> {
            struct StaticFields {
                Dpr::UI::UIWindow::__c__::Object* __9;
                UnityEngine::Events::UnityAction::Object* __9__54_0;
            };
        };


        struct __OpPlayOpenWindowAnimation_d__44 : ILClass <__OpPlayOpenWindowAnimation_d__44> {
            struct Fields {
                int32_t __1__state;
                Il2CppObject* __2__current;
                UIWindow::Object* __4__this;
                UnityEngine::Events::UnityAction::Object* onOpend;
            };
        };

        struct Fields : UnityEngine::MonoBehaviour::Fields {
            UIInputController::Object* _input;
            void* _canvas;
            UnityEngine::Animator::Object* _animator;
            void* _animEvent;
            int32_t _transitionFadeType;
            int32_t _prevWindowId;
            Dpr::MsgWindow::MsgWindow::Object* _messageWindow;
            UIManager::UIInstance::Object* instance;
            UnityEngine::Events::UnityAction::Object* onClosed;
            UnityEngine::Events::UnityAction::Object* onPreClose;
            bool _IsClosing_k__BackingField;
            int32_t _animStateIn;
            int32_t _animStateOut;
        };

        inline bool IsPushButton(int32_t button, bool isForce) {
            return external<bool>(0x01a352a0, this, button, isForce);
        }

        inline bool IsRepeatButton(int32_t button, bool isForce) {
            return external<bool>(0x01a352c0, this, button, isForce);
        }

        inline void OnOpen(int32_t prevWindowId) {
            external<void>(0x01a351e0, this, prevWindowId);
        }

        inline System::Collections::IEnumerator::Object* OpPlayOpenWindowAnimation(
                int32_t prevWindowId, UnityEngine::Events::UnityAction::Object* onOpen) {
            return external<System::Collections::IEnumerator::Object*>(0x01a35390, this, prevWindowId, onOpen);
        }

        inline Dpr::UI::ContextMenuWindow* CreateContextMenuYesNo(void* onClicked, uint32_t SeDecide) {
            return external<Dpr::UI::ContextMenuWindow*>(0x01a35c50, this, onClicked, SeDecide);
        }

        inline void OpenMessageWindow(Dpr::MsgWindow::MsgWindowParam::Object* messageParam) {
            external<void>(0x01a358b0, this, messageParam);
        }

        inline void CloseMessageWindow() {
            external<void>(0x01a359c0, this);
        }
    };
}
