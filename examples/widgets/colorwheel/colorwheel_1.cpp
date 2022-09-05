#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/colorwheel/colorwheel.h" // for ColorWheel

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void colorwheel_1() {
        static auto cw = ColorWheel(scr_act(), true);
        cw.set_size(200, 200);
        cw.center();
    }
}