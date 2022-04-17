#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/misc/anim.h" // for Animation
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;

    void anim_2() {
        static auto obj = Container(scr_act());

        obj.set_style_bg_color(palette::main(Color::Red), 0);
        obj.set_style_radius(LV_RADIUS_CIRCLE, 0);

        obj.align(LV_ALIGN_LEFT_MID, 10, 0);

        static Animation a1, a2;
        a1.set_var(obj);
        a1.set_values(10, 50);
        a1.set_time(1000);
        a1.set_playback_delay(100);
        a1.set_playback_time(300);
        a1.set_repeat_delay(500);
        a1.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a1.set_path_cb(lv_anim_path_ease_in_out);
        auto anim_size_cb = [] (Container & obj, int32_t v) {
            obj.set_size(v, v);
        };
        a1.set_exec_cb<Container>(anim_size_cb);
        a1.start();

        a2.set_var(obj);
        a2.set_values(10, 50);
        a2.set_time(1000);
        a2.set_playback_delay(100);
        a2.set_playback_time(300);
        a2.set_repeat_delay(500);
        a2.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a2.set_path_cb(lv_anim_path_ease_in_out);
        auto anim_x_cb = [] (Container & obj, int32_t v) {
            obj.set_x(v);
        };
        a2.set_exec_cb<Container>(anim_x_cb);
        a2.set_values(10, 240);
        a2.start();
    }
}