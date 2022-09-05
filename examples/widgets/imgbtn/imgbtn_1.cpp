#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/imgbtn/imgbtn.h" // for ImageButton
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/misc/style.h" // for Style, LinearStyleTransition
#include "lvglpp/misc/color.h" // for colors
#include <vector>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void imgbtn_1() {
        static std::vector<ImageDescriptor> btn_imgs(3);
        btn_imgs[0].set_src(imgbtn_left_map, 8, 50, LV_IMG_CF_TRUE_COLOR_ALPHA);
        btn_imgs[1].set_src(imgbtn_mid_map, 5, 49, LV_IMG_CF_TRUE_COLOR_ALPHA);
        btn_imgs[2].set_src(imgbtn_right_map, 8, 50, LV_IMG_CF_TRUE_COLOR_ALPHA);

        /*Create a transition animation on width transformation and recolor.*/
        std::vector<lv_style_prop_t> tr_prop = {LV_STYLE_TRANSFORM_WIDTH, LV_STYLE_IMG_RECOLOR_OPA, LV_STYLE_PROP_INV};
        static LinearStyleTransition tr(tr_prop, 200, 0);

        static Style style_def;
        style_def.set_text_color(palette::white());
        style_def.set_transition(tr);

        /*Darken the button when pressed and make it wider*/
        static Style style_pr;
        style_pr.set_img_recolor_opa(LV_OPA_30);
        style_pr.set_img_recolor(palette::black());
        style_pr.set_transform_width(20);

        /*Create an image button*/
        static auto imgbtn = ImageButton(scr_act());
        imgbtn.set_src_left_img(LV_IMGBTN_STATE_RELEASED, btn_imgs[0]);
        imgbtn.set_src_mid_img(LV_IMGBTN_STATE_RELEASED, btn_imgs[1]);
        imgbtn.set_src_right_img(LV_IMGBTN_STATE_RELEASED, btn_imgs[2]);
        imgbtn.add_style(style_def, LV_STATE_DEFAULT);
        imgbtn.add_style(style_pr, LV_STATE_PRESSED);

        imgbtn.align(LV_ALIGN_CENTER, 0, 0);

        /*Create a label on the image button*/
        static auto label = Label(imgbtn);
        label.set_text("Button");
        label.align(LV_ALIGN_CENTER, 0, -4);

    }
}