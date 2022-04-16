#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/button.h" // for Button
#include "lvglpp/widgets/label.h" // for Label
#include "lvglpp/misc/style.h" // for Style, LinearStyleTransition
#include <vector>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;
    using namespace lvgl::widgets;

    void button_3() {
        auto root = scr_act();

        /*Properties to transition*/
        static std::vector<lv_style_prop_t> props = {
            LV_STYLE_TRANSFORM_WIDTH, LV_STYLE_TRANSFORM_HEIGHT, LV_STYLE_TEXT_LETTER_SPACE, LV_STYLE_PROP_INV
        };

        /*Transition descriptor when going back to the default state.
        *Add some delay to be sure the press transition is visible even if the press was very short*/
        OvershootStyleTransition transition_def;
        transition_def.set_props(props);
        transition_def.set_time(250);
        transition_def.set_delay(100);

        /*Transition descriptor when going to pressed state.
        *No delay, go to presses state immediately*/
        EaseInOutStyleTransition transition_pr;
        transition_pr.set_props(props);
        transition_pr.set_time(250);
        transition_pr.set_delay(0);

        /*Add only the new transition to he default state*/
        Style style_def;
        style_def.set_transition(transition_def);

        /*Add the transition and some transformation to the presses state.*/
        Style style_pr;
        style_pr.set_transform_width(10);
        style_pr.set_transform_height(-10);
        style_pr.set_text_letter_space(10);
        style_pr.set_transition(transition_pr);

        auto button = Button(root);
        button.align(LV_ALIGN_CENTER, 0, -80);
        button.add_style(style_pr, LV_STATE_PRESSED);
        button.add_style(style_def, LV_STATE_DEFAULT);

        auto label = Label(button);
        label.set_text("Gum");
    }
}
