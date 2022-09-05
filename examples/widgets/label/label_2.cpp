#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void label_2() {
        auto root = scr_act();
        
        /*Create a style for the shadow*/
        static Style style_shadow;
        style_shadow.set_text_opa(LV_OPA_30);
        style_shadow.set_text_color(palette::black());

        /*Create a label for the shadow first (it's in the background)*/
        static auto shadow_label = Label(root);
        shadow_label.add_style(style_shadow, LV_PART_MAIN);

        /*Create the main label*/
        static auto main_label = Label(root);
        main_label.set_text("A simple method to create\n"
                            "shadows on a text.\n"
                            "It even works with\n\n"
                            "newlines     and spaces.");

        /*Set the same text for the shadow label*/
        shadow_label.set_text(main_label.get_text());

        /*Position the main label*/
        main_label.align(LV_ALIGN_CENTER, 0, 0);

        /*Shift the second label down and to the right by 2 pixel*/
        shadow_label.align_to(main_label, LV_ALIGN_TOP_LEFT, 2, 2);
    }
}