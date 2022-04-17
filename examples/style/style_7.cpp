#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors
#include "lvglpp/widgets/arc.h" // for Arc

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;
    using namespace lvgl::widgets;

    void style_7() {
        Style style;
        style.set_arc_color(palette::main(Color::Red));
        style.set_arc_width(4);        
        /*Create an object with the new style*/
        auto root = scr_act();
        auto obj = Arc(root);
        obj.add_style(style, LV_STATE_DEFAULT);
        obj.center();
    }
}