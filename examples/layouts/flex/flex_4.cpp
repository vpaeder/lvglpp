#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void flex_4() {
        static auto cont = Container(scr_act());
        cont.set_size(300, 220);
        cont.center();
        cont.set_flex_flow(LV_FLEX_FLOW_COLUMN_REVERSE);

        for(uint32_t i = 0; i < 6; i++) {
            auto obj = obj.create(cont);
            obj.set_size(100, 50);
            auto label = Label(obj);
            label.set_text_fmt("Item: %" LV_PRIu32, i);
            label.center();
            obj.release_ptr();
            label.release_ptr();
        }
    }
}