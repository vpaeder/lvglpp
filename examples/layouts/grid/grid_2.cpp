#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/label/label.h" // for Label

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void grid_2() {
        static std::vector<lv_coord_t> col_dsc = {70, 70, 70, LV_GRID_TEMPLATE_LAST};
        static std::vector<lv_coord_t> row_dsc = {50, 50, 50, LV_GRID_TEMPLATE_LAST};

        /*Create a container with grid*/
        static auto cont = Container(scr_act());
        cont.set_style_grid_column_dsc_array(col_dsc, 0);
        cont.set_style_grid_row_dsc_array(row_dsc, 0);
        cont.set_size(300, 220);
        cont.center();
        cont.set_layout(LV_LAYOUT_GRID);

        /*Cell to 0;0 and align to to the start (left/top) horizontally and vertically too*/
        static auto obj1 = Container(cont);
        obj1.set_size(LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        obj1.set_grid_cell(LV_GRID_ALIGN_START, 0, 1,
                            LV_GRID_ALIGN_START, 0, 1);
        static auto label1 = Label(obj1);
        label1.set_text("c0, r0");

        /*Cell to 1;0 and align to to the start (left) horizontally and center vertically too*/
        static auto obj2 = Container(cont);
        obj2.set_size(LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        obj2.set_grid_cell(LV_GRID_ALIGN_START, 1, 1,
                           LV_GRID_ALIGN_CENTER, 0, 1);
        static auto label2 = Label(obj2);
        label2.set_text("c1, r0");

        /*Cell to 2;0 and align to to the start (left) horizontally and end (bottom) vertically too*/
        static auto obj3 = Container(cont);
        obj3.set_size(LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        obj3.set_grid_cell(LV_GRID_ALIGN_START, 2, 1,
                           LV_GRID_ALIGN_END, 0, 1);
        static auto label3 = Label(obj3);
        label3.set_text("c2, r0");

        /*Cell to 1;1 but 2 column wide (span = 2).Set width and height to stretched.*/
        static auto obj4 = Container(cont);
        obj4.set_size(LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        obj4.set_grid_cell(LV_GRID_ALIGN_STRETCH, 1, 2,
                           LV_GRID_ALIGN_STRETCH, 1, 1);
        static auto label4 = Label(obj4);
        label4.set_text("c1-2, r1");

        /*Cell to 0;1 but 2 rows tall (span = 2).Set width and height to stretched.*/
        static auto obj5 = Container(cont);
        obj5.set_size(LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        obj5.set_grid_cell(LV_GRID_ALIGN_STRETCH, 0, 1,
                           LV_GRID_ALIGN_STRETCH, 1, 2);
        static auto label5 = Label(obj5);
        label5.set_text("c0\nr1-2");
    }
}