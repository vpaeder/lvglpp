#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/spinbox/spinbox.h" // for Spinbox
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    using SpinboxPtr = std::unique_ptr<Spinbox>;
    SpinboxPtr spinbox;

    void spinbox_1() {
        auto root = scr_act();
        spinbox = std::make_unique<Spinbox>(root);

        spinbox->set_range(-1000, 25000);
        spinbox->set_digit_format(5, 2);
        spinbox->step_prev();
        spinbox->set_width(100);
        spinbox->center();

        auto h = spinbox->get_height();

        static auto btn1 = Button(root);
        btn1.set_size(h, h);
        btn1.align_to(*spinbox, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
        btn1.set_style_bg_img_src(LV_SYMBOL_PLUS, 0);
        auto lv_spinbox_increment_event_cb = [](Event & e) {
            auto code = e.get_code();
            if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT)
                spinbox->increment();
        };
        btn1.add_event_cb(lv_spinbox_increment_event_cb, LV_EVENT_ALL);

        static auto btn2 = Button(root);
        btn2.set_size(h, h);
        btn2.align_to(*spinbox, LV_ALIGN_OUT_LEFT_MID, -5, 0);
        btn2.set_style_bg_img_src(LV_SYMBOL_MINUS, 0);
        auto lv_spinbox_decrement_event_cb = [](Event & e) {
            auto code = e.get_code();
            if(code == LV_EVENT_SHORT_CLICKED || code  == LV_EVENT_LONG_PRESSED_REPEAT)
                spinbox->decrement();
        };
        btn2.add_event_cb(lv_spinbox_decrement_event_cb, LV_EVENT_ALL);
    }
}