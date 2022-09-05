#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/slider/slider.h" // for Slider

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    std::unique_ptr<Label> label;

    void get_started_3() {
        /*Create a slider in the center of the display*/
        auto root = scr_act();
        static auto slider = Slider(root);
        slider.set_width(200);                          /*Set the width*/
        slider.center();                                  /*Align to the center of the parent (screen)*/
        auto slider_event_cb = [](Event & e) {
            auto slider = e.get_target<Slider>();
            /*Refresh the text*/
            label->set_text_fmt("%" LV_PRId32, slider.get_value());
            label->align_to(slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
        };
        slider.add_event_cb(slider_event_cb, LV_EVENT_VALUE_CHANGED);     /*Assign an event function*/

        /*Create a label below the slider*/
        label = std::make_unique<Label>(root);
        label->set_text("0");
        label->align_to(slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
    }
}