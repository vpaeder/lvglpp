/** \file roller.cpp
 *  \brief Implementation file for C++ wrapper for lv_roller_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "roller.h"
#if LV_USE_ROLLER != 0

namespace lvgl::widgets {

    void Roller::set_options(const std::string & options, lv_roller_mode_t mode) {
        lv_roller_set_options(this->raw_ptr(), options.c_str(), mode);
    }

    void Roller::set_selected(uint16_t sel_opt, lv_anim_enable_t anim) {
        lv_roller_set_selected(this->raw_ptr(), sel_opt, anim);
    }

    void Roller::set_visible_row_count(uint8_t row_cnt) {
        lv_roller_set_visible_row_count(this->raw_ptr(), row_cnt);
    }

    uint16_t Roller::get_selected() const {
        return lv_roller_get_selected(this->raw_ptr());
    }

    std::string Roller::get_selected_str() const {
        char buf[256];
        lv_roller_get_selected_str(this->raw_ptr(), buf, 256);
        return std::string(buf);
    }

    const char * Roller::get_options() const {
            return lv_roller_get_options(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    uint16_t Roller::get_option_cnt() const {
        return lv_roller_get_option_cnt(this->raw_ptr());
    }

}
#endif // LV_USE_ROLLER