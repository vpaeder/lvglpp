/** \file display.cpp
 *  \brief Implementation file for C++ wrapper for LVGL display driver.
 *  This is a base class made to connect a screen driver with LVGL.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "display.h"
#include "object.h"
#include "theme.h"
#include "../draw/image.h"

namespace lvgl::core {

    void Display::initialize() {
        this->lv_buf_1 = std::vector<lv_color_t>(this->fb_size);

        lv_disp_draw_buf_init(&(this->lv_disp_buf), this->lv_buf_1.data(), nullptr, fb_size);
        lv_disp_drv_init(&(this->lv_disp_drv));
        this->lv_disp_drv.draw_buf = &(this->lv_disp_buf);
        this->lv_disp_drv.hor_res = this->hor_res;
        this->lv_disp_drv.ver_res = this->ver_res;

        this->lv_disp = std::unique_ptr<lv_disp_t>(lv_disp_drv_register(&(this->lv_disp_drv)));
    }
    
    Display::~Display() {
        lv_disp_remove(this->raw_ptr());
    }

    void Display::set_default() {
        lv_disp_set_default(this->raw_ptr());
    }

    bool Display::is_default() const {
        return lv_disp_get_default() == this->raw_ptr();
    }

    lv_coord_t Display::get_hor_res() const {
        return lv_disp_get_hor_res(const_cast<lv_disp_t*>(this->raw_ptr()));
    }

    lv_coord_t Display::get_ver_res() const {
        return lv_disp_get_ver_res(const_cast<lv_disp_t*>(this->raw_ptr()));
    }

    lv_coord_t Display::get_physical_hor_res() const {
        return lv_disp_get_physical_hor_res(const_cast<lv_disp_t*>(this->raw_ptr()));
    }

    lv_coord_t Display::get_physical_ver_res() const {
        return lv_disp_get_physical_ver_res(const_cast<lv_disp_t*>(this->raw_ptr()));
    }

    lv_coord_t Display::get_offset_x() const {
        return lv_disp_get_offset_x(const_cast<lv_disp_t*>(this->raw_ptr()));
    }

    lv_coord_t Display::get_offset_y() const {
        return lv_disp_get_offset_y(const_cast<lv_disp_t*>(this->raw_ptr()));
    }

    bool Display::get_antialiasing() const {
        return lv_disp_get_antialiasing(const_cast<lv_disp_t*>(this->raw_ptr()));
    }

    lv_coord_t Display::get_dpi() const {
        return lv_disp_get_dpi(this->raw_ptr());
    }

    void Display::set_rotation(lv_disp_rot_t rotation) {
        lv_disp_set_rotation(this->raw_ptr(), rotation);
    }

    lv_disp_rot_t Display::get_rotation() const {
        return lv_disp_get_rotation(const_cast<lv_disp_t*>(this->raw_ptr()));
    }

    Object Display::get_scr_act() const {
        return Object(lv_disp_get_scr_act(const_cast<lv_disp_t*>(this->raw_ptr())), false);
    }

    Object Display::get_scr_prev() const {
        return Object(lv_disp_get_scr_prev(const_cast<lv_disp_t*>(this->raw_ptr())), false);
    }

    Object Display::get_layer_top() const {
        return Object(lv_disp_get_layer_top(const_cast<lv_disp_t*>(this->raw_ptr())), false);
    }

    Object Display::get_layer_sys() const {
        return Object(lv_disp_get_layer_sys(const_cast<lv_disp_t*>(this->raw_ptr())), false);
    }

    void Display::set_theme(Theme & th) {
        lv_disp_set_theme(this->raw_ptr(), th.raw_ptr());
    }

    Theme Display::get_theme() const {
        return Theme(lv_disp_get_theme(const_cast<lv_disp_t*>(this->raw_ptr())), false);
    }

    void Display::set_bg_color(lv_color_t color) {
        lv_disp_set_bg_color(this->raw_ptr(), color);
    }

    void Display::set_bg_image(const draw::ImageDescriptor & img) {
        lv_disp_set_bg_image(this->raw_ptr(), static_cast<const void*>(img.raw_ptr()));
    }

    void Display::set_bg_image(const std::string & path) {
        lv_disp_set_bg_image(this->raw_ptr(), static_cast<const void*>(path.c_str()));
    }

    void Display::set_bg_opa(lv_opa_t value) {
        lv_disp_set_bg_opa(this->raw_ptr(), value);
    }

    uint32_t Display::get_inactive_time() const {
        return lv_disp_get_inactive_time(this->raw_ptr());
    }

    void Display::trig_activity() {
        lv_disp_trig_activity(this->raw_ptr());
    }

    void Display::clean_dcache() {
        lv_disp_clean_dcache(this->raw_ptr());
    }


    void load_scr(Object & scr) {
        lv_disp_load_scr(scr.raw_ptr());
    }

    Object scr_act() {
        return Object(lv_scr_act(), false);
    }

    Object layer_top() {
        return Object(lv_layer_top(), false);
    }

    Object layer_sys() {
        return Object(lv_layer_sys(), false);
    }
}
