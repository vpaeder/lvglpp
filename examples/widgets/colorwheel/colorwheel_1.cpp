#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/colorwheel.h" // for ColorWheel

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void colorwheel_1() {
        auto root = scr_act();
        auto cw = ColorWheel(root,true);
        cw.set_size(200, 200);
        cw.center();
    }
}