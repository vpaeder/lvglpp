#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/animimg/animimg.h" // for AnimatedImage
#include "lvglpp/draw/image.h" // for ImageDescriptor

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    
    void animimg_1() {
        static std::vector<ImageDescriptor> anim_imgs(3);

        anim_imgs[0].set_src(animimg001_map, 130, 170, LV_IMG_CF_TRUE_COLOR_ALPHA);
        anim_imgs[1].set_src(animimg002_map, 130, 170, LV_IMG_CF_TRUE_COLOR_ALPHA);
        anim_imgs[2].set_src(animimg003_map, 130, 170, LV_IMG_CF_TRUE_COLOR_ALPHA);

        static auto animimg = AnimatedImage(scr_act());
        animimg.center();
        animimg.set_src(anim_imgs);
        animimg.set_duration(1000);
        animimg.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        animimg.start();
    }
}