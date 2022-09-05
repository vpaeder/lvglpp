#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/misc/style.h" // for Style, LinearStyleTransition
#include <vector>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;
    using namespace lvgl::widgets;

    void button_3() {
        /*Properties to transition*/
        std::vector<lv_style_prop_t> props = {
            LV_STYLE_TRANSFORM_WIDTH, LV_STYLE_TRANSFORM_HEIGHT, LV_STYLE_TEXT_LETTER_SPACE, LV_STYLE_PROP_INV
        };

        /*Transition descriptor when going back to the default state.
        *Add some delay to be sure the press transition is visible even if the press was very short*/
        static OvershootStyleTransition transition_def(props, 250, 100);

        /*Transition descriptor when going to pressed state.
        *No delay, go to presses state immediately*/
        static EaseInOutStyleTransition transition_pr(props, 250, 0);

        /*Add only the new transition to he default state*/
        static Style style_def;
        style_def.set_transition(transition_def);

        /*Add the transition and some transformation to the presses state.*/
        static Style style_pr;
        style_pr.set_transform_width(10);
        style_pr.set_transform_height(-10);
        style_pr.set_text_letter_space(10);
        style_pr.set_transition(transition_pr);

        static auto button = Button(scr_act());
        button.align(LV_ALIGN_CENTER, 0, -80);
        button.add_style(style_pr, LV_STATE_PRESSED);
        button.add_style(style_def, LV_STATE_DEFAULT);

        static auto label = Label(button);
        label.set_text("Gum");
    }
}
