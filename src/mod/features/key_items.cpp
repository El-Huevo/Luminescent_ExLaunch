#include "exlaunch.hpp"

#include "data/items.h"
#include "data/utils.h"

#include "externals/Dpr/EvScript/EvDataManager.h"
#include "externals/Dpr/UI/UIBag.h"
#include "externals/FieldManager.h"
#include "externals/FlagWork.h"

#include "features/key_items/key_items.h"

#include "logger/logger.h"

bool CanUseRegisteredCustomItem(uint16_t itemno)
{
    switch(itemno) {
        case array_index(ITEMS, "Clothing Trunk"):
        case array_index(ITEMS, "Incense Burner"):
        case array_index(ITEMS, "Infinite Repel"): {
            return true;
        }
        default: {
            return false;
        }
    }
}

bool CustomItemBehavior(int32_t itemId, bool fromBag, Dpr::UI::UIBag::__c__DisplayClass127_1::Object* bagDisplayClass) {
    switch(itemId) {
        case array_index(ITEMS, "Clothing Trunk"): {
            UseClothingTrunk(itemId, fromBag, bagDisplayClass);
            return true;
        }
        case array_index(ITEMS, "Incense Burner"): {
            UseIncenseBurner(itemId, fromBag, bagDisplayClass);
            return true;
        }
        case array_index(ITEMS, "Infinite Repel"): {
            UseInfiniteRepel(itemId, fromBag, bagDisplayClass);
            return true;
        }
        default: {
            return false;
        }
    }
}

HOOK_DEFINE_TRAMPOLINE(BagUseKeyItem) {
    static void Callback(Dpr::UI::UIBag::__c__DisplayClass127_1::Object* __this) {
        int32_t id = __this->fields.CS___8__locals1->fields.item->get_Id();

        if (CustomItemBehavior(id, true, __this)) {
            return;
        }

        Orig(__this);
    }
};

HOOK_DEFINE_TRAMPOLINE(ShortcutCheckAvailability) {
    static bool Callback(FieldManager::Object *__this, uint16_t itemno) {
        Logger::log("ShortcutCheckAvailability: %s\n", ITEMS[itemno]);

        if (CanUseRegisteredCustomItem(itemno)) {
            return true;
        }

        return Orig(__this, itemno);
    }
};

HOOK_DEFINE_TRAMPOLINE(ShortcutUseKeyItem) {
    static void Callback(FieldManager::Object *__this, uint16_t itemno) {
        Logger::log("ShortcutUseKeyItem: %s\n", ITEMS[itemno]);

        if (CustomItemBehavior(itemno, false, nullptr)) {
            return;
        }

        Logger::log("Calling Orig ShortcutUseKeyItem: %s\n", ITEMS[itemno]);
        Orig(__this, itemno);
    }
};

void exl_key_items_main() {
    BagUseKeyItem::InstallAtOffset(0x01bde370);
    ShortcutCheckAvailability::InstallAtOffset(0x017a2710);
    ShortcutUseKeyItem::InstallAtOffset(0x017a17d0);
}
