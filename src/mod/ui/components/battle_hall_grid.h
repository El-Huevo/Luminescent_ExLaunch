#pragma once

#include "memory/string.h"
#include "ui/base/element.h"
#include "ui/base/combo.h"
#include "ui/base/selectable.h"
#include "nn/fs/fs_directories.hpp"
#include "nn/result.h"
#include "logger/logger.h"
#include "externals/UnityEngine/Transform.h"
#include "externals/UnityEngine/_Object.h"
#include "externals/UnityEngine/UI/ListPool.h"
#include "externals/UnityEngine/SceneManagement/SceneManager.h"
#include "externals/Dpr/UI/UIManager.h"
#include "externals/Dpr/Battle/View/BattleViewCore.h"


namespace ui {
    ELEMENT(BattleHallGrid) {

        void draw() override {
                if (ImGui::BeginTable("ButtonGrid", 3, ImGuiTableFlags_Borders)) {
                    nn::vector<std::pair<const char*, Rank>> typeRanks = getCustomSaveData()->battleHall.getAllTypeRanks();
                    int typeIndex = 0;
                    for (int row = 0; row < 6; ++row) {
                        ImGui::TableNextRow();
                        for (int column = 0; column < 3; ++column) {
                            ImGui::TableSetColumnIndex(column);
                            if (typeIndex < TYPE_COUNT) {
                                std::string buttonLabel = std::string(typeRanks[typeIndex].first) + " (" + std::to_string(typeRanks[typeIndex].second) + ")";
                                if (ImGui::Button(buttonLabel.c_str())) {
                                    // Handle button click
                                    // For example, you could increment the value for demonstration
                                    getCustomSaveData()->battleHall.setRank(typeRanks[typeIndex].first, static_cast<Rank>(typeRanks[typeIndex].second + 1));
                                }
                                typeIndex++;
                            }
                        }
                    }
                    ImGui::EndTable();
                }
        }
    };
}
