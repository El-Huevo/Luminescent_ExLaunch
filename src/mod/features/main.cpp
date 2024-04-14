#include "data/features.h"
#include "data/utils.h"

#include "features/activated_features.h"
#include "features/features.h"

void CallFeatureHooks()
{
    exl_debug_features_main();
}

void exl_features_main() {
    // First disables all features
    DisableFeatures();
    DisableDebugFeatures();

    // Select which new features are activated
//    SetActivatedFeature(array_index(FEATURES, "Ability Changes"));
//    SetActivatedFeature(array_index(FEATURES, "Alt Starters"));
//    SetActivatedFeature(array_index(FEATURES, "Area/Zone Codes"));
//    SetActivatedFeature(array_index(FEATURES, "Badge Check"));
//    SetActivatedFeature(array_index(FEATURES, "New Poké Balls"));
//    SetActivatedFeature(array_index(FEATURES, "Battle Escape Flag"));
//    SetActivatedFeature(array_index(FEATURES, "Battle Camera Fix"));
//    SetActivatedFeature(array_index(FEATURES, "Color Variations"));
//    SetActivatedFeature(array_index(FEATURES, "Commands"));
//    SetActivatedFeature(array_index(FEATURES, "Encounter Slots"));
//    SetActivatedFeature(array_index(FEATURES, "EV/IV in Summary"));
//    SetActivatedFeature(array_index(FEATURES, "Evolution Methods"));
//    SetActivatedFeature(array_index(FEATURES, "Extended TM Learnsets"));
//    SetActivatedFeature(array_index(FEATURES, "Form Change Held Items"));
//    SetActivatedFeature(array_index(FEATURES, "Gender Neutral Boutique"));
//    SetActivatedFeature(array_index(FEATURES, "Hidden Power UI"));
//    SetActivatedFeature(array_index(FEATURES, "Language Select"));
//    SetActivatedFeature(array_index(FEATURES, "Level Cap"));
//    SetActivatedFeature(array_index(FEATURES, "NPC Collision Audio"));
//    SetActivatedFeature(array_index(FEATURES, "Uniform UI"));
//    SetActivatedFeature(array_index(FEATURES, "Party Context Menu"));
//    SetActivatedFeature(array_index(FEATURES, "Pickup Changes"));
//    SetActivatedFeature(array_index(FEATURES, "Poké Radar Fixes"));
//    SetActivatedFeature(array_index(FEATURES, "Thief Deposits to Bag"));
//    SetActivatedFeature(array_index(FEATURES, "Two-Button Pokétch"));
//    SetActivatedFeature(array_index(FEATURES, "Relearn TMs"));
//    SetActivatedFeature(array_index(FEATURES, "New Settings"));
//    SetActivatedFeature(array_index(FEATURES, "Shiny Rates"));
//    SetActivatedFeature(array_index(FEATURES, "Swarm Forms"));
//    SetActivatedFeature(array_index(FEATURES, "Turn Counter"));
//    SetActivatedFeature(array_index(FEATURES, "Underground Forms"));
//    SetActivatedFeature(array_index(FEATURES, "Validity Checks"));
//    SetActivatedFeature(array_index(FEATURES, "Wild Forms"));
//    SetActivatedFeature(array_index(FEATURES, "Wild Held Item Rates"));
//    SetActivatedFeature(array_index(FEATURES, "Contest NPC Forms"));
//
//    SetActivatedDebugFeature(array_index(DEBUG_FEATURES, "Battle Bundles in UI"));
//    SetActivatedDebugFeature(array_index(DEBUG_FEATURES, "Boutique Models"));
//    //SetActivatedDebugFeature(array_index(DEBUG_FEATURES, "IL2CPP Logging"));
//    SetActivatedDebugFeature(array_index(DEBUG_FEATURES, "PokemonInfo Logging"));
//    SetActivatedDebugFeature(array_index(DEBUG_FEATURES, "Unity Logging"));
//    SetActivatedDebugFeature(array_index(DEBUG_FEATURES, "Feature Logging"));
//    SetActivatedDebugFeature(array_index(DEBUG_FEATURES, "Pickup 100%"));
//
//    SetActivatedItemFeature(array_index(ITEM_FEATURES, "Ability Patch"));
//    SetActivatedItemFeature(array_index(ITEM_FEATURES, "Everlasting Candies"));
//    SetActivatedItemFeature(array_index(ITEM_FEATURES, "Infinite TMs"));
//    SetActivatedItemFeature(array_index(ITEM_FEATURES, "Leek"));
//    SetActivatedItemFeature(array_index(ITEM_FEATURES, "Infinite Repel"));
//
//    SetActivatedKeyItemFeature(array_index(KEY_ITEM_FEATURES, "Clothing Trunk"));
//    SetActivatedKeyItemFeature(array_index(KEY_ITEM_FEATURES, "Incense Burner"));
//    SetActivatedKeyItemFeature(array_index(KEY_ITEM_FEATURES, "Infinite Repel"));
//
//    SetActivatedSaveFeature(array_index(SAVE_FEATURES, "Dex Expansion"));
//
//    SetActivatedSmallPatchFeature(array_index(SMALL_PATCH_FEATURES, "Affection Toggle"));
//    SetActivatedSmallPatchFeature(array_index(SMALL_PATCH_FEATURES, "Global Exp. Share Toggle"));
//    SetActivatedSmallPatchFeature(array_index(SMALL_PATCH_FEATURES, "Catch Rate Fix"));

    // Install all activated hooks
    CallFeatureHooks();
}
