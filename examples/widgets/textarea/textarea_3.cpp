#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/textarea/textarea.h" // for TextArea
#include "lvglpp/widgets/keyboard/keyboard.h" // for Keyboard
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    static void ta_event_cb(Event & e) {
        auto ta = e.get_target<TextArea>();
        auto txt = ta.get_text();
        if(txt[0] >= '0' && txt[0] <= '9' &&
        txt[1] >= '0' && txt[1] <= '9' &&
        txt[2] != ':') {
            ta.set_cursor_pos(2);
            ta.add_char(':');
        }
    }

    void textarea_3() {
        auto root = scr_act();
        
        static auto ta = TextArea(root);
        ta.add_event_cb(ta_event_cb, LV_EVENT_VALUE_CHANGED);
        ta.set_accepted_chars("0123456789:");
        ta.set_max_length(5);
        ta.set_one_line(true);
        ta.set_text("");

        /*Create a keyboard*/
        static auto kb = Keyboard(root);
        kb.set_size(LV_HOR_RES, LV_VER_RES / 2);
        kb.set_mode(LV_KEYBOARD_MODE_NUMBER);
        kb.set_textarea(ta);
    }
}