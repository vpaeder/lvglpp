#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/dropdown.h" // for Dropdown

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void dropdown_2() {
        auto root = scr_act();

        static const std::string opts = "Apple\n"
                                        "Banana\n"
                                        "Orange\n"
                                        "Melon";

        auto dd1 = Dropdown(root);
        dd1.set_options_static(opts);
        dd1.align(LV_ALIGN_TOP_MID, 0, 10);

        auto dd2 = Dropdown(root);
        dd2.set_options_static(opts);
        dd2.set_dir(LV_DIR_TOP);
        dd2.set_symbol(LV_SYMBOL_UP);
        dd2.align(LV_ALIGN_BOTTOM_MID, 0, -10);

        auto dd3 = Dropdown(root);
        dd3.set_options_static(opts);
        dd3.set_dir(LV_DIR_RIGHT);
        dd3.set_symbol(LV_SYMBOL_RIGHT);
        dd3.align(LV_ALIGN_LEFT_MID, 10, 0);

        auto dd4 = Dropdown(root);
        dd4.set_options_static(opts);
        dd4.set_dir(LV_DIR_LEFT);
        dd4.set_symbol(LV_SYMBOL_LEFT);
        dd4.align(LV_ALIGN_RIGHT_MID, -10, 0);

    }
}