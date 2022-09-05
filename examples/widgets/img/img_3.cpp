#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/image/image.h" // for Image
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/anim.h" // for Animation

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void image_3() {
        static auto img_src = ImageDescriptor();
        img_src.set_src(img_cogwheel_argb_map, 100, 100, LV_IMG_CF_TRUE_COLOR_ALPHA);

        /*Now create the actual image*/
        static auto img = Image(scr_act());
        img.set_src(img_src);
        img.align(LV_ALIGN_CENTER, 50, 50);
        img.set_pivot(0, 0);    /*Rotate around the top left corner*/

        static Animation a1, a2;
        a1.set_var(img);
        auto set_angle = [](Image & img, int32_t v) {
            img.set_angle(v);
        };
        a1.set_exec_cb<Image>(set_angle);
        a1.set_values(0, 3600);
        a1.set_time(5000);
        a1.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a1.start();

        a2.set_var(img);
        auto set_zoom = [](Image & img, int32_t v) {
            img.set_zoom(v);
        };
        a2.set_exec_cb<Image>(set_zoom);
        a2.set_values(128, 256);
        a2.set_time(5000);
        a2.set_playback_time(3000);
        a2.set_repeat_count(LV_ANIM_REPEAT_INFINITE);
        a2.start();
    }
}