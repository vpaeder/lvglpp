#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void grid_3() {
        /*Column 1: fix width 60 px
        *Column 2: 1 unit from the remaining free space
        *Column 3: 2 unit from the remaining free space*/
        static std::vector<lv_coord_t> col_dsc = {60, LV_GRID_FR(1), LV_GRID_FR(2), LV_GRID_TEMPLATE_LAST};

        /*Row 1: fix width 50 px
        *Row 2: 1 unit from the remaining free space
        *Row 3: fix width 50 px*/
        static std::vector<lv_coord_t> row_dsc = {50, LV_GRID_FR(1), 50, LV_GRID_TEMPLATE_LAST};

        /*Create a container with grid*/
        static auto cont = Container(scr_act());
        cont.set_size(300, 220);
        cont.center();
        cont.set_grid_dsc_array(col_dsc, row_dsc);

        for(uint32_t i = 0; i < 9; i++) {
            uint8_t col = i % 3;
            uint8_t row = i / 3;

            auto obj = Container(cont);
            /*Stretch the cell horizontally and vertically too
            *Set span to 1 to make the cell 1 column/row sized*/
            obj.set_grid_cell(LV_GRID_ALIGN_STRETCH, col, 1,
                              LV_GRID_ALIGN_STRETCH, row, 1);

            auto label = Label(obj);
            label.set_text_fmt("%d,%d", col, row);
            label.center();
            obj.release_ptr();
            label.release_ptr();
        }
    }
}