#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;

    void style_2() {
        static Style style;
        style.set_radius(5);

        /*Make a gradient*/
        style.set_bg_opa(LV_OPA_COVER);
        lv_grad_dsc_t grad;
        grad.dir = LV_GRAD_DIR_VER;
        grad.stops_count = 2;
        grad.stops[0].color = palette::light(Color::Grey, 1);
        grad.stops[1].color = palette::main(Color::Blue);

        /*Shift the gradient to the bottom*/
        grad.stops[0].frac  = 128;
        grad.stops[1].frac  = 192;

        style.set_bg_grad(&grad);
        /*Create an object with the new style*/
        static auto obj = Container(scr_act());
        obj.add_style(style, LV_STATE_DEFAULT);
        obj.center();
    }
}