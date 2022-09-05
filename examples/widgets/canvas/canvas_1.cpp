#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/canvas/canvas.h" // for Canvas
#include "lvglpp/misc/color.h" // for colors

#define CANVAS_WIDTH  200
#define CANVAS_HEIGHT  150

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void canvas_1() {
        RectangleDrawDescriptor rect_dsc;
        rect_dsc->radius = 10;
        rect_dsc->bg_opa = LV_OPA_COVER;
        rect_dsc->bg_grad.dir = LV_GRAD_DIR_HOR;
        rect_dsc->bg_grad.stops[0].color = palette::main(Color::Red);
        rect_dsc->bg_grad.stops[1].color = palette::main(Color::Blue);
        rect_dsc->border_width = 2;
        rect_dsc->border_opa = LV_OPA_90;
        rect_dsc->border_color = palette::white();
        rect_dsc->shadow_width = 5;
        rect_dsc->shadow_ofs_x = 5;
        rect_dsc->shadow_ofs_y = 5;

        LabelDrawDescriptor label_dsc;
        label_dsc->color = palette::main(Color::Orange);

        static std::vector<lv_color_t> cbuf(LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_WIDTH, CANVAS_HEIGHT));

        auto canvas = Canvas(scr_act());
        canvas.set_buffer(cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
        canvas.center();
        canvas.fill_bg(palette::light(Color::Grey, 3), LV_OPA_COVER);
        
        canvas.draw_rect(70, 60, 100, 70, rect_dsc);
        canvas.draw_text(40, 20, 100, label_dsc, "Some text on text canvas");

        /*Test the rotation. It requires another buffer where the original image is stored.
        *So copy the current image to buffer and rotate it to the canvas*/
        static std::vector<lv_color_t> cbuf_tmp[CANVAS_WIDTH * CANVAS_HEIGHT];
        std::copy(cbuf.begin(), cbuf.end(), std::back_inserter(cbuf_tmp));
        ImageDescriptor img;
        img.set_src(cbuf_tmp, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);

        canvas.fill_bg(palette::light(Color::Grey, 3), LV_OPA_COVER);
        canvas.set_buffer(img);
        canvas.transform(120, LV_IMG_ZOOM_NONE, 0, 0, CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, true);
    }
}