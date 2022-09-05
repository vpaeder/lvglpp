#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/button/button.h" // for Button

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    using LabelPtr = std::unique_ptr<Label>;
    LabelPtr info_label;

    void event_2() {
        auto root = scr_act();
        static auto btn = Button(root);
        btn.set_size(100, 50);
        btn.center();

        static auto btn_label = Label(btn);
        btn_label.set_text("Click me!");
        btn_label.center();

        info_label = std::make_unique<Label>(root);
        info_label->set_text("The last button event:\nNone");

        auto event_cb = [](Event & e) {
            auto code = e.get_code();

            switch(code) {
                case LV_EVENT_PRESSED:
                    info_label->set_text("The last button event:\nLV_EVENT_PRESSED");
                    break;
                case LV_EVENT_CLICKED:
                    info_label->set_text("The last button event:\nLV_EVENT_CLICKED");
                    break;
                case LV_EVENT_LONG_PRESSED:
                    info_label->set_text("The last button event:\nLV_EVENT_LONG_PRESSED");
                    break;
                case LV_EVENT_LONG_PRESSED_REPEAT:
                    info_label->set_text("The last button event:\nLV_EVENT_LONG_PRESSED_REPEAT");
                    break;
                default:
                    break;
            }
        };
        btn.add_event_cb(event_cb, LV_EVENT_ALL);

    }
}