/** \file spinner.h
 *  \brief Header file for C++ wrapper for lv_spinner_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_SPINNER

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Spinner
     *  \brief Wraps a lv_spinner_t object.
     */
    class Spinner : public Object {
    protected:
        void initialize() = delete;
        void initialize(Object & parent) = delete;
        /** \fn void initialize(uint32_t time, uint32_t arc_length)
         *  \brief Initialize object with parameters.
         *  \param time: duration of spinner animation, in ms.
         *  \param arc_length: length of spinner arc, in degrees.
         */
        void initialize(uint32_t time, uint32_t arc_length);
        /** \fn void initialize(Object & parent, uint32_t time, uint32_t arc_length)
         *  \brief Initialize object with parameters and parent object.
         *  \param parent: parent LVGL object.
         *  \param time: duration of spinner animation, in ms.
         *  \param arc_length: length of spinner arc, in degrees.
         */
        void initialize(Object & parent, uint32_t time, uint32_t arc_length);
    
    public:
        using Object::Object;
        
        Spinner() = delete;
        Spinner(Object & parent) = delete;
        /** \fn Spinner(uint32_t time, uint32_t arc_length)
         *  \brief Constructor with parameters.
         *  \param time: duration of spinner animation, in ms.
         *  \param arc_length: length of spinner arc, in degrees.
         */
        Spinner(uint32_t time, uint32_t arc_length);
        /** \fn Spinner(Object & parent, uint32_t time, uint32_t arc_length)
         *  \brief Constructor with parameters and parent object.
         *  \param parent: parent LVGL object.
         *  \param time: duration of spinner animation, in ms.
         *  \param arc_length: length of spinner arc, in degrees.
         */
        Spinner(Object & parent, uint32_t time, uint32_t arc_length);
    };

}
#endif // LV_USE_SPINNER