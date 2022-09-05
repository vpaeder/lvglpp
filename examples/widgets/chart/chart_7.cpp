#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/chart/chart.h" // for Chart
#include "lvglpp/misc/timer.h" // for Timer
#include "lvglpp/misc/color.h" // for colors
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    using ChartPtr = std::shared_ptr<Chart>;

    static void draw_event_cb(Event & e) {
        auto dsc = e.get_draw_part_dsc();
        if(dsc->part == LV_PART_ITEMS) {
            auto obj = e.get_target<Chart>();
            auto ser = obj.get_series_first();
            uint32_t cnt = obj.get_point_count();
            /*Make older value more transparent*/
            dsc->rect_dsc->bg_opa = (LV_OPA_COVER *  dsc->id) / (cnt - 1);

            /*Make smaller values blue, higher values red*/
            auto x_array = obj.get_x_array(ser);
            auto y_array = obj.get_y_array(ser);
            /*dsc->id is the tells drawing order, but we need the ID of the point being drawn.*/
            uint32_t start_point = obj.get_x_start_point(ser);
            uint32_t p_act = (start_point + dsc->id) % cnt; /*Consider start point to get the index of the array*/
            lv_opa_t x_opa = (x_array[p_act] * LV_OPA_50) / 200;
            lv_opa_t y_opa = (y_array[p_act] * LV_OPA_50) / 1000;

            dsc->rect_dsc->bg_color = color::mix(palette::main(Color::Red),
                                                 palette::main(Color::Blue),
                                                 x_opa + y_opa);
        }

    }

    class ChartTimer : public Timer {
    private:
        ChartPtr chart;

    public:
        ChartTimer(uint32_t period, ChartPtr chart) : Timer(period), chart(chart) {}
        
        void callback(Timer & timer) override {
            this->chart->set_next_xy_values(
                this->chart->get_series_first(), lv_rand(0, 200), lv_rand(0, 1000));

        }
    };

    void chart_7() {
        static auto chart = std::make_shared<Chart>(scr_act());

        chart->set_size(200, 150);
        chart->align(LV_ALIGN_CENTER, 0, 0);
        chart->add_event_cb(draw_event_cb, LV_EVENT_DRAW_PART_BEGIN);
        chart->set_style_line_width(0, LV_PART_ITEMS);   /*Remove the lines*/

        chart->set_type(LV_CHART_TYPE_SCATTER);

        chart->set_axis_tick(LV_CHART_AXIS_PRIMARY_X, 5, 5, 5, 1, true, 30);
        chart->set_axis_tick(LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 5, true, 50);

        chart->set_range(LV_CHART_AXIS_PRIMARY_X, 0, 200);
        chart->set_range(LV_CHART_AXIS_PRIMARY_Y, 0, 1000);

        chart->set_point_count(50);

        auto ser = chart->add_series(palette::main(Color::Red), LV_CHART_AXIS_PRIMARY_Y);
        for(uint32_t i = 0; i < 50; i++)
            chart->set_next_xy_values(ser, lv_rand(0, 200), lv_rand(0, 1000));

        static auto timer = ChartTimer(100, chart);
    }
}