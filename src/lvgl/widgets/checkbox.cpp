/** \file checkbox.cpp
 *  \brief Implementation file for C++ wrapper for lv_checkbox_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "checkbox.h"

namespace lvgl::widgets {

    Checkbox::Checkbox() {
        this->initialize();
    }

    Checkbox::Checkbox(Object & parent) {
        this->initialize(parent);
    }

    void Checkbox::initialize() {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_checkbox_create(nullptr));
    }
    void Checkbox::initialize(Object & parent) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_checkbox_create(parent.raw_ptr()));
    }

    void Checkbox::set_text(const std::string & txt) {
        lv_checkbox_set_text(this->raw_ptr(), txt.c_str());
    }

    void Checkbox::set_text_static(const std::shared_ptr<char> txt) {
        lv_checkbox_set_text_static(this->raw_ptr(), txt.get());
    }

    const std::shared_ptr<const char> Checkbox::get_text() const {
        return std::shared_ptr<const char>(
            lv_checkbox_get_text(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

}