/** \file textarea.cpp
 *  \brief Implementation file for C++ wrapper for lv_textarea_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "textarea.h"
#if LV_USE_TEXTAREA != 0

namespace lvgl::widgets {

    void TextArea::add_char(uint32_t c) {
        lv_textarea_add_char(this->raw_ptr(), c);
    }

    void TextArea::add_text(const std::string & txt) {
        lv_textarea_add_text(this->raw_ptr(), txt.c_str());
    }

    void TextArea::del_char() {
        lv_textarea_del_char(this->raw_ptr());
    }

    void TextArea::del_char_forward() {
        lv_textarea_del_char_forward(this->raw_ptr());
    }

    void TextArea::set_text(const std::string & txt) {
        lv_textarea_set_text(this->raw_ptr(), txt.c_str());
    }

    void TextArea::set_placeholder_text(const std::string & txt) {
        lv_textarea_set_placeholder_text(this->raw_ptr(), txt.c_str());
    }

    void TextArea::set_cursor_pos(int32_t pos) {
        lv_textarea_set_cursor_pos(this->raw_ptr(), pos);
    }

    void TextArea::set_cursor_click_pos(bool en) {
        lv_textarea_set_cursor_click_pos(this->raw_ptr(), en);
    }

    void TextArea::set_password_mode(bool en) {
        lv_textarea_set_password_mode(this->raw_ptr(), en);
    }

    void TextArea::set_password_bullet(const char * bullet) {
        lv_textarea_set_password_bullet(this->raw_ptr(), bullet);
    }
    void TextArea::set_password_bullet(const std::string & bullet) {
        lv_textarea_set_password_bullet(this->raw_ptr(), bullet.c_str());
    }

    void TextArea::set_one_line(bool en) {
        lv_textarea_set_one_line(this->raw_ptr(), en);
    }

    void TextArea::set_accepted_chars(const std::string & list) {
        lv_textarea_set_accepted_chars(this->raw_ptr(), list.c_str());
    }

    void TextArea::set_max_length(uint32_t num) {
        lv_textarea_set_max_length(this->raw_ptr(), num);
    }

    void TextArea::set_insert_replace(const std::string & txt) {
        lv_textarea_set_insert_replace(this->raw_ptr(), txt.c_str());
    }

    void TextArea::set_text_selection(bool en) {
        lv_textarea_set_text_selection(this->raw_ptr(), en);
    }

    void TextArea::set_password_show_time(uint16_t time) {
        lv_textarea_set_password_show_time(this->raw_ptr(), time);
    }

    void TextArea::set_align(lv_text_align_t align) {
        lv_textarea_set_align(this->raw_ptr(), align);
    }

    
    const char* TextArea::get_text() const {
            return lv_textarea_get_text(const_cast<lv_cls_ptr>(
                const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

    const char* TextArea::get_placeholder_text() const {
            return lv_textarea_get_placeholder_text(
                const_cast<lv_cls_ptr>(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

    Object TextArea::get_label() const {
        return Object(lv_textarea_get_label(this->raw_ptr()));
    }

    uint32_t TextArea::get_cursor_pos() const {
        return lv_textarea_get_cursor_pos(this->raw_ptr());
    }

    bool TextArea::get_cursor_click_pos() const {
        return lv_textarea_get_cursor_click_pos(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    bool TextArea::get_password_mode() const {
        return lv_textarea_get_password_mode(this->raw_ptr());
    }

    std::string TextArea::get_password_bullet() const {
        return std::string(lv_textarea_get_password_bullet(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

    bool TextArea::get_one_line() const {
        return lv_textarea_get_one_line(this->raw_ptr());
    }

    const char* TextArea::get_accepted_chars() const {
            return lv_textarea_get_accepted_chars(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    uint32_t TextArea::get_max_length() const {
        return lv_textarea_get_max_length(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    bool TextArea::text_is_selected() const {
        return lv_textarea_text_is_selected(this->raw_ptr());
    }

    bool TextArea::get_text_selection() const {
        return lv_textarea_get_text_selection(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    uint16_t TextArea::get_password_show_time() const {
        return lv_textarea_get_password_show_time(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    void TextArea::clear_selection() {
        lv_textarea_clear_selection(this->raw_ptr());
    }

    void TextArea::cursor_right() {
        lv_textarea_cursor_right(this->raw_ptr());
    }

    void TextArea::cursor_left() {
        lv_textarea_cursor_left(this->raw_ptr());
    }

    void TextArea::cursor_down() {
        lv_textarea_cursor_down(this->raw_ptr());
    }

    void TextArea::cursor_up() {
        lv_textarea_cursor_up(this->raw_ptr());
    }

}
#endif // LV_USE_TEXTAREA