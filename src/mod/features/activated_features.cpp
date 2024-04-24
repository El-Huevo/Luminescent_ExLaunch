#include "features/activated_features.h"

#include "data/features.h"

static bool ACTIVATED_FEATURES[FEATURE_COUNT];
static bool ACTIVATED_DEBUG_FEATURES[DEBUG_FEATURE_COUNT];


void DisableFeatures()
{
    for (bool & i : ACTIVATED_FEATURES)
        i = false;
}

void DisableDebugFeatures()
{
    for (bool & i : ACTIVATED_DEBUG_FEATURES)
        i = false;
}

void SetActivatedFeature(int feature)
{
    ACTIVATED_FEATURES[feature] = true;
}

void SetActivatedDebugFeature(int feature)
{
    ACTIVATED_DEBUG_FEATURES[feature] = true;
}

bool IsActivatedFeature(int feature)
{
    return ACTIVATED_FEATURES[feature];
}

bool IsActivatedDebugFeature(int feature)
{
    return ACTIVATED_DEBUG_FEATURES[feature];
}