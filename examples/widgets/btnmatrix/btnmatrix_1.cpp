#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/btnmatrix/btnmatrix.h" // for ButtonMatrix
#include "lvglpp/core/event.h" // for Event
#include <vector>
#include <string>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void btnmatrix_1() {
        static auto btnm = ButtonMatrix(scr_act());

        static std::vector<std::string> btnm_map = {"1", "2", "3", "4", "5", "\n",
                                                    "6", "7", "8", "9", "0", "\n",
                                                    "Action1", "Action2", ""};

        btnm.set_map(btnm_map);
        btnm.set_btn_width(10, 2); /*Make "Action1" twice as wide as "Action2"*/
        btnm.set_btn_ctrl(10, LV_BTNMATRIX_CTRL_CHECKABLE);
        btnm.set_btn_ctrl(11, LV_BTNMATRIX_CTRL_CHECKED);
        btnm.align(LV_ALIGN_CENTER, 0, 0);

        auto event_handler = [](Event & e) {
            auto code = e.get_code();
            auto obj = e.get_target<ButtonMatrix>();
            if(code == LV_EVENT_VALUE_CHANGED) {
                uint32_t id = obj.get_selected_btn();
                auto txt = obj.get_btn_text(id);
                LV_LOG_USER("%s was pressed\n", txt);
            }
        };
        btnm.add_event_cb(event_handler, LV_EVENT_ALL);

   }
}