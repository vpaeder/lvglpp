/** \file switch.h
 *  \brief Header file for C++ wrapper for lv_switch_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#if LV_USE_SWITCH != 0

#include "../core/object.h"

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \typedef Switch
     *  \brief Wraps a lv_switch_t object.
     */
    using Switch = Widget<lv_switch_create>;

}
#endif // LV_USE_SWITCH
