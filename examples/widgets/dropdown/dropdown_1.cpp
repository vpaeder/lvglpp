#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/dropdown/dropdown.h" // for Dropdown
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    static void event_handler(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<Dropdown>();
        if(code == LV_EVENT_VALUE_CHANGED) {
            auto txt = obj.get_selected_str();
            LV_LOG_USER("Option: %s", txt.c_str());
        }
    }

    void dropdown_1() {
        static auto dd = Dropdown(scr_act());
        dd.set_options("Apple\n"
                       "Banana\n"
                       "Orange\n"
                       "Cherry\n"
                       "Grape\n"
                       "Raspberry\n"
                       "Melon\n"
                       "Orange\n"
                       "Lemon\n"
                       "Nuts");

        dd.align(LV_ALIGN_TOP_MID, 0, 20);
        dd.add_event_cb(event_handler, LV_EVENT_ALL);
    }
}