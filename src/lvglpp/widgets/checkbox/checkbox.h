/** \file checkbox.h
 *  \brief Header file for C++ wrapper for lv_checkbox_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_CHECKBOX != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Checkbox
     *  \brief Wraps a lv_checkbox_t object.
     */
    class Checkbox : public Widget<lv_checkbox_create> {
    public:
        using Widget::Widget;

        /** \fn void set_text(const std::string & txt)
         *  \brief Sets checkbox text.
         *  \param txt: text string. String content gets copied.
         */
        void set_text(const std::string & txt);

        /** \fn void set_text_static(const std::string & txt)
         *  \brief Sets checkbox text.
         *  \param txt: text string. String content must remain allocated.
         */
        void set_text_static(const std::string & txt);

        /** \fn const char* get_text() const
         *  \brief Gets checkbox text.
         *  \returns a pointer to the checkbox text.
         */
        const char* get_text() const;
    };

}
#endif // LV_USE_CHECKBOX