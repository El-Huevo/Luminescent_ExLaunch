#pragma once

// Disables all features.
void DisableFeatures();

// Disables all debug features.
void DisableDebugFeatures();


// Activate a given feature.
void SetActivatedFeature(int feature);

// Activate a given debug feature.
void SetActivatedDebugFeature(int feature);


// Check if a given feature is enabled.
bool IsActivatedFeature(int feature);

// Check if a given debug feature is enabled.
bool IsActivatedDebugFeature(int feature);
