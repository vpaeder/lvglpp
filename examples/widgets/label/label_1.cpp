#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void label_1() {
        auto root = scr_act();
        
        static auto label1 = Label(root);
        label1.set_long_mode(LV_LABEL_LONG_WRAP);     /*Break the long lines*/
        label1.set_recolor(true);                      /*Enable re-coloring by commands in the text*/
        label1.set_text("#0000ff Re-color# #ff00ff words# #ff0000 of a# label, align the lines to the center "
                        "and wrap long text automatically.");
        label1.set_width(150);  /*Set smaller width to make the lines wrap*/
        label1.set_style_text_align(LV_TEXT_ALIGN_CENTER, 0);
        label1.align(LV_ALIGN_CENTER, 0, -40);

        static auto label2 = Label(root);
        label2.set_long_mode(LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
        label2.set_width(150);
        label2.set_text("It is a circularly scrolling text. ");
        label2.align(LV_ALIGN_CENTER, 0, 40);
    }
}