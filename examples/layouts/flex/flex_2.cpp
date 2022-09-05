#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/misc/style.h" // for Style

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void flex_2() {
        static Style style;
        style.set_flex_flow(LV_FLEX_FLOW_ROW_WRAP);
        style.set_flex_main_place(LV_FLEX_ALIGN_SPACE_EVENLY);
        style.set_layout(LV_LAYOUT_FLEX);

        static auto cont = Container(scr_act());
        cont.set_size(300, 220);
        cont.center();
        cont.add_style(style, LV_PART_MAIN);

        for(uint32_t i = 0; i < 8; i++) {
            auto obj = obj.create(cont);
            obj.set_size(70, LV_SIZE_CONTENT);
            obj.add_flag(LV_OBJ_FLAG_CHECKABLE);
            auto label = Label(obj);
            label.set_text_fmt("%" LV_PRIu32, i);
            label.center();
            obj.release_ptr();
            label.release_ptr();
        }
    }
}