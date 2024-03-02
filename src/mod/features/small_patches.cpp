#include "exlaunch.hpp"

#include "data/features.h"
#include "data/items.h"
#include "data/utils.h"
#include "externals/FlagWork.h"
#include "features/activated_features.h"

HOOK_DEFINE_REPLACE(FriendshipFlag) {
    static bool Callback() {
        return FlagWork::GetFlag(FlagWork_Flag::FLAG_DISABLE_AFFECTION);
    }
};

HOOK_DEFINE_REPLACE(ExpShareFlag) {
    static bool Callback() {
        return FlagWork::GetFlag(FlagWork_Flag::FLAG_DISABLE_EXP_SHARE);
    }
};

void exl_patches_main() {
    using namespace exl::armv8::inst;
    using namespace exl::armv8::reg;
    exl::patch::CodePatcher p(0);

    if (IsActivatedSmallPatchFeature(array_index(SMALL_PATCH_FEATURES, "Affection Toggle")))
        FriendshipFlag::InstallAtOffset(0x020378d0);

    if (IsActivatedSmallPatchFeature(array_index(SMALL_PATCH_FEATURES, "Global Exp. Share Toggle")))
        ExpShareFlag::InstallAtOffset(0x020397f0);

    if (IsActivatedSmallPatchFeature(array_index(SMALL_PATCH_FEATURES, "Catch Rate Fix")))
    {
        p.Seek(0x02177394);
        p.WriteInst(Branch(0x44));
    }

    // Always-on Patches
    auto inst = nn::vector<exl::patch::Instruction> {
        { 0x02053b24, CmpImmediate(W8, 0x7) },          // Allow 6IV Pokémon
        { 0x0202c140, CmpImmediate(W19, ITEM_COUNT) },  // Make the battle check for if you own balls that go past 1822 items
    };
    p.WriteInst(inst);
}
