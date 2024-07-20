#include "exlaunch.hpp"
#include "logger/logger.h"
#include "externals/UIWindowID.h"
#include "externals/Dpr/UI/BattleTowerRecordWindow.h"
#include "externals/FlagWork.h"
#include "externals/FlagWork_Enums.h"
#include "externals/UnityEngine/_Object.h"
#include "externals/BtlTowerWork.h"
#include "externals/RecordWork.h"
#include "externals/Dpr/UI/BoxWindow.h"
#include "externals/SmartPoint/AssetAssistant/Sequencer.h"
#include "externals/Dpr/UI/SelectPlayerVisualWindow.h"
#include "externals/OpeningController.h"
#include "ui/ui.h"
#include "externals/Dpr/Demo/DemoSceneManager.h"
#include "externals/Dpr/Demo/Demo_Hakase.h"
#include "externals/Dpr/UI/UINavigator.h"
#include "externals/Audio/AudioManager.h"
#include "externals/UnityEngine/Animator.h"
#include "externals/Dpr/UI/UIWindowStateMachine.h"
#include "externals/Dpr/MsgWindow/MsgWindow.h"
#include "externals/UnityEngine/Mathf.h"
#include "externals/Dpr/Message/MessageManager.h"
#include "externals/Dpr/UI/ContextMenuItem.h"
#include "externals/ContextMenuID.h"
#include "externals/Dpr/UI/ContextMenuWindow.h"
#include "externals/Dpr/UI/SelectLanguageWindow.h"
#include "externals/Dpr/UI/CardBackView.h"
#include "externals/System/Func.h"
#include "externals/Dpr/Message/MessageWordSetHelper.h"
#include "data/utils.h"
#include "data/types.h"
#include "save/save.h"
#include "externals/Dpr/UI/PokemonStatusWindow.h"
#include "externals/Dpr/BattleMatching/BattleMatchingWork.h"
#include "externals/UnityEngine/Sprite.h"
#include "externals/Dpr/UI/PokemonIcon.h"

const int32_t typeSelectorRowNum = 5;
const int32_t typeSelectorColNum = 4;
const uint32_t AK_EVENTS_UI_COMMON_DONE = 0x4491b890;
const uint32_t AK_EVENTS_UI_COMMON_SELECT = 0xb7533038;
const uint32_t AK_EVENTS_UI_COMMON_BEEP = 0x707237C4;

void RankTextHandler(Dpr::UI::BoxWindow::__c__DisplayClass200_0::Object* __this) {
    system_load_typeinfo(0x96a3);
    auto saveData = &getCustomSaveData()->battleHall;
    int32_t typeIndex = FlagWork::GetWork(FlagWork_Work::WK_BATTLE_HALL_CURRENT_TYPE);
    Rank currentRank = saveData->getRank(TYPES[typeIndex]);

    Dpr::Message::MessageWordSetHelper::getClass()->initIfNeeded();
    Dpr::Message::MessageWordSetHelper::SetDigitWord(0, currentRank <= RANK_10 ? currentRank + 1 : RANK_10 + 1);
}

void MonsIconTextHandler(Dpr::UI::BoxWindow::__c__DisplayClass200_0::Object* __this) {
    system_load_typeinfo(0x96a3);
    auto saveData = &getCustomSaveData()->battleHall;

    Dpr::Message::MessageWordSetHelper::getClass()->initIfNeeded();
    Dpr::Message::MessageWordSetHelper::SetMonsNameWord(0, saveData->streakPokePID);
}

void MonsSpriteHandler(Dpr::UI::PokemonIcon::Object* __this, UnityEngine::Sprite::Object* sprite) {
    system_load_typeinfo(0x6d84);
    __this->fields._imageMonsIcon->set_sprite(sprite);
    auto component = reinterpret_cast<UnityEngine::Component::Object*>(__this->fields._imageMonsIcon);
    auto gameObj = component->get_gameObject();
    bool inequalityCheck = UnityEngine::_Object::op_Inequality(reinterpret_cast<UnityEngine::_Object::Object*>(sprite),
                                                               nullptr);
    gameObj->SetActive(inequalityCheck);
}

bool SetSelectIndex(Dpr::UI::BoxWindow::Object* __this, int32_t index, bool isInitialized = false) {
    system_load_typeinfo(0x79bb);
    UnityEngine::RectTransform::Object* boxTrays = __this->fields._boxTrayRoot;
    UnityEngine::Transform::Object* traysChild = reinterpret_cast<UnityEngine::Transform::Object*>(boxTrays)->GetChild(0);

    if (!isInitialized) {
        int32_t beforeIndex = __this->fields._currentTrayIndex;
        if (beforeIndex == index) {
            return false;
        }

        else {
            Logger::log("[SetSelectIndex] SelectIndex: %d.\n", index);
        }

        __this->fields._currentTrayIndex = index;
    }

    else {
        __this->fields._currentTrayIndex = index;
    }


    auto cursorComponent = (UnityEngine::Component::Object*) __this->fields._cursor;
    auto transform = cursorComponent->get_transform();

    auto parent = reinterpret_cast<UnityEngine::Transform::Object*>(
            reinterpret_cast<UnityEngine::Component::Object*>(traysChild->GetChild(index)));
    transform->SetParent(parent, false);
    return true;
}

void UpdateSelect(Dpr::UI::BoxWindow::Object* __this, float deltaTime) {
    system_load_typeinfo(0x26bd);

    // Diagonal Movement Check
    Dpr::UI::UIManager::getClass()->initIfNeeded();
    auto uiWindow = (Dpr::UI::UIWindow::Object*) __this;
    bool isRepeatButton = uiWindow->IsRepeatButton(Dpr::UI::UIManager::getClass()->static_fields->StickLRight |
                                              Dpr::UI::UIManager::getClass()->static_fields->StickLLeft, false);
    if (isRepeatButton) {
        isRepeatButton = uiWindow->IsRepeatButton(Dpr::UI::UIManager::getClass()->static_fields->StickLDown |
                                                  Dpr::UI::UIManager::getClass()->static_fields->StickLUp, false);

        if (isRepeatButton) return;
    }

    int32_t selectIndex = __this->fields._currentTrayIndex;
    int32_t x = selectIndex % typeSelectorColNum;
    int32_t y = selectIndex / typeSelectorColNum;

    //L-Stick Right
    if (uiWindow->IsPushButton(Dpr::UI::UIManager::getClass()->static_fields->StickLRight, false)) {
        x = Dpr::UI::UIManager::Repeat(x + 1, 0, typeSelectorColNum - 1);
        if (SetSelectIndex(__this, x + y * typeSelectorColNum)) {
            Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_SELECT, nullptr);
        }
    }

    else if (uiWindow->IsRepeatButton(Dpr::UI::UIManager::getClass()->static_fields->StickLRight, false)) {
        x = UnityEngine::Mathf::Min(x + 1, typeSelectorColNum - 1);
        if (SetSelectIndex(__this, x + y * typeSelectorColNum)) {
            Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_SELECT, nullptr);
        }
    }

        //L-Stick Left
    else if (uiWindow->IsPushButton(Dpr::UI::UIManager::getClass()->static_fields->StickLLeft, false)) {
        x = Dpr::UI::UIManager::Repeat(x - 1, 0, typeSelectorColNum - 1);
        if (SetSelectIndex(__this, x + y * typeSelectorColNum)) {
            Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_SELECT, nullptr);
        }
    }

    else if (uiWindow->IsRepeatButton(Dpr::UI::UIManager::getClass()->static_fields->StickLLeft, false)) {
        x = UnityEngine::Mathf::Max(x - 1, 0);
        if (SetSelectIndex(__this, x + y * typeSelectorColNum)) {
            Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_SELECT, nullptr);
        }
    }

        //L-Stick Down
    else if (uiWindow->IsPushButton(Dpr::UI::UIManager::getClass()->static_fields->StickLDown, false)) {
        y = Dpr::UI::UIManager::Repeat(y + 1, 0, typeSelectorRowNum - 1);
        if (SetSelectIndex(__this, x + y * typeSelectorColNum)) {
            Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_SELECT, nullptr);
        }
    }

    else if (uiWindow->IsRepeatButton(Dpr::UI::UIManager::getClass()->static_fields->StickLDown, false)) {
        y = UnityEngine::Mathf::Min(y + 1, typeSelectorRowNum - 1);
        if (SetSelectIndex(__this, x + y * typeSelectorColNum)) {
            Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_SELECT, nullptr);
        }
    }

        //L-Stick Up
    else if (uiWindow->IsPushButton(Dpr::UI::UIManager::getClass()->static_fields->StickLUp, false)) {
        y = Dpr::UI::UIManager::Repeat(y - 1, 0, typeSelectorRowNum - 1);
        if (SetSelectIndex(__this, x + y * typeSelectorColNum)) {
            Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_SELECT, nullptr);
        }
    }

    else if (uiWindow->IsRepeatButton(Dpr::UI::UIManager::getClass()->static_fields->StickLUp, false)) {
        y = UnityEngine::Mathf::Max(y- 1, 0);
        if (SetSelectIndex(__this, x + y * typeSelectorColNum)) {
            Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_SELECT, nullptr);
        }
    }
}

void MatronInboundMessageHandler(Dpr::UI::UIWindow::Object* window) {

    window->CloseMessageWindow();

    auto boxWindow = reinterpret_cast<Dpr::UI::BoxWindow::Object*>(window);
    UnityEngine::RectTransform::Object* boxTrays = boxWindow->fields._boxTrayRoot;
    auto traysChild = boxTrays->cast<UnityEngine::Transform>()->GetChild(0);

    UnityEngine::UI::Image::Object* dimmedImage;
    UnityEngine::GameObject* gameObj;
    for (int32_t i = 0; i < TYPE_COUNT+2; ++i) {
        if (i != 16) {
            dimmedImage = traysChild->GetChild({i, 2})->GetComponent(
                    UnityEngine::Component::Method$$Image$$GetComponent);
            gameObj = dimmedImage->cast<UnityEngine::Component>()->get_gameObject();
            gameObj->SetActive(i != 19); // Sets all dimmed images active except 19 which is set inactive.
        }
    }

    if (SetSelectIndex(boxWindow, 19)) {
        Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_SELECT, nullptr);
    }

    window->fields._input->fields._inputEnabled = true;

}

bool OpenConfirmMessageWindowHandler2(Dpr::UI::UIWindow::Object* window, Dpr::UI::ContextMenuItem::Object* contextMenuItem) {

    window->CloseMessageWindow();

    if (contextMenuItem->fields._param->fields.menuId == ContextMenuID::BOX_YES) {

        if (!FlagWork::GetFlag(FlagWork_Flag::FLAG_FTR_HALL_MATRON_INBOUND) || FlagWork::GetWork(FlagWork_Work::WK_BATTLE_HALL_CURRENT_TYPE) == -1) {
            reinterpret_cast<Dpr::UI::BoxWindow::Object*>(window)->Close(window->fields.onClosed, window->fields._prevWindowId);
            Dpr::UI::UIManager::instance()->_ReleaseUIWindow(window);
            if (window->fields.onClosed != nullptr) {
                window->fields.onClosed->Invoke();
            }
        }

        else {
            Dpr::MsgWindow::MsgWindowParam::Object* msgWindowParam = Dpr::MsgWindow::MsgWindowParam::newInstance();
            auto msgManager = Dpr::Message::MessageManager::instance();
            msgWindowParam->fields.useMsgFile = msgManager->GetMsgFile(System::String::Create("ss_btl_tower_menu_ui_text"));
            msgWindowParam->fields.labelName = System::String::Create("ftr_hall_stage_typeselect_matron_text");
            msgWindowParam->fields.inputEnabled = true;
            msgWindowParam->fields.inputCloseEnabled = false;

            system_load_typeinfo(0x79b7);
            MethodInfo* mi = (
                    *Dpr::UI::SelectLanguageWindow::Method$$SelectLanguageWindow__OpenConfirmMessageWindow__b__18_0)->
                    copyWith((Il2CppMethodPointer) &MatronInboundMessageHandler);
            auto onFinishedShowAllMessage = System::Action::getClass(
                    System::Action::void_TypeInfo)->newInstance(window, mi);

            msgWindowParam->fields.onFinishedShowAllMessage = onFinishedShowAllMessage;

            window->OpenMessageWindow(msgWindowParam);

        }

    }

    else {
        window->fields._input->fields._inputEnabled = true;
    }

    return true;
}

void OpenConfirmMessageWindowHandler(Dpr::UI::UIWindow::Object* window) {
    system_load_typeinfo(0x79bd);
    MethodInfo* mi = (
            *Dpr::UI::SelectLanguageWindow::Method$$SelectLanguageWindow__OpenConfirmMessageWindow__b__18_1)->
            copyWith((Il2CppMethodPointer) &OpenConfirmMessageWindowHandler2);

    auto sysFunc = System::Func::getClass(
            System::Func::ContextMenuItem__bool__TypeInfo)->newInstance(window, mi);
    Dpr::UI::ContextMenuWindow* contextMenu = window->CreateContextMenuYesNo(sysFunc, 0xb53c8c80);
    reinterpret_cast<Dpr::UI::BoxWindow::Object*>(window)->fields._contextMenu = reinterpret_cast<Dpr::UI::ContextMenuWindow::Object*>(contextMenu);
}

int32_t RemapTypeIndex(int32_t selectIndex) {
    switch (selectIndex) {
        case TypeSelectorIndex::FIRE: return array_index(TYPES, "Fire");
        case TypeSelectorIndex::WATER: return array_index(TYPES, "Water");
        case TypeSelectorIndex::ELECTRIC: return array_index(TYPES, "Electric");
        case TypeSelectorIndex::GRASS: return array_index(TYPES, "Grass");
        case TypeSelectorIndex::ICE: return array_index(TYPES, "Ice");
        case TypeSelectorIndex::FIGHTING: return array_index(TYPES, "Fighting");
        case TypeSelectorIndex::POISON: return array_index(TYPES, "Poison");
        case TypeSelectorIndex::GROUND: return array_index(TYPES, "Ground");
        case TypeSelectorIndex::FLYING: return array_index(TYPES, "Flying");
        case TypeSelectorIndex::PSYCHIC: return array_index(TYPES, "Psychic");
        case TypeSelectorIndex::BUG: return array_index(TYPES, "Bug");
        case TypeSelectorIndex::ROCK: return array_index(TYPES, "Rock");
        case TypeSelectorIndex::GHOST: return array_index(TYPES, "Ghost");
        case TypeSelectorIndex::DRAGON: return array_index(TYPES, "Dragon");
        case TypeSelectorIndex::DARK: return array_index(TYPES, "Dark");
        case TypeSelectorIndex::STEEL: return array_index(TYPES, "Steel");
        case TypeSelectorIndex::FAIRY: return array_index(TYPES, "Fairy");

            // Normal Type
        default: return selectIndex;
    }
}

int32_t FindSelectIndex(int32_t currentType) {
    nn::vector<int32_t> selectIndexMap = {TypeSelectorIndex::NORMAL, TypeSelectorIndex::FIGHTING, TypeSelectorIndex::FLYING,
                                          TypeSelectorIndex::POISON, TypeSelectorIndex::GROUND, TypeSelectorIndex::ROCK,
                                          TypeSelectorIndex::BUG, TypeSelectorIndex::GHOST, TypeSelectorIndex::STEEL,
                                          TypeSelectorIndex::FIRE, TypeSelectorIndex::WATER, TypeSelectorIndex::GRASS,
                                          TypeSelectorIndex::ELECTRIC, TypeSelectorIndex::PSYCHIC, TypeSelectorIndex::ICE,
                                          TypeSelectorIndex::DRAGON, TypeSelectorIndex::DARK, TypeSelectorIndex::FAIRY};


    if (currentType == -2) return 16;
    else if (currentType == -1) return 19;

    return selectIndexMap.at(currentType);
}


void OnUpdate(Dpr::UI::BoxWindow::Object* __this, float deltaTime) {
    // Initialize UI Manager
    Dpr::UI::UIManager::getClass()->initIfNeeded();
    auto uiManager = Dpr::UI::UIManager::instance();

    // Get the current UI window and check if it's different from the current BoxWindow instance
    auto retrievedWindow = (UnityEngine::_Object::Object*) uiManager->GetCurrentUIWindow(Dpr::UI::UIManager::Method$$GetCurrentUIWindow_UIWindow_);
    bool inequalityCheck = UnityEngine::_Object::op_Inequality(retrievedWindow, (UnityEngine::_Object::Object*) __this);

    if (!inequalityCheck && __this->fields._input->fields._inputEnabled) {
        auto msgWindow = __this->fields._messageWindow;

        // Check if there is an active message window
        inequalityCheck = UnityEngine::_Object::op_Inequality((UnityEngine::_Object::Object*) msgWindow, nullptr);

        if (inequalityCheck && msgWindow->get_isEnabledInput()) {
            return;
        }

        Dpr::UI::UIManager::getClass()->initIfNeeded();
        auto uiWindow = (Dpr::UI::UIWindow::Object*) __this;
        auto buttonA = Dpr::UI::UIManager::getClass()->static_fields->ButtonA;

        // Check if A button is pressed
        if (uiWindow->IsPushButton(buttonA, false)) {
            Logger::log("[BoxWindow$$OnUpdate] Pressed A.\n");

            int32_t selectIndex = __this->fields._currentTrayIndex;
            UnityEngine::RectTransform::Object* boxTrays = __this->fields._boxTrayRoot;
            auto traysChild = boxTrays->cast<UnityEngine::Transform>()->GetChild(0);

            bool isDimmed = false;

            if (selectIndex != TypeSelectorIndex::SUMMARY) {
                UnityEngine::UI::Image::Object *dimmedImage = traysChild->GetChild({selectIndex, 2})->GetComponent(
                        UnityEngine::Component::Method$$Image$$GetComponent);
                isDimmed = dimmedImage->cast<UnityEngine::Component>()->get_gameObject()->get_activeSelf();
            }

            if (selectIndex == TypeSelectorIndex::SUMMARY) {
                Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_DONE, nullptr);
                Dpr::UI::PokemonStatusWindow::Param::Object* windowParam = Dpr::UI::PokemonStatusWindow::Param::newInstance();

                auto paramList = System::Collections::Generic::List$$PokemonParam::getClass(
                        System::Collections::Generic::List$$PokemonParam::typeInfo)->newInstance(
                                *System::Collections::Generic::List$$PokemonParam::Method$$ctor);

                Dpr::BattleMatching::BattleMatchingWork::getClass()->initIfNeeded();
                auto pokeParam = Dpr::BattleMatching::BattleMatchingWork::getClass()->static_fields->pokemonParams;
                auto orderIndexList = Dpr::BattleMatching::BattleMatchingWork::getClass()->static_fields->orderIndexList;
                auto playerPoke = pokeParam->m_Items[orderIndexList->m_Items[0]];

                paramList->Add(playerPoke);
                windowParam->fields.pokemonParams = paramList;
                windowParam->fields.selectIndex = 0;
                windowParam->fields.selectTabIndex = 0;
                windowParam->fields.limitType = 4;

                __this->OpenStatusWindow(windowParam, nullptr);
            }

            else if (!isDimmed && selectIndex != TypeSelectorIndex::FAIRY) {
                Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_DONE, nullptr);
                //__this->fields._cursor->Play()
                __this->fields._input->fields._inputEnabled = false;

                Dpr::MsgWindow::MsgWindowParam::Object* msgWindowParam = Dpr::MsgWindow::MsgWindowParam::newInstance();
                auto msgManager = Dpr::Message::MessageManager::instance();
                msgWindowParam->fields.useMsgFile = msgManager->GetMsgFile(System::String::Create("ss_btl_tower_menu_ui_text"));
                msgWindowParam->fields.labelName = System::String::Create(selectIndex ==
                        TypeSelectorIndex::MATRON ? "ftr_hall_stage_typeselect_matron_text_2" : "ftr_hall_stage_typeselect_confirm");
                msgWindowParam->fields.inputEnabled = true;
                msgWindowParam->fields.inputCloseEnabled = false;

                if (selectIndex != TypeSelectorIndex::MATRON) {
                    int32_t remappedIndex = RemapTypeIndex(selectIndex);
                    Rank currentRank = getCustomSaveData()->battleHall.getRank(TYPES[remappedIndex]);

                    Dpr::Message::MessageWordSetHelper::SetWazaTypeWord(0, remappedIndex);
                    Dpr::Message::MessageWordSetHelper::SetDigitWord(1, static_cast<int32_t>(currentRank) + 1);
                }

                else {
                    FlagWork::SetWork(FlagWork_Work::WK_BATTLE_HALL_CURRENT_TYPE, -1);
                }

                system_load_typeinfo(0x79b7);
                MethodInfo* mi = (
                        *Dpr::UI::SelectLanguageWindow::Method$$SelectLanguageWindow__OpenConfirmMessageWindow__b__18_0)->
                        copyWith((Il2CppMethodPointer) &OpenConfirmMessageWindowHandler);
                auto onFinishedShowAllMessage = System::Action::getClass(
                        System::Action::void_TypeInfo)->newInstance(uiWindow, mi);

                msgWindowParam->fields.onFinishedShowAllMessage = onFinishedShowAllMessage;

                uiWindow->OpenMessageWindow(msgWindowParam);
            }

            else {
                Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_BEEP, nullptr);
            }

        }
        UpdateSelect(__this, deltaTime);
    }
}

void OpenBoxWindow(Dpr::UI::BoxWindow::Object* __this, Dpr::UI::BoxWindow::OpenParam::Object* param,
                   int32_t prevWindowId, bool isDuckOn) {

    system_load_typeinfo(0x2674);
    __this->fields._param = param;
    __this->fields._isDuckOn = isDuckOn & 1;
    __this->fields._searchData = (((__this->fields)._param)->fields).searchData;
    __this->fields._onSelected = (System::Action::Object*) nullptr;

    system_load_typeinfo(0x266b);

    Dpr::UI::BoxWindow::__OpOpen_d__200::Object* displayClass =
            Dpr::UI::BoxWindow::__OpOpen_d__200::newInstance(0);

    auto boxInstance = &(displayClass->fields).__4__this;
    *boxInstance = __this;
    displayClass->fields.prevWindowId = prevWindowId;

    SmartPoint::AssetAssistant::Sequencer::getClass()->initIfNeeded();

    auto IEnumerator = SmartPoint::AssetAssistant::Sequencer::Start(
            (System::Collections::IEnumerator::Object*) displayClass);
    __this->fields._coOpen = IEnumerator;
}

HOOK_DEFINE_TRAMPOLINE(BoxWindow$$Open) {
    static void Callback(Dpr::UI::BoxWindow::Object* __this, int32_t prevWindowId, bool isDuckOn) {
        switch (__this->fields.instance->fields._windowId) {
            case UIWindowID::BOX:
            default:
                //Logger::log("[BoxWindow$$Open] UIWindowID = BOX.\n");
                Orig(__this, prevWindowId, isDuckOn);
                break;
            case UIWindowID::BATTLEHALL_TYPE_SELECT:
                //Logger::log("[BoxWindow$$Open] UIWindowID = BATTLEHALL_TYPE_SELECT.\n");

                system_load_typeinfo(0x2675);
                Dpr::UI::BoxWindow::OpenParam::Object* openParam =
                        Dpr::UI::BoxWindow::OpenParam::newInstance();
                openParam->fields.openType = 0;
                openParam->fields.tray = 0;
                OpenBoxWindow(__this, openParam, prevWindowId, isDuckOn);
                break;
        }
    }
};

HOOK_DEFINE_TRAMPOLINE(BoxWindow$$OpOpenMoveNext) {
    static bool Callback(Dpr::UI::BoxWindow::__OpOpen_d__200::Object* __this) {
        Logger::log("[BoxWindow...d__200$$MoveNext].\n");
        UIWindowID windowId = FlagWork::GetFlag(FlagWork_Flag::FLAG_UI_WINDOW_SWITCH)
                              ? UIWindowID::BATTLEHALL_TYPE_SELECT : UIWindowID::BOX;
        switch (windowId) {
            case UIWindowID::BOX: {
                return Orig(__this);
            }
            case UIWindowID::BATTLEHALL_TYPE_SELECT: {
                system_load_typeinfo(0x92a1);
                system_load_typeinfo(0x26c7);
                Dpr::UI::BoxWindow::Object* window = (__this->fields).__4__this;
                switch ((__this->fields).__1__state) {
                    case 0: {
                        (__this->fields).__1__state = -1;

                        ((Dpr::UI::UIWindow::Object*) window)->OnOpen(__this->fields.prevWindowId);

                        window->SetupKeyguide();
                        auto audioManager = Audio::AudioManager::instance();
                        audioManager->PlaySe(0xb53c8c80, nullptr);
                        audioManager->SetBgmEvent(0x743e45ca, false);

                        system_load_typeinfo(0x870a);

                        UnityEngine::RectTransform::Object* boxTrays = window->fields._boxTrayRoot;
                        auto traysChild = boxTrays->cast<UnityEngine::Transform>()->GetChild(0);

                        MethodInfo* mi = (*Dpr::UI::BoxWindow::__c__DisplayClass200_0::Method$$__OpOpen__b__1)->
                                copyWith((Il2CppMethodPointer) &RankTextHandler);

                        MethodInfo* monsIconMI = (*Dpr::UI::BoxWindow::__c__DisplayClass200_0::Method$$__OpOpen__b__1)->
                                copyWith((Il2CppMethodPointer) &MonsIconTextHandler);

                        auto opOpenDisplayClass = __this->fields.__8__1;
                        auto onSet = UnityEngine::Events::UnityAction::getClass(
                                UnityEngine::Events::UnityAction::void_TypeInfo)->newInstance(opOpenDisplayClass, mi);

                        auto onSetMonsIcon = UnityEngine::Events::UnityAction::getClass(
                                UnityEngine::Events::UnityAction::void_TypeInfo)->newInstance(opOpenDisplayClass, monsIconMI);

                        Dpr::UI::UIText::Object* rankText;
                        UnityEngine::UI::Image::Object* dimmedImage;
                        UnityEngine::GameObject* gameObj;
                        for (int32_t i = 0; i < TYPE_COUNT; ++i) { //Intentionally excludes Fairy for now
                            if (i != 16) {
                                rankText = traysChild->GetChild({i, 3})->GetComponent(
                                        UnityEngine::Component::Method$$UIText$$GetComponent);
                                int32_t typeIndex = RemapTypeIndex(i);

                                dimmedImage = traysChild->GetChild({i, 2})->GetComponent(
                                        UnityEngine::Component::Method$$Image$$GetComponent);
                                gameObj = dimmedImage->cast<UnityEngine::Component>()->get_gameObject();
                                gameObj->SetActive(getCustomSaveData()->battleHall.currentRank[typeIndex] == RANK_COUNT);
                                rankText->SetFormattedText(onSet, nullptr, nullptr);
                            }
                        }

                        system_load_typeinfo(0x73b2);

                        Dpr::UI::UIText::Object* monsIconText = traysChild->GetChild(
                                {TypeSelectorIndex::SUMMARY, 1})->GetComponent(
                                        UnityEngine::Component::Method$$UIText$$GetComponent);

                        monsIconText->SetFormattedText(onSetMonsIcon, nullptr, nullptr);
                        Logger::log("[OnOpen] Set monsIconText.\n");
                        Dpr::UI::PokemonIcon::Object* monsIcon = traysChild->GetChild(
                                {TypeSelectorIndex::SUMMARY, 2})->GetComponent(
                                UnityEngine::Component::Method$$PokemonIcon$$GetComponent);
                        Logger::log("[OnOpen] Got monsIcon component.\n");
                        Dpr::BattleMatching::BattleMatchingWork::getClass()->initIfNeeded();
                        auto pokeParam = Dpr::BattleMatching::BattleMatchingWork::getClass()->static_fields->pokemonParams;
                        auto orderIndexList = Dpr::BattleMatching::BattleMatchingWork::getClass()->static_fields->orderIndexList;
                        auto playerPoke = pokeParam->m_Items[orderIndexList->m_Items[0]];
                        Logger::log("[OnOpen] Retrieved poke params.\n");

                        int32_t monsNo = playerPoke->cast<Pml::PokePara::CoreParam>()->GetMonsNo();
                        int32_t formNo = playerPoke->cast<Pml::PokePara::CoreParam>()->GetFormNo();
                        uint8_t sex = playerPoke->cast<Pml::PokePara::CoreParam>()->GetSex();
                        uint8_t rareType = playerPoke->cast<Pml::PokePara::CoreParam>()->GetRareType();

                        Logger::log("[OnOpen] Retrieved all lookup details.\n");

                        MethodInfo* onCompleteMI = (*Dpr::UI::PokemonIcon::Method$$__Load__b__9_0)->copyWith(
                                (Il2CppMethodPointer) &MonsSpriteHandler);
                        auto onComplete = UnityEngine::Events::UnityAction::getClass(
                                UnityEngine::Events::UnityAction::Sprite_TypeInfo)->newInstance(monsIcon, onCompleteMI);

                        Logger::log("[OnOpen] onComplete primed.\n");

                        Dpr::UI::UIManager::instance()->LoadSpritePokemon(monsNo, formNo, sex, rareType, false, onComplete);

                        Logger::log("[OnOpen] Loaded sprite.\n");

                        (__this->fields).__2__current = reinterpret_cast<Il2CppObject *>(((Dpr::UI::UIWindow::Object *) window)->OpPlayOpenWindowAnimation(
                                __this->fields.prevWindowId, nullptr));

                        (__this->fields).__1__state = 1;
                        return true;
                    }

                    case 1: {
                        (__this->fields).__1__state = -1;
                        SmartPoint::AssetAssistant::Sequencer::getClass()->initIfNeeded();
                        SmartPoint::AssetAssistant::Sequencer::TickCallback::Object* update =
                                SmartPoint::AssetAssistant::Sequencer::getClass()->static_fields->update;
                        auto tickCallback = SmartPoint::AssetAssistant::Sequencer::TickCallback::newInstance(
                                reinterpret_cast<Il2CppObject*>(window),
                                *Dpr::UI::BoxWindow::Method$$Dpr_UI_BoxWindow_OnUpdate);
                        auto sendUpdate = System::Delegate::Combine(reinterpret_cast<System::Delegate::Object*>(update),
                                                  reinterpret_cast<System::Delegate::Object*>(tickCallback));

                        SmartPoint::AssetAssistant::Sequencer::getClass()->static_fields->update =
                                reinterpret_cast<SmartPoint::AssetAssistant::Sequencer::TickCallback::Object*>(sendUpdate);
                        (__this->fields).__2__current = nullptr;
                        (__this->fields).__1__state = 2;
                        return true;
                    }

                    case 2: {
                        (__this->fields).__1__state = -1;
                        window->fields._input->fields._inputEnabled = true;
                        auto cursor = window->fields._cursor;
                        cursor->SetActive(true);

                        int32_t lastSelected = FindSelectIndex(FlagWork::GetWork(
                                FlagWork_Work::WK_BATTLE_HALL_CURRENT_TYPE));
                        SetSelectIndex(window, lastSelected, true);

                        (__this->fields).__2__current = nullptr;
                        (__this->fields).__1__state = 3;
                        return true;
                    }

                    case 3: {
                        (__this->fields).__1__state = -1;

                        window->fields._coOpen = nullptr;
                        return false;
                    }

                    default: {
                        return false;
                    }
                }
            }
            default: {
                return false;
            }
        }
    }
};

HOOK_DEFINE_TRAMPOLINE(BoxWindow$$OnUpdate) {
    static void Callback(Dpr::UI::BoxWindow::Object* __this, float deltaTime) {
        switch (__this->fields.instance->fields._windowId) {
            case UIWindowID::BOX:
            default:
                //Logger::log("[BoxWindow$$OnUpdate] UIWindowID = BOX.\n");
                Orig(__this, deltaTime);
                break;
            case UIWindowID::BATTLEHALL_TYPE_SELECT:
                //Logger::log("[BoxWindow$$OnUpdate] UIWindowID = BATTLEHALL_TYPE_SELECT.\n");
                OnUpdate(__this, deltaTime);
                break;
        }
    }
};

HOOK_DEFINE_TRAMPOLINE(BoxWindow$$Awake) {
    static void Callback(Dpr::UI::BoxWindow::Object* __this) {
        switch (FlagWork::GetFlag(FlagWork_Flag::FLAG_UI_WINDOW_SWITCH) ? UIWindowID::BATTLEHALL_TYPE_SELECT : UIWindowID::BOX) {
            case UIWindowID::BOX:
            default:
                //Logger::log("[BoxWindow$$Awake] UIWindowID = BOX.\n");
                Orig(__this);
                break;
            case UIWindowID::BATTLEHALL_TYPE_SELECT:
                //Logger::log("[BoxWindow$$Awake] UIWindowID = BATTLEHALL_TYPE_SELECT.\n");
                Orig(__this);
                break;
        }
    }
};

HOOK_DEFINE_TRAMPOLINE(BoxWindow$$Close) {
    static void Callback(Dpr::UI::BoxWindow::Object* __this, UnityEngine::Events::UnityAction::Object* onClosed_, int32_t nextWindowId) {
        switch (__this->fields.instance->fields._windowId) {
            case UIWindowID::BOX:
            default:
                //Logger::log("[BoxWindow$$Close] UIWindowID = BOX.\n");
                Orig(__this, onClosed_, nextWindowId);
                break;
            case UIWindowID::BATTLEHALL_TYPE_SELECT:
                //Logger::log("[BoxWindow$$Close] UIWindowID = BATTLEHALL_TYPE_SELECT.\n");

                system_load_typeinfo(0x2645);
                system_load_typeinfo(0x266a);

                if (__this->fields._coClose != nullptr)
                    return;

                Dpr::UI::BoxWindow::__OpClose_d__204::Object* displayClass =
                        Dpr::UI::BoxWindow::__OpClose_d__204::newInstance(0);

                displayClass->fields.__4__this = __this;
                displayClass->fields.onClosed_ = onClosed_;
                displayClass->fields.nextWindowId = nextWindowId;

                SmartPoint::AssetAssistant::Sequencer::getClass()->initIfNeeded();

                auto IEnumerator = SmartPoint::AssetAssistant::Sequencer::Start(
                        (System::Collections::IEnumerator::Object*) displayClass);
                __this->fields._coClose = IEnumerator;
                break;
        }
    }
};

HOOK_DEFINE_TRAMPOLINE(BoxWindow$$OpCloseMoveNext) {
    static bool Callback(Dpr::UI::BoxWindow::__OpClose_d__204::Object* __this) {
        Logger::log("[BoxWindow...d__204$$MoveNext].\n");
        UIWindowID windowId = FlagWork::GetFlag(FlagWork_Flag::FLAG_UI_WINDOW_SWITCH)
                              ? UIWindowID::BATTLEHALL_TYPE_SELECT : UIWindowID::BOX;
        switch (windowId) {
            case UIWindowID::BOX: {
                return Orig(__this);
            }
            case UIWindowID::BATTLEHALL_TYPE_SELECT: {
                system_load_typeinfo(0x91ed);
                Dpr::UI::BoxWindow::Object* window = (__this->fields).__4__this;
                switch ((__this->fields).__1__state) {
                    case 0: {
                        (__this->fields).__1__state = -1;

                        __this->fields.__8__1 = Dpr::UI::BoxWindow::__c__DisplayClass204_0::newInstance();

                        ((Dpr::UI::UIWindow::Object*)window)->CloseMessageWindow();

                        int32_t currentTypeIndex;
                        if (window->fields._currentTrayIndex == TypeSelectorIndex::MATRON) {
                            currentTypeIndex = -1;
                            Logger::log("[OpClose] Setting current type to: %s.\n", "Matron");
                        }
                        else {
                            currentTypeIndex = RemapTypeIndex(window->fields._currentTrayIndex);
                            Logger::log("[OpClose] Setting current type to: %s.\n", TYPES[currentTypeIndex]);
                        }

                        FlagWork::SetWork(FlagWork_Work::WK_BATTLE_HALL_CURRENT_TYPE, currentTypeIndex);

                        if (window->fields._coOpen == nullptr)
                        {
                            auto audioManager = Audio::AudioManager::instance();
                            audioManager->PlaySe(0xb53c8c8f, nullptr);

                            window->fields._input->fields._inputEnabled = false;
                            window->fields._isControlEnable = false;

                            SmartPoint::AssetAssistant::Sequencer::getClass()->initIfNeeded();
                            SmartPoint::AssetAssistant::Sequencer::TickCallback::Object* update =
                                    SmartPoint::AssetAssistant::Sequencer::getClass()->static_fields->update;
                            auto tickCallback = SmartPoint::AssetAssistant::Sequencer::TickCallback::newInstance(
                                    reinterpret_cast<Il2CppObject*>(window),
                                    *Dpr::UI::BoxWindow::Method$$Dpr_UI_BoxWindow_OnUpdate);
                            auto sendUpdate = System::Delegate::Remove(reinterpret_cast<System::Delegate::Object*>(update),
                                                                        reinterpret_cast<System::Delegate::Object*>(tickCallback));

                            SmartPoint::AssetAssistant::Sequencer::getClass()->static_fields->update =
                                    reinterpret_cast<SmartPoint::AssetAssistant::Sequencer::TickCallback::Object*>(sendUpdate);

                            if (window->fields.onPreClose != nullptr)
                                window->fields.onPreClose->Invoke(reinterpret_cast<Dpr::UI::UIWindow *>(window), UnityEngine::Events::UnityAction::Method$$Invoke$$UIWindow);

                            (__this->fields).__2__current = reinterpret_cast<Il2CppObject *>(((Dpr::UI::UIWindow::Object *) window)->OpPlayCloseWindowAnimationAndWaiting(
                                    __this->fields.nextWindowId));
                            (__this->fields).__1__state = 2;
                        }
                        else
                        {
                            (__this->fields).__2__current = nullptr;
                            (__this->fields).__1__state = 1;
                        }

                        Logger::log("[BoxWindow...d__204$$MoveNext] Case 0 complete.\n");
                        return true;
                    }

                    case 1: {
                        Logger::log("[BoxWindow...d__204$$MoveNext] Starting Case 1.\n");
                        (__this->fields).__1__state = -1;

                        if (window->fields._coOpen == nullptr)
                        {
                            window->fields._input->fields._inputEnabled = false;
                            window->fields._isControlEnable = false;

                            SmartPoint::AssetAssistant::Sequencer::getClass()->initIfNeeded();
                            SmartPoint::AssetAssistant::Sequencer::TickCallback::Object* update =
                                    SmartPoint::AssetAssistant::Sequencer::getClass()->static_fields->update;
                            auto tickCallback = SmartPoint::AssetAssistant::Sequencer::TickCallback::newInstance(
                                    reinterpret_cast<Il2CppObject*>(window),
                                    *Dpr::UI::BoxWindow::Method$$Dpr_UI_BoxWindow_OnUpdate);
                            auto sendUpdate = System::Delegate::Remove(reinterpret_cast<System::Delegate::Object*>(update),
                                                                       reinterpret_cast<System::Delegate::Object*>(tickCallback));

                            SmartPoint::AssetAssistant::Sequencer::getClass()->static_fields->update =
                                    reinterpret_cast<SmartPoint::AssetAssistant::Sequencer::TickCallback::Object*>(sendUpdate);

                            if (window->fields.onPreClose != nullptr)
                                window->fields.onPreClose->Invoke(reinterpret_cast<Dpr::UI::UIWindow *>(window), UnityEngine::Events::UnityAction::Method$$Invoke$$UIWindow);

                            (__this->fields).__2__current = reinterpret_cast<Il2CppObject *>(((Dpr::UI::UIWindow::Object *) window)->OpPlayCloseWindowAnimationAndWaiting(
                                    __this->fields.nextWindowId));
                            (__this->fields).__1__state = 2;
                        }
                        else
                        {
                            (__this->fields).__2__current = nullptr;
                            (__this->fields).__1__state = 1;
                        }

                        Logger::log("[BoxWindow...d__204$$MoveNext] Case 1 Complete.\n");
                        return true;
                    }

                    case 2: {
                        Logger::log("[BoxWindow...d__204$$MoveNext] Starting Case 2.\n");
                        (__this->fields).__1__state = -1;

                        window->fields._messageParam = nullptr;
                        window->fields._keyguideParam = nullptr;

                        SmartPoint::AssetAssistant::SingletonMonoBehaviour::getClass()->initIfNeeded();
                        Dpr::UI::UIManager::Object* uiManager = Dpr::UI::UIManager::instance();
                        uiManager->_ReleaseUIWindow(reinterpret_cast<Dpr::UI::UIWindow *>(window));

                        if (__this->fields.onClosed_ != nullptr)
                            __this->fields.onClosed_->Invoke(reinterpret_cast<Dpr::UI::UIWindow *>(window), UnityEngine::Events::UnityAction::Method$$Invoke$$UIWindow);

                        window->fields._coClose = nullptr;

                        Logger::log("[BoxWindow...d__204$$MoveNext] Case 2 Complete.\n");
                        return false;
                    }

                    default: {
                        return false;
                    }
                }
            }
            default: {
                return false;
            }
        }
    }
};

HOOK_DEFINE_REPLACE(UIWindow$$OnAddContextMenuYesNoItemParams) {
    static void Callback(Dpr::UI::UIWindow::Object* __this, System::Collections::Generic::List$$ContextMenuItem_Param::Object* contextMenuItemParams) {
        switch (__this->fields.instance->fields._windowId) {
            case UIWindowID::BATTLEHALL_TYPE_SELECT:
            {
                Logger::log("[UIWindow$$OnAddContextMenuYesNoItemParams] UIWindowID = BATTLEHALL_TYPE_SELECT.\n");
                system_load_typeinfo(0x5011);

                Dpr::UI::ContextMenuItem::Param::Object* yesParam = Dpr::UI::ContextMenuItem::Param::newInstance();
                Dpr::UI::ContextMenuItem::Param::Object* noParam = Dpr::UI::ContextMenuItem::Param::newInstance();
                yesParam->fields.menuId = ContextMenuID::BOX_YES;
                noParam->fields.menuId = ContextMenuID::BOX_NO;
                contextMenuItemParams->Add(yesParam);
                contextMenuItemParams->Add(noParam);
            }
            break;

            default:
                // Nothing by default
                break;
        }
    }
};

HOOK_DEFINE_INLINE(OpLoadWindows_b__136_0) {
    static void Callback(exl::hook::nx64::InlineCtx* ctx) {
        auto assetName = (System::String::Object*) ctx->X[1];
        auto name = (System::String::Object*) ctx->X[0];
        bool res = System::String::op_Equality(name, assetName);

        if (strcmp(name->asCString().c_str(), "BattleTowerRecord") == 0 ||
            strcmp(name->asCString().c_str(), "BattleHallRecord") == 0 ||
            strcmp(name->asCString().c_str(), "BattleHallTypeSelector") == 0) {

            if (res) {
                Logger::log("[OpLoadWindows_b__136_0] Name: %s, AssetName: %s.\n",
                            name->asCString().c_str(), assetName->asCString().c_str());
                Logger::log("[OpLoadWindows_b__136_0] Returning true.\n");
            }
        }
        ctx->X[0] = res;
    }
};

HOOK_DEFINE_TRAMPOLINE(OpenStatusWindow__b__2) {
    static void Callback(void* __this, Dpr::UI::UIWindow::Object* statusWindow) {
        Logger::log("[OpenStatusWindow__b__2]\n");
        //Orig(__this, statusWindow);

        system_load_typeinfo(0x96ab);

        Dpr::UI::UIManager::getClass()->initIfNeeded();
        auto boxWindow = Dpr::UI::UIManager::instance()->CreateUIWindow(
                UIWindowID::BATTLEHALL_TYPE_SELECT,Dpr::UI::UIManager::Method$$CreateUIWindow_BoxWindow_);

        Dpr::EvScript::EvDataManager::getClass()->initIfNeeded();
        auto manager = Dpr::EvScript::EvDataManager::get_Instanse();

        MethodInfo* mi = *UnityEngine::Events::UnityAction::Method$$Dpr_EvScript_EvDataManager__EvCmdBoxSetProc__b__742_0;
        auto onClosed = UnityEngine::Events::UnityAction::getClass(UnityEngine::Events::UnityAction::UIWindow_TypeInfo)->newInstance(manager, mi);
        auto parentOnClosed = &(boxWindow->fields).onClosed;
        *parentOnClosed = onClosed;

        boxWindow->Open(-2, true);
    }
};

void exl_more_ui_main() {
    BoxWindow$$Awake::InstallAtOffset(0x01cb6020);
    BoxWindow$$OnUpdate::InstallAtOffset(0x01cb8b20);
    BoxWindow$$Open::InstallAtOffset(0x01cb6080);
    BoxWindow$$OpOpenMoveNext::InstallAtOffset(0x01a25870);
    BoxWindow$$Close::InstallAtOffset(0x01cb5cc0);
    BoxWindow$$OpCloseMoveNext::InstallAtOffset(0x01a25310);

    OpenStatusWindow__b__2::InstallAtOffset(0x01a21db0);

    UIWindow$$OnAddContextMenuYesNoItemParams::InstallAtOffset(0x01a35e30);

    OpLoadWindows_b__136_0::InstallAtOffset(0x017c7ccc);
}