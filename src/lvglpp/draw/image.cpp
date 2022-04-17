/** \file image.cpp
 *  \brief Implementation file for C++ wrapper for low-level image-handling
 *  LVGL objects, such as lv_img_decoder_dsc_t, lv_img_header_t and lv_img_dsc_t.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "image.h"

namespace lvgl::draw {
    
    ImageDecoder::ImageDecoder(const ImageDescriptor & src, lv_color_t color, int32_t frame_id) {
        lv_img_decoder_open(this->raw_ptr(), src.raw_ptr(), color, frame_id);
    }

    ImageDecoder::ImageDecoder(const std::string & src, lv_color_t color, int32_t frame_id) {
        lv_img_decoder_open(this->raw_ptr(), src.c_str(), color, frame_id);
    }

    ImageHeader ImageDecoder::get_info(const ImageDescriptor & src) {
        auto header = ImageHeader(lv_cls_alloc<lv_img_header_t>());
        auto res = lv_img_decoder_get_info(src.raw_ptr(), header.raw_ptr());
        header.is_valid(res == LV_RES_OK);
        return header;
    }

    ImageHeader ImageDecoder::get_info(const std::string & src) {
        auto header = ImageHeader(lv_cls_alloc<lv_img_header_t>());
        auto res = lv_img_decoder_get_info(src.c_str(), header.raw_ptr());
        header.is_valid(res == LV_RES_OK);
        return header;
    }

    lv_res_t ImageDecoder::read_line(lv_coord_t x, lv_coord_t y, lv_coord_t len, std::vector<uint8_t> & buf) {
        return lv_img_decoder_read_line(this->raw_ptr(), x, y, len, buf.data());
    }

    void ImageDecoder::close() {
        lv_img_decoder_close(this->raw_ptr());
    }


    bool ImageHeader::is_valid() const {
        return this->valid;
    }

    void ImageHeader::is_valid(bool valid) {
        this->valid = valid;
    }


    ImageDescriptor::ImageDescriptor() {
        this->lv_obj = LvPointer<lv_img_dsc_t, lv_img_buf_free>(lv_cls_alloc<lv_img_dsc_t>());
    }

    ImageDescriptor::ImageDescriptor(lv_coord_t w, lv_coord_t h, lv_img_cf_t cf) {
        this->lv_obj = LvPointer<lv_img_dsc_t, lv_img_buf_free>(lv_img_buf_alloc(w, h, cf));
    }

    lv_color_t ImageDescriptor::get_px_color(lv_coord_t x, lv_coord_t y, lv_color_t bg_color) const {
        return lv_img_buf_get_px_color(const_cast<lv_cls_ptr>(this->raw_ptr()), x, y, bg_color);
    }

    lv_opa_t ImageDescriptor::get_px_alpha(lv_coord_t x, lv_coord_t y) const {
        return lv_img_buf_get_px_alpha(const_cast<lv_cls_ptr>(this->raw_ptr()), x, y);
    }

    void ImageDescriptor::set_px_color(lv_coord_t x, lv_coord_t y, lv_color_t c) {
        lv_img_buf_set_px_color(this->raw_ptr(), x, y, c);
    }
    
    void ImageDescriptor::set_px_alpha(lv_coord_t x, lv_coord_t y, lv_opa_t opa) {
        lv_img_buf_set_px_alpha(this->raw_ptr(), x, y, opa);
    }

    void ImageDescriptor::set_palette(uint8_t id, lv_color_t c) {
        lv_img_buf_set_palette(this->raw_ptr(), id, c);
    }

    uint32_t ImageDescriptor::get_img_size(lv_coord_t w, lv_coord_t h, lv_img_cf_t cf) const {
        return lv_img_buf_get_img_size(w, h, cf);
    }

    void ImageDescriptor::set_src(const std::vector<uint8_t> & src, uint32_t w, uint32_t h, lv_img_cf_t cf) {
        this->raw_ptr()->data = src.data();
        this->raw_ptr()->data_size = src.size();
        this->raw_ptr()->header.w = w;
        this->raw_ptr()->header.h = h;
        this->raw_ptr()->header.cf = cf;
    }

    void ImageDescriptor::set_src(const uint8_t * src, uint32_t w, uint32_t h, lv_img_cf_t cf) {
        this->raw_ptr()->data = src;
        this->raw_ptr()->data_size = lv_img_buf_get_img_size(w, h, cf);
        this->raw_ptr()->header.w = w;
        this->raw_ptr()->header.h = h;
        this->raw_ptr()->header.cf = cf;
    }
    
}