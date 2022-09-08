/** \file dropdown.cpp
 *  \brief Implementation file for C++ wrapper for lv_dropdown_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "dropdown.h"
#if LV_USE_DROPDOWN != 0

namespace lvgl::widgets {

    void Dropdown::set_text(const std::string & txt) {
        if (txt.size()==0) {
            lv_dropdown_set_text(this->raw_ptr(), nullptr);
        } else {
            lv_dropdown_set_text(this->raw_ptr(), txt.c_str());
        }
    }

    void Dropdown::set_options(const std::string & options) {
        lv_dropdown_set_options(this->raw_ptr(), options.c_str());
    }

    void Dropdown::set_options_static(const std::string & options) {
        lv_dropdown_set_options_static(this->raw_ptr(), options.data());
    }

    void Dropdown::add_option(const std::string & option, uint32_t pos) {
        lv_dropdown_add_option(this->raw_ptr(), option.c_str(), pos);
    }

    void Dropdown::clear_options() {
        lv_dropdown_clear_options(this->raw_ptr());
    }

    void Dropdown::set_selected(uint16_t sel_opt) {
        lv_dropdown_set_selected(this->raw_ptr(), sel_opt);
    }

    void Dropdown::set_dir(lv_dir_t dir) {
        lv_dropdown_set_dir(this->raw_ptr(), dir);
    }

    void Dropdown::set_symbol(const std::string & symbol) {
        lv_dropdown_set_symbol(this->raw_ptr(), symbol.c_str());
    }

    void Dropdown::set_symbol(const ImageDescriptor & symbol) {
        lv_dropdown_set_symbol(this->raw_ptr(), symbol.raw_ptr());
    }

    void Dropdown::set_selected_highlight(bool en) {
        lv_dropdown_set_selected_highlight(this->raw_ptr(), en);
    }
   
    Object Dropdown::get_list() const {
        return Object(lv_dropdown_get_list(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

    const char * Dropdown::get_text() const {
        return lv_dropdown_get_text(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    const char * Dropdown::get_options() const {
        return lv_dropdown_get_options(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    uint16_t Dropdown::get_selected() const {
        return lv_dropdown_get_selected(this->raw_ptr());
    }

    uint16_t Dropdown::get_option_cnt() const {
        return lv_dropdown_get_option_cnt(this->raw_ptr());
    }

    std::string Dropdown::get_selected_str() const {
        char buf[64];
        lv_dropdown_get_selected_str(this->raw_ptr(), buf, 64);
        return std::string(std::move(buf));
    }

    int32_t Dropdown::get_option_index(const char * option) const {
        return lv_dropdown_get_option_index(const_cast<lv_cls_ptr>(this->raw_ptr()), option);
    }

    int32_t Dropdown::get_option_index(const std::string & option) const {
        return lv_dropdown_get_option_index(const_cast<lv_cls_ptr>(this->raw_ptr()), option.c_str());
    }

    const char * Dropdown::get_symbol() const {
        return lv_dropdown_get_symbol(const_cast<lv_cls_ptr>(this->raw_ptr()));

    }

    bool Dropdown::get_selected_highlight() const {
        return lv_dropdown_get_selected_highlight(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_dir_t Dropdown::get_dir() const {
        return lv_dropdown_get_dir(this->raw_ptr());
    }

    void Dropdown::open() {
        lv_dropdown_open(this->raw_ptr());
    }

    void Dropdown::close() {
        lv_dropdown_close(this->raw_ptr());
    }

    bool Dropdown::is_open() const {
        return lv_dropdown_is_open(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

}
#endif // LV_USE_DROPDOWN