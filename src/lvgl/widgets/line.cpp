/** \file line.cpp
 *  \brief Implementation file for C++ wrapper for lv_line_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "line.h"

namespace lvgl::widgets {

    Line::Line() {
        this->initialize();
    }

    Line::Line(Object & parent) {
        this->initialize(parent);
    }

    void Line::initialize() {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_line_create(nullptr));
    }
    void Line::initialize(Object & parent) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_line_create(parent.raw_ptr()));
    }

    void Line::set_points(const std::vector<lv_point_t> & points, uint16_t point_num) {
        lv_line_set_points(this->raw_ptr(), points.data(), point_num);
    }

    void Line::set_y_invert(bool en) {
        lv_line_set_y_invert(this->raw_ptr(), en);
    }

    bool Line::get_y_invert() const {
        return lv_line_get_y_invert(this->raw_ptr());
    }

}