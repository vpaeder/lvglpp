#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/button/button.h" // for Button

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    static void btn_event_cb(Event & e) {
        auto code = e.get_code();
        auto btn = e.get_target<Button>();
        if(code == LV_EVENT_CLICKED) {
            static uint8_t cnt = 0;
            cnt++;
            /*Get the first child of the button which is the label and change its text*/
            auto label = btn.get_child<Label>(0);
            label.set_text_fmt("Button: %d", cnt);
        }
    }

    void get_started_1() {
        static auto btn = Button(scr_act());     /*Add a button the current screen*/
        btn.set_pos(10, 10);                            /*Set its position*/
        btn.set_size(120, 50);                          /*Set its size*/
        btn.add_event_cb(btn_event_cb, LV_EVENT_ALL);           /*Assign a callback to the button*/

        static auto label = Label(btn);          /*Add a label to the button*/
        label.set_text("Button");                     /*Set the labels text*/
        label.center();
    }
}