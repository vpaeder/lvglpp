#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void grid_1() {
        static std::vector<lv_coord_t> col_dsc = {70, 70, 70, LV_GRID_TEMPLATE_LAST};
        static std::vector<lv_coord_t> row_dsc = {50, 50, 50, LV_GRID_TEMPLATE_LAST};

        /*Create a container with grid*/
        static auto cont = Container(scr_act());
        cont.set_style_grid_column_dsc_array(col_dsc, 0);
        cont.set_style_grid_row_dsc_array(row_dsc, 0);
        cont.set_size(300, 220);
        cont.center();
        cont.set_layout(LV_LAYOUT_GRID);

        for(uint32_t i = 0; i < 9; i++) {
            uint8_t col = i % 3;
            uint8_t row = i / 3;
            auto obj = Button(cont);
            /*Stretch the cell horizontally and vertically too
            *Set span to 1 to make the cell 1 column/row sized*/
            obj.set_grid_cell(LV_GRID_ALIGN_STRETCH, col, 1,
                              LV_GRID_ALIGN_STRETCH, row, 1);

            auto label = Label(obj);
            label.set_text_fmt("c%d, r%d", col, row);
            label.center();
            obj.release_ptr();
            label.release_ptr();
        }
    }
}