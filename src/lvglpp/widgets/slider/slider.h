/** \file slider.h
 *  \brief Header file for C++ wrapper for lv_slider_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_SLIDER != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Slider
     *  \brief Wraps a lv_slider_t object.
     */
    class Slider : public Widget<lv_slider_create> {
    public:
        using Widget::Widget;

        /** \fn void set_value(int32_t value, lv_anim_enable_t anim)
         *  \brief Sets slider value.
         *  \param value: value to set.
         *  \param anim: defines if value change is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void set_value(int32_t value, lv_anim_enable_t anim);

        /** \fn void set_left_value(int32_t value, lv_anim_enable_t anim)
         *  \brief Sets slider's left value.
         *  \param value: value to set.
         *  \param anim: defines if value change is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void set_left_value(int32_t value, lv_anim_enable_t anim);

        /** \fn void set_range(int32_t min, int32_t max)
         *  \brief Sets slider range.
         *  \param min: minimum value.
         *  \param max: maximum value.
         */
        void set_range(int32_t min, int32_t max);

        /** \fn void set_mode(mode_t mode)
         *  \brief Sets slider mode: LV_SLIDER_MODE_NORMAL/SYMMETRICAL/RANGE
         *  \param mode: slider mode.
         */
        void set_mode(mode_t mode);

        /** \fn int32_t get_value() const
         *  \brief Gets slider value.
         *  \returns slider value.
         */
        int32_t get_value() const;

        /** \fn int32_t get_left_value() const
         *  \brief Gets slider's left value.
         *  \returns slider's left value.
         */
        int32_t get_left_value() const;

        /** \fn int32_t get_min_value() const
         *  \brief Gets slider's minimum value.
         *  \returns slider's minimum value.
         */
        int32_t get_min_value() const;

        /** \fn int32_t get_max_value() const
         *  \brief Gets slider's maximum value.
         *  \returns slider's maximum value.
         */
        int32_t get_max_value() const;

        /** \fn bool is_dragged() const
         *  \brief Tells if slider is being dragged.
         *  \returns true if slider is being dragged, false otherwise.
         */
        bool is_dragged() const;

        /** \fn mode_t get_mode() const
         *  \brief Gets slider mode: LV_SLIDER_MODE_NORMAL/SYMMETRICAL/RANGE
         *  \returns code for slider mode.
         */
        mode_t get_mode() const;
    };

}
#endif // LV_USE_SLIDER