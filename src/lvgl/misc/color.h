/** \file color.h
 *  \brief Header file for C++ wrapper for lv_color_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../lv_thin_wrapper.h"

namespace lvgl::misc {

    /** \class Color
     *  \brief Wraps a lv_color_t object.
     */
    class Color : public ThinWrapper<lv_color_t> {
    public:
        using ThinWrapper::ThinWrapper;

        /** \fn Color(uint8_t r, uint8_t g, uint8_t b)
         *  \brief Constructor with RGB color components.
         *  \param r: red component.
         *  \param g: green component.
         *  \param b: blue component.
         */
        Color(uint8_t r, uint8_t g, uint8_t b); // RGB
        /** \fn Color(uint32_t c)
         *  \brief Constructor with 24bit color.
         *  \param c: 24bit color value.
         */
        Color(uint32_t c); // 24bit RGB as hex
        /** \fn Color(uint16_t c)
         *  \brief Constructor with 12bit color.
         *  \param c: 12bit color value.
         */
        Color(uint16_t c); // 12bit RGB as hex

        /** \fn uint8_t to1() const
         *  \brief Converts color to 1bit.
         *  \returns binary color.
         */
        uint8_t to1() const;

        /** \fn uint8_t to8() const
         *  \brief Converts color to 8bit.
         *  \returns 8bit color.
         */
        uint8_t to8() const;

        /** \fn uint16_t to16() const
         *  \brief Converts color to 16bit.
         *  \returns 16bit color.
         */
        uint16_t to16() const;

        /** \fn uint32_t to32() const
         *  \brief Converts color to 32bit.
         *  \returns 32bit color.
         */
        uint32_t to32() const;

        /** \fn uint8_t brightness() const
         *  \brief Gets color brightness.
         *  \returns color brightness.
         */
        uint8_t brightness() const;

        /** \fn Color lighten(lv_opa_t lvl)
         *  \brief Lightens color by given amount.
         *  \param lvl: amount of lightening.
         *  \returns lighter color.
         */
        Color lighten(lv_opa_t lvl);

        /** \fn Color darken(lv_opa_t lvl)
         *  \brief Darkens color by given amount.
         *  \param lvl: amount of darkening.
         *  \returns darker color.
         */
        Color darken(lv_opa_t lvl);

        /** \fn Color change_lightness(lv_opa_t lvl)
         *  \brief Change color lightness to given value.
         *  \param lvl: lightness value.
         *  \returns adjusted color.
         */
        Color change_lightness(lv_opa_t lvl);

        /** \fn lv_color_hsv_t to_hsv() const
         *  \brief Converts color to HSV.
         *  \returns HSV color.
         */
        lv_color_hsv_t to_hsv() const;

        /** \fn void from_hsv(uint16_t h, uint8_t s, uint8_t v)
         *  \brief Sets color components from HSV values.
         *  \param h: hue.
         *  \param s: saturation.
         *  \param v: value.
         */
        void from_hsv(uint16_t h, uint8_t s, uint8_t v);

        /** \fn void from_hsv(lv_color_hsv_t color_hsv)
         *  \brief Sets color components from an HSV color.
         *  \param color_hsv: HSV representation of a color.
         */
        void from_hsv(lv_color_hsv_t color_hsv);

        /** \fn Color mix(Color & c, uint8_t ratio) const
         *  \brief Mix another color with this one.
         *  \param c: other color.
         *  \param ratio: amount of other color (255=other color, 0=this color).
         *  \returns mixed colors.
         */
        Color mix(Color & c, uint8_t ratio) const;
        
    };


    /** \class ColorFilter
     *  \brief Wraps a lv_color_filter_dsc_t object. This is a base class
     *  used to define color filters.
     */
    class ColorFilter : public ThinPointerWrapper<lv_color_filter_dsc_t, lv_mem_free> {
    protected:
        /** \fn virtual lv_color_t callback(lv_color_t color, lv_opa_t opa)
         *  \brief Color filter callback.
         *  \param color: color value.
         *  \param opa: opacity.
         *  \returns processed color.
         */
        virtual lv_color_t callback(lv_color_t color, lv_opa_t opa) = 0;

    public:
        /** \fn ColorFilter()
         *  \brief Default constructor.
         */
        ColorFilter();

    };
}
