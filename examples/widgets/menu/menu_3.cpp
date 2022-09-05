#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/menu/menu.h" // for Menu
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void menu_3() {
        static auto menu = Menu(scr_act());

        menu.set_size(lv_disp_get_hor_res(nullptr), lv_disp_get_ver_res(nullptr));
        menu.center();

        /*Modify the header*/
        auto back_btn = menu.get_main_header_back_btn();
        static auto back_btn_label = Label(back_btn);
        back_btn_label.set_text("Back");

        /*Create sub pages*/
        auto sub_1_page = menu.page_create("Page 1");
        {
            auto cont = menu.cont_create(sub_1_page);
            auto label = Label(cont);
            label.set_text("Hello, I am hiding here");
            label.release_ptr();
        }

        auto sub_2_page = menu.page_create("Page 2");
        {
            auto cont = menu.cont_create(sub_2_page);
            auto label = Label(cont);
            label.set_text("Hello, I am hiding here");
            label.release_ptr();
        }

        auto sub_3_page = menu.page_create("Page 3");
        {
            auto cont = menu.cont_create(sub_3_page);
            auto label = Label(cont);
            label.set_text("Hello, I am hiding here");
            label.release_ptr();
        }

        /*Create a main page*/
        auto main_page = menu.page_create();
        {
            auto cont = menu.cont_create(main_page);
            auto label = Label(cont);
            label.set_text("Item 1 (Click me!)");
            menu.set_load_page_event(cont, sub_1_page);
        }
        {
            auto cont = menu.cont_create(main_page);
            auto label = Label(cont);
            label.set_text("Item 2 (Click me!)");
            menu.set_load_page_event(cont, sub_2_page);
        }
        {
            auto cont = menu.cont_create(main_page);
            auto label = Label(cont);
            label.set_text("Item 3 (Click me!)");
            menu.set_load_page_event(cont, sub_3_page);
        }

        menu.set_page(main_page);
    }
}