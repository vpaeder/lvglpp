#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/led.h" // for Led

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void led_1() {
        auto root = scr_act();

        /*Create a LED and switch it OFF*/
        auto led1  = Led(root);
        led1.align(LV_ALIGN_CENTER, -80, 0);
        led1.off();

        /*Copy the previous LED and set a brightness*/
        auto led2  = Led(root);
        led2.align(LV_ALIGN_CENTER, 0, 0);
        led2.set_brightness(150);
        led2.set_color(lv_palette_main(LV_PALETTE_RED));

        /*Copy the previous LED and switch it ON*/
        auto led3  = Led(root);
        led3.align(LV_ALIGN_CENTER, 80, 0);
        led3.on();
    }
}