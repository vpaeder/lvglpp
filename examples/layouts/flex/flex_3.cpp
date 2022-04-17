#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container

namespace lvgl::examples {
    
    using namespace lvgl::core;

    void flex_3() {
        static auto cont = Container(scr_act());
        obj.set_size(300, 220);
        obj.center();
        obj.set_flex_flow(LV_FLEX_FLOW_ROW);

        static auto obj1 = Container(cont);
        obj1.set_size(40, 40);           /*Fix size*/

        static auto obj2 = Container(cont);
        obj2.set_height(40);
        obj2.set_flex_grow(1);           /*1 portion from the free space*/

        static auto obj3 = Container(cont);
        obj3.set_height(40);
        obj3.set_flex_grow(2);           /*2 portion from the free space*/

        static auto obj4 = Container(cont);
        obj4.set_size(40, 40);           /*Fix size. It is flushed to the right by the "grow" items*/
    }
}