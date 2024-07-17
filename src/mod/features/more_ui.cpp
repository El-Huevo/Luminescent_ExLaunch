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
#include "externals/System/Func.h"
#include "externals/Dpr/Message/MessageWordSetHelper.h"

const int32_t typeSelectorRowNum = 5;
const int32_t typeSelectorColNum = 4;
const uint32_t AK_EVENTS_UI_COMMON_DONE = 0x4491b890;
const uint32_t AK_EVENTS_UI_COMMON_SELECT = 0xb7533038;

HOOK_DEFINE_REPLACE(EvCmdBoxSetProc) {
    static bool Callback(Dpr::EvScript::EvDataManager::Object* manager) {
        UIWindowID windowId = FlagWork::GetFlag(FlagWork_Flag::FLAG_UI_WINDOW_SWITCH)
                ? UIWindowID::BATTLEHALL_TYPE_SELECT : UIWindowID::BOX;
        system_load_typeinfo(0x43ea);
        manager->fields._pc_window_close = false;

        SmartPoint::AssetAssistant::SingletonMonoBehaviour::getClass()->initIfNeeded();
        Dpr::UI::UIManager::Object* uiManager = Dpr::UI::UIManager::instance();
        Logger::log("[EvCmdBoxSetProc] Running manager->CreateUIWindow.\n");
        auto boxWindow = (Dpr::UI::BoxWindow::Object*)
                uiManager->CreateUIWindow(windowId,
                                          Dpr::UI::UIManager::Method$$CreateUIWindow_BoxWindow_);
        MethodInfo* mi = *UnityEngine::Events::UnityAction::Method$$Dpr_EvScript_EvDataManager__EvCmdBoxSetProc__b__742_0;
        auto onClosed = UnityEngine::Events::UnityAction::getClass(UnityEngine::Events::UnityAction::UIWindow_TypeInfo)->newInstance(manager, mi);
        auto parentOnClosed = &(boxWindow->fields).onClosed;
        *parentOnClosed = onClosed;
        Logger::log("[EvCmdBoxSetProc] UI Window created.\n");
        boxWindow->Open(-2, true);
        return true;
    }
};

bool SetSelectIndex(Dpr::UI::BoxWindow::Object* __this, int32_t index, bool isInitialized = false) {
    system_load_typeinfo(0x79bb);
    UnityEngine::RectTransform::Object* boxTrays = __this->fields._boxTrayRoot;
    UnityEngine::Transform::Object* traysChild = reinterpret_cast<UnityEngine::Transform::Object*>(boxTrays)->GetChild(0);

    if (!isInitialized) {
        int32_t beforeIndex = __this->fields._currentTrayIndex;
        if (beforeIndex == index) {
            return false;
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

bool OpenConfirmMessageWindowHandler2(Dpr::UI::UIWindow::Object* window, Dpr::UI::ContextMenuItem::Object* contextMenuItem) {

    window->CloseMessageWindow();

    if (contextMenuItem->fields._param->fields.menuId == ContextMenuID::FTR_HALL_YES) {
        reinterpret_cast<Dpr::UI::BoxWindow::Object*>(window)->Close(window->fields.onClosed, window->fields._prevWindowId);
        Dpr::UI::UIManager::instance()->_ReleaseUIWindow(reinterpret_cast<Il2CppObject*>(window));
        if (window->fields.onClosed != nullptr) {
            window->fields.onClosed->Invoke();
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


void OnUpdate(Dpr::UI::BoxWindow::Object* __this, float deltaTime) {
    Dpr::UI::UIManager::getClass()->initIfNeeded();
    auto uiManager = Dpr::UI::UIManager::instance();
    auto retrievedWindow = (UnityEngine::_Object::Object*) uiManager->GetCurrentUIWindow(Dpr::UI::UIManager::Method$$GetCurrentUIWindow_UIWindow_);
    bool inequalityCheck = UnityEngine::_Object::op_Inequality(retrievedWindow, (UnityEngine::_Object::Object*) __this);
    if (!inequalityCheck && __this->fields._input->fields._inputEnabled) {

        auto msgWindow = __this->fields._messageWindow;

        inequalityCheck = UnityEngine::_Object::op_Inequality((UnityEngine::_Object::Object*) msgWindow, nullptr);

        if (inequalityCheck) {
            bool inputEnabled = msgWindow->get_isEnabledInput();
            if (inputEnabled) return;
        }


        Dpr::UI::UIManager::getClass()->initIfNeeded();
        auto uiWindow = (Dpr::UI::UIWindow::Object*) __this;

        auto buttonA = Dpr::UI::UIManager::getClass()->static_fields->ButtonA;
        if (uiWindow->IsPushButton(buttonA, false)) {
            Logger::log("[BoxWindow$$OnUpdate] Pressed A\n");
            Audio::AudioManager::instance()->PlaySe(AK_EVENTS_UI_COMMON_DONE, nullptr);
            //__this->fields._cursor->Play()
            __this->fields._input->fields._inputEnabled = false;

            Dpr::MsgWindow::MsgWindowParam::Object* msgWindowParam = Dpr::MsgWindow::MsgWindowParam::newInstance();
            auto msgManager = Dpr::Message::MessageManager::instance();
            msgWindowParam->fields.useMsgFile = msgManager->GetMsgFile(System::String::Create("ss_btl_tower_menu_ui_text"));
            msgWindowParam->fields.labelName = System::String::Create("ftr_hall_stage_typeselect_confirm");
            msgWindowParam->fields.inputEnabled = true;
            msgWindowParam->fields.inputCloseEnabled = false;

            Dpr::Message::MessageWordSetHelper::SetDigitWord(0, 0);
            Dpr::Message::MessageWordSetHelper::SetDigitWord(1, 0);

            system_load_typeinfo(0x79b7);
            MethodInfo* mi = (
                    *Dpr::UI::SelectLanguageWindow::Method$$SelectLanguageWindow__OpenConfirmMessageWindow__b__18_0)->
                            copyWith((Il2CppMethodPointer) &OpenConfirmMessageWindowHandler);
            auto onFinishedShowAllMessage = System::Action::getClass(
                    System::Action::void_TypeInfo)->newInstance(uiWindow, mi);
            Logger::log("[BoxWindow$$OnUpdate] Created action\n");

            msgWindowParam->fields.onFinishedShowAllMessage = onFinishedShowAllMessage;

            uiWindow->OpenMessageWindow(msgWindowParam);
            Logger::log("[BoxWindow$$OnUpdate] Opened window\n");
        }

        UpdateSelect(__this, deltaTime);
    }

}


// Method$Dpr.UI.SelectLanguageWindow.<OpenConfirmMessageWindow>b__18_0()
// Method$Dpr.UI.SelectLanguageWindow.<OnUpdate>b__16_1()
// Close Message Window()



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

                        (__this->fields).__2__current = reinterpret_cast<Il2CppObject *>(((Dpr::UI::UIWindow::Object *) window)->OpPlayOpenWindowAnimation(
                                __this->fields.prevWindowId, nullptr));

                        (__this->fields).__1__state = 1;
                        //Logger::log("[BoxWindow...d__200$$MoveNext] Case 0 complete.\n");
                        return true;
                    }

                    case 1: {
                        Logger::log("[BoxWindow...d__200$$MoveNext] Starting Case 1.\n");
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
                        Logger::log("[BoxWindow...d__200$$MoveNext] Case 1 Complete.\n");
                        return true;
                    }

                    case 2: {
                        Logger::log("[BoxWindow...d__200$$MoveNext] Starting Case 2.\n");
                        (__this->fields).__1__state = -1;
                        window->fields._input->fields._inputEnabled = true;
                        auto cursor = window->fields._cursor;
                        cursor->SetActive(true);
                        SetSelectIndex(window, 0, true);

                        (__this->fields).__2__current = nullptr;
                        (__this->fields).__1__state = 3;
                        Logger::log("[BoxWindow...d__200$$MoveNext] Case 2 Complete.\n");
                        return true;
                    }

                    case 3: {
                        Logger::log("[BoxWindow...d__200$$MoveNext] Starting Case 3.\n");
                        (__this->fields).__1__state = -1;

                        window->fields._coOpen = nullptr;
                        Logger::log("[BoxWindow...d__200$$MoveNext] Case 3 Complete.\n");
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
                Logger::log("[BoxWindow$$Awake] UIWindowID = BOX.\n");
                Orig(__this);
                break;
            case UIWindowID::BATTLEHALL_TYPE_SELECT:
                Logger::log("[BoxWindow$$Awake] UIWindowID = BATTLEHALL_TYPE_SELECT.\n");
                Orig(__this);
                break;
        }
    }
};

HOOK_DEFINE_REPLACE(UIWindow$$OnAddContextMenuYesNoItemParams) {
    static void Callback(Dpr::UI::UIWindow::Object* __this, System::Collections::Generic::List$$ContextMenuItem_Param::Object* contextMenuItemParams) {
        switch (__this->fields.instance->fields._windowId) {
            case UIWindowID::BATTLEHALL_TYPE_SELECT:
            {
                Logger::log("[UIWindow$$OnAddContextMenuYesNoItemParams] UIWindowID = BATTLEHALL_TYPE_SELECT.\n");
                Dpr::UI::ContextMenuItem::Param::Object* yesParam = Dpr::UI::ContextMenuItem::Param::newInstance();
                Dpr::UI::ContextMenuItem::Param::Object* noParam = Dpr::UI::ContextMenuItem::Param::newInstance();
                yesParam->fields.menuId = ContextMenuID::FTR_HALL_YES;
                noParam->fields.menuId = ContextMenuID::FTR_HALL_NO;
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

HOOK_DEFINE_REPLACE(EvCmdBTowerAppSetProc) {
    static bool Callback(Dpr::EvScript::EvDataManager::Object* manager) {

        system_load_typeinfo(0x43d6);

        Logger::log("_BHALL_APP_SET_PROC\n");

        EvData::Aregment::Array* args = manager->fields._evArg;


        if (args->max_length >= 3) {
            auto argType1 = args->m_Items[1].fields.argType;
            auto argData1 = (float)args->m_Items[1].fields.data;
            auto argType2 = args->m_Items[2].fields.argType;
            auto argData2 = (float)args->m_Items[2].fields.data;
            int32_t towerMode;
            int32_t work1;
            int32_t work2;

            switch (argType1) {
                case 2:
                    work1 = FlagWork::GetWork((int32_t)argData1);
                    break;
                case 1:
                    work1 = (int)argData1;
                    break;
                default:
                    work1 = 0;
                    break;
            }

            switch (argType2) {
                case 2:
                    work2 = FlagWork::GetWork((int32_t)argData2);
                    break;
                case 1:
                    work2 = (int)argData2;
                    break;
                default:
                    work2 = 0;
                    break;
            }

            manager->fields._isOpenBtlTowerRecode = true;

            SmartPoint::AssetAssistant::SingletonMonoBehaviour::getClass()->initIfNeeded();
            Dpr::UI::UIManager::Object* uiManager = Dpr::UI::UIManager::instance();
            auto recordWindow = (Dpr::UI::BattleTowerRecordWindow::Object*)
                    uiManager->CreateUIWindow(UIWindowID::BATTLEHALL_RECORD,
                                              Dpr::UI::UIManager::Method$$CreateUIWindow_BattleTowerRecordWindow_);
            MethodInfo* mi = *UnityEngine::Events::UnityAction::Method$$Dpr_EvScript_EvDataManager__EvCmdBTowerAppSetProc__b__1143_0;
            auto onClosed = UnityEngine::Events::UnityAction::getClass(UnityEngine::Events::UnityAction::UIWindow_TypeInfo)->newInstance(manager, mi);
            auto parentOnClosed = &(recordWindow->fields).onClosed;
            *parentOnClosed = onClosed;
            Dpr::UI::BattleTowerRecordWindow::Param::Object* recordParam = Dpr::UI::BattleTowerRecordWindow::Param::newInstance();
            recordParam->fields.isSuspended = false;


            if (work1 == 1) {
                if (work2 == 1) {
                    recordParam->fields.recordType = 0;
                    towerMode = 0;
                }

                else {
                    recordParam->fields.recordType = 2;
                    towerMode = 2;
                }
            }

            else if (work2 == 1) {
                recordParam->fields.recordType = 1;
                towerMode = 1;
            }

            else {
                recordParam->fields.recordType = 3;
                towerMode = 3;
            }
            BtlTowerWork::getClass()->initIfNeeded();

            uint32_t round = BtlTowerWork::GetRenshou(towerMode);
            recordParam->fields.isSuspended = (round != 0);

            int32_t index;
            switch (recordParam->fields.recordType) {
                case 0:
                    recordParam->fields.consecutiveWins = (int32_t) RecordWork::Get(7);
                    recordParam->fields.maxConsecutiveWins = (int32_t) RecordWork::Get(6);
                    index = 6;
                    break;
                case 1:
                    recordParam->fields.consecutiveWins = (int32_t) RecordWork::Get(9);
                    recordParam->fields.maxConsecutiveWins = (int32_t) RecordWork::Get(8);
                    index = 8;
                    break;
                case 2:
                    recordParam->fields.consecutiveWins = (int32_t) RecordWork::Get(11);
                    recordParam->fields.maxConsecutiveWins = (int32_t) RecordWork::Get(10);
                    index = 2;
                    break;
                case 3:
                    recordParam->fields.consecutiveWins = (int32_t) RecordWork::Get(13);
                    recordParam->fields.maxConsecutiveWins = (int32_t) RecordWork::Get(12);
                    index = 3;
                    break;
            }

            if (index == 2 || index == 3) {
                recordParam->fields.rank = BtlTowerWork::GetRank(index);
            }

            recordWindow->Open(recordParam, -2);
        }
        return true;
    }
};

void exl_more_ui_main() {
    BoxWindow$$Awake::InstallAtOffset(0x01cb6020);
    BoxWindow$$OnUpdate::InstallAtOffset(0x01cb8b20);
    BoxWindow$$Open::InstallAtOffset(0x01cb6080);
    BoxWindow$$OpOpenMoveNext::InstallAtOffset(0x01a25870);

    UIWindow$$OnAddContextMenuYesNoItemParams::InstallAtOffset(0x01a35e30);

    EvCmdBoxSetProc::InstallAtOffset(0x02c699b0);
    //EvCmdBoxSetProc::InstallAtOffset(0x02c69a2c); // Inline Offset
    EvCmdBTowerAppSetProc::InstallAtOffset(0x02c7cc30);
    //EvCmdBTowerAppSetProc::InstallAtOffset(0x02c7cd64); // Inline Offset
    OpLoadWindows_b__136_0::InstallAtOffset(0x017c7ccc);
}