#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/menu/menu.h" // for Menu
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/image/image.h" // for Image
#include "lvglpp/widgets/slider/slider.h" // for Slider
#include "lvglpp/widgets/switch/switch.h" // for Switch
#include "lvglpp/widgets/msgbox/msgbox.h" // for MessageBox
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    enum {
        LV_MENU_ITEM_BUILDER_VARIANT_1,
        LV_MENU_ITEM_BUILDER_VARIANT_2
    };
    typedef uint8_t lv_menu_builder_variant_t;

    using MenuPtr = std::unique_ptr<Menu>;
    using MessageBoxPtr = std::unique_ptr<MessageBox>;
    using ObjectPtr = std::shared_ptr<Object>;
    static MenuPtr menu;
    static MessageBoxPtr mbox;
    static ObjectPtr root_page;


    static void back_event_handler(Event & e) {
        auto obj = e.get_target<Object>();
        if (menu->back_btn_is_root(obj)) {
            std::vector<std::string> btn_strs;
            mbox = std::make_unique<MessageBox>("Hello", "Root back btn click.", btn_strs, true);
            mbox->center();
        } else {
            mbox = nullptr;
        }
    }

    static void switch_handler(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<Object>();
        if (code == LV_EVENT_VALUE_CHANGED) {
            if (obj.has_state(LV_STATE_CHECKED)) {
                menu->clear_page();
                menu->set_sidebar_page(*root_page);
                menu->get_cur_sidebar_page().get_child<Object>(0).get_child<Object>(0).send_event(LV_EVENT_CLICKED);
            } else {
                menu->clear_sidebar_page();
                menu->clear_history(); /* Clear history because we will be showing the root page later */
                menu->set_page(*root_page);
            }
        }
    }

    static ObjectPtr create_text(
        Object & parent, const std::string & icon, const std::string & txt,
        lv_menu_builder_variant_t builder_variant) {
        
        auto obj = menu->cont_create(parent).get_shared<Object>();

        std::unique_ptr<Image> img;
        std::unique_ptr<Label> label;

        if (icon.size()>0) {
            img = std::make_unique<Image>(*obj);
            img->set_src(icon);
        }

        if (txt.size()>0) {
            label = std::make_unique<Label>(*obj);
            label->set_text(txt);
            label->set_long_mode(LV_LABEL_LONG_SCROLL_CIRCULAR);
            label->set_flex_grow(1);
        }

        if (builder_variant == LV_MENU_ITEM_BUILDER_VARIANT_2 && img!=nullptr && label!=nullptr) {
            img->add_flag(LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
            img->swap(*label);
        }

        if (img != nullptr) img->release_ptr();
        if (label != nullptr) label->release_ptr();

        return obj;
    }

    static ObjectPtr create_slider(
        Object & parent, const std::string & icon, const std::string & txt,
        int32_t min, int32_t max, int32_t val) {
        
        auto obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_2);

        auto slider = Slider(*obj);
        slider.set_flex_grow(1);
        slider.set_range(min, max);
        slider.set_value(val, LV_ANIM_OFF);

        if (icon.size()==0)
            slider.add_flag(LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
        
        slider.release_ptr();

        return obj;
    }

    static ObjectPtr create_switch(
        Object & parent, const std::string & icon, const std::string & txt, bool chk) {
        
        auto obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_1);

        auto sw = Switch(*obj);
        sw.add_state(chk ? LV_STATE_CHECKED : 0);
        sw.release_ptr();

        return obj;
    }

    void menu_5() {
        menu = std::make_unique<Menu>(scr_act());

        auto bg_color = menu->get_style_bg_color(0);
        if (lv_color_brightness(bg_color) > 127) {
            menu->set_style_bg_color(lv_color_darken(menu->get_style_bg_color(0), 10), 0);
        }
        else {
            menu->set_style_bg_color(lv_color_darken(menu->get_style_bg_color(0), 50), 0);
        }
        menu->set_mode_root_back_btn(LV_MENU_ROOT_BACK_BTN_ENABLED);
        menu->add_event_cb(back_event_handler, LV_EVENT_CLICKED);

        menu->set_size(lv_disp_get_hor_res(nullptr), lv_disp_get_ver_res(nullptr));
        menu->center();

        /*Create sub pages*/
        auto sub_mechanics_page = menu->page_create();
        sub_mechanics_page.set_style_pad_hor(menu->get_main_header().get_style_pad_left(0), 0);
        menu->separator_create(sub_mechanics_page);
        
        auto section1 = menu->section_create(sub_mechanics_page);
        create_slider(section1, LV_SYMBOL_SETTINGS, "Velocity", 0, 150, 120);
        create_slider(section1, LV_SYMBOL_SETTINGS, "Acceleration", 0, 150, 50);
        create_slider(section1, LV_SYMBOL_SETTINGS, "Weight limit", 0, 150, 80);

        auto sub_sound_page = menu->page_create();
        sub_sound_page.set_style_pad_hor(menu->get_main_header().get_style_pad_left(0), 0);
        menu->separator_create(sub_sound_page);
        auto section2 = menu->section_create(sub_sound_page);
        create_switch(section2, LV_SYMBOL_AUDIO, "Sound", false);

        auto sub_display_page = menu->page_create();
        sub_display_page.set_style_pad_hor(menu->get_main_header().get_style_pad_left(0), 0);
        menu->separator_create(sub_display_page);
        auto section3 = menu->section_create(sub_display_page);
        create_slider(section3, LV_SYMBOL_SETTINGS, "Brightness", 0, 150, 100);

        auto sub_software_info_page = menu->page_create();
        sub_software_info_page.set_style_pad_hor(menu->get_main_header().get_style_pad_left(0), 0);
        auto section4 = menu->section_create(sub_software_info_page);
        create_text(section4, "", "Version 1.0", LV_MENU_ITEM_BUILDER_VARIANT_1);

        auto sub_legal_info_page = menu->page_create();
        sub_legal_info_page.set_style_pad_hor(menu->get_main_header().get_style_pad_left(0), 0);
        auto section5 = menu->section_create(sub_legal_info_page);
        for (uint32_t i = 0; i < 15; i++)
            create_text(section5, "",
                        "This is a long long long long long long long long long text, if it is long enough it may scroll.",
                        LV_MENU_ITEM_BUILDER_VARIANT_1);

        auto sub_about_page = menu->page_create();
        sub_about_page.set_style_pad_hor(menu->get_main_header().get_style_pad_left(0), 0);
        menu->separator_create(sub_about_page);
        auto section6 = menu->section_create(sub_about_page);
        auto cont1 = create_text(section6, "", "Software information", LV_MENU_ITEM_BUILDER_VARIANT_1);
        menu->set_load_page_event(*cont1, sub_software_info_page);
        auto cont2 = create_text(section6, "", "Legal information", LV_MENU_ITEM_BUILDER_VARIANT_1);
        menu->set_load_page_event(*cont2, sub_legal_info_page);

        auto sub_menu_mode_page = menu->page_create();
        sub_menu_mode_page.set_style_pad_hor(menu->get_main_header().get_style_pad_left(0), 0);
        menu->separator_create(sub_menu_mode_page);
        auto section7 = menu->section_create(sub_menu_mode_page);
        auto cont3 = create_switch(section7, LV_SYMBOL_AUDIO, "Sidebar enable", true);
        cont3->get_child<Object>(2).add_event_cb(switch_handler, LV_EVENT_VALUE_CHANGED);

        /*Create a root page*/
        root_page = menu->page_create("Settings").get_shared<Object>();
        root_page->set_style_pad_hor(menu->get_main_header().get_style_pad_left(0), 0);
        auto section8 = menu->section_create(*root_page);
        auto cont4 = create_text(section8, LV_SYMBOL_SETTINGS, "Mechanics", LV_MENU_ITEM_BUILDER_VARIANT_1);
        menu->set_load_page_event(*cont4, sub_mechanics_page);
        auto cont5 = create_text(section8, LV_SYMBOL_AUDIO, "Sound", LV_MENU_ITEM_BUILDER_VARIANT_1);
        menu->set_load_page_event(*cont5, sub_sound_page);
        auto cont6 = create_text(section8, LV_SYMBOL_SETTINGS, "Display", LV_MENU_ITEM_BUILDER_VARIANT_1);
        menu->set_load_page_event(*cont6, sub_display_page);

        create_text(*root_page, "", "Others", LV_MENU_ITEM_BUILDER_VARIANT_1);
        auto section9 = menu->section_create(*root_page);
        auto cont7 = create_text(section9, "", "About", LV_MENU_ITEM_BUILDER_VARIANT_1);
        menu->set_load_page_event(*cont7, sub_about_page);
        auto cont8 = create_text(section9, LV_SYMBOL_SETTINGS, "Menu mode", LV_MENU_ITEM_BUILDER_VARIANT_1);
        menu->set_load_page_event(*cont8, sub_menu_mode_page);

        menu->set_sidebar_page(*root_page);

        menu->get_cur_sidebar_page().get_child<Object>(0).get_child<Object>(0).send_event(LV_EVENT_CLICKED);
    }
}