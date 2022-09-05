#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void grid_4() {
        static std::vector<lv_coord_t> col_dsc = {60, 60, 60, LV_GRID_TEMPLATE_LAST};
        static std::vector<lv_coord_t> row_dsc = {45, 45, 45, LV_GRID_TEMPLATE_LAST};

        /*Create a container with grid*/
        static auto cont = Container(scr_act());
        cont.set_size(300, 220);
        cont.center();
        cont.set_grid_dsc_array(col_dsc, row_dsc);
        cont.set_grid_align(LV_GRID_ALIGN_SPACE_BETWEEN, LV_GRID_ALIGN_END);
 
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