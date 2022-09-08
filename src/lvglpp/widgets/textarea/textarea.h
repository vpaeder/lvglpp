/** \file textarea.h
 *  \brief Header file for C++ wrapper for lv_textarea_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_TEXTAREA != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class TextArea
     *  \brief Wraps a lv_textarea_t object.
     */
    class TextArea : public Widget<lv_textarea_create> {
    public:
        using Widget::Widget;

        /** \fn void add_char(uint32_t c)
         *  \brief Adds character to the text area content at the current cursor position.
         *  \param c: character code.
         */
        void add_char(uint32_t c);

        /** \fn void add_text(const std::string & txt)
         *  \brief Adds text string to the text area content at the current cursor position.
         *  \param txt: text string.
         */
        void add_text(const std::string & txt);

        /** \fn void del_char()
         *  \brief Deletes one character at the current cursor position (equivalent of backspace).
         */
        void del_char();

        /** \fn void del_char_forward()
         *  \brief Deletes one character at the current cursor position (equivalent of delete key).
         */
        void del_char_forward();

        /** \fn void set_text(const std::string & txt)
         *  \brief Sets text area content.
         *  \param txt: text string.
         */
        void set_text(const std::string & txt);

        /** \fn void set_placeholder_text(const std::string & txt)
         *  \brief Sets placeholder text (this is the text displayed when text area is empty).
         *  \param txt: text string.
         */
        void set_placeholder_text(const std::string & txt);

        /** \fn void set_cursor_pos(int32_t pos)
         *  \brief Sets cursor position.
         *  \param pos: character index where to set cursor to.
         */
        void set_cursor_pos(int32_t pos);

        /** \fn void set_cursor_click_pos(bool en)
         *  \brief Enables/disables setting cursor position on click.
         *  \param en: if true, setting cursor position on click is enabled.
         */
        void set_cursor_click_pos(bool en);

        /** \fn void set_password_mode(bool en)
         *  \brief Enables/disables password obfuscation.
         *  \param en: if true, content is considered a password and is obfuscated.
         */
        void set_password_mode(bool en);

        /** \fn void set_password_bullet(const char * bullet)
         *  \brief Set password bullet character.
         *  \param bullet: bullet characters.
         */
        void set_password_bullet(const char * bullet);
        /** \fn void set_password_bullet(const std::string & bullet)
         *  \brief Set password bullet character.
         *  \param bullet: bullet characters.
         */
        void set_password_bullet(const std::string & bullet);

        /** \fn void set_one_line(bool en)
         *  \brief Enables/disables single line mode.
         *  \param en: if true, content is displayed on a single line. If false, multi-line.
         */
        void set_one_line(bool en);

        /** \fn void set_accepted_chars(const std::string & list)
         *  \brief Sets a list of accepted characters.
         *  \param list: characters accepted by text area.
         */
        void set_accepted_chars(const std::string & list);

        /** \fn void set_max_length(uint32_t num)
         *  \brief Sets the maximum length of content.
         *  \param num: maximum number of characters.
         */
        void set_max_length(uint32_t num);

        /** \fn void set_insert_replace(const std::string & txt)
         *  \brief Replaces some text at cursor position, up to the length of given text string.
         *  \param txt: text string to replace with.
         */
        void set_insert_replace(const std::string & txt);

        /** \fn void set_text_selection(bool en)
         *  \brief Enables/disables text selection.
         *  \param en: if true, text selection is enabled.
         */
        void set_text_selection(bool en);

        /** \fn void set_password_show_time(uint16_t time)
         *  \brief Sets the time password characters are displayed before being obfuscated.
         *  \param time: display time in ms.
         */
        void set_password_show_time(uint16_t time);

        /** \fn void set_align(lv_text_align_t align)
         *  \brief Sets the text alignment.
         *  \param align: alignment mode.
         */
        void set_align(lv_text_align_t align);
        
        /** \fn const char* get_text() const
         *  \brief Gets text area content.
         *  \returns a pointer to the text area content.
         */
        const char* get_text() const;

        /** \fn const char* get_placeholder_text() const
         *  \brief Gets placeholder text.
         *  \returns a pointer to the placeholder text.
         */
        const char* get_placeholder_text() const;

        /** \fn Object get_label() const
         *  \brief Gets label object.
         *  \returns an object representing the textarea label.
         */
        Object get_label() const;

        /** \fn uint32_t get_cursor_pos() const
         *  \brief Gets cursor position.
         *  \returns the cursor position.
         */
        uint32_t get_cursor_pos() const;

        /** \fn bool get_cursor_click_pos() const
         *  \brief Tells if setting cursor position on click is enabled.
         *  \returns true if setting cursor position on click is enabled, false otherwise.
         */
        bool get_cursor_click_pos() const;

        /** \fn bool get_password_mode() const
         *  \brief Tells if password obfuscation mode is enabled.
         *  \returns true if password obfuscation mode is enabled, false otherwise.
         */
        bool get_password_mode() const;

        /** \brief Get characters used as password bullet.
         *  \returns password bullet characters.
         */
        std::string get_password_bullet() const;

        /** \fn bool get_one_line() const
         *  \brief Tells if text area is in single line mode.
         *  \returns true if text area is in single line mode, false otherwise.
         */
        bool get_one_line() const;

        /** \fn const char* get_accepted_chars() const
         *  \brief Gets the list of accepted characters.
         *  \returns a pointer to the list of accepted characters.
         */
        const char* get_accepted_chars() const;

        /** \fn uint32_t get_max_length() const
         *  \brief Gets the maximum number of characters.
         *  \returns the maximum number of characters.
         */
        uint32_t get_max_length() const;

        /** \fn bool text_is_selected() const
         *  \brief Tells if some text is selected.
         *  \returns true if some text is selected, false otherwise.
         */
        bool text_is_selected() const;

        /** \fn bool get_text_selection() const
         *  \brief Tells if some text selected is enabled.
         *  \returns true if text selection is enabled, false otherwise.
         */
        bool get_text_selection() const;

        /** \fn uint16_t get_password_show_time() const
         *  \brief Gets the time password characters are displayed before being obfuscated.
         *  \returns password display time, in ms.
         */
        uint16_t get_password_show_time() const;

        /** \fn void clear_selection()
         *  \brief Clears selection.
         */
        void clear_selection();

        /** \fn void cursor_right()
         *  \brief Moves cursor to the right.
         */
        void cursor_right();

        /** \fn void cursor_left()
         *  \brief Moves cursor to the left.
         */
        void cursor_left();

        /** \fn void cursor_down()
         *  \brief Moves cursor down.
         */
        void cursor_down();

        /** \fn void cursor_up()
         *  \brief Moves cursor up.
         */
        void cursor_up();

    };

}
#endif // LV_USE_TEXTAREA