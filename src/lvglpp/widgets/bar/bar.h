/** \file bar.h
 *  \brief Header file for C++ wrapper for lv_bar_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_BAR != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Bar
     *  \brief Wraps a lv_bar_t object. This is a linear progress/indicator bar.
     */
    class Bar : public Widget<lv_bar_create> {
    public:
        using Widget::Widget;

        /** \fn void set_value(int32_t value, lv_anim_enable_t anim)
         *  \brief Sets the bar value.
         *  \param value: value to set.
         *  \param anim: enable (LV_ANIM_ON) or disable (LV_ANIM_OFF) animation.
         */
        void set_value(int32_t value, lv_anim_enable_t anim);

        /** \fn void set_start_value(int32_t value, lv_anim_enable_t anim)
         *  \brief Sets the bar's start value.
         *  \param value: value to set.
         *  \param anim: enable (LV_ANIM_ON) or disable (LV_ANIM_OFF) animation.
         */
        void set_start_value(int32_t start_value, lv_anim_enable_t anim);

        /** \fn void set_range(int32_t min, int32_t max)
         *  \brief Sets the bar's value range.
         *  \param min: minimum value.
         *  \param max: maximum value.
         */
        void set_range(int32_t min, int32_t max);

        /** \fn void set_mode(mode_t mode)
         *  \brief Sets the bar mode.
         *  \param mode: bar mode.
         */
        void set_mode(mode_t mode);

        /** \fn int32_t get_value() const
         *  \brief Gets the bar value.
         *  \returns bar value.
         */
        int32_t get_value() const;

        /** \fn int32_t get_start_value() const
         *  \brief Gets the bar's start value.
         *  \returns bar's start value.
         */
        int32_t get_start_value() const;

        /** \fn int32_t get_min_value() const
         *  \brief Gets the bar minimum value.
         *  \returns bar minimum value.
         */
        int32_t get_min_value() const;

        /** \fn int32_t get_max_value() const
         *  \brief Gets the bar maximum value.
         *  \returns bar maximum value.
         */
        int32_t get_max_value() const;

        /** \fn mode_t get_mode() const
         *  \brief Gets the bar mode.
         *  \returns bar mode.
         */
        mode_t get_mode() const;

    };

}

#endif // LV_USE_BAR
