#pragma once
#include "externals/il2cpp-api.h"
#include "externals/Dpr/UI/SelectOpeningItem.h"


namespace Dpr::UI {
    struct SelectPlayerVisualItem : ILClass<SelectPlayerVisualItem> {
        struct Fields : Dpr::UI::SelectOpeningItem::Fields {
            bool sex;
            int32_t colorId;
        };
    };
}