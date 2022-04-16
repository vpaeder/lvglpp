/** \file color.cpp
 *  \brief Implementation file for C++ wrapper for lv_color_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "color.h"

namespace lvgl::misc {
        Color::Color(uint8_t r, uint8_t g, uint8_t b) {
            this->lv_obj = lv_color_make(r, g, b);
        }

        Color::Color(uint32_t c) {
            this->lv_obj = lv_color_hex(c);
        }

        Color::Color(uint16_t c) {
            this->lv_obj = lv_color_hex3(c);
        }

        void Color::from_hsv(uint16_t h, uint8_t s, uint8_t v) {
            this->lv_obj = lv_color_hsv_to_rgb(h, s, v);
        }

        void Color::from_hsv(lv_color_hsv_t color_hsv) {
            this->lv_obj = lv_color_hsv_to_rgb(color_hsv.h, color_hsv.s, color_hsv.v);
        }

        uint8_t Color::to1() const {
            return lv_color_to1(this->raw());
        }

        uint8_t Color::to8() const {
            return lv_color_to8(this->raw());
        }

        uint16_t Color::to16() const {
            return lv_color_to16(this->raw());
        }

        uint32_t Color::to32() const {
            return lv_color_to32(this->raw());
        }

        uint8_t Color::brightness() const {
            return lv_color_brightness(this->raw());
        }

        lv_color_hsv_t Color::to_hsv() const {
            return lv_color_to_hsv(this->raw());
        }

        Color Color::mix(Color & c, uint8_t ratio) const {
            lv_color_t c2 = c.raw();
            lv_color_t res = lv_color_mix(this->lv_obj, c2, ratio);
            return Color(std::move(res));
        }


        ColorFilter::ColorFilter() {
            this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
            // color_filter_t has a user_data field => store 'this' pointer in it
            this->lv_obj->user_data = static_cast<void*>(this);

            this->lv_obj->filter_cb = [](const lv_color_filter_dsc_t * col_filter, lv_color_t color, lv_opa_t opa) -> lv_color_t {
                if (col_filter == nullptr) return lv_color_t{};
                auto obj = reinterpret_cast<ColorFilter*>(col_filter->user_data);
                return obj->callback(color, opa);
            };
        }
}