#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/list/list.h" // for List

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    std::unique_ptr<List> list;

    static uint32_t btn_cnt = 1;

    static void float_btn_event_cb(Event & e) {
        auto code = e.get_code();
        auto float_btn = e.get_target<List>();
        if(code == LV_EVENT_CLICKED) {
            char buf[32];
            auto txt = "Track " + std::to_string(btn_cnt);
            auto list_btn = list->add_btn(LV_SYMBOL_AUDIO, txt);
            btn_cnt++;
            float_btn.move_foreground();
            list_btn.scroll_to_view(LV_ANIM_ON);
            list_btn.release_ptr();
        }
    }

    void scroll_3() {
        auto root = scr_act();
        list = std::unique_ptr<List>(root);
        list->set_size(280, 220);
        list->center();

        for(btn_cnt = 1; btn_cnt <= 2; btn_cnt++) {
            auto txt = "Track " + std::to_string(btn_cnt);
            list->add_btn(LV_SYMBOL_AUDIO, txt);
        }

        static auto float_btn = Button(*list);
        float_btn.set_size(50, 50);
        float_btn.add_flag(LV_OBJ_FLAG_FLOATING);
        float_btn.align(LV_ALIGN_BOTTOM_RIGHT, 0, -list->get_style_pad_right(LV_PART_MAIN));
        float_btn.add_event_cb(float_btn_event_cb, LV_EVENT_ALL);
        float_btn.set_style_radius(LV_RADIUS_CIRCLE, 0);
        float_btn.set_style_bg_img_src(LV_SYMBOL_PLUS, 0);
        float_btn.set_style_text_font(float_btn.get_font_large(), 0);
    }
}