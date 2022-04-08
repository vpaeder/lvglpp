/** \file switch.h
 *  \brief Header file for C++ wrapper for lv_switch_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../core/object.h"

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Switch
     *  \brief Wraps a lv_switch_t object.
     */
    class Switch : public Object {
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
        /** \fn Switch()
         *  \brief Default constructor.
         */
        Switch();
        /** \fn Switch(Object & parent)
         *  \brief Constructor with parent object.
         *  \param parent: parent LVGL object.
         */
        Switch(Object & parent);
    };

}
