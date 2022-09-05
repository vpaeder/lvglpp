/** \file btnmatrix.h
 *  \brief Header file for C++ wrapper for lv_btnmatrix_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_BTNMATRIX != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class ButtonMatrix
     *  \brief Wraps a lv_btnmatrix_t object.
     */
    class ButtonMatrix : public Widget<lv_btnmatrix_create> {
    private:
        /** \property RawDblArray<char> map
         *  \brief Button map.
         */
        RawDblArray<char> map;

    public:
        using Widget::Widget;

        /** \fn void set_map(const std::vector<std::string> & map)
         *  \brief Sets button map. This is an array of strings with
         *  one string per button. Add "\n" for line break. The last element
         *  must be an empty string "".
         *  \param map: button map.
         */
        void set_map(const std::vector<std::string> & map);

        /** \fn void set_ctrl_map(const std::vector<lv_btnmatrix_ctrl_t> & ctrl_map)
         *  \brief Sets control map. This sets the state of each button
         *  in the matrix.
         *  \param ctrl_map: control map.
         */
        void set_ctrl_map(const std::vector<lv_btnmatrix_ctrl_t> & ctrl_map);

        /** \fn void set_selected_btn(uint16_t btn_id)
         *  \brief Sets selected button.
         *  \param btn_id: button index.
         */
        void set_selected_btn(uint16_t btn_id);

        /** \fn void set_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl)
         *  \brief Sets the attributes of a button in the matrix.
         *  \param btn_id: button index.
         *  \param ctrl: button attributes.
         */
        void set_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl);

        /** \fn void clear_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl)
         *  \brief Clears the attributes of a button in the matrix.
         *  \param btn_id: button index.
         *  \param ctrl: button attributes.
         */
        void clear_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl);

        /** \fn void set_btn_ctrl_all(lv_btnmatrix_ctrl_t ctrl)
         *  \brief Sets the attributes of every button in the matrix.
         *  \param ctrl: button attributes.
         */
        void set_btn_ctrl_all(lv_btnmatrix_ctrl_t ctrl);

        /** \fn void clear_btn_ctrl_all(lv_btnmatrix_ctrl_t ctrl)
         *  \brief Clears the attributes of every button in the matrix.
         *  \param ctrl: button attributes.
         */
        void clear_btn_ctrl_all(lv_btnmatrix_ctrl_t ctrl);

        /** \fn void set_btn_width(uint16_t btn_id, uint8_t width)
         *  \brief Sets button width.
         *  \param btn_id: button index.
         *  \param width: button width.
         */
        void set_btn_width(uint16_t btn_id, uint8_t width);

        /** \fn void set_one_checked(bool en)
         *  \brief Sets button matrix mode. If enabled, matrix is like a selector
         *  widget, with only one button selected at once.
         *  \param en: state of selector mode.
         */
        void set_one_checked(bool en);

        /** \fn RawDblArray<char> & get_map()
         *  \brief Gets the associated button map.
         *  \returns button map.
         */
        RawDblArray<char> & get_map();

        /** \fn uint16_t get_selected_btn() const
         *  \brief Gets the index of the button selected last.
         *  \returns index of button selected last.
         */
        uint16_t get_selected_btn() const;

        /** \fn const char* ButtonMatrix::get_btn_text(uint16_t btn_id) const
         *  \brief Gets the text displayed on a given button.
         *  \param btn_id: button index.
         *  \returns text string displayed on button.
         */
        const char* get_btn_text(uint16_t btn_id) const;

        /** \fn bool has_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl) const
         *  \brief Tells if given button has a given attribute.
         *  \param btn_id: button index.
         *  \param ctrl: button attribute.
         *  \returns true if the button has the attribute, false otherwise.
         */
        bool has_btn_ctrl(uint16_t btn_id, lv_btnmatrix_ctrl_t ctrl) const;

        /** \fn bool get_one_checked() const
         *  \brief Tells in what mode the button matrix is.
         *  \returns true for selector mode, false otherwise.
         */
        bool get_one_checked() const;
    };

}
#endif // LV_USE_BTNMATRIX