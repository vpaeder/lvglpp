/** \file dropdown.h
 *  \brief Header file for C++ wrapper for lv_dropdown_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"
#include "../../draw/image.h"

#if LV_USE_DROPDOWN != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Dropdown
     *  \brief Wraps a lv_dropdown_t object. This makes a dropdown menu.
     */
    class Dropdown : public Widget<lv_dropdown_create> {
    public:
        using Widget::Widget;

        /** \fn void set_text(const std::string & txt)
         *  \brief Sets text displayed on dropdown menu.
         *  \param txt: text displayed. If empty, displays the selected option.
         */
        void set_text(const std::string & txt);

        /** \fn void set_options(const std::string & options)
         *  \brief Sets dropdown menu options. String is copied.
         *  \param options: a string containing options separated with "\n".
         */
        void set_options(const std::string & options);

        /** \fn void set_options_static(const std::string & options)
         *  \brief Sets dropdown menu options. String must remain allocated.
         *  \param options: a string containing options separated with "\n".
         */
        void set_options_static(const std::string & options);

        /** \fn void add_option(const std::string & option, uint32_t pos)
         *  \brief Adds an option to dropdown menu.
         *  \param option: a string containing option text.
         *  \param pos: option position.
         */
        void add_option(const std::string & option, uint32_t pos);

        /** \fn void clear_options()
         *  \brief Clears dropdown menu options.
         */
        void clear_options();

        /** \fn void set_selected(uint16_t sel_opt)
         *  \brief Sets selected option.
         *  \param sel_opt: selected option index.
         */
        void set_selected(uint16_t sel_opt);

        /** \fn void set_dir(lv_dir_t dir)
         *  \brief Sets dropdown direction.
         *  \param dir: direction (LV_DIR_LEFT, LV_DIR_RIGHT, LV_DIR_TOP, LV_DIR_BOTTOM).
         */
        void set_dir(lv_dir_t dir);

        /** \fn void set_symbol(const std::string & symbol)
         *  \brief Sets symbol to display on the side of the dropdown menu.
         *  \param symbol: a text describing a symbol, like 'LV_SYMBOL_DOWN'.
         */
        void set_symbol(const std::string & symbol);

        /** \fn void set_symbol(const ImageDescriptor & symbol)
         *  \brief Sets symbol to display on the side of the dropdown menu.
         *  \param symbol: an image buffer containing the symbol to display.
         */
        void set_symbol(const ImageDescriptor & symbol);

        /** \fn void set_selected_highlight(bool en)
         *  \brief Sets whether the selected option should be highlighted.
         *  \param en: if true, selected option gets highlighted.
         */
        void set_selected_highlight(bool en);

        /** \fn Object get_list() const
         *  \brief Provides an access to the dropdown list (for styling).
         *  \returns object instance wrapping the dropdown list object.
         */
        Object get_list() const;

        /** \fn const char * get_text() const
         *  \brief Gets the text displayed on the dropdown menu.
         *  \returns pointer to text displayed on dropdown menu.
         */
        const char * get_text() const;

        /** \fn const char * get_options() const
         *  \brief Gets the options of the dropdown menu.
         *  \returns pointer to the list of options of the dropdown menu.
         */
        const char * get_options() const;

        /** \fn uint16_t get_selected() const
         *  \brief Gets the index of the selected menu option.
         *  \returns index of selected menu option.
         */
        uint16_t get_selected() const;

        /** \fn uint16_t get_option_cnt() const
         *  \brief Gets the number of menu options.
         *  \returns the number of menu options.
         */
        uint16_t get_option_cnt() const;

        /** \fn std::string get_selected_str() const
         *  \brief Gets the text of the selected menu option.
         *  \returns a copy of the text of the selected menu option.
         */
        std::string get_selected_str() const;

        /** \brief Get index of option with given text.
         *  \param option: option text.
         *  \returns option index, or -1 if not found.
         */
        int32_t get_option_index(const char * option) const;

        /** \brief Get index of option with given text.
         *  \param option: option text.
         *  \returns option index, or -1 if not found.
         */
        int32_t get_option_index(const std::string & option) const;

        /** \fn const char * get_symbol() const
         *  \brief Gets the symbol displayed on the side of the dropdown menu.
         *  \returns the symbol name, or nullptr if no symbol was set.
         */
        const char * get_symbol() const;

        /** \fn bool get_selected_highlight() const
         *  \brief Gets whether the selected option is highlighted.
         *  \returns true if the selected option gets highlighted, false otherwise.
         */
        bool get_selected_highlight() const;

        /** \fn lv_dir_t get_dir() const
         *  \brief Gets dropdown menu direction.
         *  \returns the code for dropdown menu direction.
         */
        lv_dir_t get_dir() const;

        /** \fn void open()
         *  \brief Opens the dropdown menu.
         */
        void open();

        /** \fn void close()
         *  \brief Closes the dropdown menu.
         */
        void close();

        /** \fn bool is_open() const
         *  \brief Tells if the dropdown menu is open.
         *  \returns true if the dropdown menu is open, false otherwise.
         */
        bool is_open() const;
    };

}
#endif // LV_USE_DROPDOWN