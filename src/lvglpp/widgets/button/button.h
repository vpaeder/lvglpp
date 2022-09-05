/** \file button.h
 *  \brief Header file for C++ wrapper for lv_btn_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_BTN != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Button
     *  \brief Wraps a lv_btn_t object.
     */
    class Button : public Widget<lv_btn_create> {
    public:
        using Widget::Widget;
    };

}
#endif // LV_USE_BTN