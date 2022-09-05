#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/list/list.h" // for List
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/core/event.h" // for Event

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    using ListPtr = std::shared_ptr<List>;
    using ButtonPtr = std::shared_ptr<Button>;
    using LabelPtr = std::shared_ptr<Label>;
    ListPtr list1, list2;
    ButtonPtr currentButton;

    static void event_handler(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<Button>();
        if(code == LV_EVENT_CLICKED) {
            LV_LOG_USER("Clicked: %s", list1->get_btn_text(obj).c_str());

            auto parent = obj.get_parent<Object>();
            uint32_t i;
            for(i = 0; i < parent.get_child_cnt(); i++) {
                auto child = parent.get_child<Button>(i);
                child.clear_state(LV_STATE_CHECKED);
            }
            if (*currentButton == obj) {
                currentButton = nullptr;
            } else {
                currentButton = obj.get_shared();
                obj.add_state(LV_STATE_CHECKED);
            }
        }
    }

    static void event_handler_top(Event & e) {
        auto code = e.get_code();
        if(code == LV_EVENT_CLICKED) {
            if(currentButton == nullptr) return;
            currentButton->to_background();
            currentButton->scroll_to_view(LV_ANIM_ON);
        }
    }

    static void event_handler_up(Event & e) {
        auto code = e.get_code();
        if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
            if (currentButton == nullptr) return;
            uint32_t index = currentButton->get_index();
            if(index <= 0) return;
            currentButton->move_to_index(index - 1);
            currentButton->scroll_to_view(LV_ANIM_ON);
        }
    }

    static void event_handler_center(Event & e) {
        auto code = e.get_code();
        if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
            if (currentButton == nullptr) return;
            auto parent = currentButton->get_parent<Object>();
            const uint32_t pos = parent.get_child_cnt() / 2;
            currentButton->move_to_index(pos);
            currentButton->scroll_to_view(LV_ANIM_ON);
        }
    }

    static void event_handler_dn(Event & e) {
        auto code = e.get_code();
        if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
            if (currentButton == nullptr) return;
            const uint32_t index = currentButton->get_index();
            currentButton->move_to_index(index + 1);
            currentButton->scroll_to_view(LV_ANIM_ON);
        }
    }


    static void event_handler_bottom(Event & e) {
        auto code = e.get_code();
        if(code == LV_EVENT_CLICKED) {
            if (currentButton == nullptr) return;
            currentButton->to_foreground();
            currentButton->scroll_to_view(LV_ANIM_ON);
        }
    }

    static void event_handler_swap(Event & e) {
        auto code = e.get_code();
        // lv_obj_t* obj = lv_event_get_target(e);
        if((code == LV_EVENT_CLICKED) || (code == LV_EVENT_LONG_PRESSED_REPEAT)) {
            uint32_t cnt = list1->get_child_cnt();
            for(int i = 0; i < 100; i++)
                if(cnt > 1) {
                    auto obj = list1->get_child<Object>(rand() % cnt);
                    obj.move_to_index(rand() % cnt);
                    if(currentButton != nullptr)
                        currentButton->scroll_to_view(LV_ANIM_ON);
                }
        }
    }


    void list_2() {
        auto root = scr_act();

        /*Create a list*/
        list1 = std::make_shared<List>(root);
        list1->set_size(lv_pct(60), lv_pct(100));
        list1->set_style_pad_row(5, 0);

        /*Add buttons to the list*/
        std::vector<ButtonPtr> buttons;
        std::vector<LabelPtr> labels;
        int i;
        for(i = 0; i < 15; i++) {
            buttons.emplace_back(std::make_shared<Button>(*list1));
            buttons[i]->set_width(lv_pct(50));
            buttons[i]->add_event_cb(event_handler, LV_EVENT_CLICKED);
            labels.emplace_back(std::make_shared<Label>(*buttons[i]));
            labels[i]->set_text_fmt("Item %d", i);
        }

        /*Select the first button by default*/
        currentButton = list1->get_child<Button>(0).get_shared<Button>();
        currentButton->add_state(LV_STATE_CHECKED);

        /*Create a second list with up and down buttons*/
        list2 = std::make_shared<List>(root);
        list2->set_size(lv_pct(40), lv_pct(100));
        list2->align(LV_ALIGN_TOP_RIGHT, 0, 0);
        list2->set_flex_flow(LV_FLEX_FLOW_COLUMN);
        
        {auto btn = list2->add_btn("Top");
        btn.add_event_cb(event_handler_top, LV_EVENT_ALL);
        btn.remove_from_group();}

        {auto btn = list2->add_btn(LV_SYMBOL_UP, "Up");
        btn.add_event_cb(event_handler_up, LV_EVENT_ALL);
        btn.remove_from_group();}

        {auto btn = list2->add_btn(LV_SYMBOL_LEFT, "Center");
        btn.add_event_cb(event_handler_center, LV_EVENT_ALL);
        btn.remove_from_group();}

        {auto btn = list2->add_btn(LV_SYMBOL_DOWN, "Down");
        btn.add_event_cb(event_handler_dn, LV_EVENT_ALL);
        btn.remove_from_group();}

        {auto btn = list2->add_btn("Bottom");
        btn.add_event_cb(event_handler_bottom, LV_EVENT_ALL);
        btn.remove_from_group();}

        {auto btn = list2->add_btn(LV_SYMBOL_SHUFFLE, "Shuffle");
        btn.add_event_cb(event_handler_swap, LV_EVENT_ALL);
        btn.remove_from_group();}
    }
}