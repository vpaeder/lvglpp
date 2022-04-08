/** \file button.h
 *  \brief Header file for C++ wrapper for lv_btn_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../core/object.h"

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \typedef Button
     *  \brief Wraps a lv_btn_t object.
     */
    using Button = Widget<lv_btn_create>;

}
