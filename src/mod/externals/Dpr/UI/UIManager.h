#pragma once

#include "externals/il2cpp-api.h"

#include "externals/Dpr/UI/UIModelViewController.h"

#include "externals/SmartPoint/AssetAssistant/SingletonMonoBehaviour.h"
#include "externals/SpriteAtlasID.h"
#include "externals/System/Action.h"
#include "externals/System/Func.h"
#include "externals/UnityEngine/Events/UnityAction.h"
#include "externals/UnityEngine/Transform.h"
#include "externals/XLSXContent/UIDatabase.h"
#include "externals/UIWindowID.h"
#include "externals/System/Collections/IEnumerator.h"
#include "externals/UnityEngine/Sprite.h"

namespace Dpr::UI {
    struct UIWindow;
    struct ContextMenuWindow;
    struct ShopBoutiqueChange;
    struct UIWazaManage;
    struct BattleTowerRecordWindow;
    struct BoxWindow;
    struct PokemonStatusWindow;
    struct SelectPlayerVisualWindow;
    struct UIKinomi;
}

namespace Dpr::UI {
    struct UIManager : ILClass<UIManager, 0x04c5cc28> {
        struct UIInstance : ILClass<UIInstance> {
            struct Fields {
                UIWindow* _uiWindow;
                UIWindowID _windowId;
            };

            inline int32_t get_windowId() {
                return external<int32_t>(0x01a0e370, this);
            }
        };

        struct __OpLoad_d__101 : ILClass<__OpLoad_d__101> {
            struct Fields {
                int32_t __1__state;
                Il2CppObject* __2__current;
                int32_t type;
                Dpr::UI::UIManager::Object* __4__this;
                bool isOpening;
            };
        };

        enum class InitializeStateBit : int32_t {
            EntrySpriteAtlas = 1 << 0, // 1
            LoadedSpriteAtlas = 1 << 1, // 2
            EntryWindows = 1 << 2, // 4
            LoadedWindows = 1 << 3, // 8
            EntryAterLang = 1 << 4, // 16
            LoadAterLang = 1 << 5, // 32
            Loaded = (1 << 1) | (1 << 3) // 10 (Combination of LoadedSpriteAtlas and LoadedWindows)
        };

        struct Fields : SmartPoint::AssetAssistant::SingletonMonoBehaviour::Fields {
            UnityEngine::Transform::Object* _activeRoot;
            Dpr::UI::UIModelViewController::Object* _modelView;
            UnityEngine::Transform::Object* _blurBgRoot;
            XLSXContent::UIDatabase::Object* _mdUis;
            void* _mdTownmapGuide;
            void* _mdTownmap;
            void* _mdDistribution;
            void* _mdPlaceName;
            void* _mdInputLimit;
            void* _inputLimitHashSets;
            void* _mdSearchIndexData;
            void* _spriteMonsterBallDict;
            void* _spriteMonsterBallStrange;
            void* _spriteMonsterBallIllegal;
            void* _spriteAtlasParams;
            void* _keyguide;
            InitializeStateBit _InitializeStateBits;
            UnityEngine::Events::UnityAction::Object* onXMenuClosed;
            bool _fureaiLimit;
            void* _objectPool;
            void* _objectPoolTransition;
            void* _transitionInstances;
            int32_t _transitionId;
            bool _isFadeTransition;
            void* _cacheSpritePokemons;
            void* _blurBg;
            void* _blurBgParam;
            float _debugInstrument;
            System::String::Array* _databaseAssetBundleNames;
            bool _isLoadedDatabase;
            void* _atlasSpriteDict;
            System::String::Object* _assetPathIndexdata;
            void* _transitionWindowIds;
            void* _xMenu;
            void* _nowLoadingController;
        };

        struct StaticFields {
            int32_t StickLLeft;
            int32_t StickLRight;
            int32_t StickLUp;
            int32_t StickLDown;
            int32_t ButtonA;
            int32_t ButtonB;
            int32_t ButtonX;
            int32_t ButtonY;
            int32_t ButtonPlusMinus;
            UnityEngine::Events::UnityAction::Object* onWazaFly;
            UnityEngine::Events::UnityAction::Object* onDressChanged;
            System::Func::Object* onFieldWaza;
            System::Func::Object* onUseFieldItem;
            System::Action::Object* onUseItemInBattle;
            System::Action::Object* onUseHidenWaza;
            System::Func::Object* onUseDowsing;
            void* _comparerPokemonIcon; // Dpr_UI_UIManager_ComparerPokemonIcon_o*
            void* _comparerAshiatoIcon; // Dpr_UI_UIManager_ComparerAshiatoIcon_o*
            void* _comparerZukanDisplay; // Dpr_UI_UIManager_ComparerZukanDisplay_o*
            void* _comparerPokemonVoice; // Dpr_UI_UIManager_ComparerPokemonVoice_o*
            void* _comparerZukanCompareHeight; // Dpr_UI_UIManager_ComparerZukanCompareHeight_o*
            void* _langParams; // Dpr_UI_UIManager_LangParam_array*
            void* _pokemonParamMappings; // System_Collections_Generic_List_UIManager_PokemonParamMapping__o*
            int32_t _id_GrayscaleAmount;
            void* _comparerTownMapGuide; // Dpr_UI_UIManager_ComparerTownMapGuide_o*
            void* _comparerPlaceName; // Dpr_UI_UIManager_ComparerPlaceName_o*
        };

        static inline Dpr::UI::UIManager::Object* instance() {
            return SmartPoint::AssetAssistant::SingletonMonoBehaviour::get_Instance(SmartPoint::AssetAssistant::SingletonMonoBehaviour::Method$$UIManager$$get_Instance);
        }

        static inline StaticILMethod<0x04c8ff28, Dpr::UI::BattleTowerRecordWindow> Method$$CreateUIWindow_BattleTowerRecordWindow_ {};

        static inline StaticILMethod<0x04c8ff30, Dpr::UI::BoxWindow> Method$$CreateUIWindow_BoxWindow_ {};

        static inline StaticILMethod<0x04c8ff48, Dpr::UI::ContextMenuWindow> Method$$CreateUIWindow_ContextMenuWindow_ {};

        static inline StaticILMethod<0x04c8ff98, Dpr::UI::PokemonStatusWindow> Method$$CreateUIWindow_PokemonStatusWindow_ {};

        static inline StaticILMethod<0x04c8ffd0, Dpr::UI::SelectPlayerVisualWindow> Method$$CreateUIWindow_SelectPlayerVisualWindow_ {};

        static inline StaticILMethod<0x04c8ffe8, Dpr::UI::ShopBoutiqueChange> Method$$CreateUIWindow_ShopBoutiqueChange_ {};

        static inline StaticILMethod<0x04c90058, Dpr::UI::UIKinomi> Method$$CreateUIWindow_UIKinomi_ {};

        static inline StaticILMethod<0x04c90098, Dpr::UI::UIWazaManage> Method$$CreateUIWindow_UIWazaManage_ {};

        static inline StaticILMethod<0x04c90130, Dpr::UI::UIWindow> Method$$GetCurrentUIWindow_UIWindow_ {};

        template <typename T>
        inline T::Object* CreateUIWindow(UIWindowID windowId, ILMethod<T>& method) {
            return external<typename T::Object*>(0x01cf9f20, this, (int32_t)windowId, *method);
        }

        template <typename T>
        inline T::Object* GetCurrentUIWindow(ILMethod<T>& method) {
            return external<typename T::Object*>(0x01cfa100, this, *method);
        }

        static inline int32_t Repeat(int32_t value, int32_t start, int32_t end) {
            return external<int32_t>(0x017c4990, value, start, end);
        }

        inline void LoadSpritePokemon(int32_t monsNo, uint16_t formNo, Pml::Sex sex, Pml::PokePara::RareType  rareType, bool isEgg, UnityEngine::Events::UnityAction::Object* onComplete) {
            external<void>(0x017c3ef0, this, monsNo, formNo, sex, rareType, isEgg, onComplete);
        }

        inline void LoadSpritePokemon(Pml::PokePara::PokemonParam::Object* pokemonParam, UnityEngine::Events::UnityAction::Object* onComplete) {
            external<void>(0x017c3e40, this, pokemonParam, onComplete);
        }

        inline UnityEngine::Sprite::Object* GetSpritePokemonTypeZukan(int32_t typeNo, int32_t langId) {
            return external<UnityEngine::Sprite::Object*>(0x017c2650, this, typeNo, langId);
        }

        inline UnityEngine::Sprite::Object* GetAtlasSprite(SpriteAtlasID spriteAtlasId, System::String::Object* name) {
            return external<UnityEngine::Sprite::Object*>(0x017a9080, this, spriteAtlasId, name);
        }

        inline void LoadSpriteItem(uint16_t itemNo, UnityEngine::Events::UnityAction::Object* onComplete) {
            external<void>(0x017c48b0, this, itemNo, onComplete);
        }

        inline System::Collections::IEnumerator::Object* OpLoadWindows(
                System::Collections::Generic::List$$int32_t::Object* windowIDs, bool isVariant) {
            return external<System::Collections::IEnumerator::Object*>(0x017b0380, this, windowIDs, isVariant);
        }

        inline void _ReleaseUIWindow(UIWindow* window) {
            external<void>(0x017a58a0, this, window);
        }

        inline XLSXContent::UIDatabase::SheetPokemonIcon::Object* GetPokemonIconData(int32_t monsNo, uint16_t formNo, Pml::Sex sex, Pml::PokePara::RareType rareType, bool isEgg) {
            return external<XLSXContent::UIDatabase::SheetPokemonIcon::Object*>(0x017c1250, this, monsNo, formNo, sex, rareType, isEgg);
        }

        friend UIManager::InitializeStateBit operator&(UIManager::InitializeStateBit lhs, UIManager::InitializeStateBit rhs) {
            return static_cast<UIManager::InitializeStateBit>(
                    static_cast<int32_t>(lhs) & static_cast<int32_t>(rhs)
            );
        }

        friend UIManager::InitializeStateBit operator|(UIManager::InitializeStateBit lhs, UIManager::InitializeStateBit rhs) {
            return static_cast<UIManager::InitializeStateBit>(
                    static_cast<int32_t>(lhs) | static_cast<int32_t>(rhs)
            );
        }

    };
}

static_assert(offsetof(Dpr::UI::UIManager::Fields, _mdUis) == 0x20);
static_assert(sizeof(Dpr::UI::UIManager::Fields) == 280);

