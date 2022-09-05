#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void label_3() {
        auto root = scr_act();
        
        static auto ltr_label = Label(root);
        ltr_label.set_text("In modern terminology, a microcontroller is similar to a system on a chip (SoC).");
        ltr_label.set_style_text_font(&lv_font_montserrat_16, LV_PART_MAIN);
        ltr_label.set_width(310);
        ltr_label.align(LV_ALIGN_TOP_LEFT, 5, 5);

        static auto rtl_label = Label(root);
        rtl_label.set_text("מעבד, או בשמו המלא יחידת עיבוד מרכזית (באנגלית: CPU - Central Processing Unit).");
        rtl_label.set_style_base_dir(LV_BASE_DIR_RTL, 0);
        rtl_label.set_style_text_font(&lv_font_dejavu_16_persian_hebrew, LV_PART_MAIN);
        rtl_label.set_width(310);
        rtl_label.align(LV_ALIGN_LEFT_MID, 5, 0);

        static auto cz_label = Label(root);
        cz_label.set_text("嵌入式系统（Embedded System），\n是一种嵌入机械或电气系统内部、具有专一功能和实时计算性能的计算机系统。");
        cz_label.set_style_text_font(&lv_font_simsun_16_cjk, LV_PART_MAIN);
        cz_label.set_width(310);
        cz_label.align(LV_ALIGN_BOTTOM_LEFT, 5, -5);

    }
}