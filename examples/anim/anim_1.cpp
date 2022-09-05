#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/switch/switch.h" // for Switch
#include "lvglpp/misc/anim.h" // for Animation

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;
    using namespace lvgl::widgets;

    using LabelPtr = std::unique_ptr<Label>;
    LabelPtr label;

    static void sw_event_cb(Event & e) {
        auto sw = e.get_target<Switch>();

        static Animation a;
        a.set_var(*label);
        a.set_time(500);
        auto anim_x_cb = [] (Label & obj, int32_t v) {
            obj.set_x(v);
        };
        a.set_exec_cb<Label>(anim_x_cb);
        if(sw.has_state(LV_STATE_CHECKED)) {
            a.set_values(sw.get_x(), 100);
            a.set_path_cb(lv_anim_path_overshoot);
        }
        else {
            a.set_values(sw.get_x(), -sw.get_width());
            a.set_path_cb(lv_anim_path_ease_in);
        }
        a.start();
    }


    void anim_1() {
        auto root = scr_act();
        label = std::make_unique<Label>(root);
        label->set_text("Hello animations!");
        label->set_pos(100, 10);

        static auto sw = Switch(root);
        sw.center();
        sw.add_state(LV_STATE_CHECKED);
        sw.add_event_cb(sw_event_cb, LV_EVENT_VALUE_CHANGED);
    }
}