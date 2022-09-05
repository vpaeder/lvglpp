#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    static void drag_event_handler(Event & e) {
        auto obj = e.get_target<Object>();

        auto indev = indev_get_act<PointerInputDevice>();
        if(&*indev == nullptr)  return;

        auto vect = indev.get_vect();
        lv_coord_t x = obj.get_x() + vect.x;
        lv_coord_t y = obj.get_y() + vect.y;
        obj.set_pos(x, y);
    }

    void object_2() {
        // the Object class is a base class without an allocator;
        // the Container class derives from Object and has the lv_obj_create allocator.
        static auto obj = Container(scr_act());
        obj.set_size(150, 100);
        obj.add_event_cb(drag_event_handler, LV_EVENT_PRESSING);

        static auto label = Label(obj);
        label.set_text("Drag me");
        label.center();
    }
}