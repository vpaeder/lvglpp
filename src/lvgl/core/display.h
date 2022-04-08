/** \file display.h
 *  \brief Header file for C++ wrapper for LVGL display driver.
 *  This is a base class made to connect a screen driver with LVGL.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include <vector>
#include <memory>
#include "lvgl.h"

/** \namespace lvgl::core
 *  \brief LVGL core components.
 */
namespace lvgl::core {

    /** \class Display
     *  \brief Wraps a lv_disp_t object. This is a base class to connect
     *  a screen driver with LVGL.
     */
    class Display {
    protected:
        /** \property lv_disp_draw_buf_t lv_disp_buf
         *  \brief Display buffer descriptor.
         */
        lv_disp_draw_buf_t lv_disp_buf;

        /** \property lv_disp_drv_t lv_disp_drv
         *  \brief Display driver instance.
         */
        lv_disp_drv_t lv_disp_drv;

        /** \property std::unique_ptr<lv_disp_t> lv_disp
         *  \brief Pointer to the associated display instance.
         */
        std::unique_ptr<lv_disp_t> lv_disp;

        /** \property std::vector<lv_color_t> lv_buf_1
         *  \brief Display buffer.
         */
        std::vector<lv_color_t> lv_buf_1;

        /** \property uint32_t fb_size
         *  \brief Framebuffer size.
         */
        uint32_t fb_size;

        /** \property lv_coord_t hor_res
         *  \brief Horizontal resolution.
         */
        lv_coord_t hor_res;

        /** \property lv_coord_t ver_res
         *  \brief Vertical resolution.
         */
        lv_coord_t ver_res;

        /** \fn virtual void flush(lv_disp_drv_t * drv, const lv_area_t * area,  lv_color_t * color_map)
         *  \brief Callback to draw data on display.
         *  \param drv: pointer to underlying display driver.
         *  \param area: target draw area.
         *  \param color_map: data to draw.
         */
        virtual void flush(lv_disp_drv_t * drv, const lv_area_t * area,  lv_color_t * color_map) = 0;

        /** \fn virtual void initialize()
         *  \brief Initializes display driver.
         */
        virtual void initialize();
    
    public:
        /** \fn ~Display()
         *  \brief Destructor.
         */
        ~Display();

        /** \fn lv_disp_t * raw_ptr()
         *  \brief Gets a raw pointer to the associated display instance.
         *  \returns a raw pointer to the associated display instance.
         */
        lv_disp_t * raw_ptr() { return this->lv_disp.get(); }

        /** \fn const lv_disp_t * raw_ptr() const
         *  \brief Gets a raw const pointer to the associated display instance.
         *  \returns a raw const pointer to the associated display instance.
         */
        const lv_disp_t * raw_ptr() const { return this->lv_disp.get(); }

        /** \fn void set_default()
         *  \brief Sets display as default.
         */
        void set_default();

        /** \fn bool is_default() const
         *  \brief Tells if display is set as default.
         *  \returns true if display is default display, false otherwise.
         */
        bool is_default() const;

        /** \fn lv_coord_t get_hor_res() const
         *  \brief Gets horizontal display resolution.
         *  \returns horizontal resolution.
         */
        lv_coord_t get_hor_res() const;

        /** \fn lv_coord_t get_ver_res() const
         *  \brief Gets vertical display resolution.
         *  \returns vertical resolution.
         */
        lv_coord_t get_ver_res() const;

        /** \fn lv_coord_t get_physical_hor_res() const
         *  \brief Gets physical horizontal display resolution.
         *  \returns physical horizontal resolution.
         */
        lv_coord_t get_physical_hor_res() const;

        /** \fn lv_coord_t get_physical_ver_res() const
         *  \brief Gets physical vertical display resolution.
         *  \returns physical vertical resolution.
         */
        lv_coord_t get_physical_ver_res() const;

        /** \fn lv_coord_t get_offset_x() const
         *  \brief Gets horizontal offset.
         *  \returns horizontal offset.
         */
        lv_coord_t get_offset_x() const;

        /** \fn lv_coord_t get_offset_y() const
         *  \brief Gets vertical offset.
         *  \returns vertical offset.
         */
        lv_coord_t get_offset_y() const;

        /** \fn bool get_antialiasing() const
         *  \brief Tells if antialiasing is enabled.
         *  \returns true if antialiasing is enabled, false otherwise.
         */
        bool get_antialiasing() const;

        /** \fn lv_coord_t get_dpi() const
         *  \brief Gets display DPI.
         *  \returns display DPI value.
         */
        lv_coord_t get_dpi() const;

        /** \fn void set_rotation(lv_disp_rot_t rotation)
         *  \brief Sets display rotation.
         *  \param rotation: display rotation code.
         */
        void set_rotation(lv_disp_rot_t rotation);

        /** \fn lv_disp_rot_t get_rotation() const
         *  \brief Gets display rotation.
         *  \returns display rotation code.
         */
        lv_disp_rot_t get_rotation() const;
    };

}
