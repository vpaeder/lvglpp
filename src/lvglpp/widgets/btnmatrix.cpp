/** \file btnmatrix.cpp
 *  \brief Implementation file for C++ wrapper for lv_btnmatrix_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "btnmatrix.h"

#if LV_USE_BTNMATRIX != 0

namespace lvgl::widgets {

    void ButtonMatrix::set_map(const std::vector<std::string> & map) {
        this->map = str_vector_to_char_array(map);
        // this->map is defined but this->map.get() returns a char** and not
        // a const char**, despite of having the attributes of a const char**.
        // The reason is that get() returns the pointer to the raw object
        // and one cannot assume it's not going to change (although it usually doesn't happen).
        // Therefore, we force casting to const char**, even if it's not really clean.
        lv_btnmatrix_set_map(this->raw_ptr(), (const char**)this->map.get());
    }

    void ButtonMatrix::set_ctrl_map(const std::vector<lv_btnmatrix_ctrl_t> & ctrl_map) {
        lv_btnmatrix_set_ctrl_map(this->raw_ptr(), ctrl_map.data());
    }

    void ButtonMatrix::set_selected_btn(uint16_t btn_id) {
        lv_btnmatrix_set_selected_btn(this->raw_ptr(), btn_id);
    }

    void ButtonMatrix::set_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl) {
        lv_btnmatrix_set_btn_ctrl(this->raw_ptr(), btn_id, ctrl);
    }

    void ButtonMatrix::clear_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl) {
        lv_btnmatrix_clear_btn_ctrl(this->raw_ptr(), btn_id, ctrl);
    }

    void ButtonMatrix::set_btn_ctrl_all(lv_btnmatrix_ctrl_t ctrl) {
        lv_btnmatrix_set_btn_ctrl_all(this->raw_ptr(), ctrl);
    }

    void ButtonMatrix::clear_btn_ctrl_all(lv_btnmatrix_ctrl_t ctrl) {
        lv_btnmatrix_clear_btn_ctrl_all(this->raw_ptr(), ctrl);
    }

    void ButtonMatrix::set_btn_width(uint16_t btn_id, uint8_t width) {
        lv_btnmatrix_set_btn_width(this->raw_ptr(), btn_id, width);
    }

    void ButtonMatrix::set_one_checked(bool en) {
        lv_btnmatrix_set_one_checked(this->raw_ptr(), en);
    }

    RawDblArray<char> & ButtonMatrix::get_map() {
        return this->map;
    }

    uint16_t ButtonMatrix::get_selected_btn() const {
        return lv_btnmatrix_get_selected_btn(this->raw_ptr());
    }

    const char* ButtonMatrix::get_btn_text(uint16_t btn_id) const {
        return lv_btnmatrix_get_btn_text(this->raw_ptr(), btn_id);
    }

    bool ButtonMatrix::has_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl) const {
        return lv_btnmatrix_has_btn_ctrl(const_cast<lv_cls_ptr>(this->raw_ptr()), btn_id, ctrl);
    }

    bool ButtonMatrix::get_one_checked() const {
        return lv_btnmatrix_get_one_checked(this->raw_ptr());
    }

}
#endif // LV_USE_BTNMATRIX
