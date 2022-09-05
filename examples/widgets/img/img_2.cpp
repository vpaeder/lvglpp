#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/image/image.h" // for Image
#include "lvglpp/widgets/slider/slider.h" // for Slider
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/color.h" // for colors

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    using SliderPtr = std::unique_ptr<Slider>;
    using ImagePtr = std::unique_ptr<Image>;

    static SliderPtr red_slider, green_slider, blue_slider, intense_slider;
    static ImagePtr img1;

    static void slider_event_cb(Event & e) {
        /*Recolor the image based on the sliders' values*/
        auto color  = lv_color_make(red_slider->get_value(), green_slider->get_value(),
                                          blue_slider->get_value());
        auto intense = intense_slider->get_value();
        img1->set_style_img_recolor_opa(intense, 0);
        img1->set_style_img_recolor(color, 0);
    }

    static SliderPtr create_slider(Object & parent, lv_color_t color) {
        auto slider = std::make_unique<Slider>(parent);
        slider.set_range(0, 255);
        slider.set_size(10, 200);
        slider.set_style_bg_color(color, LV_PART_KNOB);
        slider.set_style_bg_color(lv_color_darken(color, LV_OPA_40), LV_PART_INDICATOR);
        slider.add_event_cb(slider_event_cb, LV_EVENT_VALUE_CHANGED);
        return slider;
    }

    void image_2() {
        auto root = scr_act();
        
        /*Create 4 sliders to adjust RGB color and re-color intensity*/
        red_slider = create_slider(root, palette::main(Color::Red));
        green_slider = create_slider(root, palette::main(Color::Green));
        blue_slider = create_slider(root, palette::main(Color::Blue));
        intense_slider = create_slider(root, palette::main(Color::Grey));

        red_slider->set_value(LV_OPA_20, LV_ANIM_OFF);
        green_slider->set_value(LV_OPA_90, LV_ANIM_OFF);
        blue_slider->set_value(LV_OPA_60, LV_ANIM_OFF);
        intense_slider->set_value(LV_OPA_50, LV_ANIM_OFF);

        red_slider->align(LV_ALIGN_LEFT_MID, 25, 0);
        green_slider->align_to(*red_slider, LV_ALIGN_OUT_RIGHT_MID, 25, 0);
        blue_slider->align_to(*green_slider, LV_ALIGN_OUT_RIGHT_MID, 25, 0);
        intense_slider->align_to(*blue_slider, LV_ALIGN_OUT_RIGHT_MID, 25, 0);

        /*Now create the actual image*/
        static auto img = ImageDescriptor();
        img.set_src(img_cogwheel_argb_map, 100, 100, LV_IMG_CF_TRUE_COLOR_ALPHA);
        img1 = std::make_unique<Image>(root);
        img1->set_src(img);
        img1->align(LV_ALIGN_RIGHT_MID, -20, 0);

        intense_slider->send_event(LV_EVENT_VALUE_CHANGED);
    }
}