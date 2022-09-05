#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/menu/menu.h" // for Menu
#include "lvglpp/widgets/msgbox/msgbox.h" // for MessageBox
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/core/event.h" // for Event
#include <vector>
#include <string>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    using MenuPtr = std::unique_ptr<Menu>;
    using MessageBoxPtr = std::unique_ptr<MessageBox>;
    static MenuPtr menu;
    static MessageBoxPtr mbox;

    static void back_event_handler(Event & e) {
        auto obj = e.get_target<Object>();
        if(menu->back_btn_is_root(obj)) {
            std::vector<std::string> btn_strs;
            mbox = std::make_unique<MessageBox>("Hello", "Root back btn click.", btn_strs, true);
            mbox->center();
        } else {
            mbox = nullptr;
        }
    }

    void menu_2() {
        menu = std::make_unique<Menu>(scr_act());

        menu->set_mode_root_back_btn(LV_MENU_ROOT_BACK_BTN_ENABLED);
        menu->add_event_cb(back_event_handler, LV_EVENT_CLICKED);
        menu->set_size(lv_disp_get_hor_res(nullptr), lv_disp_get_ver_res(nullptr));
        menu->center();

        /*Create a sub page*/
        auto sub_page = menu->page_create();

        {
            auto cont = menu->cont_create(sub_page);
            auto label = Label(cont);
            label.set_text("Hello, I am hiding here");
            label.release_ptr();
        }

        /*Create a main page*/
        auto main_page = menu->page_create();

        {
            auto cont = menu->cont_create(main_page);
            auto label = Label(cont);
            label.set_text("Item 1");
            label.release_ptr();
        }

        {
            auto cont = menu->cont_create(main_page);
            auto label = Label(cont);
            label.set_text("Item 2");
            label.release_ptr();
        }

        {
            auto cont = menu->cont_create(main_page);
            auto label = Label(cont);
            label.set_text("Item 3 (Click me!)");
            label.release_ptr();
            menu->set_load_page_event(cont, sub_page);
        }
        
        menu->set_page(main_page);
    }
}