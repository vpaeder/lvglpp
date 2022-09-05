/** \file spinner.cpp
 *  \brief Implementation file for C++ wrapper for lv_spinner_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "spinner.h"
#if LV_USE_SPINNER

namespace lvgl::widgets {

    Spinner::Spinner(uint32_t time, uint32_t arc_length) {
        this->initialize(time, arc_length);
    }

    Spinner::Spinner(Object & parent, uint32_t time, uint32_t arc_length) {
        this->initialize(parent, time, arc_length);
    }

    void Spinner::initialize(uint32_t time, uint32_t arc_length) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_spinner_create(nullptr, time, arc_length));
    }

    void Spinner::initialize(Object & parent, uint32_t time, uint32_t arc_length) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_spinner_create(parent.raw_ptr(), time, arc_length));
    }

}
#endif // LV_USE_SPINNER