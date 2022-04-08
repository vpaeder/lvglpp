/** \file led.h
 *  \brief Header file for C++ wrapper for lv_led_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../core/object.h"

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    /** \class Led
     *  \brief Wraps a lv_led_t object.
     */
    class Led : public Object {
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
        /** \fn Led()
         *  \brief Default constructor.
         */
        Led();
        /** \fn Led(Object & parent)
         *  \brief Constructor with parent object.
         *  \param parent: parent LVGL object.
         */
        Led(Object & parent);

        /** \fn void set_color(lv_color_t color)
         *  \brief Sets LED color.
         *  \param color: color.
         */
        void set_color(lv_color_t color);

        /** \fn void set_brightness(uint8_t bright)
         *  \brief Sets LED brightness.
         *  \param bright: brightness (0=minimum, 255=maximum).
         */
        void set_brightness(uint8_t bright);

        /** \fn void on()
         *  \brief Turns LED on.
         */
        void on();

        /** \fn void off()
         *  \brief Turns LED off.
         */
        void off();

        /** \fn void toggle()
         *  \brief Toggles LED.
         */
        void toggle();

        /** \fn uint8_t get_brightness() const
         *  \brief Gets LED brightness.
         *  \returns brightness value.
         */
        uint8_t get_brightness() const;
    };

}
