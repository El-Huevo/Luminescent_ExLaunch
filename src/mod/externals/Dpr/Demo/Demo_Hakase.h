#pragma once

#include "externals/il2cpp-api.h"

#include "externals/Dpr/Demo/DemoBase.h"
#include "externals/Pml/PokePara/PokemonParam.h"
#include "externals/System/Primitives.h"
#include "externals/UnityEngine/RectTransform.h"
#include "externals/UnityEngine/Transform.h"
#include "externals/UnityEngine/UI/Image.h"
#include "externals/UnityEngine/Vector2.h"
#include "externals/UnityEngine/_Object.h"
#include "externals/OpeningController.h"

namespace Dpr::Demo {
    struct Demo_Hakase : ILClass<Demo_Hakase, 0x04c5e5f8> {
        struct Fields : Dpr::Demo::DemoBase::Fields {
            UnityEngine::_Object::Object* Rival3DModel;
            void* animController;
            OpeningController::Object* openingController;
            void* hakaseEntity;
            void* bgEffect;
            void* bgEffectData;
            bool isSkip;
        };

        inline void ctor() {
            external<void>(0x01acaeb0, this);
        }
    };
}