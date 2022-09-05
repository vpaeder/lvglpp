#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/image/image.h" // for Image

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    void image_1() {
        auto root = scr_act();
        
        static auto img = ImageDescriptor();
        img.set_src(img_cogwheel_argb_map, 100, 100, LV_IMG_CF_TRUE_COLOR_ALPHA);

        static auto img1 = Image(root);
        img1.set_src(img);
        img1.align(LV_ALIGN_CENTER, 0, -20);
        img1.set_size(200, 200);

        static auto img2 = Image(root);
        img2.set_src(LV_SYMBOL_OK "Accept");
        img2.align_to(img1, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    }
}