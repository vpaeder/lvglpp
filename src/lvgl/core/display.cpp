/** \file display.cpp
 *  \brief Implementation file for C++ wrapper for LVGL display driver.
 *  This is a base class made to connect a screen driver with LVGL.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "display.h"

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

}
