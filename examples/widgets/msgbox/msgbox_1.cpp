#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/msgbox/msgbox.h" // for MessageBox
#include "lvglpp/core/event.h" // for Event
#include <vector>
#include <string>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void msgbox_1() {
        std::vector<std::string> btns = {"Apply", "Close", ""};
        static auto mbox = MessageBox("Hello", "This is a message box with two buttons.", btns, true);
        auto event_cb = [](Event & e) {
            auto obj = e.get_current_target<MessageBox>();
            LV_LOG_USER("Button %s clicked", obj.get_active_btn_text().c_str());
        };
        mbox.add_event_cb(event_cb, LV_EVENT_VALUE_CHANGED);
        mbox.center();
    }
}