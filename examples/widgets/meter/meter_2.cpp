#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/meter/meter.h" // for Meter
#include "lvglpp/misc/anim.h" // for Animation
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    using MeterPtr = std::unique_ptr<Meter>;
    static MeterPtr meter;

    void meter_2() {
        meter = std::make_unique<Meter>(scr_act());
        meter->center();
        meter->set_size(200, 200);

        /*Remove the circle from the middle*/
        meter->remove_style(LV_PART_INDICATOR);

        /*Add a scale first*/
        auto scale = meter->add_scale();
        meter->set_scale_ticks(scale, 11, 2, 10, palette::main(Color::Grey));
        meter->set_scale_major_ticks(scale, 1, 2, 30, lv_color_hex3(0xeee), 15);
        meter->set_scale_range(scale, 0, 100, 270, 90);

        /*Add a three arc indicator*/
        auto indic1 = meter->add_arc(scale, 10, palette::main(Color::Red), 0);
        auto indic2 = meter->add_arc(scale, 10, palette::main(Color::Green), -10);
        auto indic3 = meter->add_arc(scale, 10, palette::main(Color::Blue), -20);

        /*Create an animation to set the value*/
        static Animation a1, a2, a3, a4;
        auto set_value = [](lv_meter_indicator_t *& indic, int32_t v) {
            meter->set_indicator_end_value(indic, v);
        };
        a1.set_exec_cb<lv_meter_indicator_t*>(set_value);
        a1.set_values(0, 100);
        a1.set_repeat_delay(100);
        a1.set_playback_delay(100);
        a1.set_repeat_count(LV_ANIM_REPEAT_INFINITE);

        a2.set_exec_cb<lv_meter_indicator_t*>(set_value);
        a2.set_values(0, 100);
        a2.set_repeat_delay(100);
        a2.set_playback_delay(100);
        a2.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a2.set_time(2000);
        a2.set_playback_time(500);
        a2.set_var(indic1);
        a2.start();

        a3.set_exec_cb<lv_meter_indicator_t*>(set_value);
        a3.set_values(0, 100);
        a3.set_repeat_delay(100);
        a3.set_playback_delay(100);
        a3.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a3.set_time(1000);
        a3.set_playback_time(1000);
        a3.set_var(indic2);
        a3.start();

        a4.set_exec_cb<lv_meter_indicator_t*>(set_value);
        a4.set_values(0, 100);
        a4.set_repeat_delay(100);
        a4.set_playback_delay(100);
        a4.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a4.set_time(1000);
        a4.set_playback_time(2000);
        a4.set_var(indic3);
        a4.start();
    }
}