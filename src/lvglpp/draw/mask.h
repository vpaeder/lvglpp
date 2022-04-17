/** \file mask.h
 *  \brief Header file for C++ wrapper for image masking routines.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../lv_wrapper.h"
#include <vector>

namespace lvgl::misc {
    class Area;
}

namespace lvgl::draw {

    /** \brief Base class for mask parts.
     *  \tparam LvClass: LVGL class of mask part.
     */
    template <typename LvClass> class Mask : public PointerWrapper<LvClass, lv_mem_buf_release> {
    protected:
        /** \property int16_t id
         *  \brief Mask part index (-1 if not active, >=0 if active).
         */
        int16_t id = -1;

        /** \property void * custom_id
         *  \brief Custom part index.
         */
        void * custom_id;
    
    public:
        using PointerWrapper<LvClass,lv_mem_buf_release>::PointerWrapper;

        /** \property Mask()
         *  \brief Default constructor.
         */
        Mask() = default;

        /** \property ~Mask()
         *  \brief Destructor.
         */
        ~Mask() {
            this->remove();
        }

        /** \fn void set_id(int16_t id)
         *  \brief Sets mask part index.
         *  \param id: index value.
         */
        void set_id(int16_t id);

        /** \fn int16_t get_id() const
         *  \brief Gets mask part index.
         *  \returns index value.
         */
        int16_t get_id() const;

        /** \fn void add()
         *  \brief Makes mask part active.
         */
        void add() {
            this->add(nullptr);
        }

        /** \fn void add(void * custom_id)
         *  \brief Makes mask part active assigning custom ID.
         *  \param custom_id: a pointer to a custom ID.
         */
        void add(void * custom_id) {
            this->custom_id = custom_id;
            this->id = lv_draw_mask_add(static_cast<void*>(this->lv_obj.get()), custom_id);
        }

        /** \fn void remove()
         *  \brief Removes mask part from the list of active masks.
         */
        void remove() {
            if (this->id>=0) {
                lv_draw_mask_remove_id(this->id);
                lv_draw_mask_free_param(this->raw_ptr());
                this->id = -1;
            }
        }

        /** \fn void remove_custom()
         *  \brief Removes mask part from the list of active masks using custom ID.
         */
        void remove_custom() {
            if (this->custom_id != nullptr) {
                lv_draw_mask_remove_custom(this->custom_id);
                this->custom_id = nullptr;
                this->id = -1;
            }
        }
    };


    /** \class LineMask
     *  \brief Wraps a lv_draw_mask_line_param_t object.
     */
    class LineMask : public Mask<lv_draw_mask_line_param_t> {
    public:
        using Mask::Mask;

        /** \typedef LvClass
         *  \brief A shorthand for LVGL mask part type.
         */
        using LvClass = lv_draw_mask_line_param_t;

        /** \fn LineMask(lv_coord_t p1x, lv_coord_t p1y, lv_coord_t p2x,
         *                  lv_coord_t p2y, lv_draw_mask_line_side_t side)
         *  \brief Constructor with two points.
         *  
         *  Defines a line by two points. The area on the specified side
         *  of the line is masked.
         * 
         *  \param p1x: horizontal coordinate of first point.
         *  \param p1y: vertical coordinate of first point.
         *  \param p2x: horizontal coordinate of second point.
         *  \param p2y: vertical coordinate of second point.
         *  \param side: code for mask side.
         */
        LineMask(lv_coord_t p1x, lv_coord_t p1y, lv_coord_t p2x,
                 lv_coord_t p2y, lv_draw_mask_line_side_t side);

        /** \fn LineMask(lv_coord_t px, lv_coord_t py, int16_t angle,
         *                  lv_draw_mask_line_side_t side)
         *  \brief Constructor with pivot point and angle.
         *  
         *  Defines a line by point and angle. The area on the specified side
         *  of the line is masked.
         * 
         *  \param px: horizontal coordinate of pivot point.
         *  \param py: vertical coordinate of pivot point.
         *  \param angle: angle defining line direction.
         *  \param side: code for mask side.
         */
        LineMask(lv_coord_t px, lv_coord_t py, int16_t angle,
                 lv_draw_mask_line_side_t side);
    };


    /** \class AngleMask
     *  \brief Wraps a lv_draw_mask_angle_param_t object.
     */
    class AngleMask : public Mask<lv_draw_mask_angle_param_t> {
    public:
        using Mask::Mask;

        /** \typedef LvClass
         *  \brief A shorthand for LVGL mask part type.
         */
        using LvClass = lv_draw_mask_angle_param_t;

        /** \fn AngleMask(lv_coord_t vertex_x, lv_coord_t vertex_y,
         *                   lv_coord_t start_angle, lv_coord_t end_angle)
         *  \brief Constructor.
         *  
         *  Defines a pie section with given center vertex, in between given angles.
         * 
         *  \param vertex_x: horizontal coordinate of vertex.
         *  \param vertex_y: vertical coordinate of vertex.
         *  \param start_angle: start angle.
         *  \param end_angle: end angle.
         */
        AngleMask(lv_coord_t vertex_x, lv_coord_t vertex_y,
                  lv_coord_t start_angle, lv_coord_t end_angle);
    };


    /** \class RadiusMask
     *  \brief Wraps a lv_draw_mask_radius_param_t object.
     */
    class RadiusMask : public Mask<lv_draw_mask_radius_param_t> {
    public:
        using Mask::Mask;

        /** \typedef LvClass
         *  \brief A shorthand for LVGL mask part type.
         */
        using LvClass = lv_draw_mask_radius_param_t;

        /** \fn RadiusMask(const misc::Area & rect, lv_coord_t radius, bool inv)
         *  \brief Constructor.
         *  
         *  Defines a masked area. Given radius shrinks or expands area, depending
         *  on inv parameter.
         * 
         *  \param rect: mask area.
         *  \param radius: expansion or contraction radius.
         *  \param inv: if true, pixels outside are masked; if false, pixels inside are masked.
         */
        RadiusMask(const misc::Area & rect, lv_coord_t radius, bool inv);

        /** \fn RadiusMask(const lv_area_t & rect, lv_coord_t radius, bool inv)
         *  \brief Constructor.
         *  
         *  Defines a masked area. Given radius shrinks or expands area, depending
         *  on inv parameter.
         * 
         *  \param rect: mask area.
         *  \param radius: expansion or contraction radius.
         *  \param inv: if true, pixels outside are masked; if false, pixels inside are masked.
         */
        RadiusMask(const lv_area_t & rect, lv_coord_t radius, bool inv);
    };


    /** \class FadeMask
     *  \brief Wraps a lv_draw_mask_fade_param_t object.
     */
    class FadeMask : public Mask<lv_draw_mask_fade_param_t> {
    public:
        using Mask::Mask;

        /** \typedef LvClass
         *  \brief A shorthand for LVGL mask part type.
         */
        using LvClass = lv_draw_mask_fade_param_t;

        /** \fn FadeMask(const misc::Area & coords, lv_opa_t opa_top, lv_coord_t y_top,
         *                  lv_opa_t opa_bottom, lv_coord_t y_bottom);
         *  \brief Constructor.
         *  
         *  Defines a masked area with vertical gradient.
         * 
         *  \param coords: mask area.
         *  \param opa_top: mask opacity on top.
         *  \param y_top: top position.
         *  \param opa_bottom: mask opacity at bottom.
         *  \param y_bottom: bottom position.
         */
        FadeMask(const misc::Area & coords, lv_opa_t opa_top, lv_coord_t y_top,
                 lv_opa_t opa_bottom, lv_coord_t y_bottom);

        /** \fn FadeMask(const lv_area_t & coords, lv_opa_t opa_top, lv_coord_t y_top,
         *                  lv_opa_t opa_bottom, lv_coord_t y_bottom);
         *  \brief Constructor.
         *  
         *  Defines a masked area with vertical gradient.
         * 
         *  \param coords: mask area.
         *  \param opa_top: mask opacity on top.
         *  \param y_top: top position.
         *  \param opa_bottom: mask opacity at bottom.
         *  \param y_bottom: bottom position.
         */
        FadeMask(const lv_area_t & coords, lv_opa_t opa_top, lv_coord_t y_top,
                 lv_opa_t opa_bottom, lv_coord_t y_bottom);
    };


    /** \class MapMask
     *  \brief Wraps a lv_draw_mask_map_param_t object.
     */
    class MapMask : public Mask<lv_draw_mask_map_param_t> {
    public:
        using Mask::Mask;

        /** \typedef LvClass
         *  \brief A shorthand for LVGL mask part type.
         */
        using LvClass = lv_draw_mask_map_param_t;

        /** \fn MapMask(const misc::Area & coords, const std::vector<lv_opa_t> & map)
         *  \brief Constructor.
         *  
         *  Defines a masked area from an opacity map.
         * 
         *  \param coords: mask area.
         *  \param map: opacity values for each pixel of the masked area.
         */
        MapMask(const misc::Area & coords, const std::vector<lv_opa_t> & map);

        /** \fn MapMask(const lv_area_t & coords, const std::vector<lv_opa_t> & map)
         *  \brief Constructor.
         *  
         *  Defines a masked area from an opacity map.
         * 
         *  \param coords: mask area.
         *  \param map: opacity values for each pixel of the masked area.
         */
        MapMask(const lv_area_t & coords, const std::vector<lv_opa_t> & map);
    };


    /** \class PolygonMask
     *  \brief Wraps a lv_draw_mask_polygon_param_t object.
     */
    class PolygonMask : public Mask<lv_draw_mask_polygon_param_t> {
    public:
        using Mask::Mask;

        /** \typedef LvClass
         *  \brief A shorthand for LVGL mask part type.
         */
        using LvClass = lv_draw_mask_polygon_param_t;

        /** \fn PolygonMask(const std::vector<lv_point_t> & points)
         *  \brief Constructor.
         *  
         *  Defines a masked area from a polygon.
         * 
         *  \param points: polygon vertices.
         */
        PolygonMask(const std::vector<lv_point_t> & points);
    };


    /** \namespace lvgl::draw::mask
     *  \brief Contains general mask functions.
     */
    namespace mask {

        /** \fn uint8_t get_count()
         *  \brief Gets the number of active mask parts.
         */
        uint8_t get_count();

        /** \fn bool has_any(const misc::Area & a)
         *  \brief Tells if given area is covered by any mask.
         *  \param a: area to test.
         *  \returns true if area is covered by at least one mask, false otherwise.
         */
        bool has_any(const misc::Area & a);

        /** \fn bool has_any(const lv_area_t & a)
         *  \brief Tells if given area is covered by any mask.
         *  \param a: area to test.
         *  \returns true if area is covered by at least one mask, false otherwise.
         */
        bool has_any(const lv_area_t & a);

    }

}
