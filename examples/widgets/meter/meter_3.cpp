#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/meter/meter.h" // for Meter
#include "lvglpp/misc/anim.h" // for Animation
#include "lvglpp/misc/color.h" // for colors
#include "lvglpp/draw/image.h" // for ImageDescriptor

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    using MeterPtr = std::unique_ptr<Meter>;
    static MeterPtr meter;

    void meter_3() {
        meter = std::make_unique<Meter>(scr_act());
        meter->center();
        meter->set_size(200, 200);
        /*Create a scale for the minutes*/
        /*61 ticks in a 360 degrees range (the last and the first line overlaps)*/
        auto scale_min = meter->add_scale();
        meter->set_scale_ticks(scale_min, 61, 1, 10, palette::main(Color::Grey));
        meter->set_scale_range(scale_min, 0, 60, 360, 270);

        /*Create another scale for the hours. It's only visual and contains only major ticks*/
        auto scale_hour = meter->add_scale();
        meter->set_scale_ticks(scale_hour, 12, 0, 0, palette::main(Color::Grey));               /*12 ticks*/
        meter->set_scale_major_ticks(scale_hour, 1, 2, 20, palette::black(), 10);    /*Every tick is major*/
        meter->set_scale_range(scale_hour, 1, 12, 330, 300);       /*[1..12] values in an almost full circle*/

        static ImageDescriptor img_hand;
        img_hand.set_src(img_hand_map, 100, 9, LV_IMG_CF_TRUE_COLOR_ALPHA);

        /*Add a the hands from images*/
        auto indic_min = meter->add_needle_img(scale_min, img_hand, 5, 5);
        auto indic_hour = meter->add_needle_img(scale_min, img_hand, 5, 5);

        /*Create an animation to set the value*/
        static Animation a1, a2;
        auto set_value = [](lv_meter_indicator_t *& indic, int32_t v) {
            meter->set_indicator_end_value(indic, v);
        };
        a1.set_exec_cb<decltype(indic_min)>(set_value);
        a1.set_values(0, 60);
        a1.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a1.set_time(2000);     /*2 sec for 1 turn of the minute hand (1 hour)*/
        a1.set_var(indic_min);
        a1.start();
        a2.set_exec_cb<decltype(indic_hour)>(set_value);
        a2.set_values(0, 60);
        a2.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a2.set_time(24000);    /*24 sec for 1 turn of the hour hand*/
        a2.set_var(indic_hour);
        a2.start();
    }
}