#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/chart/chart.h" // for Chart
#include "lvglpp/misc/timer.h" // for Timer
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    class ChartTimer : public Timer {
    private:
        ChartPtr chart;

    public:
        ChartTimer(uint32_t period, ChartPtr chart) : Timer(period), chart(chart) {}
        
        void callback(Timer & timer) override {
            auto ser = this->chart->get_series_next(nullptr);
            this->chart->set_next_value(ser, lv_rand(10, 90));

            uint16_t p = this->chart->get_point_count();
            uint16_t s = this->chart->get_x_start_point(ser);
            auto a = this->chart->get_y_array(ser);

            a[(s + 1) % p] = LV_CHART_POINT_NONE;
            a[(s + 2) % p] = LV_CHART_POINT_NONE;
            a[(s + 2) % p] = LV_CHART_POINT_NONE;

            this->chart->refresh();
        }
    };

    void chart_9() {
        static auto chart = std::make_shared<Chart>(scr_act());

        chart->set_update_mode(LV_CHART_UPDATE_MODE_CIRCULAR);
        chart->set_size(200, 150);
        chart->center();

        chart->set_point_count(30);
        auto ser = chart->add_series(palette::main(Color::Red), LV_CHART_AXIS_PRIMARY_Y);
    
        /*Prefill with data*/
        uint32_t i;
        for(i = 0; i < 30; i++)
            chart->set_next_value(ser, lv_rand(10, 90));
        
        auto timer = ChartTimer(300, chart);
    }
}