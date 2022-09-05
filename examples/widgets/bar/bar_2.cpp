#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/bar/bar.h" // for Bar
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void bar_2() {
        static Style style_bg, style_indic;

        style_bg.set_border_color(palette::main(Color::Blue));
        style_bg.set_border_width(2);
        style_bg.set_pad_all(6);
        style_bg.set_radius(6);
        style_bg.set_anim_time(1000);

        style_indic.set_bg_opa(LV_OPA_COVER);
        style_indic.set_bg_color(palette::main(Color::Blue));
        style_indic.set_radius(3);

        static auto bar = Bar(scr_act());
        bar.remove_style_all();
        bar.add_style(style_bg, LV_PART_MAIN);
        bar.add_style(style_indic, LV_PART_INDICATOR);
        bar.set_size(200, 20);
        bar.center();
        bar.set_value(100, LV_ANIM_ON);
    }

}