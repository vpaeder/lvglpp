/** \file spinbox.cpp
 *  \brief Implementation file for C++ wrapper for lv_spinbox_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "spinbox.h"
#if LV_USE_SPINBOX

namespace lvgl::widgets {

    void Spinbox::set_value(int32_t i) {
        lv_spinbox_set_value(this->raw_ptr(), i);
    }

    void Spinbox::set_rollover(bool b) {
        lv_spinbox_set_rollover(this->raw_ptr(), b);
    }

    void Spinbox::set_digit_format(uint8_t digit_count, uint8_t separator_position) {
        lv_spinbox_set_digit_format(this->raw_ptr(), digit_count, separator_position);
    }

    void Spinbox::set_step(uint32_t step) {
        lv_spinbox_set_step(this->raw_ptr(), step);
    }

    void Spinbox::set_range(int32_t range_min, int32_t range_max) {
        lv_spinbox_set_range(this->raw_ptr(), range_min, range_max);
    }

    void Spinbox::set_cursor_pos(uint8_t pos) {
        lv_spinbox_set_cursor_pos(this->raw_ptr(), pos);
    }

    void Spinbox::set_digit_step_direction(lv_dir_t direction) {
        lv_spinbox_set_digit_step_direction(this->raw_ptr(), direction);
    }

    bool Spinbox::get_rollover() const {
        return lv_spinbox_get_rollover(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    int32_t Spinbox::get_value() const {
        return lv_spinbox_get_value(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    int32_t Spinbox::get_step() const {
        return lv_spinbox_get_step(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    void Spinbox::step_next() {
        lv_spinbox_step_next(this->raw_ptr());
    }

    void Spinbox::step_prev() {
        lv_spinbox_step_prev(this->raw_ptr());
    }

    void Spinbox::increment() {
        lv_spinbox_increment(this->raw_ptr());
    }

    void Spinbox::decrement() {
        lv_spinbox_decrement(this->raw_ptr());
    }

}
#endif // LV_USE_SPINBOX