#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/canvas/canvas.h" // for Canvas
#include "lvglpp/draw/mask.h" // for MapMask
#include "lvglpp/draw/desc.h" // for LabelDrawDescriptor
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::draw;
    using namespace lvgl::misc;

    #define MASK_WIDTH 100
    #define MASK_HEIGHT 45
    /* Create the mask of a text by drawing it to a canvas*/
    static std::vector<lv_opa_t> mask_map(MASK_WIDTH * MASK_HEIGHT);

    static void add_mask_event_cb(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<Container>();
        static std::unique_ptr<MapMask> mask_part;

        if(code == LV_EVENT_COVER_CHECK) {
            e.set_cover_res(LV_COVER_RES_MASKED);
        }
        else if(code == LV_EVENT_DRAW_MAIN_BEGIN) {
            mask_part = std::make_unique<MapMask>(obj->coords, mask_map);
            mask_part->add();
        }
        else if(code == LV_EVENT_DRAW_MAIN_END) {
            mask_part = nullptr;
        }
    }

    void label_4() {
        auto root = scr_act();

        /*Create a "8 bit alpha" canvas and clear it*/
        auto canvas = std::make_unique<Canvas>(root);
        canvas->set_buffer<lv_opa_t>(mask_map, MASK_WIDTH, MASK_HEIGHT, LV_IMG_CF_ALPHA_8BIT);
        canvas->fill_bg(palette::black(), LV_OPA_TRANSP);
        
        /*Draw a label to the canvas. The result "image" will be used as mask*/
        LabelDrawDescriptor label_dsc;
        label_dsc->color = palette::white();
        label_dsc->align = LV_TEXT_ALIGN_CENTER;
        canvas->draw_text(5, 5, MASK_WIDTH, label_dsc, "Text with gradient");

        /*The canvas is not required anymore*/
        canvas = nullptr;

        /* Create an object from where the text will be masked out.
        * Now it's a rectangle with a gradient but it could be an image too*/
        static auto grad = Container(root);
        grad.set_size(MASK_WIDTH, MASK_HEIGHT);
        grad.center();
        grad.set_style_bg_color(lv_color_hex(0xff0000), 0);
        grad.set_style_bg_grad_color(lv_color_hex(0x0000ff), 0);
        grad.set_style_bg_grad_dir(LV_GRAD_DIR_HOR, 0);
        grad.add_event_cb(add_mask_event_cb, LV_EVENT_ALL);
    }
}