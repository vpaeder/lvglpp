/** \file switch.cpp
 *  \brief Implementation file for C++ wrapper for lv_switch_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "switch.h"
#if LV_USE_SWITCH != 0

namespace lvgl::widgets {

    Switch::Switch() {
        this->initialize();
    }

    Switch::Switch(Object & parent) {
        this->initialize(parent);
    }

    void Switch::initialize() {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_switch_create(nullptr));
    }
    void Switch::initialize(Object & parent) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_switch_create(parent.raw_ptr()));
    }

}
#endif // LV_USE_SWITCH
