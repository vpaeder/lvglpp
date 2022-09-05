#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/list/list.h" // for List
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    using ListPtr = std::shared_ptr<List>;
    ListPtr list;

    static void event_handler(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<Button>();
        if(code == LV_EVENT_CLICKED)
            LV_LOG_USER("Clicked: %s", list->get_btn_text(obj).c_str());
    }

    void list_1() {
        /*Create a list*/
        list = std::make_shared<List>(scr_act());
        list->set_size(180, 220);
        list->center();

        /*Add buttons to the list*/
        std::vector<std::string> symbols = {"", LV_SYMBOL_FILE, LV_SYMBOL_DIRECTORY, LV_SYMBOL_SAVE, LV_SYMBOL_CLOSE,
        LV_SYMBOL_EDIT, "", LV_SYMBOL_BLUETOOTH, LV_SYMBOL_GPS, LV_SYMBOL_USB, LV_SYMBOL_BATTERY_FULL, "", LV_SYMBOL_OK,
        LV_SYMBOL_CLOSE};
        std::vector<std::string> texts = {"File", "New", "Open", "Save", "Delete", "Edit", "Connectivity",
        "Bluetooth", "Navigation", "USB", "Battery", "Exit", "Apply", "Close"};
        for (size_t n=0; n<texts.size(); n++) {
            if (symbols[n]=="") {
                list->add_text(texts[n]);
            } else {
                auto btn = list->add_btn(symbols[n], texts[n]);
                btn.add_event_cb(event_handler, LV_EVENT_CLICKED);
            }
        }
    }
}