/** \file color.cpp
 *  \brief Implementation file for C++ wrapper for lv_color_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "color.h"

namespace lvgl::misc {

        namespace color {
            lv_color_t from_rgb(uint8_t r, uint8_t g, uint8_t b) {
                return lv_color_make(r, g, b);
            }

            lv_color_t from_hex(uint32_t c) {
                return lv_color_hex(c);
            }

            lv_color_t from_hex3(uint16_t c) {
                return lv_color_hex3(c);
            }

            lv_color_t from_hsv(uint16_t h, uint8_t s, uint8_t v) {
                return lv_color_hsv_to_rgb(h, s, v);
            }

            lv_color_t from_hsv(lv_color_hsv_t color_hsv) {
                return lv_color_hsv_to_rgb(color_hsv.h, color_hsv.s, color_hsv.v);
            }

            inline uint8_t to1(lv_color_t color) {
                return lv_color_to1(color);
            }

            inline uint8_t to8(lv_color_t color) {
                return lv_color_to8(color);
            }

            inline uint16_t to16(lv_color_t color) {
                return lv_color_to16(color);
            }

            inline uint32_t to32(lv_color_t color) {
                return lv_color_to32(color);
            }

            uint8_t brightness(lv_color_t color) {
                return lv_color_brightness(color);
            }

            lv_color_hsv_t to_hsv(lv_color_t color) {
                return lv_color_to_hsv(color);
            }

            lv_color_t mix(lv_color_t c1, lv_color_t c2, uint8_t ratio) {
                return lv_color_mix(c1, c2, ratio);
            }

            lv_color_t lighten(lv_color_t color, lv_opa_t lvl) {
                return lv_color_lighten(color, lvl);
            }

            lv_color_t darken(lv_color_t color, lv_opa_t lvl) {
                return lv_color_darken(color, lvl);
            }

            lv_color_t change_lightness(lv_color_t color, lv_opa_t lvl) {
                return lv_color_change_lightness(color, lvl);
            }
        }

        namespace palette {
            lv_color_t main(Color p) {
                return lv_palette_main(static_cast<lv_palette_t>(p));
            }

            lv_color_t light(Color p, uint8_t lvl) {
                return lv_palette_lighten(static_cast<lv_palette_t>(p), lvl);
            }

            lv_color_t dark(Color p, uint8_t lvl) {
                return lv_palette_darken(static_cast<lv_palette_t>(p), lvl);
            }

            lv_color_t white() {
                return lv_color_white();
            }
            
            lv_color_t black() {
                return lv_color_black();
            }
        }

#if LV_USE_USER_DATA
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
#endif // LV_USE_USER_DATA        
}