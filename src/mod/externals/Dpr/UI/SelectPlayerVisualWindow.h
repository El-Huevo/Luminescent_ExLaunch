#pragma once
#include "externals/il2cpp-api.h"
#include "externals/Dpr/UI/SelectOpeningBase.h"
#include "externals/UnityEngine/RectTransform.h"


namespace Dpr::UI {
    struct SelectPlayerVisualWindow : ILClass<SelectPlayerVisualWindow> {
        struct __OpOpen_d__10_ : ILClass<__OpOpen_d__10_, 0x04c623d8> {
            struct Fields {
                int32_t __1__state;
                Il2CppObject* __2__current;
                SelectPlayerVisualWindow::Object* __4__this;
                int32_t prevWindowId;
            };
            inline void ctor(int32_t __1__state) {
                external<void>(0x01d3d7b0, this, __1__state);
            }
        };

        struct Fields : Dpr::UI::SelectOpeningBase::Fields {
            UnityEngine::RectTransform::Object* _content;
            void* _cursor;
            void* _items;
            int32_t selectIndex;
        };
    };
}
