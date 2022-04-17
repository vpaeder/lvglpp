#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;

    void object_1() {
        auto root = scr_act();
        // the Object class is a base class without an allocator;
        // the Container class derives from Object and has the lv_obj_create allocator.
        static auto obj1 = Container(root);
        obj1.set_size(100, 50);
        obj1.align(LV_ALIGN_CENTER, -60, -30);

        static Style style_shadow;
        style_shadow.set_shadow_width(10);
        style_shadow.set_shadow_spread(5);
        style_shadow.set_shadow_color(palette::main(Color::Blue));

        static auto obj2 = Container(root);
        obj2.add_style(style_shadow, LV_PART_MAIN);
        obj2.align(LV_ALIGN_CENTER, 60, 30);
    }
}