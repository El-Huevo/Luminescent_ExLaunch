#pragma once
#include "externals/il2cpp-api.h"
#include "externals/Dpr/UI/UIText.h"
#include "externals/Dpr/UI/UIWindow.h"
#include "externals/UnityEngine/RectTransform.h"
#include "externals/Dpr/UI/UIMsgWindowController.h"

namespace Dpr::UI {
    struct UIKinomi : ILClass<UIKinomi> {
        struct Fields : UIWindow::Fields {
            void* iconSpriteAtlas;
            UnityEngine::RectTransform::Object* upArrowTransform;
            UnityEngine::RectTransform::Object* downArrowTransform;
            UIText::Object* numberText;
            UIText::Object* nameText;
            void* iconImage;
            UIText::Object* sizeText;
            UIText::Object* hardnessText;
            UIText::Object* descriptionText;
            void* raderChart;
            int32_t _animStateIn;
            int32_t _animStateOut;
            UIMsgWindowController::Object* msgWindowController;
            void* kinomiInfos;
            void* indexSelector;

        };
    };
}
