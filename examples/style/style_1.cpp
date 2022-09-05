#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;
    using namespace lvgl::widgets;

    void style_1() {
        static Style style;
        style.set_radius(5);

        style.set_width(150);
        style.set_height(LV_SIZE_CONTENT);

        style.set_pad_ver(20);
        style.set_pad_left(5);

        style.set_x(lv_pct(50));
        style.set_y(80);

        /*Create an object with the new style*/
        static auto obj = Container(scr_act());
        obj.add_style(style, LV_STATE_DEFAULT);
        static auto label = Label(obj);
        label.set_text("Hello");
    }
}