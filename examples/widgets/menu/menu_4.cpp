#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/menu/menu.h" // for Menu
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/button/button.h" // for Button

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    static uint32_t btn_cnt = 1;
    static std::shared_ptr<Object> main_page;
    static std::unique_ptr<Menu> menu;

    static void float_btn_event_cb(Event & e) {
        btn_cnt++;
        auto sub_page = menu->page_create();
        {
            auto cont = menu->cont_create(sub_page);
            auto label = Label(cont);
            label.set_text_fmt("Hello, I am hiding inside %i", btn_cnt);
            label.release_ptr();
        }
        {
            auto cont = menu->cont_create(*main_page);
            auto label = Label(cont);
            label.set_text_fmt("Item %i", btn_cnt);
            label.release_ptr();
            menu->set_load_page_event(cont, sub_page);
            cont.scroll_to_view_recursive(LV_ANIM_ON);
        }
    }

    void menu_4() {
        auto root = scr_act();
        
        menu = std::make_unique<Menu>(root);
        menu->set_size(lv_disp_get_hor_res(nullptr), lv_disp_get_ver_res(nullptr));
        menu->center();

        /*Create a sub page*/
        auto sub_page = menu->page_create();
        {
            auto cont = menu->cont_create(sub_page);
            auto label = Label(cont);
            label.set_text("Hello, I am hiding inside the first item");
            label.release_ptr();
        }
        main_page = menu->page_create().get_shared<Object>();
        {
            auto cont = menu->cont_create(*main_page);
            auto label = Label(cont);
            label.set_text("Item 1");
            label.release_ptr();
            menu->set_load_page_event(cont, sub_page);
        }
        menu->set_page(*main_page);

        /*Create floating btn*/
        static auto float_btn = Button(root);
        float_btn.set_size(50, 50);
        float_btn.add_flag(LV_OBJ_FLAG_FLOATING);
        float_btn.align(LV_ALIGN_BOTTOM_RIGHT, -10, -10);
        float_btn.add_event_cb(float_btn_event_cb, LV_EVENT_CLICKED);
        float_btn.set_style_radius(LV_RADIUS_CIRCLE, 0);
        float_btn.set_style_bg_img_src(LV_SYMBOL_PLUS, 0);
        float_btn.set_style_text_font(float_btn.get_font_large(), 0);
    }
}