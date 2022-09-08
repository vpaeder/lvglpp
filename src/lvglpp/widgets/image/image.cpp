/** \file image.cpp
 *  \brief Implementation file for C++ wrapper for lv_img_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "image.h"

#if LV_USE_IMG != 0

#include "../../draw/image.h"

namespace lvgl::widgets {

    void Image::set_src(const ImageDescriptor & src) {
        lv_img_set_src(this->raw_ptr(), src.raw_ptr());
    }

    void Image::set_src(const std::string & src) {
        lv_img_set_src(this->raw_ptr(), src.c_str());
    }

    void Image::set_offset_x(lv_coord_t x) {
        lv_img_set_offset_x(this->raw_ptr(), x);
    }

    void Image::set_offset_y(lv_coord_t y) {
        lv_img_set_offset_y(this->raw_ptr(), y);
    }

    void Image::set_angle(int16_t angle) {
        lv_img_set_angle(this->raw_ptr(), angle);
    }

    void Image::set_pivot(lv_coord_t x, lv_coord_t y) {
        lv_img_set_pivot(this->raw_ptr(), x, y);
    }

    void Image::set_zoom(uint16_t zoom) {
        lv_img_set_zoom(this->raw_ptr(), zoom);
    }

    void Image::set_antialias(bool antialias) {
        lv_img_set_antialias(this->raw_ptr(), antialias);
    }

    void Image::set_size_mode(lv_img_size_mode_t mode) {
        lv_img_set_size_mode(this->raw_ptr(), mode);
    }

    lv_img_src_t Image::get_src_type() const {
        return lv_img_src_get_type(lv_img_get_src(const_cast<lv_obj_t*>(this->raw_ptr())));
    }

    const ImageDescriptor Image::get_src_img() const {
        assert(this->get_src_type() == LV_IMG_SRC_VARIABLE);
        return ImageDescriptor(
            const_cast<lv_img_dsc_t*>(reinterpret_cast<const lv_img_dsc_t*>(
                lv_img_get_src(const_cast<lv_obj_t*>(this->raw_ptr()))
            ))
        );
    }

    const std::string Image::get_src_str() const {
        auto src_type = this->get_src_type();
        assert(src_type == LV_IMG_SRC_FILE || src_type == LV_IMG_SRC_SYMBOL);
        return std::string(
            const_cast<char*>(reinterpret_cast<const char*>(
                lv_img_get_src(const_cast<lv_obj_t*>(this->raw_ptr()))
            ))
        );
    }

    lv_coord_t Image::get_offset_x() const {
        return lv_img_get_offset_x(const_cast<lv_obj_t*>(this->raw_ptr()));
    }

    lv_coord_t Image::get_offset_y() const {
        return lv_img_get_offset_y(const_cast<lv_obj_t*>(this->raw_ptr()));
    }

    uint16_t Image::get_angle() const {
        return lv_img_get_angle(const_cast<lv_obj_t*>(this->raw_ptr()));
    }

    lv_point_t Image::get_pivot() const {
        lv_point_t pivot;
        lv_img_get_pivot(const_cast<lv_obj_t*>(this->raw_ptr()), &pivot);
        return pivot;
    }

    uint16_t Image::get_zoom() const {
        return lv_img_get_zoom(const_cast<lv_obj_t*>(this->raw_ptr()));
    }

    bool Image::get_antialias() const {
        return lv_img_get_antialias(const_cast<lv_obj_t*>(this->raw_ptr()));
    }

    lv_img_size_mode_t Image::get_size_mode() const {
        return lv_img_get_size_mode(const_cast<lv_obj_t*>(this->raw_ptr()));
    }

}
#endif // LV_USE_IMG