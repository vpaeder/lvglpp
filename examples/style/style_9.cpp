#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors
#include "lvglpp/widgets/line.h" // for Line
#include <vector>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;
    using namespace lvgl::widgets;

    void style_9() {
        Style style;
        style.set_line_color(palette::main(Color::Grey));
        style.set_line_width(6);
        style.set_line_rounded(true);
        /*Create an object with the new style*/
        auto root = scr_act();
        auto obj = Line(root);
        obj.add_style(style, LV_STATE_DEFAULT);
        std::vector<lv_point_t> points = {{10, 30}, {30, 50}, {100, 0}};
        obj.set_points(points);
        obj.center();
    }
}