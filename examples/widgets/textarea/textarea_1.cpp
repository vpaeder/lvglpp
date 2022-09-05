#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/textarea/textarea.h" // for TextArea
#include "lvglpp/widgets/btnmatrix/btnmatrix.h" // for ButtonMatrix
#include "lvglpp/core/event.h" // for Event
#include <vector>
#include <string>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    using TextAreaPtr = std::unique_ptr<TextArea>;
    static TextAreaPtr ta;

    static void textarea_event_handler(Event & e) {
        LV_LOG_USER("Enter was pressed. The current text is: %s", ta->get_text());
    }

    static void btnm_event_handler(Event & e) {
        auto obj = e.get_target<ButtonMatrix>();
        auto txt = obj.get_btn_text(obj.get_selected_btn());

        if(strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) ta->del_char();
        else if(strcmp(txt, LV_SYMBOL_NEW_LINE) == 0) ta->send_event(LV_EVENT_READY);
        else ta->add_text(txt);

    }

    void textarea_1() {
        auto root = scr_act();
        
        ta = std::make_unique<TextArea>(root);
        ta->set_one_line(true);
        ta->align(LV_ALIGN_TOP_MID, 0, 10);
        ta->add_event_cb(textarea_event_handler, LV_EVENT_READY);
        ta->add_state(LV_STATE_FOCUSED); /*To be sure the cursor is visible*/

        static const std::vector<std::string> btnm_map = {
            "1", "2", "3", "\n",
            "4", "5", "6", "\n",
            "7", "8", "9", "\n",
            LV_SYMBOL_BACKSPACE, "0", LV_SYMBOL_NEW_LINE, ""
        };

        static auto btnm = ButtonMatrix(root);
        btnm.set_size(200, 150);
        btnm.align(LV_ALIGN_BOTTOM_MID, 0, -10);
        btnm.add_event_cb(btnm_event_handler, LV_EVENT_VALUE_CHANGED);
        btnm.clear_flag(LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
        btnm.set_map(btnm_map);
    }
}