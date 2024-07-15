#pragma once
#include "il2cpp-api.h"
#include "UnityEngine/MonoBehaviour.h"
#include "Dpr/UI/SelectPlayerVisualItem.h"
#include "Dpr/UI/SelectPlayerVisualWindow.h"
#include "System/Action.h"
#include "UnityEngine/GameObject.h"

struct OpeningController : ILClass<OpeningController> {
    struct __c__DisplayClass9_0_ : ILClass<__c__DisplayClass9_0_> {
        struct Fields {
            OpeningController::Object* __4__this;
            Dpr::UI::SelectPlayerVisualWindow::Object* selectPlayer;
        };
    };


    struct Fields : UnityEngine::MonoBehaviour::Fields {
        Dpr::UI::SelectPlayerVisualItem::Object* _selectPlayerVisualItem;
        System::Action::Object* onFinishedCallBack;
        void* demoRequestOperation;
        UnityEngine::GameObject::Object* demoInstance;
        void* demoSceneManager;
        void* demoModel;
    };
};