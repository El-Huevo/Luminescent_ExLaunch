#pragma once
#include "externals/il2cpp-api.h"
#include "externals/UnityEngine/RectTransform.h"
#include "externals/KeyguideItem.h"
#include "externals/Dpr/UI/UIWindow.h"
#include "externals/UnityEngine/Coroutine.h"
#include "externals/System/Collections/Generic/List.h"

namespace Dpr::UI {
    struct Keyguide : ILClass<Keyguide> {
        struct Param : ILClass<Param> {
            struct Fields {
                System::Collections::Generic::List$$KeyguideItem_Param::Object* itemParams;
            };
        };
        struct Fields : UIWindow::Fields {
            UnityEngine::RectTransform::Object* _guideRoot;
            KeyguideItem::Object* _itemPrefab;
            UnityEngine::Coroutine::Object* _coClose;
            bool isOpen;
        };

        inline void Setup(Param::Object* param) {
            external<void>(0x01c57fd0, this, param);
        }
    };
}
