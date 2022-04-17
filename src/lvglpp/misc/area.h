/** \file area.h
 *  \brief Header file for C++ wrapper for lv_area_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../lv_wrapper.h"

namespace lvgl::misc {

    /** \class Area
     *  \brief Wraps a lv_area_t object. This represents a surface area.
     */
    class Area : public PointerWrapper<lv_area_t, lv_mem_free> {
    public:
        using PointerWrapper::PointerWrapper;

        /** \fn Area()
         *  \brief Default constructor.
         */
        Area();

        /** \fn Area(const lv_area_t & obj)
         *  \brief Copy constructor with lv_area_t object.
         *  \param obj: lv_area_t object.
         */
        Area(const lv_area_t & obj);
        /** \fn Area(const Area & obj)
         *  \brief Copy constructor with Area object.
         *  \param obj: Area object.
         */
        Area(const Area & obj);

        /** \fn void set(lv_coord_t x1, lv_coord_t y1, lv_coord_t x2, lv_coord_t y2)
         *  \brief Sets area coordinates.
         *  \param x1: left coordinate.
         *  \param y1: top coordinate.
         *  \param x2: right coordinate.
         *  \param y2: bottom coordinate.
         */
        void set(lv_coord_t x1, lv_coord_t y1, lv_coord_t x2, lv_coord_t y2);

        /** \fn lv_coord_t get_width() const
         *  \brief Gets area width.
         *  \returns area width.
         */
        lv_coord_t get_width() const;

        /** \fn lv_coord_t get_height() const
         *  \brief Gets area height.
         *  \returns area height.
         */
        lv_coord_t get_height() const;

        /** \fn lv_coord_t get_pos_x() const
         *  \brief Gets horizontal position.
         *  \returns horizontal position.
         */
        lv_coord_t get_pos_x() const;

        /** \fn lv_coord_t get_pos_y() const
         *  \brief Gets vertical position.
         *  \returns vertical position.
         */
        lv_coord_t get_pos_y() const;

        /** \fn void set_width(lv_coord_t w)
         *  \brief Sets area width.
         *  \param w: area width.
         */
        void set_width(lv_coord_t w);

        /** \fn void set_height(lv_coord_t h)
         *  \brief Sets area height.
         *  \param h: area height.
         */
        void set_height(lv_coord_t h);

        /** \fn void set_pos(lv_coord_t x, lv_coord_t y)
         *  \brief Sets area top left coordinates.
         *  \param x: left coordinate.
         *  \param y: top coordinate.
         */
        void set_pos(lv_coord_t x, lv_coord_t y);

        /** \fn uint32_t get_size()
         *  \brief Gets area surface.
         *  \returns area surface.
         */
        uint32_t get_size();

        /** \fn void increase(lv_coord_t w_extra, lv_coord_t h_extra)
         *  \brief Extends area by given amounts.
         *  \param w_extra: horizontal amount.
         *  \param h_extra: vertical amount.
         */
        void increase(lv_coord_t w_extra, lv_coord_t h_extra);

        /** \fn void move(lv_coord_t x_ofs, lv_coord_t y_ofs)
         *  \brief Moves area by given offsets.
         *  \param x_ofs: horizontal offset.
         *  \param y_ofs: vertical offset.
         */
        void move(lv_coord_t x_ofs, lv_coord_t y_ofs);

        /** \fn Area intersect_with(const Area & ar)
         *  \brief Intersects area with another.
         *  \param ar: other area.
         *  \returns intersection of both areas.
         */
        Area intersect_with(const Area & ar);

        /** \fn Area join_with(const Area & ar)
         *  \brief Joins area with another.
         *  \param ar: other area.
         *  \returns union of both areas.
         */
        Area join_with(const Area & ar);

        /** \fn bool is_point_on(const lv_point_t & pt, lv_coord_t radius)
         *  \brief Tells if point is within area.
         *  \param pt: point.
         *  \param radius: radius of area corners.
         *  \returns true if point is within area, false otherwise.
         */
        bool is_point_on(const lv_point_t & pt, lv_coord_t radius);

        /** \fn bool is_on(const Area & ar)
         *  \brief Tells if given area is on area.
         *  \param ar: other area.
         *  \returns true if other area is within area, false otherwise.
         */
        bool is_on(const Area & ar);

        /** \fn bool is_in(const Area & ar, lv_coord_t radius)
         *  \brief Tells if given area is included in area.
         *  \param ar: other area.
         *  \param radius: radius of area corners.
         *  \returns true if given area is within area, false otherwise.
         */
        bool is_in(const Area & ar, lv_coord_t radius);

        /** \fn bool is_out(const Area & ar)
         *  \brief Tells if given area is outside area.
         *  \param ar: other area.
         *  \param radius: radius of area corners.
         *  \returns true if given area is outside area, false otherwise.
         */
        bool is_out(const Area & ar, lv_coord_t radius);

        /** \fn bool is_equal(const Area & ar)
         *  \brief Tells if areas are identical.
         *  \param ar: other area.
         *  \returns true if given area is the identical, false otherwise.
         */
        bool is_equal(const Area & ar);

        /** \fn void align_to(const Area & ar, lv_align_t align, lv_coord_t ofs_x, lv_coord_t ofs_y)
         *  \brief Aligns area to given area with given parameters.
         *  \param ar: area to align to.
         *  \param align: alignment mode.
         *  \param ofs_x: horizontal offset.
         *  \param ofs_y: vertical offset.
         */
        void align_to(const Area & ar, lv_align_t align, lv_coord_t ofs_x, lv_coord_t ofs_y);
    };


}
