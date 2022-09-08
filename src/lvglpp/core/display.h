/** \file display.h
 *  \brief Header file for C++ wrapper for LVGL display driver.
 *  This is a base class made to connect a screen driver with LVGL.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../lv_wrapper.h"
#include <vector>

// we need user_data to store pointer to C++ object, otherwise we cannot
// access callbacks defined as class members.
#if LV_USE_USER_DATA

namespace lvgl::draw { class ImageDescriptor; }

/** \namespace lvgl::core
 *  \brief LVGL core components.
 */
namespace lvgl::core {

    class Object;
    class Theme;

    /** \class Display
     *  \brief Wraps a lv_disp_t object. This is a base class to connect
     *  a screen driver with LVGL.
     */
    class Display : public PointerWrapper<lv_disp_t, lv_disp_remove> {
    protected:
        /** \property lv_disp_draw_buf_t lv_disp_buf
         *  \brief Display buffer descriptor.
         */
        lv_disp_draw_buf_t lv_disp_buf;

        /** \property lv_disp_drv_t lv_disp_drv
         *  \brief Display driver instance.
         */
        lv_disp_drv_t lv_disp_drv;

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

        /** \fn virtual void flush(const lv_area_t * area,  lv_color_t * color_map)
         *  \brief Callback to draw data on display.
         *  \param area: target draw area.
         *  \param color_map: data to draw.
         */
        virtual void flush(const lv_area_t * area,  lv_color_t * color_map) {}

        /** \fn void update_driver()
         *  \brief Updates driver with stored values.
         */
        void update_driver();

        /** \fn void flush_ready()
         *  \brief Tells LVGL that flush operation is over. This must be called
         *  at the end of the flush method.
         */
        void flush_ready();
    
    public:
        /** \fn Display(lv_coord_t hor_res, lv_coord_t ver_res, uint32_t fb_size)
         *  \brief Constructor.
         *  \param hor_res: horizontal resolution.
         *  \param ver_res: vertical resolution.
         *  \param fb_size: frame buffer size.
         */
        Display(lv_coord_t hor_res, lv_coord_t ver_res, uint32_t fb_size);

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

        /** \fn Object get_scr_act() const
         *  \brief Gets active screen on this display.
         *  \returns object representing active screen.
         */
        Object get_scr_act() const;

        /** \fn Object get_scr_prev() const
         *  \brief Gets the screen before the active screen on this display.
         *  \returns object representing previous screen.
         */
        Object get_scr_prev() const;

        /** \fn Object get_layer_top() const
         *  \brief Gets access to the top layer.
         *  \returns object representing the top layer.
         */
        Object get_layer_top() const;

        /** \fn Object get_layer_sys() const
         *  \brief Gets access to the sys layer.
         *  \returns object representing the sys layer.
         */
        Object get_layer_sys() const;

        /** \fn void set_theme(Theme & th)
         *  \brief Sets active theme on display.
         *  \param th: theme object.
         */
        void set_theme(Theme & th);

        /** \fn Theme get_theme() const
         *  \brief Gets active theme.
         *  \returns theme object.
         */
        Theme get_theme() const;

        /** \fn void set_bg_color(lv_color_t color)
         *  \brief Sets display background color.
         *  \param color: color to set.
         */
        void set_bg_color(lv_color_t color);

        /** \fn void set_bg_image(const draw::ImageDescriptor & img)
         *  \brief Sets display background image.
         *  \param img: image buffer.
         */
        void set_bg_image(const draw::ImageDescriptor & img);

        /** \fn void set_bg_image(const std::string & path)
         *  \brief Sets display background image.
         *  \param path: path to image file.
         */
        void set_bg_image(const std::string & path);

        /** \fn void set_bg_opa(lv_opa_t value)
         *  \brief Sets display background opacity.
         *  \param value: opacity value.
         */
        void set_bg_opa(lv_opa_t value);

        /** \brief Set state of display invalidation.
         *  \param en: if true, invalidation is enabled; if false, disabled.
         */
        void enable_invalidation(bool en);

        /** \brief Get state of display invalidation.
         *  \returns true if invalidation is enabled, false otherwise.
         */
        bool is_invalidation_enabled();

        /** \fn uint32_t get_inactive_time() const
         *  \brief Gets elapsed time since last activity.
         *  \returns elapsed time in ms.
         */
        uint32_t get_inactive_time() const;

        /** \fn void trig_activity()
         *  \brief Triggers activity on the display.
         */
        void trig_activity();

        /** \fn void clean_dcache()
         *  \brief Cleans display cache.
         */
        void clean_dcache();

    };

    // TODO: void lv_scr_load_anim(lv_obj_t * scr, lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool auto_del);

    /** \fn void load_scr(Object & scr)
     *  \brief Sets active screen.
     *  \param scr: object representing a screen.
     */
    void load_scr(Object & scr);

    /** \fn Object scr_act()
     *  \brief Gets the currently active screen.
     *  \returns object representing currently active screen.
     */
    Object scr_act();

    /** \fn Object layer_top()
     *  \brief Gets the currently active top layer.
     *  \returns object representing currently active top layer.
     */
    Object layer_top();

    /** \fn Object layer_sys()
     *  \brief Gets the currently active sys layer.
     *  \returns object representing currently active sys layer.
     */
    Object layer_sys();

}

#endif // LV_USE_USER_DATA