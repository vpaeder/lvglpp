#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/btnmatrix/btnmatrix.h" // for ButtonMatrix
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors
#include <vector>
#include <string>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    static void event_cb(Event & e) {
        auto obj = e.get_target<ButtonMatrix>();
        auto id = obj.get_selected_btn();
        bool prev = id == 0 ? true : false;
        bool next = id == 6 ? true : false;
        if(prev || next) {
            /*Find the checked button*/
            uint32_t i;
            for(i = 1; i < 7; i++) {
                if(obj.has_btn_ctrl(i, LV_BTNMATRIX_CTRL_CHECKED)) break;
            }

            if(prev && i > 1) i--;
            else if(next && i < 5) i++;

            obj.set_btn_ctrl(i, LV_BTNMATRIX_CTRL_CHECKED);
        }
    }


    void btnmatrix_2() {
        static auto btnm = ButtonMatrix(scr_act());

        static Style style_bg;
        style_bg.set_pad_all(0);
        style_bg.set_pad_gap(0);
        style_bg.set_clip_corner(true);
        style_bg.set_radius(LV_RADIUS_CIRCLE);
        style_bg.set_border_width(0);


        static Style style_btn;
        style_btn.set_radius(0);
        style_btn.set_border_width(1);
        style_btn.set_border_opa(LV_OPA_50);
        style_btn.set_border_color(palette::main(Color::Grey));
        style_btn.set_border_side(LV_BORDER_SIDE_INTERNAL);
        style_btn.set_radius(0);

        static std::vector<std::string> map = {LV_SYMBOL_LEFT, "1", "2", "3", "4", "5", LV_SYMBOL_RIGHT, ""};

        btnm.set_map(map);
        btnm.add_style(style_bg, 0);
        btnm.add_style(style_btn, LV_PART_ITEMS);
        btnm.add_event_cb(event_cb, LV_EVENT_VALUE_CHANGED);
        btnm.set_size(225, 35);

        /*Allow selecting on one number at time*/
        btnm.set_btn_ctrl_all(LV_BTNMATRIX_CTRL_CHECKABLE);
        btnm.clear_btn_ctrl(0, LV_BTNMATRIX_CTRL_CHECKABLE);
        btnm.clear_btn_ctrl(6, LV_BTNMATRIX_CTRL_CHECKABLE);

        btnm.set_one_checked(true);
        btnm.set_btn_ctrl(1, LV_BTNMATRIX_CTRL_CHECKED);

        btnm.center();

   }
}