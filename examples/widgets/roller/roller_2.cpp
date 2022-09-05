#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/roller/roller.h" // for Roller
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/style.h" // for Style

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    static void event_handler(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<Roller>();
        if(code == LV_EVENT_VALUE_CHANGED) {
            auto txt = obj.get_selected_str();
            LV_LOG_USER("Selected value: %s\n", txt.c_str());
        }
    }

    void roller_2() {
        auto root = scr_act();
        
        static auto roller = Roller(root);
        /*A style to make the selected option larger*/
        Style style_sel;
        style_sel.set_text_font(&lv_font_montserrat_22);

        const std::string opts = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10";

        /*A roller on the left with left aligned text, and custom width*/
        static auto roller1 = Roller(root);
        roller1.set_options(opts, LV_ROLLER_MODE_NORMAL);
        roller1.set_visible_row_count(2);
        roller1.set_width(100);
        roller1.add_style(style_sel, LV_PART_SELECTED);
        roller1.set_style_text_align(LV_TEXT_ALIGN_LEFT, 0);
        roller1.align(LV_ALIGN_LEFT_MID, 10, 0);
        roller1.add_event_cb(event_handler, LV_EVENT_ALL);
        roller1.set_selected(2, LV_ANIM_OFF);

        /*A roller on the middle with center aligned text, and auto (default) width*/
        static auto roller2 = Roller(root);
        roller2.set_options(opts, LV_ROLLER_MODE_NORMAL);
        roller2.set_visible_row_count(3);
        roller2.add_style(style_sel, LV_PART_SELECTED);
        roller2.align(LV_ALIGN_CENTER, 0, 0);
        roller2.add_event_cb(event_handler, LV_EVENT_ALL);
        roller2.set_selected(5, LV_ANIM_OFF);

        /*A roller on the right with right aligned text, and custom width*/
        static auto roller3 = Roller(root);
        roller3.set_options(opts, LV_ROLLER_MODE_NORMAL);
        roller3.set_visible_row_count(4);
        roller3.set_width(80);
        roller3.add_style(style_sel, LV_PART_SELECTED);
        roller3.set_style_text_align(LV_TEXT_ALIGN_RIGHT, 0);
        roller3.align(LV_ALIGN_RIGHT_MID, -10, 0);
        roller3.add_event_cb(event_handler, LV_EVENT_ALL);
        roller3.set_selected(8, LV_ANIM_OFF);
    }
}