#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/core/object.h" // for Container

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;

    void style_3() {
        Style style;
        /*Set a background color and a radius*/
        style.set_radius(10);
        style.set_bg_opa(LV_OPA_COVER);
        style.set_bg_color(lv_palette_lighten(LV_PALETTE_GREY, 1));

        /*Add border to the bottom+right*/
        style.set_border_color(lv_palette_main(LV_PALETTE_BLUE));
        style.set_border_width(5);
        style.set_border_opa(LV_OPA_50);
        style.set_border_side(LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT);

        /*Create an object with the new style*/
        auto root = scr_act();
        auto obj = Container(root);
        obj.add_style(style, LV_STATE_DEFAULT);
        obj.center();
    }
}