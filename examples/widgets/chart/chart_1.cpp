#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/chart.h" // for Chart

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void chart_1() {
        auto root = scr_act();
        auto chart = Chart(root);
        chart.set_size(200, 150);
        chart.center();
        chart.set_type(LV_CHART_TYPE_LINE);   /*Show lines and points too*/

        /*Add two data series*/
        auto ser1 = chart.add_series(lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
        auto ser2 = chart.add_series(lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_SECONDARY_Y);

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