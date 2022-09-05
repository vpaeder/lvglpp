#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void button_1() {
        auto root = scr_act();
        static auto button1 = Button(root);
        static auto label1 = Label(button1);

        auto event_handler = [](Event & e) {
            auto code = e.get_code();

            if(code == LV_EVENT_CLICKED) {
                LV_LOG_USER("Clicked");
            }
            else if(code == LV_EVENT_VALUE_CHANGED) {
                LV_LOG_USER("Toggled");
            }            
        };
        button1.add_event_cb(event_handler, LV_EVENT_ALL);
        button1.align(LV_ALIGN_CENTER, 0, -40);

        label1.set_text("Button");
        label1.center();

        static auto button2 = Button(root);
        static auto label2 = Label(button2);
        button2.add_event_cb(event_handler, LV_EVENT_ALL);
        button2.align(LV_ALIGN_CENTER, 0, 40);
        button2.add_flag(LV_OBJ_FLAG_CHECKABLE);
        button2.set_height(LV_SIZE_CONTENT);

        label2.set_text("Toggle");
        label2.center();
    }
}