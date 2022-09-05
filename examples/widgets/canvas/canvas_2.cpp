#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/canvas/canvas.h" // for Canvas
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/misc/color.h" // for colors

#define CANVAS_WIDTH  50
#define CANVAS_HEIGHT  50

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void canvas_2() {
        auto root = scr_act();
        auto btn = Button(root);

        static std::vector<lv_color_t> cbuf(LV_CANVAS_BUF_SIZE_INDEXED_1BIT(CANVAS_WIDTH, CANVAS_HEIGHT));

        auto canvas = Canvas(root);

        canvas.set_buffer(cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_INDEXED_1BIT);
        canvas.set_palette(0, LV_COLOR_CHROMA_KEY);
        canvas.set_palette(1, palette::main(Color::Red));

        /*Create colors with the indices of the palette*/
        lv_color_t c0;
        lv_color_t c1;

        c0.full = 0;
        c1.full = 1;

        /*Red background (There is no dedicated alpha channel in indexed images so LV_OPA_COVER is ignored)*/
        canvas.fill_bg(c1, LV_OPA_COVER);

        /*Create hole on the canvas*/
        uint32_t x;
        uint32_t y;
        for(y = 10; y < 30; y++)
            for(x = 5; x < 20; x++)
                canvas.set_px_color(x, y, c0);
    }
}