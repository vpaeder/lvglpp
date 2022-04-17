#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;

    void style_5() {
        static Style style;
        /*Set a background color and a radius*/
        style.set_radius(5);
        style.set_bg_opa(LV_OPA_COVER);
        style.set_bg_color(palette::light(Color::Grey, 1));

        /*Add a shadow*/
        style.set_shadow_width(55);
        style.set_shadow_color(palette::main(Color::Blue));
        //    style.set_shadow_ofs_x(10);
        //    style.set_shadow_ofs_y(20);
        
        /*Create an object with the new style*/
        auto obj = Container(scr_act());
        obj.add_style(style, LV_STATE_DEFAULT);
        obj.center();
    }
}