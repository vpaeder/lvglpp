#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/textarea/textarea.h" // for TextArea
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/keyboard/keyboard.h" // for Keyboard
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    using KeyboardPtr = std::unique_ptr<Keyboard>;
    static KeyboardPtr kb;

    static void ta_event_cb(Event & e) {
        auto code = e.get_code();
        auto ta = e.get_target<TextArea>();
        if(code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED) {
            /*Focus on the clicked text area*/
            if(kb != nullptr) kb->set_textarea(ta);
        }
        else if(code == LV_EVENT_READY) {
            LV_LOG_USER("Ready, current text: %s", ta.get_text());
        }
    }

    void textarea_2() {
        auto root = scr_act();
        /*Create the password box*/
        static auto pwd_ta = TextArea(root);
        pwd_ta.set_text("");
        pwd_ta.set_password_mode(true);
        pwd_ta.set_one_line(true);
        pwd_ta.set_width(lv_pct(40));
        pwd_ta.set_pos(5, 20);
        pwd_ta.add_event_cb(ta_event_cb, LV_EVENT_ALL);

        /*Create a label and position it above the text box*/
        static auto pwd_label = Label(root);
        pwd_label.set_text("Password:");
        pwd_label.align_to(pwd_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 0);

        /*Create the one-line mode text area*/
        static auto text_ta = TextArea(root);
        text_ta.set_one_line(true);
        text_ta.set_password_mode(false);
        text_ta.set_width(lv_pct(40));
        text_ta.add_event_cb(ta_event_cb, LV_EVENT_ALL);
        text_ta.align(LV_ALIGN_TOP_RIGHT, -5, 20);


        /*Create a label and position it above the text box*/
        static auto oneline_label = Label(root);
        oneline_label.set_text("Text:");
        oneline_label.align_to(text_ta, LV_ALIGN_OUT_TOP_LEFT, 0, 0);

        /*Create a keyboard*/
        kb = std::make_unique<Keyboard>(root);
        kb->set_size(LV_HOR_RES, LV_VER_RES / 2);

        kb->set_textarea(pwd_ta); /*Focus it on one of the text areas to start*/
    }
}