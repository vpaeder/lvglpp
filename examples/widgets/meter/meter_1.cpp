#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/meter.h" // for Meter
#include "lvglpp/misc/anim.h" // for Animation

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    using MeterPtr = std::unique_ptr<Meter>;
    static MeterPtr meter;

    void meter_1() {
        auto root = scr_act();
        meter = std::make_unique<Meter>(root);
        meter->center();
        meter->set_size(200, 200);

        /*Add a scale first*/
        auto scale = meter->add_scale();
        meter->set_scale_ticks(scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
        meter->set_scale_major_ticks(scale, 8, 4, 15, lv_color_black(), 10);

        /*Add a blue arc to the start*/
        {
            auto indic = meter->add_arc(scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
            meter->set_indicator_start_value(indic, 0);
            meter->set_indicator_end_value(indic, 20);
        }
        /*Make the tick lines blue at the start of the scale*/
        {
            auto indic = meter->add_scale_lines(scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE),
                                               false, 0);
            meter->set_indicator_start_value(indic, 0);
            meter->set_indicator_end_value(indic, 20);
        }
        /*Add a red arc to the end*/
        {
            auto indic = meter->add_arc(scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
            meter->set_indicator_start_value(indic, 80);
            meter->set_indicator_end_value(indic, 100);
        }
        /*Make the tick lines red at the end of the scale*/
        {
            auto indic = meter->add_scale_lines(scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false, 0);
            meter->set_indicator_start_value(indic, 80);
            meter->set_indicator_end_value(indic, 100);
        }
        /*Add a needle line indicator*/
        auto indic = meter->add_needle_line(scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);

        /*Create an animation to set the value*/
        Animation anim;
        auto set_value = [](lv_meter_indicator_t *& indic, int32_t v) {
            meter->set_indicator_value(indic, v);
        };
        anim.set_exec_cb<lv_meter_indicator_t*>(set_value);
        anim.set_var(indic);
        anim.set_values(0, 100);
        anim.set_time(2000);
        anim.set_repeat_delay(100);
        anim.set_playback_time(500);
        anim.set_playback_delay(100);
        anim.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        anim.start();
    }
}