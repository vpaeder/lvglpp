/* This example shows how to write a display driver the C++ way */
#include "lvglpp/lvglpp.h"
#include "lvglpp/core/display.h"

class CustomDisplay : public lvgl::core::Display {

    void flush(const lv_area_t * area,  lv_color_t * color_map) override {
        /* Place here the code to write data to the display */
        /* This is like the C LVGL callback, so area contains the area to paint */
        /* and color_map the pixel values. */
        /* You can also access the class members the C++ way, with this->... */
    }

public:
    // Define a constructor that sets up the display. You need to pass hor_res,
    // ver_res and fb_size to the base class constructor.
    CustomDisplay(lv_coord_t hor_res, lv_coord_t ver_res, uint32_t fb_size)
        : Display(hor_res, ver_res, fb_size) {
        // if you touch lv_disp or lv_disp_drv, don't forget this line
        this->update_driver();
    }
};


void main() {
    // initialize LVGL
    lvgl::init();
    // create display object for LVGL
    static auto disp = CustomDisplay(args...);
    // you can set it as default this way:
    disp.set_default();
}
