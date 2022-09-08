/** \file canvas.cpp
 *  \brief Implementation file for C++ wrapper for lv_canvas_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "canvas.h"
#if LV_USE_CANVAS != 0

#include "../../misc/area.h"
#include "../../draw/desc.h"

namespace lvgl::widgets {

    void Canvas::set_px_color(lv_coord_t x, lv_coord_t y, lv_color_t c) {
        lv_canvas_set_px_color(this->raw_ptr(), x, y, c);
    }

    void Canvas::set_px_opa(lv_coord_t x, lv_coord_t y, lv_opa_t opa) {
        lv_canvas_set_px_opa(this->raw_ptr(), x, y, opa);
    }

    void Canvas::set_palette(uint8_t id, lv_color_t c) {
        lv_canvas_set_palette(this->raw_ptr(), id, c);
    }

    lv_color_t Canvas::get_px(lv_coord_t x, lv_coord_t y) const {
        return lv_canvas_get_px(const_cast<lv_cls_ptr>(this->raw_ptr()), x, y);
    }

    std::shared_ptr<lv_img_dsc_t> Canvas::get_img() const {
        return std::shared_ptr<lv_img_dsc_t>(
            lv_canvas_get_img(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

    void Canvas::copy_buf(const std::shared_ptr<void> to_copy, lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h) {
        lv_canvas_copy_buf(this->raw_ptr(), to_copy.get(), x, y, w, h);
    }

    void Canvas::transform(int16_t angle, uint16_t zoom, lv_coord_t offset_x, lv_coord_t offset_y, int32_t pivot_x, int32_t pivot_y, bool antialias) {
        lv_canvas_transform(this->raw_ptr(), this->get_img().get(), angle, zoom, offset_x, offset_y, pivot_x, pivot_y, antialias);
    }

    void Canvas::blur_hor(uint16_t r) {
        lv_canvas_blur_hor(this->raw_ptr(), nullptr, r);
    }

    void Canvas::blur_hor(const Area & area, uint16_t r) {
        lv_canvas_blur_hor(this->raw_ptr(), area.raw_ptr(), r);
    }

    void Canvas::blur_ver(uint16_t r) {
        lv_canvas_blur_ver(this->raw_ptr(), nullptr, r);
    }

    void Canvas::blur_ver(const Area & area, uint16_t r) {
        lv_canvas_blur_ver(this->raw_ptr(), area.raw_ptr(), r);
    }

    void Canvas::fill_bg(const lv_color_t & color, lv_opa_t opa) {
        lv_canvas_fill_bg(this->raw_ptr(), color, opa);
    }

    void Canvas::draw_rect(lv_coord_t x, lv_coord_t y, lv_coord_t w, lv_coord_t h, const RectangleDrawDescriptor & draw_dsc) {
        lv_canvas_draw_rect(this->raw_ptr(), x, y, w, h, draw_dsc.raw_ptr());
    }

    void Canvas::draw_text(lv_coord_t x, lv_coord_t y, lv_coord_t max_w, LabelDrawDescriptor & draw_dsc, const std::string & txt) {
        lv_canvas_draw_text(this->raw_ptr(), x, y, max_w, draw_dsc.raw_ptr(), txt.c_str());
    }

    void Canvas::draw_img(lv_coord_t x, lv_coord_t y, const void * src, const ImageDrawDescriptor & draw_dsc) {
        lv_canvas_draw_img(this->raw_ptr(), x, y, src, draw_dsc.raw_ptr());
    }

    void Canvas::draw_line(const std::vector<lv_point_t> & points, uint32_t point_cnt, const LineDrawDescriptor & draw_dsc) {
        lv_canvas_draw_line(this->raw_ptr(), points.data(), point_cnt, draw_dsc.raw_ptr());
    }

    void Canvas::draw_polygon(const std::vector<lv_point_t> & points, uint32_t point_cnt, const RectangleDrawDescriptor & draw_dsc) {
        lv_canvas_draw_polygon(this->raw_ptr(), points.data(), point_cnt, draw_dsc.raw_ptr());
    }

    void Canvas::draw_arc(lv_coord_t x, lv_coord_t y, lv_coord_t r, int32_t start_angle, int32_t end_angle, const ArcDrawDescriptor & draw_dsc) {
        lv_canvas_draw_arc(this->raw_ptr(), x, y, r, start_angle, end_angle, draw_dsc.raw_ptr());
    }

}
#endif // LV_USE_CANVAS