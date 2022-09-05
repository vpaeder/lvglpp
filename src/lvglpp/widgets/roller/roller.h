/** \file roller.h
 *  \brief Header file for C++ wrapper for lv_roller_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_ROLLER != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Roller
     *  \brief Wraps a lv_roller_t object. This is a widget that lets you
     *  scroll through different options by gestures.
     */
    class Roller : public Widget<lv_roller_create> {
    public:
        using Widget::Widget;

        /** \fn void set_options(const std::string & options, lv_roller_mode_t mode)
         *  \brief Sets roller options.
         *  \param options: a string with options separated with "\n".
         *  \param mode: LV_ROLLER_MODE_NORMAL or LV_ROLLER_MODE_INFINITE.
         */
        void set_options(const std::string & options, lv_roller_mode_t mode);

        /** \fn void set_selected(uint16_t sel_opt, lv_anim_enable_t anim)
         *  \brief Sets the selected option.
         *  \param sel_opt: index of option to select.
         *  \param anim: defines if selection is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void set_selected(uint16_t sel_opt, lv_anim_enable_t anim);

        /** \fn void set_visible_row_count(uint8_t row_cnt)
         *  \brief Sets the number of visible rows.
         *  \param row_cnt: number of visible rows.
         */
        void set_visible_row_count(uint8_t row_cnt);

        /** \fn uint16_t get_selected() const
         *  \brief Gets the selected option.
         *  \returns the index of the selected option.
         */
        uint16_t get_selected() const;

        /** \fn std::string get_selected_str() const
         *  \brief Gets the text of the selected option.
         *  \returns the text of the selected option.
         */
        std::string get_selected_str() const;

        /** \fn const char * get_options() const
         *  \brief Gets the list of options.
         *  \returns a string with the options separated with "\n".
         */
        const char * get_options() const;
        
        /** \fn uint16_t get_option_cnt() const
         *  \brief Gets the number of options.
         *  \returns the number of options.
         */
        uint16_t get_option_cnt() const;

    };

}
#endif // LV_USE_ROLLER