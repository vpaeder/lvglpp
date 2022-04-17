#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/misc/style.h" // for Style, LinearStyleTransition
#include "lvglpp/misc/color.h" // for colors
#include "lvglpp/core/object.h" // for Container
#include <vector>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;

    void style_10() {
        std::vector<lv_style_prop_t> props = {LV_STYLE_BG_COLOR, LV_STYLE_BORDER_COLOR, LV_STYLE_BORDER_WIDTH, LV_STYLE_PROP_INV};
        /* A default transition
        * Make it fast (100ms) and start with some delay (200 ms)*/
        static LinearStyleTransition trans_def(props, 100, 200);
        /* A special transition when going to pressed state
        * Make it slow (500 ms) but start  without delay*/
        static LinearStyleTransition trans_pr(props, 500, 0);

        static Style style_def;
        style_def.set_transition(trans_def);

        static Style style_pr;
        style_pr.set_bg_color(palette::main(Color::Red));
        style_pr.set_border_width(6);
        style_pr.set_border_color(palette::dark(Color::Red, 3));
        style_pr.set_transition(trans_pr);
        
        /*Create an object with the new style*/
        static auto obj = Container(scr_act());
        obj.add_style(style_def, LV_STATE_DEFAULT);
        obj.add_style(style_pr, LV_STATE_PRESSED);
        obj.center();
    }
}