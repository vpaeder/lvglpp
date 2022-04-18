/* This example shows how to write an input device driver the C++ way */
#include "lvglpp/lvglpp.h"
#include "lvglpp/core/indev.h"

// choose the base class depending on the type of input device you want
class CustomInputDevice : public lvgl::core::PointerInputDevice {

    void read(lv_indev_data_t * data) override {
        // Place here the code to read data from the device
        // This is like the C LVGL callback, so data stores
        // the coordinates read by the device.
        // You can also access the class members the C++ way, with this->...
    }

public:
    // You can define a constructor that sets up the device.
    CustomInputDevice(Args... args) : PointerInputDevice() {
        // if you touch indev_drv, don't forget this line
        this->update_driver();
    }
};


void main() {
    // initialize LVGL
    lvgl::init();
    // create input device object for LVGL
    static auto indev = CustomInputDevice(args...);
    // you probably want to connect it with a display, in which case,
    // assuming that you initialized a display object called 'disp':
    indev.set_display(disp);
}
