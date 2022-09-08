/** \file arc.cpp
 *  \brief Implementation file for C++ wrapper for lv_arc_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "arc.h"
#if LV_USE_ARC != 0

namespace lvgl::widgets {

    void Arc::set_start_angle(uint16_t start) {
        lv_arc_set_start_angle(this->raw_ptr(), start);
    }

    void Arc::set_end_angle(uint16_t end) {
        lv_arc_set_end_angle(this->raw_ptr(), end);
    }

    void Arc::set_angles(uint16_t start, uint16_t end) {
        lv_arc_set_angles(this->raw_ptr(), start, end);
    }

    void Arc::set_bg_start_angle(uint16_t start) {
        lv_arc_set_bg_start_angle(this->raw_ptr(), start);
    }

    void Arc::set_bg_end_angle(uint16_t end) {
        lv_arc_set_bg_end_angle(this->raw_ptr(), end);
    }

    void Arc::set_bg_angles(uint16_t start, uint16_t end) {
        lv_arc_set_bg_angles(this->raw_ptr(), start, end);
    }

    void Arc::set_rotation(uint16_t rotation) {
        lv_arc_set_rotation(this->raw_ptr(), rotation);
    }

    void Arc::set_mode(lv_arc_mode_t type) {
        lv_arc_set_mode(this->raw_ptr(), type);
    }

    void Arc::set_value(int16_t value) {
        lv_arc_set_value(this->raw_ptr(), value);
    }

    void Arc::set_range(int16_t min, int16_t max) {
        lv_arc_set_range(this->raw_ptr(), min, max);
    }

    void Arc::set_change_rate(uint16_t rate) {
        lv_arc_set_change_rate(this->raw_ptr(), rate);
    }

    uint16_t Arc::get_angle_start() const {
        return lv_arc_get_angle_start(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    uint16_t Arc::get_angle_end() const {
        return lv_arc_get_angle_end(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    uint16_t Arc::get_bg_angle_start() const {
        return lv_arc_get_bg_angle_start(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    uint16_t Arc::get_bg_angle_end() const {
        return lv_arc_get_bg_angle_end(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    int16_t Arc::get_value() const {
        return lv_arc_get_value(this->raw_ptr());
    }

    int16_t Arc::get_min_value() const {
        return lv_arc_get_min_value(this->raw_ptr());
    }

    int16_t Arc::get_max_value() const {
        return lv_arc_get_max_value(this->raw_ptr());
    }

    lv_arc_mode_t Arc::get_mode() const {
        return lv_arc_get_mode(this->raw_ptr());
    }

    void Arc::align_obj_to_angle(Object & obj_to_align, lv_coord_t r_offset) const {
        lv_arc_align_obj_to_angle(this->raw_ptr(), obj_to_align.raw_ptr(), r_offset);
    }
    
    void Arc::rotate_obj_to_angle(Object & obj_to_rotate, lv_coord_t r_offset) const {
        lv_arc_rotate_obj_to_angle(this->raw_ptr(), obj_to_rotate.raw_ptr(), r_offset);
    }
}
#endif // LV_USE_ARC