#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/spinner/spinner.h" // for Spinner

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void spinner_1() {
        static auto spinner = Spinner(scr_act(), 1000, 60);
        spinner.set_size(100, 100);
        spinner.center();
    }
}