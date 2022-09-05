#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/checkbox/checkbox.h" // for Checkbox
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    static void event_handler(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<Checkbox>();
        if(code == LV_EVENT_VALUE_CHANGED) {
            auto txt = obj.get_text();
            auto state = obj.get_state() & LV_STATE_CHECKED ? "Checked" : "Unchecked";
            LV_LOG_USER("%s: %s", txt, state);
        }
    }

    void checkbox_1() {
        auto root = scr_act();

        root.set_flex_flow(LV_FLEX_FLOW_COLUMN);
        root.set_flex_align(LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);

        static auto cb1 = Checkbox(root);
        cb1.set_text("Apple");
        cb1.add_event_cb(event_handler, LV_EVENT_ALL);

        static auto cb2 = Checkbox(root);
        cb2.set_text("Banana");
        cb2.add_state(LV_STATE_CHECKED);
        cb2.add_event_cb(event_handler, LV_EVENT_ALL);

        static auto cb3 = Checkbox(root);
        cb3.set_text("Lemon");
        cb3.add_state(LV_STATE_DISABLED);
        cb3.add_event_cb(event_handler, LV_EVENT_ALL);

        static auto cb4 = Checkbox(root);
        cb4.add_state(LV_STATE_CHECKED | LV_STATE_DISABLED);
        cb4.set_text("Melon\nand a new line");
        cb4.add_event_cb(event_handler, LV_EVENT_ALL);

        root.update_layout();
    }
}