#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/button/button.h" // for Button

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void event_3() {
        static auto cont = Container(scr_act());
        cont.set_size(290, 200);
        cont.center();
        cont.set_flex_flow(LV_FLEX_FLOW_ROW_WRAP);

        uint32_t i;
        for(i = 0; i < 30; i++) {
            auto btn = Button(cont);
            btn.set_size(80, 50);
            btn.add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);

            auto label = Label(btn);
            label.set_text_fmt("%" LV_PRIu32, i);
            label.center();
            label.release_ptr();
            btn.release_ptr();
        }

        auto event_cb = [](Event & e) {
            /*The original target of the event. Can be the buttons or the container*/
            auto target = e.get_target<Object>();
            /*The current target is always the container as the event is added to it*/
            auto cont = e.get_current_target<Object>();
            /*If container was clicked do nothing*/
            if(target == cont) return;
            /*Make the clicked buttons red*/
            target.set_style_bg_color(palette::main(Color::Red), LV_PART_MAIN);
        };
        cont.add_event_cb(event_cb, LV_EVENT_CLICKED);
    }
}