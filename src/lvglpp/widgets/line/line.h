/** \file line.h
 *  \brief Header file for C++ wrapper for lv_line_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_LINE != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Line
     *  \brief Wraps a lv_line_t object.
     */
    class Line : public Widget<lv_line_create> {
    public:
        using Widget::Widget;

        /** \fn void set_points(const std::vector<lv_point_t> points)
         *  \brief Sets line points. Points array must remain allocated.
         *  \param points: array of points.
         */
        void set_points(const std::vector<lv_point_t> & points);

        /** \fn void set_y_invert(bool en)
         *  \brief Sets vertical inversion.
         *  \param en: if true, vertical inversion is enabled.
         */
        void set_y_invert(bool en);

        /** \fn bool get_y_invert() const
         *  \brief Tells if vertical inversion is enabled.
         *  \returns true if vertical inversion is enabled, false otherwise.
         */
        bool get_y_invert() const;
    };

}
#endif // LV_USE_LINE