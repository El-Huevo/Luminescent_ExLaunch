#pragma once

#include "data/clip_names.h"
#include "data/utils.h"
#include "externals/FlagWork.h"
#include "ui/base/collapsing_header.h"
#include "ui/base/element.h"
#include "data/types.h"
#include "data/frontier.h"
#include "save/save.h"

namespace ui {
    ELEMENT(FrontierTool) {
        FrontierTool() {
            auto header = CollapsingHeader::create([this](CollapsingHeader &_) {
                _.label = "Frontier Tool";

                auto *type = _.ComboSimple([](ComboSimple &_) {
                    _.label = "Type";
                    _.items = TYPES;
                    _.items_count = TYPE_COUNT;
                    _.selected = array_index(TYPES, "Normal");
                });

                auto *rank = _.InputInt([](InputInt &_) {
                    _.label = "Rank";
                    _.min = 1;
                    _.max = 11;
                    _.value = 1;
                });

                _.Button([type, rank](Button &_) {
                    _.label = "Set Rank";
                    _.onClick = [type, rank]() {
                        Logger::log("Setting type %s to Rank: %d\n", TYPES[type->selected], rank->value);
                        (&getCustomSaveData()->battleHall)->setRank(TYPES[type->selected], (Rank) (rank->value-1));
                    };
                });

                _.Button([type](Button &_) {
                    _.label = "Get Rank";
                    _.onClick = [type]() {
                        auto currentRank = (&getCustomSaveData()->battleHall)->getRank(TYPES[type->selected]);
                        Logger::log("Type %s is currently Rank: %d\n", TYPES[type->selected], static_cast<int32_t>(currentRank) + 1);

                    };
                });

                auto *round = _.InputInt([](InputInt &_) {
                    _.label = "Round";
                    _.min = 0;
                    _.max = 169;
                    _.value = (&getCustomSaveData()->battleHall)->currentRound;
                });

                _.Button([round](Button &_) {
                    _.label = "Set Round";
                    _.onClick = [round]() {
                        Logger::log("Setting Round to %d.\n", round->value);
                        (&getCustomSaveData()->battleHall)->currentRound = round->value;
                    };
                });

                _.Button([](Button &_) {
                    _.label = "Reset Streak Mon";
                    _.onClick = []() {
                        Logger::log("Setting Streak Mon to -1.\n");
                        (&getCustomSaveData()->battleHall)->streakPokePID = -1;
                    };
                });

                _.Button([type](Button &_) {
                    _.label = "Get Active Pool";
                    _.onClick = [type]() {
                        auto activePool = BattleHallPool::getTypePool(TYPES[type->selected], GROUP_1);
                        Logger::log("Type %s activePool element 0: %d\n", TYPES[type->selected], activePool.at(0));
                        //auto typeList = activePool->getActivePool("Normal", 1);
                        //Logger::log("Type Normal activePool element 0: %d\n", typeList.at(0));
//                        Logger::log("Type %s activePool element 0: %d\n", TYPES[type->selected], typeList.at(0));

                    };
                });
            });

            addChild(header);
        }
    };
}
