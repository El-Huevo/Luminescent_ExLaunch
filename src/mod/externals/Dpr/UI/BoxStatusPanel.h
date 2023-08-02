#pragma once

#include "externals/il2cpp-api.h"
#include "externals/UnityEngine/MonoBehaviour.h"
#include "externals/UnityEngine/UI/Image.h"
#include "externals/Dpr/UI/UIText.h"
#include "externals/UnityEngine/GameObject.h"

namespace Dpr::UI {
    struct BoxStatusPanel : ILClass<BoxStatusPanel> {
        struct Fields : UnityEngine::MonoBehaviour::Fields {
            UnityEngine::UI::Image::Object* _ballImage;
            Dpr::UI::UIText::Object* _nickNameText;
            UnityEngine::UI::Image::Object* _sexImage;
            Dpr::UI::UIText::Object* _levelText;
            UnityEngine::GameObject::Object* _statusFrame;
            UnityEngine::GameObject::Object* _judgeFrame;
            Dpr::UI::UIText::Object* _noText;
            Dpr::UI::UIText::Object* _nameText;
            UnityEngine::UI::Image::Object* _langIcon;
            void* _types; //Dpr_UI_TypePanel_array*
            UnityEngine::UI::Image::Object* _pokerusImage;
            UnityEngine::UI::Image::Object* _RereImage;
            void* _condition; //Dpr_UI_PokemonSick_o*
            void* _pokerusSprites; //UnityEngine_Sprite_array*
            void* _statusValues;
            UnityEngine::GameObject::Object* _wazaFrame;
            Dpr::UI::UIText::Object* _judgeTotalText;
            void* _wazaBgs; //UnityEngine_UI_Image_array*
            void* _wazaTexts; //Dpr_UI_UIText_array*
            void* _wazaTypeSprites; //UnityEngine_Sprite_array*
            void* _markImages; //UnityEngine_UI_Image_array*
            void* _markColorSet; //UnityEngine_Color32_array*
            float _openPosX;
            float _closePosX;
        };
    };
}