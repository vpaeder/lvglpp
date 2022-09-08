/** \file label.cpp
 *  \brief Implementation file for C++ wrapper for lv_label_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "label.h"
#if LV_USE_LABEL != 0

namespace lvgl::widgets {

    void Label::set_text(const std::string & text) {
        lv_label_set_text(this->raw_ptr(), text.c_str());
    }

    void Label::set_text_static(const std::string & text) {
        lv_label_set_text_static(this->raw_ptr(), text.data());
    }

    void Label::set_long_mode(lv_label_long_mode_t long_mode) {
        lv_label_set_long_mode(this->raw_ptr(), long_mode);
    }

    void Label::set_recolor(bool en) {
        lv_label_set_recolor(this->raw_ptr(), en);
    }

    const char * Label::get_text() const {
        return lv_label_get_text(this->raw_ptr());
    }

    lv_label_long_mode_t Label::get_long_mode() const {
        return lv_label_get_long_mode(this->raw_ptr());
    }

    bool Label::get_recolor() const {
        return lv_label_get_recolor(this->raw_ptr());
    }

    lv_point_t Label::get_letter_pos(const uint32_t char_id) const {
        lv_point_t pos;
        lv_label_get_letter_pos(this->raw_ptr(), char_id, &pos);
        return pos;
    }

    uint32_t Label::get_letter_on(lv_point_t & pos_in) const {
        return lv_label_get_letter_on(this->raw_ptr(), &pos_in);
    }

    bool Label::is_char_under_pos(lv_point_t & pos) const {
        return lv_label_is_char_under_pos(this->raw_ptr(), &pos);
    }

    uint32_t Label::get_text_selection_start() const {
        return lv_label_get_text_selection_start(this->raw_ptr());
    }

    uint32_t Label::get_text_selection_end() const {
        return lv_label_get_text_selection_end(this->raw_ptr());
    }
    
    void Label::ins_text(uint32_t pos, const std::string & txt) {
        return lv_label_ins_text(this->raw_ptr(), pos, txt.c_str());
    }

    void Label::cut_text(uint32_t pos, uint32_t cnt) {
        return lv_label_cut_text(this->raw_ptr(), pos, cnt);
    }

}
#endif // LV_USE_LABEL