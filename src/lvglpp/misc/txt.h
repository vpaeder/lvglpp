/** \file timer.h
 *  \brief Header file for C++ wrapper for LVGL text functions.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../font/font.h"

/** \namespace lvgl::misc::txt
 *  \brief LVGL text functions.
 */
namespace lvgl::misc::txt {

    /** \fn lv_point_t get_size(const std::string & text, const lv_font_t * font,
     *                          lv_coord_t letter_space, lv_coord_t line_space,
     *                          lv_coord_t max_width, lv_text_flag_t flag)
     *  \brief Computes the size of the given text with the given parameters.
     *  \param text: text string.
     *  \param font: pointer to font.
     *  \param letter_space: letter spacing.
     *  \param line_space: line spacing.
     *  \param max_width: maximum width.
     *  \param flag: text property flag (see lv_text_flag_t).
     */
    lv_point_t get_size(const std::string & text, const lv_font_t * font, lv_coord_t letter_space,
                        lv_coord_t line_space, lv_coord_t max_width, lv_text_flag_t flag) {
        lv_point_t size_res;
        lv_txt_get_size(&size_res, text.c_str(), font, letter_space, line_space, max_width, flag);
        return size_res;
    }

    /** \fn lv_point_t get_size(const std::string & text, const Font & font,
     *                          lv_coord_t letter_space, lv_coord_t line_space,
     *                          lv_coord_t max_width, lv_text_flag_t flag)
     *  \brief Computes the size of the given text with the given parameters.
     *  \param text: text string.
     *  \param font: font object.
     *  \param letter_space: letter spacing.
     *  \param line_space: line spacing.
     *  \param max_width: maximum width.
     *  \param flag: text property flag (see lv_text_flag_t).
     */
    lv_point_t get_size(const std::string & text, const Font & font, lv_coord_t letter_space,
                        lv_coord_t line_space, lv_coord_t max_width, lv_text_flag_t flag) {
        return get_size(text, font.raw_ptr(), letter_space, line_space, max_width, flag);
    }

    /** \fn lv_coord_t get_width(const std::string & txt, const lv_font_t * font,
     *                           lv_coord_t letter_space, lv_text_flag_t flag)
     *  \brief Computes the width of the given text with the given parameters.
     *  \param txt: text string.
     *  \param font: pointer to font.
     *  \param letter_space: letter spacing.
     *  \param flag: text property flag (see lv_text_flag_t).
     */
    lv_coord_t get_width(const std::string & txt, const lv_font_t * font,
                         lv_coord_t letter_space, lv_text_flag_t flag) {
        return lv_txt_get_width(txt.c_str(), txt.size(), font, letter_space, flag);
    }

    /** \fn lv_coord_t get_width(const std::string & txt, const Font & font,
     *                           lv_coord_t letter_space, lv_text_flag_t flag)
     *  \brief Computes the width of the given text with the given parameters.
     *  \param txt: text string.
     *  \param font: font object.
     *  \param letter_space: letter spacing.
     *  \param flag: text property flag (see lv_text_flag_t).
     */
    lv_coord_t get_width(const std::string & txt, const Font & font,
                         lv_coord_t letter_space, lv_text_flag_t flag) {
        return get_width(txt, font.raw_ptr(), letter_space, flag);
    }

}