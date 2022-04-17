/** \file font.h
 *  \brief Header file for C++ wrapper for lv_font_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../lv_wrapper.h"

/** \namespace lvgl::font
 *  \brief LVGL fonts and font-handling routines.
 */
namespace lvgl::font {
    
    /** \class Font
     *  \brief Wraps a lv_font_t object.
     */
    class Font : public PointerWrapper<lv_font_t, lv_font_free> {
    public:
        /** \fn Font(std::string & font_name)
         *  \brief Constructor with font name.
         *  \param font_name: font name.
         */
        Font(std::string & font_name);

        /** \fn const uint8_t* get_glyph_bitmap(uint32_t letter) const
         *  \brief Gets glyph bitmap.
         *  \param letter: glyph index.
         *  \returns pointer to the glyph bitmap.
         */
        const uint8_t* get_glyph_bitmap(uint32_t letter) const;

        /** \fn lv_font_glyph_dsc_t get_glyph_descriptor(uint32_t letter, uint32_t letter_next) const
         *  \brief Gets glyph descriptor.
         *  \param letter: glyph index.
         *  \param letter_next: index of following glyph (for kerning).
         *  \returns glyph descriptor.
         */
        lv_font_glyph_dsc_t get_glyph_descriptor(uint32_t letter, uint32_t letter_next) const;

        /** \fn uint16_t get_glyph_width(uint32_t letter, uint32_t letter_next) const
         *  \brief Gets glyph width.
         *  \param letter: glyph index.
         *  \param letter_next: index of following glyph (for kerning).
         *  \returns glyph width.
         */
        uint16_t get_glyph_width(uint32_t letter, uint32_t letter_next) const;

        /** \fn lv_coord_t get_line_height() const
         *  \brief Gets line height.
         *  \returns line height.
         */
        lv_coord_t get_line_height() const;

    };

}
