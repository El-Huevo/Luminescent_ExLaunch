#pragma once
#include "externals/il2cpp-api.h"
#include "externals/UnityEngine/UI/Image.h"
#include "externals/Dpr/UI/UIText.h"

namespace Dpr::UI {
    struct CardBackView : ILClass<CardBackView> {
        struct __c__DisplayClass27_0 : ILClass<__c__DisplayClass27_0> {
            struct Fields {
                uint32_t singleRenshouCount;
                uint32_t doubleRenshouCount;
                uint32_t masterSingleRenshouCount;
                uint32_t masterDoubleRenshouCount;
            };

            static inline StaticILMethod<0x04c7ed38> CardBackView___c__DisplayClass27_0__SetTowerTexts__b__0 {};
        };

        struct Fields : UnityEngine::MonoBehaviour::Fields {
            UnityEngine::UI::Image::Object* cardImage;
            UnityEngine::UI::Image::Object* titleImage;
            Dpr::UI::UIText::Object* contest01Text;
            Dpr::UI::UIText::Object* contest02Text;
            Dpr::UI::UIText::Object* contest03Text;
            Dpr::UI::UIText::Object* contest04Text;
            Dpr::UI::UIText::Object* contest05Text;
            Dpr::UI::UIText::Object* tower01Text;
            Dpr::UI::UIText::Object* tower02Text;
            Dpr::UI::UIText::Object* tower03Text;
            Dpr::UI::UIText::Object* tower04Text;
            Dpr::UI::UIText::Object* poffinCountText;
            Dpr::UI::UIText::Object* fossilCountText;
            Dpr::UI::UIText::Object* statueCountText;
        };
    };
}



