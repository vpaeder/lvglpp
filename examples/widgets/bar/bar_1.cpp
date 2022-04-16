#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/bar.h" // for Bar

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void bar_1() {
        auto root = scr_act();
        auto bar = Bar(root);
        bar.set_size(200, 20);
        bar.center();
        bar.set_value(70, LV_ANIM_OFF);
    }
}