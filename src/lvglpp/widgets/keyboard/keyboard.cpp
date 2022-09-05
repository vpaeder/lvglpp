/** \file keyboard.cpp
 *  \brief Implementation file for C++ wrapper for lv_keyboard_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "keyboard.h"
#if LV_USE_KEYBOARD

namespace lvgl::widgets {

    void Keyboard::initialize() {
        this->map = std::vector<RawDblArray<char>>(8);
        Widget::initialize();
    }
    void Keyboard::initialize(Object & parent) {
        this->map = std::vector<RawDblArray<char>>(8);
        Widget::initialize(parent);
    }

    void Keyboard::set_textarea(Object & ta) {
        lv_keyboard_set_textarea(this->raw_ptr(), ta.raw_ptr());
    }

    void Keyboard::unset_textarea() {
        lv_keyboard_set_textarea(this->raw_ptr(), nullptr);
    }

    void Keyboard::set_mode(lv_keyboard_mode_t mode) {
        lv_keyboard_set_mode(this->raw_ptr(), mode);
    }

    void Keyboard::set_popovers(bool en) {
        lv_keyboard_set_popovers(this->raw_ptr(), en);
    }

    void Keyboard::set_map(lv_keyboard_mode_t mode, const std::vector<std::string> & map,
                           const std::vector<lv_btnmatrix_ctrl_t> & ctrl_map) {
        this->map[mode] = str_vector_to_char_array(map);
        // see ButtonMatrix::set_map for explanation
        lv_keyboard_set_map(this->raw_ptr(), mode, (const char**)this->map[mode].get(), ctrl_map.data());
    }

    Object Keyboard::get_textarea() const {
        return Object(lv_keyboard_get_textarea(this->raw_ptr()));
    }

    lv_keyboard_mode_t Keyboard::get_mode() const {
        return lv_keyboard_get_mode(this->raw_ptr());
    }

    bool Keyboard::get_popovers() const {
        return lv_btnmatrix_get_popovers(this->raw_ptr());
    }

    RawDblArray<char> & Keyboard::get_map_array() {
        return this->map[this->get_mode()];
    }

    uint16_t Keyboard::get_selected_btn() const {
        return lv_keyboard_get_selected_btn(this->raw_ptr());
    }

    std::shared_ptr<const char> Keyboard::get_btn_text(uint16_t btn_id) const {
        return std::shared_ptr<const char>(lv_keyboard_get_btn_text(this->raw_ptr(), btn_id));
    }

}
#endif // LV_USE_KEYBOARD