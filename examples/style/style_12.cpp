#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/core/object.h" // for Container

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;

    void style_12() {
        Style style;
        style.set_bg_color(lv_palette_main(LV_PALETTE_GREEN));
        style.set_border_color(lv_palette_lighten(LV_PALETTE_GREEN, 3));
        style.set_border_width(3);
        
        auto root = scr_act();
        auto obj = Container(root);
        obj.add_style(style, LV_STATE_DEFAULT);
        obj.align(LV_ALIGN_LEFT_MID, 20, 0);
        obj.center();

        /*Overwrite the background color locally*/
        obj.set_style_bg_color(lv_palette_main(LV_PALETTE_ORANGE), LV_PART_MAIN);
    }
}