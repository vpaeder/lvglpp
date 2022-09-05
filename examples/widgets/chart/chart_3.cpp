#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/chart/chart.h" // for Chart
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    static void draw_event_cb(Event & e) {
        auto dsc = e.get_draw_part_dsc();
        
        if(!obj::draw_part_check_type<Chart>(dsc, LV_CHART_DRAW_PART_TICK_LABEL)) return;

        if(dsc->id == LV_CHART_AXIS_PRIMARY_X && dsc->text) {
            const char * month[] = {"Jan", "Febr", "March", "Apr", "May", "Jun", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
            lv_snprintf(dsc->text, dsc->text_length, "%s", month[dsc->value]);
        }
    }

    void chart_3() {
        static auto chart = Chart(scr_act());

        chart.set_size(200, 150);
        chart.center();
        chart.set_type(LV_CHART_TYPE_BAR);
        chart.set_range(LV_CHART_AXIS_PRIMARY_Y, 0, 100);
        chart.set_range(LV_CHART_AXIS_SECONDARY_Y, 0, 400);
        chart.set_point_count(12);
        chart.add_event_cb(draw_event_cb, LV_EVENT_DRAW_PART_BEGIN);

        /*Add ticks and label to every axis*/
        chart.set_axis_tick(LV_CHART_AXIS_PRIMARY_X, 10, 5, 12, 3, true, 40);
        chart.set_axis_tick(LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 2, true, 50);
        chart.set_axis_tick(LV_CHART_AXIS_SECONDARY_Y, 10, 5, 3, 4, true, 50);

        /*Zoom in a little in X*/
        chart.set_zoom_x(800);

        /*Add two data series*/
        auto ser1 = chart.add_series(palette::light(Color::Green, 2), LV_CHART_AXIS_PRIMARY_Y);
        auto ser2 = chart.add_series(palette::dark(Color::Green, 2), LV_CHART_AXIS_SECONDARY_Y);

        /*Set the next points on 'ser1'*/
        chart.set_next_y_value(ser1, 31);
        chart.set_next_y_value(ser1, 66);
        chart.set_next_y_value(ser1, 10);
        chart.set_next_y_value(ser1, 89);
        chart.set_next_y_value(ser1, 63);
        chart.set_next_y_value(ser1, 56);
        chart.set_next_y_value(ser1, 32);
        chart.set_next_y_value(ser1, 35);
        chart.set_next_y_value(ser1, 57);
        chart.set_next_y_value(ser1, 85);
        chart.set_next_y_value(ser1, 22);
        chart.set_next_y_value(ser1, 58);

        auto ser2_array = chart.get_y_array(ser2);
        /*Directly set points on 'ser2'*/
        ser2_array[0] = 92;
        ser2_array[1] = 71;
        ser2_array[2] = 61;
        ser2_array[3] = 15;
        ser2_array[4] = 21;
        ser2_array[5] = 35;
        ser2_array[6] = 35;
        ser2_array[7] = 58;
        ser2_array[8] = 31;
        ser2_array[9] = 53;
        ser2_array[10] = 33;
        ser2_array[11] = 73;

        chart.refresh(); /*Required after direct set*/
    }
}