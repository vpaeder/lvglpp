/** \file spinbox.h
 *  \brief Header file for C++ wrapper for lv_spinbox_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_SPINBOX

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Spinbox
     *  \brief Wraps a lv_spinbox_t object.
     */
    class Spinbox : public Widget<lv_spinbox_create> {
    public:
        using Widget::Widget;
        
        /** \fn void set_value(int32_t i)
         *  \brief Sets spinbox value.
         *  \param i: target value.
         */
        void set_value(int32_t i);

        /** \fn void set_rollover(bool b)
         *  \brief Enables/disables roll-over mode.
         *  \param b: if true, enables roll-over mode.
         */
        void set_rollover(bool b);

        /** \fn void set_digit_format(uint8_t digit_count, uint8_t separator_position)
         *  \brief Sets number format.
         *  \param digit_count: number of digits displayed.
         *  \param separator_position: position of decimal separator.
         */
        void set_digit_format(uint8_t digit_count, uint8_t separator_position);

        /** \fn void set_step(uint32_t step)
         *  \brief Sets amount of increment/decrement.
         *  \param step: step size.
         */
        void set_step(uint32_t step);

        /** \fn void set_range(int32_t range_min, int32_t range_max)
         *  \brief Sets spinbox range.
         *  \param range_min: minimum value.
         *  \param range_max: maximum value.
         */
        void set_range(int32_t range_min, int32_t range_max);

        /** \brief Sets cursor position.
         *  \param pos: cursor position.
         */
        void set_cursor_pos(uint8_t pos);

        /** \fn void set_digit_step_direction(lv_dir_t direction)
         *  \brief Sets step direction when clicking on encoder button.
         *  \param direction: LV_DIR_RIGHT/LEFT.
         */
        void set_digit_step_direction(lv_dir_t direction);

        /** \fn bool get_rollover() const
         *  \brief Tells if roll-over mode is enabled.
         *  \returns true if roll-over mode is enabled, false otherwise.
         */
        bool get_rollover() const;

        /** \fn int32_t get_value() const
         *  \brief Gets spinbox value.
         *  \returns spinbox value.
         */
        int32_t get_value() const;

        /** \fn int32_t get_step() const
         *  \brief Gets spinbox step size.
         *  \returns spinbox step size.
         */
        int32_t get_step() const;

        /** \fn void step_next()
         *  \brief Reduces step by 10.
         */
        void step_next();

        /** \fn void step_prev()
         *  \brief Increases step by 10.
         */
        void step_prev();

        /** \fn void increment()
         *  \brief Increments value by step size.
         */
        void increment();

        /** \fn void decrement()
         *  \brief Decrements value by step size.
         */
        void decrement();
    };

}
#endif // LV_USE_SPINBOX