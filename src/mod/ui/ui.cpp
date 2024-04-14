#include "externals/il2cpp.h"

#include "ui/base/root_element.h"
#include "ui/base/window.h"
#include "ui/ui.h"

#include "logger/logger.h"

using namespace ui;

static Window debugLogWindow = Window::single([](Window &_) {
    _.title = "Debug Log";
    auto *view = _.StringView();

    // WARNING: Turning this on is a ticking time bomb.
    // Eventually there are too many logs and the game hangs.
    /*Logger::addListener([view](const char *message) {
        view->append(message);
    });*/
});

static Window mainWindow = Window::single([](Window &_) {
    _.title = "BDSP Toolbox";
    _.toggleable = false;
    _.flags |= ImGuiWindowFlags_MenuBar;
    _.initialPos = ImVec2(50, 50);
    _.initialSize = ImVec2(450, 650);

    _.Text([](Text &_) {
        _.content = "Press ZL+ZR to toggle all menus.\nHold L to walk through walls.";
    });

    _.Spacing();

    _.MenuBar([](MenuBar &_) {
        _.Menu([](Menu &_) {
            _.label = "Tools";
            _.MenuItem([](MenuItem &_) {
                _.label = "Debug Log";
                _.checked = &debugLogWindow.open;
            });
        });
    });
});

void setup_ui() {
    ROOT->addChild(&mainWindow);
    ROOT->addChild(&debugLogWindow);
}
