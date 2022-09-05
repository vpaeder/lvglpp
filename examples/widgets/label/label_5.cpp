#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/anim.h" // for Animation

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void label_5() {
        static Animation animation_template;
        static Style label_style;

        animation_template.set_delay(1000);           /*Wait 1 second to start the first scroll*/
        animation_template.set_repeat_delay(3000);    /*Repeat the scroll 3 seconds after the label scrolls back to the initial position*/

        /*Initialize the label style with the animation template*/
        label_style.set_anim(animation_template);

        static auto label1 = Label(scr_act());
        label1.set_long_mode(LV_LABEL_LONG_SCROLL_CIRCULAR);      /*Circular scroll*/
        label1.set_width(150);
        label1.set_text("It is a circularly scrolling text. ");
        label1.align(LV_ALIGN_CENTER, 0, 40);
        label1.add_style(label_style, LV_STATE_DEFAULT);           /*Add the style to the label*/
    }
}