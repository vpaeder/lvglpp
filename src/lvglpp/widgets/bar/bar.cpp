/** \file bar.cpp
 *  \brief Implementation file for C++ wrapper for lv_bar_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "bar.h"
#if LV_USE_BAR != 0

namespace lvgl::widgets {

    void Bar::set_value(int32_t value, lv_anim_enable_t anim) {
        lv_bar_set_value(this->raw_ptr(), value, anim);
    }

    void Bar::set_start_value(int32_t start_value, lv_anim_enable_t anim) {
        lv_bar_set_start_value(this->raw_ptr(), start_value, anim);
    }

    void Bar::set_range(int32_t min, int32_t max) {
        lv_bar_set_range(this->raw_ptr(), min, max);
    }

    void Bar::set_mode(mode_t mode) {
        lv_bar_set_mode(this->raw_ptr(), mode);
    }

    int32_t Bar::get_value() const {
        return lv_bar_get_value(this->raw_ptr());
    }

    int32_t Bar::get_start_value() const {
        return lv_bar_get_start_value(this->raw_ptr());
    }

    int32_t Bar::get_min_value() const {
        return lv_bar_get_min_value(this->raw_ptr());
    }

    int32_t Bar::get_max_value() const {
        return lv_bar_get_max_value(this->raw_ptr());
    }

    mode_t Bar::get_mode() const {
        return lv_bar_get_mode(const_cast<lv_obj_t*>(this->raw_ptr()));
    }

}
#endif // LV_USE_BAR