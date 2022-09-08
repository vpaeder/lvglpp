/** \file label.h
 *  \brief Header file for C++ wrapper for lv_label_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../../core/object.h"

#if LV_USE_LABEL != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Label
     *  \brief Wraps a lv_label_t object.
     */
    class Label : public Widget<lv_label_create> {
    public:
        using Widget::Widget;

        /** \fn void set_text(const std::string & text)
         *  \brief Sets label text.
         *  \param text: text to set.
         */
        void set_text(const std::string & text);

        /** \fn template <typename... Args> void set_text_fmt(const std::string & fmt, Args... args)
         *  \brief Sets label text with format string and args.
         *  \param fmt: format string in printf format.
         *  \param args: arguments matching format string placeholders.
         */
        template <typename... Args> void set_text_fmt(const std::string & fmt, Args... args) {
            lv_label_set_text_fmt(this->raw_ptr(), fmt.c_str(), args...);
        }

        /** \fn void set_text_static(const std::string & text)
         *  \brief Sets label text. String must remain allocated.
         *  \param text: text to set.
         */
        void set_text_static(const std::string & text);

        /** \fn void set_long_mode(lv_label_long_mode_t long_mode)
         *  \brief Sets label behaviour with long text. This must be set before label size.
         *  \param long_mode: behaviour code (LV_LONG_WRAP, LV_LONG_DOT,
         *  LV_LONG_SCROLL, LV_LONG_SCROLL_CIRC).
         */
        void set_long_mode(lv_label_long_mode_t long_mode);

        /** \fn void set_recolor(bool en)
         *  \brief Sets whether inline colours are used to colour text.
         *  Example: "This is a #ff0000 red# word"
         *  \param en: if true, enable recolouring.
         */
        void set_recolor(bool en);

        /** \fn const char * get_text() const
         *  \brief Gets label text.
         *  \returns pointer to label text string.
         */
        const char * get_text() const;

        /** \fn lv_label_long_mode_t get_long_mode() const
         *  \brief Gets label behaviour with long text.
         *  \returns code for label behaviour with long text.
         */
        lv_label_long_mode_t get_long_mode() const;

        /** \fn bool get_recolor() const
         *  \brief Gets label recolouring mode.
         *  \returns true if inline colours are used to colour text, false otherwise.
         */
        bool get_recolor() const;

        /** \fn lv_point_t get_letter_pos(const uint32_t char_id) const
         *  \brief Gets relative position of a character.
         *  \param char_id: index of character.
         *  \returns the position of the character relative to the top left corner of the label.
         */
        lv_point_t get_letter_pos(const uint32_t char_id) const;

        /** \fn uint32_t get_letter_on(lv_point_t & pos_in) const
         *  \brief Gets character index at given position.
         *  \param pos_in: coordinates relative to the top left corner of the label.
         *  \returns the index of the character at given position.
         */
        uint32_t get_letter_on(lv_point_t & pos_in) const;

        /** \fn bool is_char_under_pos(lv_point_t & pos) const
         *  \brief Tells if a character is under the given position.
         *  \param pos: coordinates relative to the top left corner of the label.
         *  \returns true if a character is present, false otherwise.
         */
        bool is_char_under_pos(lv_point_t & pos) const;

        /** \fn uint32_t get_text_selection_start() const
         *  \brief Gets start of selection.
         *  \returns the character index of the selection start.
         */
        uint32_t get_text_selection_start() const;

        /** \fn uint32_t get_text_selection_end() const
         *  \brief Gets end of selection.
         *  \returns the character index of the selection end.
         */
        uint32_t get_text_selection_end() const;

        /** \fn void ins_text(uint32_t pos, const std::string & txt)
         *  \brief Inserts some text in the label string.
         *  \param pos: position where to insert text.
         *  \param txt: string to insert.
         */
        void ins_text(uint32_t pos, const std::string & txt);

        /** \fn void cut_text(uint32_t pos, uint32_t cnt)
         *  \brief Removes some characters from the label string.
         *  \param pos: position where to start removing text.
         *  \param cnt: number of characters to remove.
         */
        void cut_text(uint32_t pos, uint32_t cnt);

    };

}
#endif // LV_USE_LABEL