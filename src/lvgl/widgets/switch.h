/** \file switch.h
 *  \brief Header file for C++ wrapper for lv_switch_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../core/object.h"

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \typedef Switch
     *  \brief Wraps a lv_switch_t object.
     */
    using Switch = Widget<lv_switch_create>;

}
