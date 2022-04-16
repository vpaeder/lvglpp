#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/chart.h" // for Chart
#include "lvglpp/widgets/label.h" // for Label
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/txt.h" // for text functions

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;
    
    static lv_chart_series_t * ser;
    static lv_chart_cursor_t * cursor;

    static void event_cb(Event & e) {
        static int32_t last_id = -1;
        auto obj = e.get_target<Chart>();
        auto code = e.get_code();
        if(code == LV_EVENT_VALUE_CHANGED) {
            last_id = obj.get_selected_point();
            if(last_id != LV_CHART_POINT_NONE)
                obj.set_cursor_point(cursor, last_id);
        }
        else if(code == LV_EVENT_DRAW_PART_END) {
            auto dsc = e.get_draw_part_dsc();
            if(!obj::draw_part_check_type<Chart>(dsc, LV_CHART_DRAW_PART_CURSOR)) return;
            if(dsc->p1 == nullptr || dsc->p2 == nullptr || dsc->p1->y != dsc->p2->y || last_id < 0) return;

            auto data_array = obj.get_y_array(ser);
            auto txt = std::to_string(data_array[last_id]);
            auto size = txt::get_size(txt, LV_FONT_DEFAULT, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

            Area a;
            a->y2 = dsc->p1->y - 5;
            a->y1 = a.y2 - size.y - 10;
            a->x1 = dsc->p1->x + 10;
            a->x2 = a.x1 + size.x + 10;

            RectangleDrawDescriptor draw_rect_dsc;
            draw_rect_dsc->bg_color = lv_palette_main(LV_PALETTE_BLUE);
            draw_rect_dsc->radius = 3;
            draw_rect_dsc.draw(dsc->draw_ctx, a);

            LabelDrawDescriptor draw_label_dsc;
            draw_label_dsc->color = lv_color_white();
            a->x1 += 5;
            a->x2 -= 5;
            a->y1 += 5;
            a->y2 -= 5;
            draw_label_dsc.draw(dsc->draw_ctx, a, txt, nullptr);
        }
    }

    void chart_6() {
        auto root = scr_act();
        auto chart = Chart(root);

        chart.set_size(200, 150);
        chart.align(LV_ALIGN_CENTER, 0, -10);

        chart.set_axis_tick(LV_CHART_AXIS_PRIMARY_Y, 10, 5, 6, 5, true, 40);
        chart.set_axis_tick(LV_CHART_AXIS_PRIMARY_X, 10, 5, 10, 1, true, 30);

        chart.add_event_cb(event_cb, LV_EVENT_ALL);
        chart.refresh_ext_draw_size();

        cursor = chart.add_cursor(lv_palette_main(LV_PALETTE_BLUE), LV_DIR_LEFT | LV_DIR_BOTTOM);

        ser = chart.add_series(lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
        uint32_t i;
        for(i = 0; i < 10; i++) {
            chart.set_next_y_value(ser, lv_rand(10, 90));
        }

        chart.set_zoom_x(500);

        auto label = Label(root);
        label.set_text("Click on a point");
        label.align_to(chart, LV_ALIGN_OUT_TOP_MID, 0, -5);
    }
}