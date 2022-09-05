#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/keyboard/keyboard.h" // for Keyboard
#include "lvglpp/widgets/textarea/textarea.h" // for TextArea

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void keyboard_2() {
        /*Create an AZERTY keyboard map*/
        static const std::vector<std::string> kb_map = {
            "A", "Z", "E", "R", "T", "Y", "U", "I", "O", "P", LV_SYMBOL_BACKSPACE, "\n",
            "Q", "S", "D", "F", "G", "J", "K", "L", "M",  LV_SYMBOL_NEW_LINE, "\n",
            "W", "X", "C", "V", "B", "N", ",", ".", ":", "!", "?", "\n",
            LV_SYMBOL_CLOSE, " ",  " ", " ", LV_SYMBOL_OK
        };

        /*Set the relative width of the buttons and other controls*/
        static const std::vector<lv_btnmatrix_ctrl_t> kb_ctrl = {
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 6,
            4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
            2, LV_BTNMATRIX_CTRL_HIDDEN | 2, 6, LV_BTNMATRIX_CTRL_HIDDEN | 2, 2
        };

        /*Create a keyboard and add the new map as USER_1 mode*/
        auto root = scr_act();
        auto kb = Keyboard(root);

        kb.set_map(LV_KEYBOARD_MODE_USER_1, kb_map, kb_ctrl);
        kb.set_mode(LV_KEYBOARD_MODE_USER_1);

        /*Create a text area. The keyboard will write here*/
        auto ta = TextArea(root);
        ta.align(LV_ALIGN_TOP_MID, 0, 10);
        ta.set_size(lv_pct(90), 80);
        ta.add_state(LV_STATE_FOCUSED);

        kb.set_textarea(ta);
    }
}