#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/misc/anim.h" // for Animation

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void flex_5() {
        static auto cont = Container(scr_act());
        cont.set_size(300, 220);
        cont.center();
        cont.set_flex_flow(LV_FLEX_FLOW_ROW_WRAP);

        for(uint32_t i = 0; i < 9; i++) {
            auto obj = Container(cont);
            obj.set_size(70, LV_SIZE_CONTENT);
            auto label = Label(obj);
            label.set_text_fmt("%" LV_PRIu32, i);
            label.center();
            obj.release_ptr();
            label.release_ptr();
        }

        auto row_gap_anim = [](Container & obj, int32_t v) {
            obj.set_style_pad_row(v, 0);
        };
        auto column_gap_anim = [](Container & obj, int32_t v) {
            obj.set_style_pad_column(v, 0);
        };
        static Animation a1, a2;
        a1.set_var(cont);
        a1.set_values(0, 10);
        a1.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a1.set_exec_cb(row_gap_anim);
        a1.set_time(500);
        a1.set_playback_time(500);
        a1.start();
        a2.set_var(cont);
        a2.set_values(0, 10);
        a2.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a2.set_exec_cb(column_gap_anim);
        a2.set_time(3000);
        a2.set_playback_time(3000);
        a2.start();
    }
}