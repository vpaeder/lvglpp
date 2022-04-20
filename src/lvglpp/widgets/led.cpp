/** \file led.cpp
 *  \brief Implementation file for C++ wrapper for lv_btn_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "led.h"
#if LV_USE_LED

namespace lvgl::widgets {

    void Led::set_color(lv_color_t color) {
        lv_led_set_color(this->raw_ptr(), color);
    }

    void Led::set_brightness(uint8_t bright) {
        lv_led_set_brightness(this->raw_ptr(), bright);
    }

    void Led::on() {
        lv_led_on(this->raw_ptr());
    }

    void Led::off() {
        lv_led_off(this->raw_ptr());
    }

    void Led::toggle() {
        lv_led_toggle(this->raw_ptr());
    }

    uint8_t Led::get_brightness() const {
        return lv_led_get_brightness(this->raw_ptr());
    }

}
#endif // LV_USE_LED