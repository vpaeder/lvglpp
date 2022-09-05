#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/misc/anim.h" // for Animation

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void grid_5() {
        static std::vector<lv_coord_t> col_dsc = {60, 60, 60, LV_GRID_TEMPLATE_LAST};
        static std::vector<lv_coord_t> row_dsc = {45, 45, 45, LV_GRID_TEMPLATE_LAST};

        /*Create a container with grid*/
        static auto cont = Container(scr_act());
        cont.set_size(300, 220);
        cont.center();
        cont.set_grid_dsc_array(col_dsc, row_dsc);
 
        for(uint32_t i = 0; i < 9; i++) {
            uint8_t col = i % 3;
            uint8_t row = i / 3;

            auto obj = Container(cont);
            obj.set_grid_cell(LV_GRID_ALIGN_STRETCH, col, 1,
                              LV_GRID_ALIGN_STRETCH, row, 1);

            auto label = Label(obj);
            label.set_text_fmt("%d,%d", col, row);
            label.center();
            obj.release_ptr();
            label.release_ptr();
        }

        auto row_gap_anim = [](Container & obj, int32_t v) {
            obj.set_style_pad_row(v, 0);
        };
        auto column_gap_anim = [](Container & obj, int32_t v) {
            obj.set_style_pad_column(v, 0);
        };

        static Animation a1, a2;
        a1.set_var(cont);
        a1.set_values(0, 10);
        a1.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a1.set_exec_cb(row_gap_anim);
        a1.set_time(500);
        a1.set_playback_time(500);
        a1.start();
        a2.set_var(cont);
        a2.set_values(0, 10);
        a2.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a2.set_exec_cb(column_gap_anim);
        a2.set_time(3000);
        a2.set_playback_time(3000);
        a2.start();
    }
}