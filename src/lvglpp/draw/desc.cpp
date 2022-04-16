/** \file desc.cpp
 *  \brief Implementation file for C++ wrapper for LVGL draw descriptors.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "desc.h"
#include "../font/font.h"

namespace lvgl::draw {

    RectangleDrawDescriptor::RectangleDrawDescriptor() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
        lv_draw_rect_dsc_init(this->raw_ptr());
    }

    void RectangleDrawDescriptor::draw(lv_draw_ctx_t * draw_ctx, const Area & coords) {
        lv_draw_rect(draw_ctx, this->raw_ptr(), coords.raw_ptr());
    }


    LabelDrawDescriptor::LabelDrawDescriptor() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
        lv_draw_label_dsc_init(this->raw_ptr());
    }

    void LabelDrawDescriptor::draw(lv_draw_ctx_t * ctx, const Area & coords, const std::string & txt, lv_draw_label_hint_t * hint) {
        lv_draw_label(ctx, this->raw_ptr(), coords.raw_ptr(), txt.c_str(), hint);
    }

    void LabelDrawDescriptor::draw_letter(lv_draw_ctx_t * ctx, const lv_point_t & pos, uint32_t letter) {
        lv_draw_letter(ctx, this->raw_ptr(), &pos, letter);
    }


    ImageDrawDescriptor::ImageDrawDescriptor() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
        lv_draw_img_dsc_init(this->raw_ptr());
    }

    void ImageDrawDescriptor::draw(lv_draw_ctx_t * ctx, const Area & coords, const ImageDescriptor & img) {
        lv_draw_img(ctx, this->raw_ptr(), coords.raw_ptr(), img.raw_ptr()->data);
    }


    LineDrawDescriptor::LineDrawDescriptor() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
        lv_draw_line_dsc_init(this->raw_ptr());
    }

    void LineDrawDescriptor::draw(lv_draw_ctx_t * ctx, const lv_point_t & point1, const lv_point_t & point2) {
        lv_draw_line(ctx, this->raw_ptr(), &point1, &point2);
    }


    ArcDrawDescriptor::ArcDrawDescriptor() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
        lv_draw_arc_dsc_init(this->raw_ptr());
    }

    void ArcDrawDescriptor::draw(lv_draw_ctx_t * ctx, const lv_point_t & center, uint16_t radius,  uint16_t start_angle, uint16_t end_angle) {
        lv_draw_arc(ctx, this->raw_ptr(), &center, radius, start_angle, end_angle);
    }
    
}