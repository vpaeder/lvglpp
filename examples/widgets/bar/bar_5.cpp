#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/bar/bar.h" // for Bar
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/misc/style.h" // for Style

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void bar_5() {
        auto root = scr_act();

        static auto bar_ltr = Bar(root);
        bar_ltr.set_size(200, 20);
        bar_ltr.set_value(70, LV_ANIM_OFF);
        bar_ltr.align(LV_ALIGN_CENTER, 0, -30);

        static auto label_ltr = Label(root);
        label_ltr.set_text("Left to Right base direction");
        label_ltr.align_to(bar_ltr, LV_ALIGN_OUT_TOP_MID, 0, -5);

        static auto bar_rtl = Bar(root);
        bar_rtl.set_style_base_dir(LV_BASE_DIR_RTL, 0);
        bar_rtl.set_size(200, 20);
        bar_rtl.set_value(70, LV_ANIM_OFF);
        bar_rtl.align(LV_ALIGN_CENTER, 0, 30);

        static auto label_rtl = Label(root);
        label_rtl.set_text("Right to Left base direction");
        label_rtl.align_to(bar_rtl, LV_ALIGN_OUT_TOP_MID, 0, -5);
    }

}