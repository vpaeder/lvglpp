/** \file line.cpp
 *  \brief Implementation file for C++ wrapper for lv_line_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "line.h"
#if LV_USE_LINE != 0

namespace lvgl::widgets {

    void Line::set_points(const std::vector<lv_point_t> & points) {
        lv_line_set_points(this->raw_ptr(), points.data(), points.size());
    }

    void Line::set_y_invert(bool en) {
        lv_line_set_y_invert(this->raw_ptr(), en);
    }

    bool Line::get_y_invert() const {
        return lv_line_get_y_invert(this->raw_ptr());
    }

}
#endif // LV_USE_LINE