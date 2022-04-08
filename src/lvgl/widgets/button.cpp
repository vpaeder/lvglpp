/** \file button.cpp
 *  \brief Implementation file for C++ wrapper for lv_btn_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "button.h"

namespace lvgl::widgets {

    Button::Button() {
        this->initialize();
    }

    Button::Button(Object & parent) {
        this->initialize(parent);
    }

    void Button::initialize() {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_btn_create(nullptr));
    }
    void Button::initialize(Object & parent) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_btn_create(parent.raw_ptr()));
    }

}