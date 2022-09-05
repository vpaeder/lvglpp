/** \file button.h
 *  \brief Header file for C++ wrapper for lv_keyboard_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_KEYBOARD

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Keyboard
     *  \brief Wraps a lv_keyboard_t object.
     */
    class Keyboard : public Widget<lv_keyboard_create> {
    private:
        /** \property std::vector< RawDblArray<char> > map
         *  \brief Keyboard maps.
         */
        std::vector<RawDblArray<char>> map;

    protected:
        /** \fn void initialize()
         *  \brief Initialize object.
         */
        void initialize() override;
        /** \fn void initialize(Object & parent)
         *  \brief Initialize object and assign parent object.
         *  \param parent: parent LVGL object.
         */
        void initialize(Object & parent) override;
    
    public:
        using Widget::Widget;

        /** \fn void set_textarea(Object & ta)
         *  \brief Sets the text area towards which key events are sent.
         *  \param ta: text area instance.
         */
        void set_textarea(Object & ta);

        /** \fn void unset_textarea()
         *  \brief Detach currently attached text area from keyboard.
         */
        void unset_textarea();

        /** \fn void set_mode(lv_keyboard_mode_t mode)
         *  \brief Sets keyboard mode.
         *  \param mode: keyboard mode (see lv_keyboard_mode_t for details).
         */
        void set_mode(lv_keyboard_mode_t mode);

        /** \fn void set_popovers(bool en)
         *  \brief Enables/disables pop-over button text when pressed.
         *  \param en: if true, button text pops over when pressed.
         */
        void set_popovers(bool en);

        /** \fn void set_map(lv_keyboard_mode_t mode, const std::vector<std::string> & map,
         *                   const std::vector<lv_btnmatrix_ctrl_t> & ctrl_map);
         *  \brief Sets keyboard map for given mode.
         *  \param mode: keyboard mode.
         *  \param map: keyboard map.
         *  \param ctrl_map: key control map (hidden/disabled/...).
         */
        void set_map(lv_keyboard_mode_t mode, const std::vector<std::string> & map,
                     const std::vector<lv_btnmatrix_ctrl_t> & ctrl_map);
        
        /** \fn Object get_textarea() const
         *  \brief Gets associated text area.
         *  \returns object instance for text area.
         */
        Object get_textarea() const;

        /** \fn lv_keyboard_mode_t get_mode() const
         *  \brief Gets keyboard mode.
         *  \returns code for keyboard mode.
         */
        lv_keyboard_mode_t get_mode() const;

        /** \fn bool get_popovers() const
         *  \brief Tells if pop-overs are enabled.
         *  \returns true if pop-overs are enabled, false otherwise.
         */
        bool get_popovers() const;

        /** \fn RawDblArray<char> & get_map_array()
         *  \brief Gets map for current keyboard mode.
         *  Note that I preferred working with RawDblArray<char> instead
         *  of std::vector<std::string>> because it gives the possibility
         *  to avoid copying data, and hence modify the keyboard map
         *  externally.
         *  \returns pointer to the keyboard map.
         */
        RawDblArray<char> & get_map_array();

        /** \fn uint16_t get_selected_btn() const
         *  \brief Gets selected key.
         *  \returns index of selected key.
         */
        uint16_t get_selected_btn() const;

        /** \fn std::shared_ptr<const char> get_btn_text(uint16_t btn_id) const
         *  \brief Gets text for button with given index.
         *  \param btn_id: button index.
         *  \returns pointer to button text.
         */
        std::shared_ptr<const char> get_btn_text(uint16_t btn_id) const;

    };

}
#endif // LV_USE_KEYBOARD