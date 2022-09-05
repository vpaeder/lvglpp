#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/switch/switch.h" // for Switch
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    static void event_handler(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<Switch>();
        if(code == LV_EVENT_VALUE_CHANGED) {
            LV_LOG_USER("State: %s\n", obj.has_state(LV_STATE_CHECKED) ? "On" : "Off");
        }
   }

    void switch_1() {
        auto root = scr_act();
        
        root.set_flex_flow(LV_FLEX_FLOW_COLUMN);
        root.set_flex_align(LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        static auto sw1 = Switch(root);
        sw1.add_event_cb(event_handler, LV_EVENT_ALL);

        static auto sw2 = Switch(root);
        sw2.add_state(LV_STATE_CHECKED);
        sw2.add_event_cb(event_handler, LV_EVENT_ALL);

        static auto sw3 = Switch(root);
        sw3.add_state(LV_STATE_DISABLED);
        sw3.add_event_cb(event_handler, LV_EVENT_ALL);

        static auto sw4 = Switch(root);
        sw4.add_state(LV_STATE_CHECKED | LV_STATE_DISABLED);
        sw4.add_event_cb(event_handler, LV_EVENT_ALL);
    }
}