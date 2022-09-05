#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/keyboard/keyboard.h" // for Keyboard
#include "lvglpp/widgets/textarea/textarea.h" // for TextArea
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    std::shared_ptr<Keyboard> kb;

    static void ta_event_cb(Event & e) {
        auto code = e.get_code();
        auto ta = e.get_target<TextArea>();
        if(code == LV_EVENT_FOCUSED) {
            kb->set_textarea(ta);
            kb->clear_flag(LV_OBJ_FLAG_HIDDEN);
        }
        if(code == LV_EVENT_DEFOCUSED) {
            kb->unset_textarea();
            kb->add_flag(LV_OBJ_FLAG_HIDDEN);
        }
    }

    void keyboard_1() {
        auto root = scr_act();

        /*Create a keyboard to use it with an of the text areas*/
        kb = std::make_shared<Keyboard>(root);

        static auto ta1 = TextArea(root);
        ta1.align(LV_ALIGN_TOP_LEFT, 10, 10);
        ta1.add_event_cb(ta_event_cb, LV_EVENT_ALL);
        ta1.set_placeholder_text("Hello");
        ta1.set_size(140, 80);

        static auto ta2 = TextArea(root);
        ta2.align(LV_ALIGN_TOP_RIGHT, -10, 10);
        ta2.add_event_cb(ta_event_cb, LV_EVENT_ALL);
        ta2.set_size(140, 80);

        kb->set_textarea(ta2);
    }
}