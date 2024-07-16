#pragma once
#include "externals/il2cpp-api.h"
#include "externals/UnityEngine/MonoBehaviour.h"
#include "externals/UnityEngine/UI/Image.h"
#include "externals/UnityEngine/Animator.h"
#include "externals/UnityEngine/Coroutine.h"

namespace Dpr::UI {
    struct Cursor : ILClass<Cursor, 0x04c5dc90> {
        struct Fields : UnityEngine::MonoBehaviour::Fields {
            UnityEngine::UI::Image::Array* _frameImages;
            void* _frameSprites;
            UnityEngine::Animator::Object* _animator;
            UnityEngine::Coroutine::Object* _opPlay;
        };

        inline void SetActive(bool enabled) {
            external<void>(0x01ec07b0, this, enabled);
        }
    };
}


