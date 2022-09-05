#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/switch/switch.h" // for Switch

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    std::unique_ptr<Container> panel;

    static void sw_event_cb(Event & e) {
        auto code = e.get_code();
        auto sw = lv_event_get_target<Switch>();

        if(code == LV_EVENT_VALUE_CHANGED) {
            if(sw.has_state(LV_STATE_CHECKED)) panel->add_flag(LV_OBJ_FLAG_SCROLL_ONE);
            else panel->clear_flag(LV_OBJ_FLAG_SCROLL_ONE);
        }
    }

    void scroll_2() {
        /*Create an object with the new style*/
        auto root = scr_act();
        panel = std::make_unique<Container>(root);
        panel->set_size(280, 120);
        panel->set_scroll_snap_x(LV_SCROLL_SNAP_CENTER);
        panel->set_flex_flow(LV_FLEX_FLOW_ROW);
        panel->align(LV_ALIGN_CENTER, 0, 20);

        for(uint32_t i = 0; i < 10; i++) {
            auto btn = Button(*panel);
            btn.set_size(150, lv_pct(100));
            auto label = Label(btn);
            if(i == 3) {
                label.set_text_fmt("Panel %" LV_PRIu32 "\nno snap", i);
                btn.clear_flag(LV_OBJ_FLAG_SNAPPABLE);
            }
            else {
                label.set_text_fmt("Panel %" LV_PRIu32, i);
            }
            label.center();
            label.release_ptr();
            btn.release_ptr();
        }
        panel->update_snap(LV_ANIM_ON);

    #if LV_USE_SWITCH
        /*Switch between "One scroll" and "Normal scroll" mode*/
        static auto sw = Switch(root);
        sw.align(LV_ALIGN_TOP_RIGHT, -20, 10);
        sw.add_event_cb(sw_event_cb, LV_EVENT_ALL);
        static auto label = Label(root);
        label.set_text("One scroll");
        label.align_to(sw, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
    #endif
    }
}