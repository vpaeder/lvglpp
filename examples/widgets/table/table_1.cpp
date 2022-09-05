#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/table/table.h" // for Table
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    static void draw_part_event_cb(Event & e) {
        auto obj = e.get_target<Table>();
        auto dsc = e.get_param<lv_obj_draw_part_dsc_t>();
        /*If the cells are drawn...*/
        if(dsc->part == LV_PART_ITEMS) {
            uint32_t row = dsc->id /  obj.get_col_cnt();
            uint32_t col = dsc->id - row * obj.get_col_cnt();

            /*Make the texts in the first cell center aligned*/
            if(row == 0) {
                dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;
                dsc->rect_dsc->bg_color = color::mix(palette::main(Color::Blue), dsc->rect_dsc->bg_color, LV_OPA_20);
                dsc->rect_dsc->bg_opa = LV_OPA_COVER;
            }
            /*In the first column align the texts to the right*/
            else if(col == 0) {
                dsc->label_dsc->align = LV_TEXT_ALIGN_RIGHT;
            }

            /*MAke every 2nd row grayish*/
            if((row != 0 && row % 2) == 0) {
                dsc->rect_dsc->bg_color = color::mix(palette::main(Color::Grey), dsc->rect_dsc->bg_color, LV_OPA_10);
                dsc->rect_dsc->bg_opa = LV_OPA_COVER;
            }
        }
    }

    void table_1() {
        static auto table = Table(scr_act());

        /*Fill the first column*/
        table.set_cell_value(0, 0, "Name");
        table.set_cell_value(1, 0, "Apple");
        table.set_cell_value(2, 0, "Banana");
        table.set_cell_value(3, 0, "Lemon");
        table.set_cell_value(4, 0, "Grape");
        table.set_cell_value(5, 0, "Melon");
        table.set_cell_value(6, 0, "Peach");
        table.set_cell_value(7, 0, "Nuts");

        /*Fill the second column*/
        table.set_cell_value(0, 1, "Price");
        table.set_cell_value(1, 1, "$7");
        table.set_cell_value(2, 1, "$4");
        table.set_cell_value(3, 1, "$6");
        table.set_cell_value(4, 1, "$2");
        table.set_cell_value(5, 1, "$5");
        table.set_cell_value(6, 1, "$1");
        table.set_cell_value(7, 1, "$9");

        /*Set a smaller height to the table. It'll make it scrollable*/
        table.set_height(200);
        table.center();

        /*Add an event callback to to apply some custom drawing*/
        table.add_event_cb(draw_part_event_cb, LV_EVENT_DRAW_PART_BEGIN);
    }
}