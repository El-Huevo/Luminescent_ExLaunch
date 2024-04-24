#include "externals/Const/waza.h"


HOOK_DEFINE_TRAMPOLINE(GetActIndex) {
    static int32_t Callback(int32_t wazaIndex) {
        if (wazaIndex != (int32_t) Waza::Index::WANA_SAGASHI) {
            return Orig(wazaIndex);
        }

        return Orig((int32_t) Waza::Index::TSUUJOU_KOUGEKI);
    }
};

void exl_regular_attack_main() {
    GetActIndex::InstallAtOffset(0x0a18e30);
}