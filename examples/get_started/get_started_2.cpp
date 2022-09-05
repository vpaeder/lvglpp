#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/misc/color.h" // for ColorFilter
#include "lvglpp/misc/style.h" // for Style

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    static std::unique_ptr<Style> style_btn, style_btn_pressed, style_btn_red;

    class DarkeningFilter : public ColorFilter {
        lv_color_t callback(lv_color_t color, lv_opa_t opa) override {
            return color::darken(color, opa);
        }
    };

    static void style_init(void) {
        style_btn = std::make_unique<Style>();
        style_btn_pressed = std::make_unique<Style>();
        style_btn_red = std::make_unique<Style>();
        /*Create a simple button style*/
        style_btn->set_radius(10);
        style_btn->set_bg_opa(LV_OPA_COVER);
        style_btn->set_bg_color(palette::light(Color::Grey, 3));
        style_btn->set_bg_grad_color(palette::main(Color::Grey));
        style_btn->set_bg_grad_dir(LV_GRAD_DIR_VER);

        style_btn->set_border_color(palette::black());
        style_btn->set_border_opa(LV_OPA_20);
        style_btn->set_border_width(2);

        style_btn->set_text_color(palette::black());

        /*Create a style for the pressed state.
        *Use a color filter to simply modify all colors in this state*/
        static DarkeningFilter color_filter;
        style_btn_pressed->set_color_filter_dsc(color_filter);
        style_btn_pressed->set_color_filter_opa(LV_OPA_20);

        /*Create a red style. Change only some colors.*/
        style_btn_red->set_bg_color(palette::main(Color::Red));
        style_btn_red->set_bg_grad_color(palette::light(Color::Red, 3));
    }

    void get_started_2() {
        /*Initialize the style*/
        style_init();
        /*Create a button and use the new styles*/
        auto root = scr_act();
        static auto btn = Button(root);
        /* Remove the styles coming from the theme
        * Note that size and position are also stored as style properties
        * so lv_obj_remove_style_all will remove the set size and position too */
        btn.remove_style_all();
        btn.set_pos(10, 10);
        btn.set_size(120, 50);
        btn.add_style(*style_btn, LV_STATE_DEFAULT);
        btn.add_style(*style_btn_pressed, LV_STATE_PRESSED);

        /*Add a label to the button*/
        static auto label = Label(btn);
        label.set_text("Button");
        label.center();

        /*Create another button and use the red style too*/
        static auto btn2 = Button(root);
        btn2.remove_style_all();                      /*Remove the styles coming from the theme*/
        btn2.set_pos(10, 80);
        btn2.set_size(120, 50);
        btn2.add_style(*style_btn, LV_STATE_DEFAULT);
        btn2.add_style(*style_btn_red, LV_STATE_DEFAULT);
        btn2.add_style(*style_btn_pressed, LV_STATE_PRESSED);
        btn2.set_style_radius(LV_RADIUS_CIRCLE, 0); /*Add a local style too*/

        static auto label2 = Label(btn2);
        label2.set_text("Button 2");
        label2.center();
    }
}