#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/misc/style.h" // for Style, LinearStyleTransition
#include "lvglpp/misc/color.h" // for colors
#include <vector>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;
    using namespace lvgl::widgets;

    void button_2() {
        static Style style;

        style.set_radius(3);

        style.set_bg_opa(LV_OPA_100);
        style.set_bg_color(palette::main(Color::Blue));
        style.set_bg_grad_color(palette::dark(Color::Blue, 2));
        style.set_bg_grad_dir(LV_GRAD_DIR_VER);

        style.set_border_opa(LV_OPA_40);
        style.set_border_width(2);
        style.set_border_color(palette::main(Color::Grey));

        style.set_shadow_width(8);
        style.set_shadow_color(palette::main(Color::Grey));
        style.set_shadow_ofs_y(8);

        style.set_outline_opa(LV_OPA_COVER);
        style.set_outline_color(palette::main(Color::Blue));

        style.set_text_color(palette::white());
        style.set_pad_all(10);

        /*Init the pressed style*/
        static Style style_pr;

        /*Add a large outline when pressed*/
        style_pr.set_outline_width(30);
        style_pr.set_outline_opa(LV_OPA_TRANSP);

        style_pr.set_translate_y(5);
        style_pr.set_shadow_ofs_y(3);
        style_pr.set_bg_color(palette::dark(Color::Blue, 2));
        style_pr.set_bg_grad_color(palette::dark(Color::Blue, 4));

        /*Add a transition to the outline*/
        std::vector<lv_style_prop_t> props = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, LV_STYLE_PROP_INV};
        static LinearStyleTransition trans(props, 300, 0);
        style_pr.set_transition(trans);
        
        static auto button = Button(scr_act());
        button.remove_style_all();
        
        button.add_style(style, LV_STATE_DEFAULT);
        button.add_style(style_pr, LV_STATE_PRESSED);
        button.set_size(LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        button.center();

        static auto label = Label(button);
        label.set_text("Button");
        label.center();
    }
}
