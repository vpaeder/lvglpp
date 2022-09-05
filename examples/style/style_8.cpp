#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;
    using namespace lvgl::widgets;

    void style_8() {
        static Style style;
        style.set_radius(5);
        style.set_bg_opa(LV_OPA_COVER);
        style.set_bg_color(palette::light(Color::Grey, 2));
        style.set_border_width(2);
        style.set_border_color(palette::main(Color::Blue));
        style.set_pad_all(10);
        style.set_text_color(palette::main(Color::Blue));
        style.set_text_letter_space(5);
        style.set_text_line_space(20);
        style.set_text_decor(LV_TEXT_DECOR_UNDERLINE);        
        /*Create an object with the new style*/
        static auto obj = Label(scr_act());
        obj.add_style(style, LV_STATE_DEFAULT);
        obj.set_text("Text of\n"
                     "a label");
        obj.center();
    }
}