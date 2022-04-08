/** \file button.h
 *  \brief Header file for C++ wrapper for lv_btn_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../core/object.h"

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Button
     *  \brief Wraps a lv_btn_t object.
     */
    class Button : public Object {
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
        /** \fn Button()
         *  \brief Default constructor.
         */
        Button();
        /** \fn Button(Object & parent)
         *  \brief Constructor with parent object.
         *  \param parent: parent LVGL object.
         */
        Button(Object & parent);
    };

}
