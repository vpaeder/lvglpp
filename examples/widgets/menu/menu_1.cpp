#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/menu/menu.h" // for Menu
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void menu_1() {
        static auto menu = Menu(scr_act());

        menu.set_size(lv_disp_get_hor_res(nullptr), lv_disp_get_ver_res(nullptr));
        menu.center();

        /*Create a sub page*/
        auto sub_page = menu.page_create();

        auto cont = menu.cont_create(sub_page);
        static auto label_sub = Label(cont);
        label_sub.set_text("Hello, I am hiding here");

        /*Create a main page*/
        auto main_page = menu.page_create();

        auto cont = menu.cont_create(main_page);
        static auto label_1 = Label(cont);
        label_1.set_text("Item 1");

        auto cont = menu.cont_create(main_page);
        static auto label_2 = Label(cont);
        label_2.set_text("Item 2");

        auto cont = menu.cont_create(main_page);
        static auto label_3 = Label(cont);
        label_3.set_text("Item 3 (Click me!)");
        menu.set_load_page_event(cont, sub_page);

        menu.set_page(main_page);
    }
}