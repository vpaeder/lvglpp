#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/slider/slider.h" // for Slider
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/txt.h" // for text functions

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    static void event_handler(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<Slider>();

        /*Provide some extra space for the value*/
        if(code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
            e.set_ext_draw_size(50);
        }
        else if(code == LV_EVENT_DRAW_PART_END) {
            auto dsc = e.get_draw_part_dsc();
            if(dsc->part == LV_PART_INDICATOR) {
                auto txt = std::to_string(obj.get_left_value()) + " - " + std::to_string(obj.get_value());

                auto label_size = txt::get_size(txt, LV_FONT_DEFAULT, 0, 0, LV_COORD_MAX, 0);
                Area label_area;
                label_area->x1 = dsc->draw_area->x1 + Area(dsc->draw_area).get_width() / 2 - label_size.x / 2;
                label_area->x2 = label_area->x1 + label_size.x;
                label_area->y2 = dsc->draw_area->y1 - 10;
                label_area->y1 = label_area->y2 - label_size.y;

                LabelDrawDescriptor label_draw_dsc;
                label_draw_dsc->color = lv_color_hex3(0x888);
                label_draw_dsc.draw(dsc->draw_ctx, label_area, txt, nullptr);
            }
        }
   }

    void slider_3() {
        static auto slider = Slider(scr_act());
        slider.center();

        slider.set_mode(LV_SLIDER_MODE_RANGE);
        slider.set_value(70, LV_ANIM_OFF);
        slider.set_left_value(20, LV_ANIM_OFF);

        slider.add_event_cb(event_handler, LV_EVENT_ALL);
        slider.refresh_ext_draw_size();
    }
}