#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/tileview/tileview.h" // for Tileview
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/list/list.h" // for List

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void tileview_1() {
        static auto tileview = Tileview(scr_act());

        /*Tile1: just a label*/
        auto tile1 = tileview.add_tile(0, 0, LV_DIR_BOTTOM);
        static auto label1 = Label(tile1);
        label1.set_text("Scroll down");
        label1.center();

        /*Tile2: a button*/
        auto tile2 = tileview.add_tile(0, 1, LV_DIR_TOP | LV_DIR_RIGHT);
        static auto btn = Button(tile2);
        static auto label2 = Label(btn);
        label2.set_text("Scroll up or right");
        btn.set_size(LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        btn.center();

        /*Tile3: a list*/
        auto tile3 = tileview.add_tile(1, 1, LV_DIR_LEFT);
        static auto list = List(tile3);
        list.set_size(LV_PCT(100), LV_PCT(100));
        list.add_btn("", "One");
        list.add_btn("", "Two");
        list.add_btn("", "Three");
        list.add_btn("", "Four");
        list.add_btn("", "Five");
        list.add_btn("", "Six");
        list.add_btn("", "Seven");
        list.add_btn("", "Eight");
        list.add_btn("", "Nine");
        list.add_btn("", "Ten");
    }
}