#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/tabview/tabview.h" // for Tabview
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void tabview_1() {
        static auto tabview = Tabview(scr_act(), LV_DIR_TOP, 50);

        /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
        auto tab1 = tabview.add_tab("Tab 1");
        auto tab2 = tabview.add_tab("Tab 2");
        auto tab3 = tabview.add_tab("Tab 3");

        /*Add content to the tabs*/
        static auto label1 = Label(tab1);
        label1.set_text("This the first tab\n\n"
                        "If the content\n"
                        "of a tab\n"
                        "becomes too\n"
                        "longer\n"
                        "than the\n"
                        "container\n"
                        "then it\n"
                        "automatically\n"
                        "becomes\n"
                        "scrollable.\n"
                        "\n"
                        "\n"
                        "\n"
                        "Can you see it?");

        static auto label2 = Label(tab2);
        label2.set_text("Second tab");

        static auto label3 = Label(tab3);
        label3.set_text("Third tab");

        label3.scroll_to_view_recursive(LV_ANIM_ON);
    }
}