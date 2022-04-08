/** \file checkbox.h
 *  \brief Header file for C++ wrapper for lv_checkbox_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "../core/object.h"

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

        /** \fn void set_text_static(const std::shared_ptr<char> txt)
         *  \brief Sets checkbox text.
         *  \param txt: text string. String content must remain allocated.
         */
        void set_text_static(const std::shared_ptr<char> txt);

        /** \fn const std::shared_ptr<const char> get_text() const
         *  \brief Gets checkbox text.
         *  \returns a pointer to the checkbox text.
         */
        const std::shared_ptr<const char> get_text() const;
    };

}
