/** \file font.cpp
 *  \brief Implementation file for C++ wrapper for lv_font_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "font.h"

namespace lvgl::font {
    
    Font::Font(std::string & font_name) {
        this->lv_obj = LvPointerType(lv_font_load(font_name.c_str()));
    }

    const uint8_t* Font::get_glyph_bitmap(uint32_t letter) const {
        return lv_font_get_glyph_bitmap(this->raw_ptr(), letter);
    }

    lv_font_glyph_dsc_t Font::get_glyph_descriptor(uint32_t letter, uint32_t letter_next) const {
        lv_font_glyph_dsc_t dsc_out;
        lv_font_get_glyph_dsc(this->raw_ptr(), &dsc_out, letter, letter_next);
        return std::move(dsc_out);
    }

    uint16_t Font::get_glyph_width(uint32_t letter, uint32_t letter_next) const {
        return lv_font_get_glyph_width(this->raw_ptr(), letter, letter_next);
    }

    lv_coord_t Font::get_line_height() const {
        return lv_font_get_line_height(this->raw_ptr());
    }

}
