#pragma once

static constexpr const char* FEATURES[] = {
    "Regular Attack",
};

constexpr int FEATURE_COUNT = sizeof(FEATURES) / sizeof(FEATURES[0]);

static constexpr const char* DEBUG_FEATURES[] = {
    "IL2CPP Logging",
    "Unity Logging",
    "Feature Logging",
};

constexpr int DEBUG_FEATURE_COUNT = sizeof(DEBUG_FEATURES) / sizeof(DEBUG_FEATURES[0]);
