#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/theme.h" // for Theme
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;
    using namespace lvgl::widgets;

    static Style style_btn;

    static void new_theme_init_and_set() {
        style_btn.set_bg_color(palette::main(Color::Green));
        style_btn.set_border_color(palette::dark(Color::Green, 3));
        style_btn.set_border_width(3);
        /*Initialize the new theme from the current theme*/
        auto th_act = get_active_theme();
        static Theme th_new;
        *th_new = *th_act;
        /*Set the parent theme and the style apply callback for the new theme*/
        th_new.set_parent(th_act);

        auto new_theme_apply_cb = [](Theme & th, Object & obj) {
            if (obj.check_type(lv_btn_class))
                obj.add_style(style_btn, LV_STATE_DEFAULT);
        }
        th_new.set_apply_cb(new_theme_apply_cb);

        /*Assign the new theme to the current display*/
        set_active_theme(th_new);
    }

    void style_14() {
        auto root = scr_act();
        static auto btn1 = Button(root);
        btn1.align(LV_ALIGN_TOP_MID, 0, 20);

        static auto label1 = Label(btn1);
        label1.set_text("Original theme");

        new_theme_init_and_set();

        static auto btn2 = Button(root);
        btn2.align(LV_ALIGN_BOTTOM_MID, 0, -20);

        static auto label2 = Label(btn2);
        label2.set_text("New theme");
    }
}