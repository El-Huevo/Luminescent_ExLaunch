#include "data/features.h"
#include "data/utils.h"

#include "features/activated_features.h"
#include "features/debug/debug.h"

void exl_debug_features_main() {
    if (IsActivatedDebugFeature(array_index(DEBUG_FEATURES, "IL2CPP Logging")))
        exl_il2cpp_log_main();
    if (IsActivatedDebugFeature(array_index(DEBUG_FEATURES, "Unity Logging")))
        exl_unity_log_main();
    if (IsActivatedDebugFeature(array_index(DEBUG_FEATURES, "Feature Logging")))
        exl_feature_log_main();
};