/** \file color.h
 *  \brief Header file for C++ wrapper for lv_color_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../lv_wrapper.h"

namespace lvgl::misc {

    /** \enum Color
     *  \brief List of available color names in palettes.
     */
    enum class Color : uint8_t {
        Red=0, Pink, Purple, DeepPurple,
        Indigo, Blue, LightBlue, Cyan, Teal,
        Green, LightGreen, Lime, Yellow, Amber,
        Orange, DeepOrange, Brown, BlueGrey, Grey,
        None = 0xff
    };

    /** \namespace lvgl::misc::color
     *  \brief Contains LVGL color functions.
     */
    namespace color {
            /** \fn lv_color_t from_rgb(uint8_t r, uint8_t g, uint8_t b)
             *  \brief Creates color from RGB color components.
             *  \param r: red component.
             *  \param g: green component.
             *  \param b: blue component.
             *  \returns color.
             */
            lv_color_t from_rgb(uint8_t r, uint8_t g, uint8_t b);

            /** \fn lv_color_t from_hex(uint32_t c)
             *  \brief Creates color from 24bit number.
             *  \param c: 24bit color value (e.g. 0xffffff).
             *  \returns color.
             */
            lv_color_t from_hex(uint32_t c);

            /** \fn lv_color_t from_hex3(uint16_t c)
             *  \brief Creates color from 12bit number.
             *  \param c: 12bit color value (e.g. 0xfff).
             *  \returns color.
             */
            lv_color_t from_hex3(uint16_t c);

            /** \fn lv_color_t from_hsv(uint16_t h, uint8_t s, uint8_t v)
             *  \brief Creates color from HSV values.
             *  \param h: hue.
             *  \param s: saturation.
             *  \param v: value.
             *  \returns RGB color.
             */
            lv_color_t from_hsv(uint16_t h, uint8_t s, uint8_t v);

            /** \fn lv_color_t from_hsv(lv_color_hsv_t color_hsv)
             *  \brief Creates color from HSV color.
             *  \param color_hsv: HSV color.
             *  \returns RGB color.
             */
            lv_color_t from_hsv(lv_color_hsv_t color_hsv);

            /** \fn inline uint8_t to1(lv_color_t color)
             *  \brief Converts color to 1bit (111) representation.
             *  \param color: source color.
             *  \returns 1bit color.
             */
            inline uint8_t to1(lv_color_t color);

            /** \fn inline uint8_t to8(lv_color_t color)
             *  \brief Converts color to 8bit (233) representation.
             *  \param color: source color.
             *  \returns 8bit color.
             */
            inline uint8_t to8(lv_color_t color);

            /** \fn inline uint16_t to16(lv_color_t color)
             *  \brief Converts color to 16bit (565) representation.
             *  \param color: source color.
             *  \returns 16bit color.
             */
            inline uint16_t to16(lv_color_t color);

            /** \fn inline uint32_t to32(lv_color_t color)
             *  \brief Converts color to 32bit representation.
             *  \param color: source color.
             *  \returns 32bit color.
             */
            inline uint32_t to32(lv_color_t color);

            /** \fn uint8_t brightness(lv_color_t color)
             *  \brief Gets color brightness.
             *  \param color: source color.
             *  \returns color brightness.
             */
            uint8_t brightness(lv_color_t color);

            /** \fn lv_color_hsv_t to_hsv(lv_color_t color)
             *  \brief Converts color to HSV.
             *  \param color: source RGB color.
             *  \returns HSV color.
             */
            lv_color_hsv_t to_hsv(lv_color_t color);

            /** \fn lv_color_t mix(lv_color_t c1, lv_color_t c2, uint8_t ratio)
             *  \brief Mixes two colors with the given ratio.
             *  \param c1: first color.
             *  \param c2: second color.
             *  \param ratio: amount of second color (255=second color, 0=first color).
             *  \returns color mix.
             */
            lv_color_t mix(lv_color_t c1, lv_color_t c2, uint8_t ratio);

            /** \fn lv_color_t lighten(lv_color_t color, lv_opa_t lvl);
             *  \brief Lightens color by given amount.
             *  \param color: source color.
             *  \param lvl: amount of lightening.
             *  \returns lighter color.
             */
            lv_color_t lighten(lv_color_t color, lv_opa_t lvl);

            /** \fn lv_color_t darken(lv_color_t color, lv_opa_t lvl);
             *  \brief Darkens color by given amount.
             *  \param color: source color.
             *  \param lvl: amount of darkening.
             *  \returns darker color.
             */
            lv_color_t darken(lv_color_t color, lv_opa_t lvl);

            /** \fn lv_color_t change_lightness(lv_color_t color, lv_opa_t lvl);
             *  \brief Changes color lightness.
             *  \param color: source color.
             *  \param lvl: target lightness.
             *  \returns adjusted color.
             */
            lv_color_t change_lightness(lv_color_t color, lv_opa_t lvl);
    }

    /** \namespace lvgl::misc::palette
     *  \brief Contains palette accessors.
     */
    namespace palette {
        /** \fn lv_color_t main(Color p)
         *  \brief Retrieves color from main palette.
         *  \param p: color index.
         *  \returns corresponding color.
         */
        lv_color_t main(Color p);

        /** \fn lv_color_t light(Color p, uint8_t lvl)
         *  \brief Retrieves color from light palette.
         *  \param p: color index.
         *  \param lvl: lightening factor (0 to 4).
         *  \returns corresponding color.
         */
        lv_color_t light(Color p, uint8_t lvl);

        /** \fn lv_color_t dark(Color p, uint8_t lvl)
         *  \brief Retrieves color from dark palette.
         *  \param p: color index.
         *  \param lvl: darkening factor (0 to 3).
         *  \returns corresponding color.
         */
        lv_color_t dark(Color p, uint8_t lvl);

        /** \fn lv_color_t white()
         *  \brief Gets the color white.
         *  \returns white color.
         */
        lv_color_t white();

        /** \fn lv_color_t black()
         *  \brief Gets the color black.
         *  \returns black color.
         */
        lv_color_t black();
    }

#if LV_USE_USER_DATA
    /** \class ColorFilter
     *  \brief Wraps a lv_color_filter_dsc_t object. This is a base class
     *  used to define color filters.
     */
    class ColorFilter : public PointerWrapper<lv_color_filter_dsc_t, lv_mem_free> {
    protected:
        /** \fn virtual lv_color_t callback(lv_color_t color, lv_opa_t opa)
         *  \brief Color filter callback.
         *  \param color: color value.
         *  \param opa: opacity.
         *  \returns processed color.
         */
        virtual lv_color_t callback(lv_color_t color, lv_opa_t opa) {return lv_color_t{};}

    public:
        /** \fn ColorFilter()
         *  \brief Default constructor.
         */
        ColorFilter();

    };
#endif // LV_USE_USER_DATA
}
