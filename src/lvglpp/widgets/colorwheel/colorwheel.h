/** \file colorwheel.h
 *  \brief Header file for C++ wrapper for lv_colorwheel_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_COLORWHEEL

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class ColorWheel
     *  \brief Wraps a lv_colorwheel_t object.
     */
    class ColorWheel : public Object {
    protected:
        /** \fn void initialize()
         *  \brief Initialize object.
         */
        void initialize();
        /** \fn void initialize(Object & parent)
         *  \brief Initialize object and assign parent object.
         *  \param parent: parent LVGL object.
         */
        void initialize(Object & parent);
        /** \fn void initialize(bool knob_recolor)
         *  \brief Initialize object with parameters.
         *  \param knob_recolor: if true, sets knob color to selected color.
         */
        void initialize(bool knob_recolor);
        /** \fn void initialize(Object & parent, bool knob_recolor)
         *  \brief Initialize object with parameters and parent object.
         *  \param parent: parent LVGL object.
         *  \param knob_recolor: if true, sets knob color to selected color.
         */
        void initialize(Object & parent, bool knob_recolor);
    
    public:
        /** \fn ColorWheel()
         *  \brief Default constructor.
         */
        ColorWheel();
        /** \fn ColorWheel(Object & parent)
         *  \brief Constructor with parent object.
         *  \param parent: parent LVGL object.
         */
        ColorWheel(Object & parent);
        /** \fn ColorWheel(bool knob_recolor)
         *  \brief Constructor with parameters.
         *  \param knob_recolor: if true, sets knob color to selected color.
         */
        ColorWheel(bool knob_recolor);
        /** \fn ColorWheel(Object & parent, bool knob_recolor)
         *  \brief Constructor with parameters and parent object.
         *  \param parent: parent LVGL object.
         *  \param knob_recolor: if true, sets knob color to selected color.
         */
        ColorWheel(Object & parent, bool knob_recolor);

        /** \fn bool set_hsv(lv_color_hsv_t hsv)
         *  \brief Sets color to given HSV color.
         *  \param hsv: HSV color.
         *  \returns true if succeeded, false if failed.
         */
        bool set_hsv(lv_color_hsv_t hsv);

        /** \fn bool set_rgb(lv_color_t color)
         *  \brief Sets color to given RGB color.
         *  \param color: RGB color.
         *  \returns true if succeeded, false if failed.
         */
        bool set_rgb(lv_color_t color);

        /** \fn void set_mode(lv_colorwheel_mode_t mode)
         *  \brief Sets color wheel mode.
         *  \param mode: mode (LV_COLORWHEEL_MODE_HUE/SATURATION/VALUE).
         */
        void set_mode(lv_colorwheel_mode_t mode);

        /** \fn void set_mode_fixed(bool fixed)
         *  \brief Sets behaviour when long press event occurs.
         *  \param fixed: if false, changes mode; if true, stays fixed.
         */
        void set_mode_fixed(bool fixed);

        /** \fn lv_color_hsv_t get_hsv() const
         *  \brief Gets current color in HSV format.
         *  \returns current color in HSV format.
         */
        lv_color_hsv_t get_hsv() const;

        /** \fn lv_color_t get_rgb() const
         *  \brief Gets current color in RGB format.
         *  \returns current color in RGB format.
         */
        lv_color_t get_rgb() const;

        /** \fn lv_colorwheel_mode_t get_color_mode() const
         *  \brief Gets current color wheel mode.
         *  \returns code for current color wheel mode.
         */
        lv_colorwheel_mode_t get_color_mode() const;

        /** \fn bool get_color_mode_fixed() const
         *  \brief Gets behaviour on long press events.
         *  \returns true if color wheel stays fixed, false if mode changes.
         */
        bool get_color_mode_fixed() const;
    };

}
#endif // LV_USE_COLORWHEEL