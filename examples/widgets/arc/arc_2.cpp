#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/arc/arc.h" // for Arc
#include "lvglpp/misc/anim.h" // for Animation

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void arc_2() {
        static auto arc = Arc(scr_act());
        arc.set_size(150, 150);
        arc.set_rotation(270);
        arc.set_bg_angles(0, 360);
        arc.remove_style(LV_PART_KNOB);
        arc.clear_flag(LV_OBJ_FLAG_CLICKABLE);
        arc.center();

        static Animation a;
        a.set_var(arc);
        auto set_angle = [] (Arc & obj, int32_t v) {
            obj.set_value(v);
        };
        a.set_exec_cb<Arc>(set_angle);
        a.set_time(1000);
        a.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a.set_repeat_delay(500);
        a.set_values(0, 100);
        a.start();
    }
}