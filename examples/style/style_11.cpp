#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;
    using namespace lvgl::widgets;

    void style_11() {
        /*A base style*/
        static Style style_base;
        style_base.set_bg_color(palette::main(Color::LightBlue));
        style_base.set_border_color(palette::dark(Color::LightBlue, 3));
        style_base.set_border_width(2);
        style_base.set_radius(10);
        style_base.set_shadow_width(10);
        style_base.set_shadow_ofs_y(5);
        style_base.set_shadow_opa(LV_OPA_50);
        style_base.set_text_color(palette::white());
        style_base.set_width(100);
        style_base.set_height(LV_SIZE_CONTENT);

        /*Set only the properties that should be different*/
        static Style style_warning;
        style_warning.set_bg_color(palette::main(Color::Yellow));
        style_warning.set_border_color(palette::dark(Color::Yellow, 3));
        style_warning.set_text_color(palette::dark(Color::Yellow, 4));

        /*Create an object with the base style only*/
        auto root = scr_act();
        static auto obj_base = Container(root);
        obj_base.add_style(style_base, LV_STATE_DEFAULT);
        obj_base.align(LV_ALIGN_LEFT_MID, 20, 0);

        static auto label_base = Label(obj_base);
        label_base.set_text("Base");
        label_base.center();

        /*Create another object with the base style and earnings style too*/
        static auto obj_warning = Container(root);
        obj_warning.add_style(style_base, LV_STATE_DEFAULT);
        obj_warning.add_style(style_warning, LV_STATE_DEFAULT);
        obj_warning.align(LV_ALIGN_RIGHT_MID, -20, 0);

        static auto label_warning = Label(obj_warning);
        label_warning.set_text("Base");
        label_warning.center();

    }
}