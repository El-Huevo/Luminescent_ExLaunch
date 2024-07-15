#pragma once
#include "externals/il2cpp-api.h"
#include "externals/UnityEngine/MonoBehaviour.h"
#include "externals/UnityEngine/GameObject.h"

namespace Dpr::Demo {
    struct DemoSceneManager : ILClass<DemoSceneManager> {
        struct Fields : UnityEngine::MonoBehaviour::Fields {
            bool isAutoDestroy;
            void* DemoStock;
            void* MyEnvironmentController;
            void* PrevEnvironment;
            UnityEngine::GameObject::Object* DemoSceneAsset;
            UnityEngine::GameObject::Object* PrevDemoSceneAsset;
            void* UICanvas;
            void* RenderImage;
            void* Fade;
            int32_t PrevScreenWidth;
            void* Demo;
            int32_t _debug_demo;
            void* DebugAsset;
            int32_t Button01;
            int32_t Button03;
            int32_t TestNo;
            int32_t Button05;
        };
    };
}
