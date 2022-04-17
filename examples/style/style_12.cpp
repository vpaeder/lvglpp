#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors
#include "lvglpp/core/object.h" // for Container

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;

    void style_12() {
        static Style style;
        style.set_bg_color(palette::main(Color::Green));
        style.set_border_color(palette::light(Color::Green, 3));
        style.set_border_width(3);
        
        static auto obj = Container(scr_act());
        obj.add_style(style, LV_STATE_DEFAULT);
        obj.align(LV_ALIGN_LEFT_MID, 20, 0);
        obj.center();

        /*Overwrite the background color locally*/
        obj.set_style_bg_color(palette::main(Color::Orange), LV_PART_MAIN);
    }
}