#include "data/features.h"
#include "data/utils.h"

#include "features/activated_features.h"
#include "features/features.h"

void CallFeatureHooks()
{
    if (IsActivatedFeature(array_index(FEATURES, "Regular Attack")))
        exl_regular_attack_main();

    exl_debug_features_main();
}

void exl_features_main() {
    // First disables all features
    DisableFeatures();
    DisableDebugFeatures();

    // Select which new features are activated
    SetActivatedFeature(array_index(FEATURES, "Regular Attack"));


    // Install all activated hooks
    CallFeatureHooks();
}
