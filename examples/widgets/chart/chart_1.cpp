#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/chart/chart.h" // for Chart
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void chart_1() {
        static auto chart = Chart(scr_act());
        chart.set_size(200, 150);
        chart.center();
        chart.set_type(LV_CHART_TYPE_LINE);   /*Show lines and points too*/

        /*Add two data series*/
        auto ser1 = chart.add_series(palette::main(Color::Red), LV_CHART_AXIS_PRIMARY_Y);
        auto ser2 = chart.add_series(palette::main(Color::Green), LV_CHART_AXIS_SECONDARY_Y);

        /*Set the next points on 'ser1'*/
        chart.set_next_y_value(ser1, 10);
        chart.set_next_y_value(ser1, 10);
        chart.set_next_y_value(ser1, 10);
        chart.set_next_y_value(ser1, 10);
        chart.set_next_y_value(ser1, 10);
        chart.set_next_y_value(ser1, 10);
        chart.set_next_y_value(ser1, 10);
        chart.set_next_y_value(ser1, 30);
        chart.set_next_y_value(ser1, 70);
        chart.set_next_y_value(ser1, 90);

        /*Directly set points on 'ser2'*/
        ser2->y_points[0] = 90;
        ser2->y_points[1] = 70;
        ser2->y_points[2] = 65;
        ser2->y_points[3] = 65;
        ser2->y_points[4] = 65;
        ser2->y_points[5] = 65;
        ser2->y_points[6] = 65;
        ser2->y_points[7] = 65;
        ser2->y_points[8] = 65;
        ser2->y_points[9] = 65;

        chart.refresh(); /*Required after direct set*/
    }
}