#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/dropdown/dropdown.h" // for Dropdown
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/draw/image.h" // for ImageDescriptor

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    static void event_handler(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<Dropdown>();
        if(code == LV_EVENT_VALUE_CHANGED) {
            auto txt = obj.get_selected_str();
            LV_LOG_USER("Option: %s", txt.c_str());
        }
    }

    void dropdown_3() {
        auto root = scr_act();

        static auto dd = Dropdown(root);
        dd.align(LV_ALIGN_TOP_LEFT, 10, 10);
        dd.set_options("New project\n"
                       "New file\n"
                       "Save\n"
                       "Save as ...\n"
                       "Open project\n"
                       "Recent projects\n"
                       "Preferences\n"
                       "Exit");

        /*Set a fixed text to display on the button of the drop-down list*/
        dd.set_text("Menu");

        /*Use a custom image as down icon and flip it when the list is opened*/
        static auto img = ImageDescriptor();
        img.set_src(img_caret_down_map, 13, 8, LV_IMG_CF_TRUE_COLOR_ALPHA);
        dd.set_symbol(img);
        dd.set_style_transform_angle(1800, LV_PART_INDICATOR | LV_STATE_CHECKED);

        /*In a menu we don't need to show the last clicked item*/
        dd.set_selected_highlight(false);

        dd.add_event_cb(event_handler, LV_EVENT_VALUE_CHANGED);
    }
}