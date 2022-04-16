/** \file area.cpp
 *  \brief Implementation file for C++ wrapper for lv_area_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "area.h"

namespace lvgl::misc {
    Area::Area() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
    }

    Area::Area(const lv_area_t & obj) : LvWrapperType() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
        lv_area_copy(this->raw_ptr(), &obj);
    }

    Area::Area(const Area & obj) : LvWrapperType() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
        lv_area_copy(this->raw_ptr(), obj.raw_ptr());
    }

    lv_coord_t Area::get_width() const {
        return lv_area_get_width(this->raw_ptr());
    }

    lv_coord_t Area::get_height() const {
        return lv_area_get_height(this->raw_ptr());
    }

    lv_coord_t Area::get_pos_x() const {
        return this->raw().x1;
    }

    lv_coord_t Area::get_pos_y() const {
        return this->raw().y1;
    }

    void Area::set_width(lv_coord_t w) {
        lv_area_set_width(this->raw_ptr(), w);
    }

    void Area::set_height(lv_coord_t h) {
        lv_area_set_height(this->raw_ptr(), h);
    }

    void Area::set_pos(lv_coord_t x, lv_coord_t y) {
        _lv_area_set_pos(this->raw_ptr(), x, y);
    }

    uint32_t Area::get_size() {
        return lv_area_get_size(this->raw_ptr());
    }

    void Area::increase(lv_coord_t w_extra, lv_coord_t h_extra) {
        lv_area_increase(this->raw_ptr(), w_extra, h_extra);
    }

    void Area::move(lv_coord_t x_ofs, lv_coord_t y_ofs) {
        lv_area_move(this->raw_ptr(), x_ofs, y_ofs);
    }

    Area Area::intersect_with(const Area & ar) {
        Area res;
        _lv_area_intersect(res.raw_ptr(), this->raw_ptr(), ar.raw_ptr());
        return res;
    }

    Area Area::join_with(const Area & ar) {
        Area res;
        _lv_area_join(res.raw_ptr(), this->raw_ptr(), ar.raw_ptr());
        return res;
    }

    bool Area::is_point_on(const lv_point_t & pt, lv_coord_t radius) {
        return _lv_area_is_point_on(this->raw_ptr(), &pt, radius);
    }

    bool Area::is_on(const Area & ar) {
        return _lv_area_is_on(this->raw_ptr(), ar.raw_ptr());
    }

    bool Area::is_in(const Area & ar, lv_coord_t radius) {
        return _lv_area_is_in(this->raw_ptr(), ar.raw_ptr(), radius);
    }

    bool Area::is_out(const Area & ar, lv_coord_t radius) {
        return _lv_area_is_out(this->raw_ptr(), ar.raw_ptr(), radius);
    }

    bool Area::is_equal(const Area & ar) {
        return _lv_area_is_equal(this->raw_ptr(), ar.raw_ptr());
    }


    void Area::align_to(const Area & ar, lv_align_t align, lv_coord_t ofs_x, lv_coord_t ofs_y) {
        lv_area_align(ar.raw_ptr(), this->raw_ptr(), align, ofs_x, ofs_y);
    }

}