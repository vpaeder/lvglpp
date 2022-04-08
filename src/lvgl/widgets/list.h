/** \file list.h
 *  \brief Header file for C++ wrapper for lv_list_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../core/object.h"

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class List
     *  \brief Wraps a lv_list_t object.
     */
    class List : public Object {
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
        /** \fn List()
         *  \brief Default constructor.
         */
        List();
        /** \fn List(Object & parent)
         *  \brief Constructor with parent object.
         *  \param parent: parent LVGL object.
         */
        List(Object & parent);

        /** \fn Object add_text(const std::string & txt)
         *  \brief Adds a text entry to the list.
         *  \param txt: entry text.
         *  \returns text label instance.
         */
        Object add_text(const std::string & txt);

        /** \fn Object add_btn(const std::string & icon, const std::string & txt)
         *  \brief Adds a button entry to the list.
         *  \param icon: entry icon.
         *  \param txt: entry text.
         *  \returns button instance.
         */
        Object add_btn(const std::string & icon, const std::string & txt);

        /** \fn std::string get_btn_text(const Object & btn) const
         *  \brief Gets text of given button child.
         *  \param btn: button instance.
         *  \returns text string.
         */
        std::string get_btn_text(const Object & btn) const;
    };

}
