#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/roller/roller.h" // for Roller
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    static void event_handler(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<Roller>();
        if(code == LV_EVENT_VALUE_CHANGED) {
            auto txt = obj.get_selected_str();
            LV_LOG_USER("Selected month: %s\n", txt.c_str());
        }
    }

    void roller_1() {
        static auto roller = Roller(scr_act());
        roller.set_options("January\n"
                           "February\n"
                           "March\n"
                           "April\n"
                           "May\n"
                           "June\n"
                           "July\n"
                           "August\n"
                           "September\n"
                           "October\n"
                           "November\n"
                           "December",
                           LV_ROLLER_MODE_INFINITE);

        roller.set_visible_row_count(4);
        roller.center();
        roller.add_event_cb(event_handler, LV_EVENT_ALL);
    }
}