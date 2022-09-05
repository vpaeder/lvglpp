#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/line/line.h" // for Line
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors
#include <vector>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void line_1() {
        /*Create an array for the points of the line*/
        static auto line_points = std::vector<lv_point_t>{ {5, 5}, {70, 70}, {120, 10}, {180, 60}, {240, 10} };

        /*Create style*/
        static Style style_line;
        style_line.set_line_width(8);
        style_line.set_line_color(palette::main(Color::Blue));
        style_line.set_line_rounded(true);

        /*Create a line and apply the new style*/
        static auto line = Line(scr_act());
        line.set_points(line_points);     /*Set the points*/
        line.add_style(style_line, 0);
        line.center();
    }
}