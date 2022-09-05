#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/chart/chart.h" // for Chart
#include "lvglpp/misc/timer.h" // for Timer
#include "lvglpp/misc/color.h" // for colors
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/draw/mask.h" // for mask functions

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;
    using namespace lvgl::draw;

    using ChartPtr = std::shared_ptr<Chart>;
    using SeriesPtr = lv_chart_series_t*;

    static void draw_event_cb(Event & e) {
        auto obj = e.get_target<Chart>();

        /*Add the faded area before the lines are drawn*/
        auto dsc = e.get_draw_part_dsc();
        if(dsc->part == LV_PART_ITEMS) {
            if(!dsc->p1 || !dsc->p2) return;
            /*Add a line mask that keeps the area below the line*/
            auto line_mask = LineMask(dsc->p1->x, dsc->p1->y, dsc->p2->x, dsc->p2->y, LV_DRAW_MASK_LINE_SIDE_BOTTOM);
            line_mask.add();
            /*Add a fade effect: transparent bottom covering top*/
            auto fade_mask = FadeMask(obj->coords, LV_OPA_COVER, obj->coords.y1 + obj.get_height() / 8, LV_OPA_TRANSP, obj->coords.y2);
            fade_mask.add();
            /*Draw a rectangle that will be affected by the mask*/
            RectangleDrawDescriptor draw_rect_dsc;
            draw_rect_dsc->bg_opa = LV_OPA_20;
            draw_rect_dsc->bg_color = dsc->line_dsc->color;

            Area a;
            a->x1 = dsc->p1->x;
            a->x2 = dsc->p2->x - 1;
            a->y1 = LV_MIN(dsc->p1->y, dsc->p2->y);
            a->y2 = obj->coords.y2;
            draw_rect_dsc.draw(dsc->draw_ctx, a);
        }
        /*Hook the division lines too*/
        else if(dsc->part == LV_PART_MAIN) {
            if(dsc->line_dsc == nullptr || dsc->p1 == nullptr || dsc->p2 == nullptr) return;

            /*Vertical line*/
            if(dsc->p1->x == dsc->p2->x) {
                dsc->line_dsc->color  = palette::light(Color::Grey, 1);
                if(dsc->id == 3) {
                    dsc->line_dsc->width  = 2;
                    dsc->line_dsc->dash_gap  = 0;
                    dsc->line_dsc->dash_width  = 0;
                }
                else {
                    dsc->line_dsc->width = 1;
                    dsc->line_dsc->dash_gap  = 6;
                    dsc->line_dsc->dash_width  = 6;
                }
            }
            /*Horizontal line*/
            else {
                if(dsc->id == 2) {
                    dsc->line_dsc->width  = 2;
                    dsc->line_dsc->dash_gap  = 0;
                    dsc->line_dsc->dash_width  = 0;
                }
                else {
                    dsc->line_dsc->width = 2;
                    dsc->line_dsc->dash_gap  = 6;
                    dsc->line_dsc->dash_width  = 6;
                }

                if(dsc->id == 1  || dsc->id == 3) {
                    dsc->line_dsc->color  = palette::main(Color::Green);
                }
                else {
                    dsc->line_dsc->color  = palette::light(Color::Grey, 1);
                }
            }
        }
    }

    class ChartTimer : public Timer {
    private:
        ChartPtr chart;
        SeriesPtr ser1;
        SeriesPtr ser2;

    public:
        ChartTimer(uint32_t period, ChartPtr chart, SeriesPtr ser1, SeriesPtr ser2) : 
            Timer(period), chart(chart), ser1(ser1), ser2(ser2) {}
        
        void callback(Timer & timer) override {
            static uint32_t cnt = 0;
            this->chart->set_next_y_value(this->ser1, lv_rand(20, 90));

            if(cnt % 4 == 0) this->chart->set_next_y_value(this->ser2, lv_rand(40, 60));

            cnt++;
        }
    };

    void chart_2() {
        static auto chart = std::make_shared<Chart>(scr_act());

        chart->set_size(200, 150);
        chart->center();
        chart->set_type(LV_CHART_TYPE_LINE);   /*Show lines and points too*/

        chart->set_div_line_count(5, 7);

        chart->add_event_cb(draw_event_cb, LV_EVENT_DRAW_PART_BEGIN);
        chart->set_update_mode(LV_CHART_UPDATE_MODE_CIRCULAR);

        /*Add two data series*/
        auto ser1 = chart->add_series(palette::main(Color::Red), LV_CHART_AXIS_PRIMARY_Y);
        auto ser2 = chart->add_series(palette::main(Color::Blue), LV_CHART_AXIS_SECONDARY_Y);

        uint32_t i;
        for(i = 0; i < 10; i++) {
            chart->set_next_y_value(ser1, lv_rand(20, 90));
            chart->set_next_y_value(ser2, lv_rand(30, 70));
        }

        static auto timer = ChartTimer(200, chart, ser1, ser2);
    }
}