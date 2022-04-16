/** \file mask.cpp
 *  \brief Implementation file for C++ wrapper for image masking routines.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "mask.h"
#include "../misc/area.h"

namespace lvgl::draw {

    LineMask::LineMask(lv_coord_t p1x, lv_coord_t p1y, lv_coord_t p2x,
                       lv_coord_t p2y, lv_draw_mask_line_side_t side) {
        this->lv_obj = LvPointerType(static_cast<LvClass*>(lv_mem_buf_get(sizeof(LvClass))));
        lv_draw_mask_line_points_init(this->lv_obj.get(), p1x, p1y, p2x, p2y, side);
    }

    LineMask::LineMask(lv_coord_t px, lv_coord_t py, int16_t angle,
                       lv_draw_mask_line_side_t side) {
        this->lv_obj = LvPointerType(static_cast<LvClass*>(lv_mem_buf_get(sizeof(LvClass))));
        lv_draw_mask_line_angle_init(this->lv_obj.get(), px, py, angle, side);
    }


    AngleMask::AngleMask(lv_coord_t vertex_x, lv_coord_t vertex_y,
                         lv_coord_t start_angle, lv_coord_t end_angle) {
        this->lv_obj = LvPointerType(static_cast<LvClass*>(lv_mem_buf_get(sizeof(LvClass))));
        lv_draw_mask_angle_init(this->lv_obj.get(), vertex_x, vertex_y, start_angle, end_angle);
    }
    

    RadiusMask::RadiusMask(const misc::Area & rect, lv_coord_t radius, bool inv) {
        this->lv_obj = LvPointerType(static_cast<LvClass*>(lv_mem_buf_get(sizeof(LvClass))));
        lv_draw_mask_radius_init(this->lv_obj.get(), rect.raw_ptr(), radius, inv);
    }

    RadiusMask::RadiusMask(const lv_area_t & rect, lv_coord_t radius, bool inv) {
        this->lv_obj = LvPointerType(static_cast<LvClass*>(lv_mem_buf_get(sizeof(LvClass))));
        lv_draw_mask_radius_init(this->lv_obj.get(), &rect, radius, inv);
    }


    FadeMask::FadeMask(const misc::Area & coords, lv_opa_t opa_top, lv_coord_t y_top,
                       lv_opa_t opa_bottom, lv_coord_t y_bottom) {
        this->lv_obj = LvPointerType(static_cast<LvClass*>(lv_mem_buf_get(sizeof(LvClass))));
        lv_draw_mask_fade_init(this->lv_obj.get(), coords.raw_ptr(), opa_top, y_top, opa_bottom, y_bottom);
    }

    FadeMask::FadeMask(const lv_area_t & coords, lv_opa_t opa_top, lv_coord_t y_top,
                       lv_opa_t opa_bottom, lv_coord_t y_bottom) {
        this->lv_obj = LvPointerType(static_cast<LvClass*>(lv_mem_buf_get(sizeof(LvClass))));
        lv_draw_mask_fade_init(this->lv_obj.get(), &coords, opa_top, y_top, opa_bottom, y_bottom);
    }


    MapMask::MapMask(const misc::Area & coords, const std::vector<lv_opa_t> & map) {
        this->lv_obj = LvPointerType(static_cast<LvClass*>(lv_mem_buf_get(sizeof(LvClass))));
        lv_draw_mask_map_init(this->lv_obj.get(), coords.raw_ptr(), map.data());
    }

    MapMask::MapMask(const lv_area_t & coords, const std::vector<lv_opa_t> & map) {
        this->lv_obj = LvPointerType(static_cast<LvClass*>(lv_mem_buf_get(sizeof(LvClass))));
        lv_draw_mask_map_init(this->lv_obj.get(), &coords, map.data());
    }


    PolygonMask::PolygonMask(const std::vector<lv_point_t> & points) {
        this->lv_obj = LvPointerType(static_cast<LvClass*>(lv_mem_buf_get(sizeof(LvClass))));
        lv_draw_mask_polygon_init(this->lv_obj.get(), points.data(), points.size());
    }
        

    namespace mask {
        uint8_t get_count() {
            return lv_draw_mask_get_cnt();
        }

        bool has_any(const misc::Area & a) {
            return lv_draw_mask_is_any(a.raw_ptr());
        }

        bool has_any(const lv_area_t & a) {
            return lv_draw_mask_is_any(&a);
        }
    }

}
