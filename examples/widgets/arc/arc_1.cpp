#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/arc.h" // for Arc

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void arc_1() {
        auto root = scr_act();
        auto arc = Arc(root);
        arc.set_size(150, 150);
        arc.set_rotation(135);
        arc.set_bg_angles(0, 270);
        arc.set_value(40);
        arc.center();
    }
}