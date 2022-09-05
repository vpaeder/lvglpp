#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/slider/slider.h" // for Slider
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    std::unique_ptr<Label> slider_label;

    static void event_handler(Event & e) {
        auto slider = e.get_target<Slider>();
        slider_label->set_text(std::to_string(slider.get_value()) + "%");
        slider_label->align_to(slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
   }

    void slider_1() {
        auto root = scr_act();
        
        static auto slider = Slider(root);
        slider.center();
        slider.add_event_cb(event_handler, LV_EVENT_VALUE_CHANGED);

        /*Create a label below the slider*/
        slider_label = std::make_unique<Label>(root);
        slider_label->set_text("0%");

        slider_label->align_to(slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    }
}