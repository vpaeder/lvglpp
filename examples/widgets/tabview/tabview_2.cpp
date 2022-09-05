#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/tabview/tabview.h" // for Tabview
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/anim.h" // for Animation
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    std::unique_ptr<Tabview> tabview;

    static void scroll_begin_event(Event & e) {
        /*Disable the scroll animations. Triggered when a tab button is clicked */
        if(e.get_code() == LV_EVENT_SCROLL_BEGIN) {
            auto a = e.get_param<Animation>();
            if(a != nullptr)  (*a)->time = 0;
        }
    }

    void tabview_2() {
        tabview = std::make_unique<Tabview>(scr_act(), LV_DIR_LEFT, 80);

        tabview->get_content().add_event_cb(scroll_begin_event, LV_EVENT_SCROLL_BEGIN);

        tabview->set_style_bg_color(palette::light(Color::Red, 2), 0);

        auto tab_btns = tabview->get_tab_btns();
        tab_btns.set_style_bg_color(palette::dark(Color::Grey, 3), 0);
        tab_btns.set_style_text_color(palette::light(Color::Grey, 5), 0);
        tab_btns.set_style_border_side(LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);


        /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
        auto tab1 = tabview->add_tab("Tab 1");
        auto tab2 = tabview->add_tab("Tab 2");
        auto tab3 = tabview->add_tab("Tab 3");
        auto tab4 = tabview->add_tab("Tab 4");
        auto tab5 = tabview->add_tab("Tab 5");

        tab2.set_style_bg_color(palette::light(Color::Amber, 3), 0);
        tab2.set_style_bg_opa(LV_OPA_COVER, 0);

        /*Add content to the tabs*/
        static auto label1 = Label(tab1);
        label1.set_text("First tab");

        static auto label2 = Label(tab2);
        label2.set_text("Second tab");

        static auto label3 = Label(tab3);
        label3.set_text("Third tab");

        static auto label4 = Label(tab4);
        label4.set_text("Forth tab");

        static auto label5 = Label(tab5);
        label5.set_text("Fifth tab");

        tabview->get_content().clear_flag(LV_OBJ_FLAG_SCROLLABLE);
    }
}