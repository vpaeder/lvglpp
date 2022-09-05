#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/checkbox/checkbox.h" // for Checkbox
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    static std::vector<uint32_t> active_index{0,0};

    static Style style_radio;
    static Style style_radio_chk;

    static void radio_event_handler(Event & e) {
        auto cont = e.get_current_target<Container>();
        auto act_cb = e.get_target<Checkbox>();
        auto old_cb = cont.get_child<Checkbox>(active_index[cont.get_index()]);

        /*Do nothing if the container was clicked*/
        if(cont == act_cb) return;

        old_cb.clear_state(LV_STATE_CHECKED);   /*Uncheck the previous radio button*/
        act_cb.add_state(LV_STATE_CHECKED);     /*Uncheck the current radio button*/
        
        active_index[cont.get_index()] = act_cb.get_index();

        LV_LOG_USER("Selected radio buttons: %d, %d", (int)active_index[0], (int)active_index[1]);
    }

    static std::unique_ptr<Checkbox> radiobutton_create(Object & parent, const std::string & txt) {
        auto obj = std::make_unique<Checkbox>(parent);
        obj->set_text(txt);
        obj->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
        obj->add_style(style_radio, LV_PART_INDICATOR);
        obj->add_style(style_radio_chk, LV_PART_INDICATOR | LV_STATE_CHECKED);
        return obj;
    }

    void checkbox_2() {
        auto root = scr_act();

        style_radio.set_radius(LV_RADIUS_CIRCLE);
        style_radio_chk.set_bg_img_src(nullptr);

        uint32_t i;

        static auto cont1 = Container(root);
        cont1.set_flex_flow(LV_FLEX_FLOW_COLUMN);
        cont1.set_size(lv_pct(40), lv_pct(80));
        cont1.add_event_cb(radio_event_handler, LV_EVENT_CLICKED);
        static std::vector<std::unique_ptr<Checkbox>> rb;

        for(i = 0; i < 5; i++)
            rb.push_back(radiobutton_create(cont1, "A " + std::to_string(i+1)));
        
        /*Make the first checkbox checked*/
        cont1.get_child<Checkbox>(0).add_state(LV_STATE_CHECKED);

        static auto cont2 = Container(root);
        cont2.set_flex_flow(LV_FLEX_FLOW_COLUMN);
        cont2.set_size(lv_pct(40), lv_pct(80));
        cont2.set_x(lv_pct(50));
        cont2.add_event_cb(radio_event_handler, LV_EVENT_CLICKED);

        for(i = 0; i < 3; i++)
            rb.push_back(radiobutton_create(cont2, "B " + std::to_string(i+1)));

        /*Make the first checkbox checked*/
        cont2.get_child<Checkbox>(0).add_state(LV_STATE_CHECKED);
    }
}