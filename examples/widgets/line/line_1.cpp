#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/line.h" // for Line
#include "lvglpp/misc/style.h" // for Style
#include <vector>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void line_1() {
        auto root = scr_act();
        
        /*Create an array for the points of the line*/
        auto line_points = std::vector<lv_point_t>{ {5, 5}, {70, 70}, {120, 10}, {180, 60}, {240, 10} };

        /*Create style*/
        Style style_line;
        style_line.set_line_width(8);
        style_line.set_line_color(lv_palette_main(LV_PALETTE_BLUE));
        style_line.set_line_rounded(true);

        /*Create a line and apply the new style*/
        auto line = Line(root);
        line.set_points(line_points);     /*Set the points*/
        line.add_style(style_line, 0);
        line.center();
    }
}