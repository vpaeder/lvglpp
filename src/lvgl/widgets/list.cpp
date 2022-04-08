/** \file list.cpp
 *  \brief Implementation file for C++ wrapper for lv_list_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "list.h"

namespace lvgl::widgets {

    List::List() {
        this->initialize();
    }

    List::List(Object & parent) {
        this->initialize(parent);
    }

    void List::initialize() {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_list_create(nullptr));
    }
    void List::initialize(Object & parent) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_list_create(parent.raw_ptr()));
    }

    Object List::add_text(const std::string & txt) {
        return Object(lv_list_add_text(this->raw_ptr(), txt.c_str()));
    }

    Object List::add_btn(const std::string & icon, const std::string & txt) {
        return Object(lv_list_add_btn(this->raw_ptr(), icon.c_str(), txt.c_str()));
    }

    std::string List::get_btn_text(const Object & btn) const {
        return std::string(lv_list_get_btn_text(const_cast<lv_cls_ptr>(this->raw_ptr()),
                                                const_cast<lv_obj_t*>(btn.raw_ptr())));
    }

}