#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/win/win.h" // for Window
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void win_1() {
        static auto win = Window(scr_act(), 40);
        win.add_title("A title");

        auto event_handler(Event & e) {
            auto obj = e.get_target<Object>();
            LV_LOG_USER("Button %d clicked", static_cast<int>(obj.get_index()));
        }

        auto btn1 = win.add_btn(LV_SYMBOL_LEFT, 40);
        btn1.add_event_cb(event_handler, LV_EVENT_CLICKED);
        auto btn2 = win.add_btn(LV_SYMBOL_RIGHT, 40);
        btn2.add_event_cb(event_handler, LV_EVENT_CLICKED);
        auto btn3 = win.add_btn(LV_SYMBOL_CLOSE, 60);
        btn3.add_event_cb(event_handler, LV_EVENT_CLICKED);

        auto cont = win.get_content();  /*Content can be added here*/
        static auto label = Label(cont);
        label.set_text("This is\n"
                       "a pretty\n"
                       "long text\n"
                       "to see how\n"
                       "the window\n"
                       "becomes\n"
                       "scrollable.\n"
                       "\n"
                       "\n"
                       "Some more\n"
                       "text to be\n"
                       "sure it\n"
                       "overflows. :)");
    }
}