/** \file list.h
 *  \brief Header file for C++ wrapper for lv_list_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_LIST

namespace lvgl::widgets {

    using namespace lvgl::core;

    class Button;
    class Label;
    
    /** \class List
     *  \brief Wraps a lv_list_t object.
     */
    class List : public Widget<lv_list_create> {
    public:
        using Widget::Widget;

        /** \fn Label add_text(const std::string & txt)
         *  \brief Adds a text entry to the list.
         *  \param txt: entry text.
         *  \returns text label instance.
         */
        Label add_text(const std::string & txt);

        /** \fn Button add_btn(const std::string & icon, const std::string & txt)
         *  \brief Adds a button entry to the list.
         *  \param icon: entry icon.
         *  \param txt: entry text.
         *  \returns button instance.
         */
        Button add_btn(const std::string & icon, const std::string & txt);
        /** \fn Button add_btn(const ImageDescriptor & icon, const std::string & txt)
         *  \brief Adds a button entry to the list.
         *  \param icon: entry icon.
         *  \param txt: entry text.
         *  \returns button instance.
         */
        Button add_btn(const ImageDescriptor & icon, const std::string & txt);

        /** \fn Button add_btn(const std::string & txt)
         *  \brief Adds a button entry to the list.
         *  \param txt: entry text.
         *  \returns button instance.
         */
        Button add_btn(const std::string & txt);

        /** \fn std::string get_btn_text(const Button & btn) const
         *  \brief Gets text of given button child.
         *  \param btn: button instance.
         *  \returns text string.
         */
        std::string get_btn_text(const Button & btn) const;
    };

}
#endif // LV_USE_LIST