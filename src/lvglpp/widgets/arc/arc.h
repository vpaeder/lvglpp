/** \file arc.h
 *  \brief Header file for C++ wrapper for lv_arc_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_ARC != 0

/** \namespace lvgl::widgets
 *  \brief LVGL widget C++ wrappers.
 */
namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Arc
     *  \brief Wraps a lv_arc_t object. This is a circular progress/indicator bar.
     */
    class Arc : public Widget<lv_arc_create> {
    public:
        using Widget::Widget;

        /** \fn void set_start_angle(uint16_t start)
         *  \brief Sets the start angle of the arc. 0 deg: right, 90 bottom, etc.
         *  \param start: the start angle.
         */
        void set_start_angle(uint16_t start);

        /** \fn void set_end_angle(uint16_t end)
         *  \brief Sets the end angle of the arc. 0 deg: right, 90 bottom, etc.
         *  \param end: the end angle.
         */
        void set_end_angle(uint16_t end);

        /** \fn void set_angles(uint16_t start, uint16_t end)
         *  \brief Sets the start and end angles of the arc.
         *  \param start: the start angle.
         *  \param end: the end angle.
         */
        void set_angles(uint16_t start, uint16_t end);

        /** \fn void set_bg_start_angle(uint16_t start)
         *  \brief Sets the start angle of the arc's background. 0 deg: right, 90 bottom, etc.
         *  \param start: the start angle.
         */
        void set_bg_start_angle(uint16_t start);

        /** \fn void set_bg_end_angle(uint16_t end)
         *  \brief Sets the end angle of the arc's background. 0 deg: right, 90 bottom, etc.
         *  \param end: the end angle.
         */
        void set_bg_end_angle(uint16_t end);

        /** \fn void set_bg_angles(uint16_t start, uint16_t end)
         *  \brief Sets the start and end angles of the arc's background.
         *  \param start: the start angle.
         *  \param end: the end angle.
         */
        void set_bg_angles(uint16_t start, uint16_t end);

        /** \fn void set_rotation(uint16_t rotation)
         *  \brief Sets the rotation for the arc (= start - end).
         *  \param rotation: the rotation angle.
         */
        void set_rotation(uint16_t rotation);

        /** \fn void set_mode(lv_arc_mode_t type)
         *  \brief Sets the type of the arc.
         *  \param type: type of arc.
         */
        void set_mode(lv_arc_mode_t type);

        /** \fn void set_value(int16_t value)
         *  \brief Sets the value of the arc. This is translated into angle
         *  based on the arc's range.
         *  \param value: value to set.
         */
        void set_value(int16_t value);

        /** \fn void set_range(int16_t min, int16_t max)
         *  \brief Sets the value range for the arc.
         *  \param min: minimum value.
         *  \param max: maximum value.
         */
        void set_range(int16_t min, int16_t max);

        /** \fn void set_change_rate(uint16_t rate)
         *  \brief Sets the arc's change rate. This limits the speed at which
         *  the arc will reach the target value.
         *  \param rate: rate in /s.
         */
        void set_change_rate(uint16_t rate);

        /** \fn uint16_t get_angle_start() const
         *  \brief Gets the arc start angle.
         *  \returns arc start angle.
         */
        uint16_t get_angle_start() const;

        /** \fn uint16_t get_angle_end() const
         *  \brief Gets the arc end angle.
         *  \returns arc end angle.
         */
        uint16_t get_angle_end() const;

        /** \fn uint16_t get_bg_angle_start() const
         *  \brief Gets the arc's background start angle.
         *  \returns arc's background start angle.
         */
        uint16_t get_bg_angle_start() const;

        /** \fn uint16_t get_bg_angle_end() const
         *  \brief Gets the arc's background end angle.
         *  \returns arc's background end angle.
         */
        uint16_t get_bg_angle_end() const;

        /** \fn int16_t get_value() const
         *  \brief Gets the arc value.
         *  \returns arc value.
         */
        int16_t get_value() const;

        /** \fn int16_t get_min_value() const
         *  \brief Gets the arc minimum value.
         *  \returns arc minimum value.
         */
        int16_t get_min_value() const;

        /** \fn int16_t get_max_value() const
         *  \brief Gets the arc maximum value.
         *  \returns arc maximum value.
         */
        int16_t get_max_value() const;

        /** \fn lv_arc_mode_t get_mode() const
         *  \brief Gets the arc type.
         *  \returns arc type.
         */
        lv_arc_mode_t get_mode() const;

        /** \brief Align an object to the current position of the arc (knob).
         *  \param obj_to_align: object to align.
         *  \param r_offset: radius offset.
         */
        void align_obj_to_angle(Object & obj_to_align, lv_coord_t r_offset) const;
        
        /** \brief Rotate an object to the current position of the arc (knob).
         *  \param obj_to_rotate: object to align.
         *  \param r_offset: radius offset.
         */
        void rotate_obj_to_angle(Object & obj_to_rotate, lv_coord_t r_offset) const;

    };

}

#endif // LV_USE_ARC