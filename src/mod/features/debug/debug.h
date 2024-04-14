#pragma once

#include "exlaunch.hpp"

// Outputs all activated features at launch.
void exl_feature_log_main();

// Reroutes IL2CPP logs to the ExLaunch logger.
void exl_il2cpp_log_main();

// Reroutes Unity logs to the ExLaunch logger.
void exl_unity_log_main();
