/** \file win.cpp
 *  \brief Implementation file for C++ wrapper for lv_win_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "win.h"

namespace lvgl::widgets {

    Window::Window(lv_coord_t header_height) {
        this->initialize(header_height);
    }

    Window::Window(Object & parent, lv_coord_t header_height) {
        this->initialize(parent, header_height);
    }

    void Window::initialize(lv_coord_t header_height) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_win_create(nullptr, header_height));
    }
    void Window::initialize(Object & parent, lv_coord_t header_height) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_win_create(parent.raw_ptr(), header_height));
    }

    Object Window::add_title(const std::string & txt) {
        return Object(lv_win_add_title(this->raw_ptr(), txt.c_str()));
    }

    Object Window::add_btn(const std::shared_ptr<void> icon, lv_coord_t btn_w) {
        return Object(lv_win_add_btn(this->raw_ptr(), icon.get(), btn_w));
    }

    Object Window::get_header() const {
        return Object(lv_win_get_header(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

    Object Window::get_content() const {
        return Object(lv_win_get_content(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

}