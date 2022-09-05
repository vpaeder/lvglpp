/** \file colorwheel.cpp
 *  \brief Implementation file for C++ wrapper for lv_colorwheel_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "colorwheel.h"
#if LV_USE_COLORWHEEL

namespace lvgl::widgets {

    ColorWheel::ColorWheel() {
        this->initialize();
    }

    ColorWheel::ColorWheel(Object & parent) {
        this->initialize(parent);
    }

    ColorWheel::ColorWheel(bool knob_recolor) {
        this->initialize(knob_recolor);
    }

    ColorWheel::ColorWheel(Object & parent, bool knob_recolor) {
        this->initialize(parent, knob_recolor);
    }

    void ColorWheel::initialize() {
        this->initialize(false);
    }

    void ColorWheel::initialize(Object & parent) {
        this->initialize(parent);
    }

    void ColorWheel::initialize(bool knob_recolor) {
        this->lv_obj = LvPointerType(lv_colorwheel_create(nullptr, knob_recolor));
    }

    void ColorWheel::initialize(Object & parent, bool knob_recolor) {
        this->lv_obj = LvPointerType(lv_colorwheel_create(parent.raw_ptr(), knob_recolor));
    }

    bool ColorWheel::set_hsv(lv_color_hsv_t hsv) {
        return lv_colorwheel_set_hsv(this->raw_ptr(), hsv);
    }

    bool ColorWheel::set_rgb(lv_color_t color) {
        return lv_colorwheel_set_rgb(this->raw_ptr(), color);
    }

    void ColorWheel::set_mode(lv_colorwheel_mode_t mode) {
        lv_colorwheel_set_mode(this->raw_ptr(), mode);
    }

    void ColorWheel::set_mode_fixed(bool fixed) {
        lv_colorwheel_set_mode_fixed(this->raw_ptr(), fixed);
    }

    lv_color_hsv_t ColorWheel::get_hsv() const {
        return lv_colorwheel_get_hsv(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_color_t ColorWheel::get_rgb() const {
        return lv_colorwheel_get_rgb(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_colorwheel_mode_t ColorWheel::get_color_mode() const {
        return lv_colorwheel_get_color_mode(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    bool ColorWheel::get_color_mode_fixed() const {
        return lv_colorwheel_get_color_mode_fixed(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

}
#endif // LV_USE_COLORWHEEL