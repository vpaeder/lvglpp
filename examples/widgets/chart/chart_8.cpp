#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/chart/chart.h" // for Chart
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    class StackedAreaChart : public Chart {
    public:
        using Chart::Chart;
        std::vector<lv_chart_series_t*> series_list{3};

    };

    static void draw_event_cb(Event & e) {
        auto obj = e.get_target<StackedAreaChart>();

        /*Add the faded area before the lines are drawn*/
        auto dsc = e.get_draw_part_dsc();
        if(dsc->part == LV_PART_ITEMS) {
            if(!dsc->p1 || !dsc->p2)
                return;

            /*Add a line mask that keeps the area below the line*/
            auto line_mask = LineMask(dsc->p1->x, dsc->p1->y, dsc->p2->x, dsc->p2->y, LV_DRAW_MASK_LINE_SIDE_BOTTOM);
            line_mask.add();

            /*Draw a rectangle that will be affected by the mask*/
            RectangleDrawDescriptor draw_rect_dsc;
            draw_rect_dsc->bg_opa = LV_OPA_COVER;
            draw_rect_dsc->bg_color = dsc->line_dsc->color;

            Area a;
            a->x1 = dsc->p1->x;
            a->x2 = dsc->p2->x;
            a->y1 = std::min(dsc->p1->y, dsc->p2->y);
            a->y2 = obj->coords.y2 - 13; /* -13 cuts off where the rectangle draws over the chart margin. Without this an area of 0 doesn't look like 0 */
            draw_rect_dsc.draw(dsc->draw_ctx, a);
        }
    }

    static int32_t round_fixed_point(int32_t n, int8_t shift) {
        /* Create a bitmask to isolates the decimal part of the fixed point number */
        int32_t mask = 1;
        for(int32_t bit_pos = 0; bit_pos < shift; bit_pos++) {
            mask = (mask << 1) + 1;
        }

        int32_t decimal_part = n & mask;

        /* Get 0.5 as fixed point */
        int32_t rounding_boundary = 1 << (shift - 1);

        /* Return either the integer part of n or the integer part + 1 */
        return (decimal_part < rounding_boundary) ? (n & ~mask) : ((n >> shift) + 1) << shift;
    }

    void chart_8() {
        static auto chart = StackedAreaChart(scr_act());

        chart.set_size(200, 150);
        chart.center();
        chart.set_type(LV_CHART_TYPE_LINE);
        chart.set_div_line_count(5, 7);
        chart.add_event_cb(draw_event_cb, LV_EVENT_DRAW_PART_BEGIN);

        /* Set range to 0 to 100 for percentages. Draw ticks */
        chart.set_range(LV_CHART_AXIS_PRIMARY_Y, 0, 100);
        chart.set_axis_tick(LV_CHART_AXIS_PRIMARY_Y, 3, 0, 5, 1, true, 30);

        /*Set point size to 0 so the lines are smooth */
        chart.set_style_size(0, LV_PART_INDICATOR);

        /*Add some data series*/
        chart.series_list[0] = chart.add_series(palette::main(Color::Red), LV_CHART_AXIS_PRIMARY_Y);
        chart.series_list[1] = chart.add_series(palette::main(Color::Blue), LV_CHART_AXIS_PRIMARY_Y);
        chart.series_list[2] = chart.add_series(palette::main(Color::Green), LV_CHART_AXIS_PRIMARY_Y);

        for(int point = 0; point < 10; point++) {
            /* Make some random data */
            uint32_t vals[3] = {lv_rand(10, 20), lv_rand(20, 30), lv_rand(20, 30)};

            int8_t fixed_point_shift = 5;
            uint32_t total = vals[0] + vals[1] + vals[2];
            uint32_t draw_heights[3];
            uint32_t int_sum = 0;
            uint32_t decimal_sum = 0;

            /* Fixed point cascade rounding ensures percentages add to 100 */
            for(int32_t series_index = 0; series_index < 3; series_index++) {
                decimal_sum += (((vals[series_index] * 100) << fixed_point_shift) / total);
                int_sum += (vals[series_index] * 100) / total;

                int32_t modifier = (round_fixed_point(decimal_sum, fixed_point_shift) >> fixed_point_shift) - int_sum;

                /*  The draw heights are equal to the percentage of the total each value is + the cumulative sum of the previous percentages.
                    The accumulation is how the values get "stacked" */
                draw_heights[series_index] = int_sum + modifier;

                /*  Draw to the series in the reverse order to which they were initialised.
                    Without this the higher values will draw on top of the lower ones.
                    This is because the Z-height of a series matches the order it was initialised */
                chart.set_next_y_value(chart.series_list[3 - series_index - 1], draw_heights[series_index]);
            }
        }

        chart.refresh();
    }
}