/** \file menu.cpp
 *  \brief Implementation file for C++ wrapper for lv_menu_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "menu.h"

namespace lvgl::widgets {

    Object Menu::page_create(const std::string & title) {
        return Object(lv_menu_page_create(this->raw_ptr(), const_cast<char*>(title.c_str())));
    }

    Object Menu::cont_create() {
        return Object(lv_menu_cont_create(this->raw_ptr()));
    }

    Object Menu::section_create() {
        return Object(lv_menu_section_create(this->raw_ptr()));
    }

    Object Menu::separator_create() {
        return Object(lv_menu_separator_create(this->raw_ptr()));
    }

    void Menu::set_page(const Object & page) {
        lv_menu_set_page(this->raw_ptr(), const_cast<lv_obj_t*>(page.raw_ptr()));
    }

    void Menu::set_sidebar_page(const Object & page) {
        lv_menu_set_sidebar_page(this->raw_ptr(), const_cast<lv_obj_t*>(page.raw_ptr()));
    }

    void Menu::set_mode_header(lv_menu_mode_header_t mode_header) {
        lv_menu_set_mode_header(this->raw_ptr(), mode_header);
    }

    void Menu::set_mode_root_back_btn(lv_menu_mode_root_back_btn_t mode_root_back_btn) {
        lv_menu_set_mode_root_back_btn(this->raw_ptr(), mode_root_back_btn);
    }

    void Menu::set_load_page_event(const Object & obj, const Object & page) {
        lv_menu_set_load_page_event(this->raw_ptr(), const_cast<lv_obj_t*>(obj.raw_ptr()),
                                    const_cast<lv_obj_t*>(page.raw_ptr())); 
    }

    Object Menu::get_cur_main_page() const {
        return Object(lv_menu_get_cur_main_page(const_cast<lv_obj_t*>(this->raw_ptr())));
    }

    Object Menu::get_cur_sidebar_page() const {
        return Object(lv_menu_get_cur_sidebar_page(const_cast<lv_obj_t*>(this->raw_ptr())));
    }

    Object Menu::get_main_header() const {
        return Object(lv_menu_get_main_header(const_cast<lv_obj_t*>(this->raw_ptr())));
    }

    Object Menu::get_main_header_back_btn() const {
        return Object(lv_menu_get_main_header_back_btn(const_cast<lv_obj_t*>(this->raw_ptr())));
    }

    Object Menu::get_sidebar_header() const {
        return Object(lv_menu_get_sidebar_header(const_cast<lv_obj_t*>(this->raw_ptr())));
    }

    Object Menu::get_sidebar_header_back_btn() const {
        return Object(lv_menu_get_sidebar_header_back_btn(const_cast<lv_obj_t*>(this->raw_ptr())));
    }

    bool Menu::back_btn_is_root(const Object & obj) const {
        return lv_menu_back_btn_is_root(const_cast<lv_obj_t*>(this->raw_ptr()),
                                        const_cast<lv_obj_t*>(obj.raw_ptr()));
    }

    void Menu::clear_history() {
        lv_menu_clear_history(this->raw_ptr());
    }

}