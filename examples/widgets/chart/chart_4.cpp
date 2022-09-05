#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/chart/chart.h" // for Chart
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    static void event_cb(Event & e) {
        auto code = e.get_code();
        auto chart = e.get_target<Chart>();

        if(code == LV_EVENT_VALUE_CHANGED) {
            chart.invalidate();
        }
        if(code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
            auto s = e.get_param<lv_coord_t>();
            *s = LV_MAX(*s, 20);
        }
        else if(code == LV_EVENT_DRAW_POST_END) {
            int32_t id = chart.get_selected_point();
            if(id == LV_CHART_POINT_NONE) return;

            LV_LOG_USER("Selected point %d", static_cast<int>(id));

            auto ser = chart.get_series_first();
            while(ser) {
                auto p = chart.get_point_pos_by_id(ser, id);
                auto y_array = chart.get_y_array(ser);
                std::string txt = LV_SYMBOL_DUMMY + "$" + std::to_string(y_array[id]);

                RectangleDrawDescriptor draw_rect_dsc;
                draw_rect_dsc->bg_color = palette::black();
                draw_rect_dsc->bg_opa = LV_OPA_50;
                draw_rect_dsc->radius = 3;
                draw_rect_dsc->bg_img_src = txt.c_str();
                draw_rect_dsc->bg_img_recolor = palette::white();

                Area a;
                a->x1 = chart->coords.x1 + p.x - 20;
                a->x2 = chart->coords.x1 + p.x + 20;
                a->y1 = chart->coords.y1 + p.y - 30;
                a->y2 = chart->coords.y1 + p.y - 10;

                auto draw_ctx = e.get_draw_ctx();
                draw_rect_dsc.draw(draw_ctx, a);

                ser = chart.get_series_next(ser);
            }
        }
        else if(code == LV_EVENT_RELEASED) {
            chart.invalidate();
        }
    }

    void chart_4() {
        static auto chart = Chart(scr_act());

        chart.set_size(200, 150);
        chart.center();

        chart.add_event_cb(event_cb, LV_EVENT_ALL);
        chart.refresh_ext_draw_size();

        /*Zoom in a little in X*/
        chart.set_zoom_x(800);

        /*Add two data series*/
        auto ser1 = chart.add_series(palette::main(Color::Red), LV_CHART_AXIS_PRIMARY_Y);
        auto ser2 = chart.add_series(palette::main(Color::Green), LV_CHART_AXIS_PRIMARY_Y);
        uint32_t i;
        for(i = 0; i < 10; i++) {
            chart.set_next_y_value(ser1, lv_rand(60, 90));
            chart.set_next_y_value(ser2, lv_rand(10, 40));
        }
    }
}