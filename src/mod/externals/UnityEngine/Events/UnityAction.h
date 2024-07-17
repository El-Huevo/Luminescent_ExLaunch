#pragma once

#include "externals/il2cpp.h"
#include "externals/il2cpp-api.h"
#include "externals/System/MulticastDelegate.h"

namespace Dpr::UI {
    struct UIWindow;
}

namespace UnityEngine::Events {
    struct UnityAction : ILClass<UnityAction> {
        struct Fields : System::MulticastDelegate::Fields {

        };

        static const inline long bool_String_TypeInfo = 0x04c5ee10;
        static const inline long void_TypeInfo = 0x04c57230;
        static const inline long UIWindow_TypeInfo = 0x04c59e60;

        static inline StaticILMethod<0x04c7d008> Method$$Dpr_EvScript_EvDataManager__EvCmdBTowerAppSetProc__b__1143_0 {};
        static inline StaticILMethod<0x04c81d88> Method$$__c__DisplayClass9_0__OpenSelectPlayerVisual__b__0 {};
        static inline StaticILMethod<0x04c7d030> Method$$Dpr_EvScript_EvDataManager__EvCmdBoxSetProc__b__742_0 {};
        static inline StaticILMethod<0x04c80cf0> Method$$Dpr_UI_UIWindow__c__CreateContextMenuYesNo__b__54_0 {};

        static inline StaticILMethod<0x04c8e658, Dpr::UI::UIWindow> Method$$Invoke$$UIWindow {};


        template <typename T, typename... Args>
        inline void ctor(T* owner, ILMethod<T, Args...>& mi) {
            ctor(owner, *mi);
        }

        // Owner will be the first param of the method it seems
        inline void ctor(void* owner, MethodInfo* mi) {
            external<void>(0x026adeb0, this, owner, mi);
        }

        inline void Invoke() {
            external<void>(0x026a3140, this);
        }

        // Maybe there's a way to generalize this more?
        template <typename T>
        inline void Invoke(T* arg0, ILMethod<T>& mi) {
            external<void>(0x0253ded0, this, arg0, *mi);
        }

        inline void ctor() {
            external<void>(0x026adeb0, this);
        }

        // DEBUGGING PURPOSES ONLY
        inline uintptr_t getMethodPtrForDebug() {
            return this->instance()->fields.method_ptr - exl::util::modules::GetTargetStart();
        }
    };
}
