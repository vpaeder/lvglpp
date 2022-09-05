#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/slider/slider.h" // for Slider
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void slider_2() {
        /*Create a transition*/
        auto props = std::vector<lv_style_prop_t>{LV_STYLE_BG_COLOR, LV_STYLE_PROP_INV};
        static auto transition_dsc = LinearStyleTransition(props, 300, 0);

        static Style style_main, style_indicator, style_knob, style_pressed_color;
        style_main.set_bg_opa(LV_OPA_COVER);
        style_main.set_bg_color(lv_color_hex3(0xbbb));
        style_main.set_radius(LV_RADIUS_CIRCLE);
        style_main.set_pad_ver(-2); /*Makes the indicator larger*/

        style_indicator.set_bg_opa(LV_OPA_COVER);
        style_indicator.set_bg_color(palette::main(Color::Cyan));
        style_indicator.set_radius(LV_RADIUS_CIRCLE);
        style_indicator.set_transition(transition_dsc);

        style_knob.set_bg_opa(LV_OPA_COVER);
        style_knob.set_bg_color(palette::main(Color::Cyan));
        style_knob.set_border_color(palette::dark(Color::Cyan, 3));
        style_knob.set_border_width(2);
        style_knob.set_radius(LV_RADIUS_CIRCLE);
        style_knob.set_pad_all(6); /*Makes the knob larger*/
        style_knob.set_transition(transition_dsc);

        style_pressed_color.set_bg_color(palette::dark(Color::Cyan, 2));

        /*Create a slider and add the style*/
        static auto slider = Slider(scr_act());
        slider.remove_style_all();        /*Remove the styles coming from the theme*/

        slider.add_style(style_main, LV_PART_MAIN);
        slider.add_style(style_indicator, LV_PART_INDICATOR);
        slider.add_style(style_pressed_color, LV_PART_INDICATOR | LV_STATE_PRESSED);
        slider.add_style(style_knob, LV_PART_KNOB);
        slider.add_style(style_pressed_color, LV_PART_KNOB | LV_STATE_PRESSED);

        slider.center();
    }
}