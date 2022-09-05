#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/roller/roller.h" // for Roller
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors
#include "lvglpp/draw/mask.h" // for FadeMask

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;
    using namespace lvgl::draw;

    static void mask_event_cb(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<Roller>();
        static std::unique_ptr<FadeMask> fade_mask_top, fade_mask_bottom;

        if(code == LV_EVENT_COVER_CHECK) {
            e.set_cover_res(LV_COVER_RES_MASKED);
        }
        else if(code == LV_EVENT_DRAW_MAIN_BEGIN) {
            /* add mask */
            auto font = obj.get_style_text_font(LV_PART_MAIN);
            auto line_space = obj.get_style_text_line_space(LV_PART_MAIN);
            lv_coord_t font_h = lv_font_get_line_height(font);
            auto roller_coords = obj.get_coords();

            Area rect_area;
            rect_area->x1 = roller_coords.x1;
            rect_area->x2 = roller_coords.x2;
            rect_area->y1 = roller_coords.y1;
            rect_area->y2 = roller_coords.y1 + (obj.get_height() - font_h - line_space) / 2;
            fade_mask_top = std::make_unique<FadeMask>(rect_area, LV_OPA_TRANSP, rect_area.y1, LV_OPA_COVER, rect_area.y2);
            fade_mask_top->add();

            rect_area->y1 = rect_area->y2 + font_h + line_space - 1;
            rect_area->y2 = roller_coords.y2;
            fade_mask_bottom = std::make_unique<FadeMask>(rect_area, LV_OPA_COVER, rect_area.y1, LV_OPA_TRANSP, rect_area.y2);
            fade_mask_bottom->add();
        }
        else if(code == LV_EVENT_DRAW_POST_END) {
            fade_mask_top = nullptr;
            fade_mask_bottom = nullptr;
        }
    }

    void roller_3() {
        static Style style;
        style.set_bg_color(palette::black());
        style.set_text_color(palette::white());
        style.set_border_width(0);
        style.set_pad_all(0);
        root.add_style(style, LV_PART_MAIN);

        static auto roller = Roller(scr_act());
        roller.add_style(style, LV_PART_MAIN);
        roller.set_style_bg_opa(LV_OPA_TRANSP, LV_PART_SELECTED);

        #if LV_FONT_MONTSERRAT_22
        roller.set_style_text_font(&lv_font_montserrat_22, LV_PART_SELECTED);
        #endif

        roller.set_options("January\n"
                           "February\n"
                           "March\n"
                           "April\n"
                           "May\n"
                           "June\n"
                           "July\n"
                           "August\n"
                           "September\n"
                           "October\n"
                           "November\n"
                           "December",
                           LV_ROLLER_MODE_NORMAL);

        roller.center();
        roller.set_visible_row_count(3);
        roller.add_event_cb(mask_event_cb, LV_EVENT_ALL);
    }
}
