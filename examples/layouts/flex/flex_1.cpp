#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void flex_1() {
        auto root = scr_act();
        /*Create a container with ROW flex direction*/
        static auto cont_row = Container(root);
        cont_row.set_size(300, 75);
        cont_row.align(LV_ALIGN_TOP_MID, 0, 5);
        cont_row.set_flex_flow(LV_FLEX_FLOW_ROW);

        /*Create a container with COLUMN flex direction*/
        static auto cont_col = Container(root);
        cont_col.set_size(200, 150);
        cont_col.align_to(cont_row, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
        cont_col.set_flex_flow(LV_FLEX_FLOW_COLUMN);

        for(uint32_t i = 0; i < 10; i++) {
            /*Add items to the row*/
            {
                auto obj = Button(cont_row);
                obj.set_size(100, LV_PCT(100));
                auto label = Label(obj);
                label.set_text_fmt("Item: %u", i);
                label.center();
                obj.release_ptr();
                label.release_ptr();
            }
            /*Add items to the column*/
            {
                auto obj = Button(cont_col);
                obj.set_size(LV_PCT(100), LV_SIZE_CONTENT);
                auto label = Label(obj);
                label.set_text_fmt("Item: %" LV_PRIu32, i);
                label.center();
                obj.release_ptr();
                label.release_ptr();
            }
        }
    }
}