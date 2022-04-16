#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/bar.h" // for Bar
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/draw/image.h" // for ImageDescriptor

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void bar_4() {
        auto img = ImageDescriptor(&img_skew_strip);

        Style style_indic;
        style_indic.set_bg_img_src(img);
        style_indic.set_bg_img_tiled(true);
        style_indic.set_bg_img_opa(LV_OPA_30);

        auto root = scr_act();
        auto bar = Bar(root);
        bar.add_style(style_indic, LV_PART_INDICATOR);

        bar.set_size(260, 20);
        bar.center();
        bar.set_mode(LV_BAR_MODE_RANGE);
        bar.set_value(90, LV_ANIM_OFF);
        bar.set_start_value(20, LV_ANIM_OFF);
    }

}