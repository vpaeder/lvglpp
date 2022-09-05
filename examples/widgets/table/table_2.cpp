#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/table/table.h" // for Table
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    #define ITEM_CNT 200

    static void draw_event_cb(Event & e) {
        auto obj = e.get_target<Table>();
        auto dsc = e.get_draw_part_dsc();
        /*If the cells are drawn...*/
        if(dsc->part == LV_PART_ITEMS) {
            bool chk = obj.has_cell_ctrl(dsc->id, 0, LV_TABLE_CELL_CTRL_CUSTOM_1);
            
            RectangleDrawDescriptor rect_dsc;
            rect_dsc->bg_color = chk ? obj.get_color_primary() : palette::light(Color::Grey, 2);
            rect_dsc->radius = LV_RADIUS_CIRCLE;

            Area sw_area;
            sw_area->x1 = dsc->draw_area->x2 - 50;
            sw_area->x2 = sw_area->x1 + 40;
            sw_area->y1 = dsc->draw_area->y1 + Area(dsc->draw_area).get_height() / 2 - 10;
            sw_area->y2 = sw_area->y1 + 20;
            rect_dsc.draw(dsc->draw_ctx, sw_area);

            rect_dsc.bg_color = palette::white();
            if(chk) {
                sw_area->x2 -= 2;
                sw_area->x1 = sw_area->x2 - 16;
            } else {
                sw_area.x1 += 2;
                sw_area->x2 = sw_area->x1 + 16;
            }
            sw_area->y1 += 2;
            sw_area->y2 -= 2;
            rect_dsc.draw(dsc->draw_ctx, sw_area);
        }
    }

    static void change_event_cb(Event & e)
    {
        auto obj = e.get_target<Table>();
        auto row = std::get<1>(obj.get_selected_cell());
        bool chk = obj.has_cell_ctrl(row, 0, LV_TABLE_CELL_CTRL_CUSTOM_1);
        if(chk) obj.clear_cell_ctrl(row, 0, LV_TABLE_CELL_CTRL_CUSTOM_1);
        else obj.add_cell_ctrl(row, 0, LV_TABLE_CELL_CTRL_CUSTOM_1);
    }

    void table_2() {
        /*Measure memory usage*/
        lv_mem_monitor_t mon1;
        lv_mem_monitor(&mon1);

        uint32_t t = lv_tick_get();

        auto root = scr_act();
        
        static auto table = Table(root);

        /*Set a smaller height to the table. It'll make it scrollable*/
        table.set_size(LV_SIZE_CONTENT, 200);

        table.set_col_width(0, 150);
        table.set_row_cnt(ITEM_CNT); /*Not required but avoids a lot of memory reallocation lv_table_set_set_value*/
        table.set_col_cnt(1);

        /*Don't make the cell pressed, we will draw something different in the event*/
        table.remove_style(LV_PART_ITEMS | LV_STATE_PRESSED);

        for(uint32_t i = 0; i < ITEM_CNT; i++) {
            table.set_cell_value_fmt(i, 0, "Item %u", i + 1);
        }

        table.align(LV_ALIGN_CENTER, 0, -20);

        /*Add an event callback to to apply some custom drawing*/
        table.add_event_cb(draw_event_cb, LV_EVENT_DRAW_PART_END);
        table.add_event_cb(change_event_cb, LV_EVENT_VALUE_CHANGED);

        lv_mem_monitor_t mon2;
        lv_mem_monitor(&mon2);

        uint32_t mem_used = mon1.free_size - mon2.free_size;

        uint32_t elaps = lv_tick_elaps(t);

        static auto label = Label(root);
        label.set_text_fmt("%u items were created in %u ms\n"
                           "using %u bytes of memory",
                           ITEM_CNT, elaps, mem_used);

        label.align(LV_ALIGN_BOTTOM_MID, 0, -10);
    }
}