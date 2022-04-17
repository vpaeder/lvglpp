#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;

    void style_3() {
        static Style style;
        /*Set a background color and a radius*/
        style.set_radius(10);
        style.set_bg_opa(LV_OPA_COVER);
        style.set_bg_color(palette::lighten(Color::Grey, 1));

        /*Add border to the bottom+right*/
        style.set_border_color(palette::main(Color::Blue));
        style.set_border_width(5);
        style.set_border_opa(LV_OPA_50);
        style.set_border_side(LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT);

        /*Create an object with the new style*/
        static auto obj = Container(scr_act());
        obj.add_style(style, LV_STATE_DEFAULT);
        obj.center();
    }
}