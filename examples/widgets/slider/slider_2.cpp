#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/slider.h" // for Slider
#include "lvglpp/misc/style.h" // for Style

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void slider_2() {
        auto root = scr_act();
        
        /*Create a transition*/
        auto props = std::vector<lv_style_prop_t>{LV_STYLE_BG_COLOR, LV_STYLE_PROP_INV};
        auto transition_dsc = LinearStyleTransition();
        transition_dsc.set_props(props);
        transition_dsc.set_time(300);
        transition_dsc.set_delay(0);

        Style style_main;
        Style style_indicator;
        Style style_knob;
        Style style_pressed_color;
        style_main.set_bg_opa(LV_OPA_COVER);
        style_main.set_bg_color(lv_color_hex3(0xbbb));
        style_main.set_radius(LV_RADIUS_CIRCLE);
        style_main.set_pad_ver(-2); /*Makes the indicator larger*/

        style_indicator.set_bg_opa(LV_OPA_COVER);
        style_indicator.set_bg_color(lv_palette_main(LV_PALETTE_CYAN));
        style_indicator.set_radius(LV_RADIUS_CIRCLE);
        style_indicator.set_transition(transition_dsc);

        style_knob.set_bg_opa(LV_OPA_COVER);
        style_knob.set_bg_color(lv_palette_main(LV_PALETTE_CYAN));
        style_knob.set_border_color(lv_palette_darken(LV_PALETTE_CYAN, 3));
        style_knob.set_border_width(2);
        style_knob.set_radius(LV_RADIUS_CIRCLE);
        style_knob.set_pad_all(6); /*Makes the knob larger*/
        style_knob.set_transition(transition_dsc);

        style_pressed_color.set_bg_color(lv_palette_darken(LV_PALETTE_CYAN, 2));

        /*Create a slider and add the style*/
        auto slider = Slider(root);
        slider.remove_style_all();        /*Remove the styles coming from the theme*/

        slider.add_style(style_main, LV_PART_MAIN);
        slider.add_style(style_indicator, LV_PART_INDICATOR);
        slider.add_style(style_pressed_color, LV_PART_INDICATOR | LV_STATE_PRESSED);
        slider.add_style(style_knob, LV_PART_KNOB);
        slider.add_style(style_pressed_color, LV_PART_KNOB | LV_STATE_PRESSED);

        slider.center();
    }
}