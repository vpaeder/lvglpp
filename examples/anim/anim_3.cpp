#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/slider/slider.h" // for Slider
#include "lvglpp/misc/anim.h" // for Animation

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::misc;
    using namespace lvgl::widgets;

    static const lv_coord_t obj_width = 90;
    static const lv_coord_t obj_height = 70;

    using ContainerPtr = std::unique_ptr<Container>;
    using TimelinePtr = std::unique_ptr<AnimationTimeline>;
    ContainerPtr obj1, obj2, obj3;
    TimelinePtr anim_timeline;

    static void anim_timeline_create(void) {
        auto set_width = [](Container & obj, int32_t v) {
            obj.set_width(v);
        };
        auto set_height = [](Container & obj, int32_t v) {
            obj.set_height(v);
        };
        /* obj1 */
        static Animation a1;
        a1.set_var(*obj1);
        a1.set_values(0, obj_width);
        a1.set_early_apply(false);
        a1.set_exec_cb<Container>(set_width);
        a1.set_path_cb(lv_anim_path_overshoot);
        a1.set_time(300);

        static Animation a2;
        a2.set_var(*obj1);
        a2.set_values(0, obj_height);
        a2.set_early_apply(false);
        a2.set_exec_cb<Container>(set_height);
        a2.set_path_cb(lv_anim_path_ease_out);
        a2.set_time(300);

        /* obj2 */
        static Animation a3;
        a3.set_var(*obj2);
        a3.set_values(0, obj_width);
        a3.set_early_apply(false);
        a3.set_exec_cb<Container>(set_width);
        a3.set_path_cb(lv_anim_path_overshoot);
        a3.set_time(300);

        static Animation a4;
        a4.set_var(*obj2);
        a4.set_values(0, obj_height);
        a4.set_early_apply(false);
        a4.set_exec_cb<Container>(set_height);
        a4.set_path_cb(lv_anim_path_ease_out);
        a4.set_time(300);

        /* obj3 */
        static Animation a5;
        a5.set_var(*obj3);
        a5.set_values(0, obj_width);
        a5.set_early_apply(false);
        a5.set_exec_cb<Container>(set_width);
        a5.set_path_cb(lv_anim_path_overshoot);
        a5.set_time(300);

        static Animation a6;
        a6.set_var(*obj3);
        a6.set_values(0, obj_height);
        a6.set_early_apply(false);
        a6.set_exec_cb<Container>(set_height);
        a6.set_path_cb(lv_anim_path_ease_out);
        a6.set_time(300);

        /* Create anim timeline */
        anim_timeline = std::make_unique<AnimationTimeline>();
        anim_timeline->add(0, a1);
        anim_timeline->add(0, a2);
        anim_timeline->add(200, a3);
        anim_timeline->add(200, a4);
        anim_timeline->add(400, a5);
        anim_timeline->add(400, a6);
    }

    static void btn_start_event_handler(Event & e) {
        auto btn = e.get_target<Button>();
        if(anim_timeline == nullptr)
            anim_timeline_create();

        bool reverse = btn.has_state(LV_STATE_CHECKED);
        anim_timeline->set_reverse(reverse);
        anim_timeline->start();
    }

    static void btn_del_event_handler(Event & e) {
        if(anim_timeline != nullptr)
            anim_timeline = nullptr;
    }

    static void btn_stop_event_handler(Event & e) {
        if(anim_timeline != nullptr)
            anim_timeline->stop();
    }

    static void slider_prg_event_handler(Event & e) {
        auto slider = e.get_target<Slider>();

        if (anim_timeline == nullptr)
            anim_timeline_create();

        int32_t progress = slider.get_value();
        anim_timeline->set_progress(progress);
    }

    void anim_3() {
        auto root = scr_act();
        root.set_flex_flow(LV_FLEX_FLOW_ROW);
        root.set_flex_align(LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        /* create btn_start */
        static auto btn_start = Button(root);
        btn_start.add_event_cb(btn_start_event_handler, LV_EVENT_VALUE_CHANGED);
        btn_start.add_flag(LV_OBJ_FLAG_IGNORE_LAYOUT);
        btn_start.add_flag(LV_OBJ_FLAG_CHECKABLE);
        btn_start.align(LV_ALIGN_TOP_MID, -100, 20);

        static auto label_start = Label(btn_start);
        label_start.set_text("Start");
        label_start.center();

        /* create btn_del */
        static auto btn_del = Button(root);
        btn_del.add_event_cb(btn_del_event_handler, LV_EVENT_CLICKED);
        btn_del.add_flag(LV_OBJ_FLAG_IGNORE_LAYOUT);
        btn_del.align(LV_ALIGN_TOP_MID, 0, 20);

        static auto label_del = Label(btn_del);
        label_del.set_text("Delete");
        label_del.center();

        /* create btn_stop */
        static auto btn_stop = Button(root);
        btn_stop.add_event_cb(btn_stop_event_handler, LV_EVENT_CLICKED);
        btn_stop.add_flag(LV_OBJ_FLAG_IGNORE_LAYOUT);
        btn_stop.align(LV_ALIGN_TOP_MID, 100, 20);

        static auto label_stop = Label(btn_stop);
        label_stop.set_text("Stop");
        label_stop.center();

        /* create slider_prg */
        static auto slider_prg = Slider(root);
        slider_prg.add_event_cb(slider_prg_event_handler, LV_EVENT_VALUE_CHANGED);
        slider_prg.add_flag(LV_OBJ_FLAG_IGNORE_LAYOUT);
        slider_prg.align(LV_ALIGN_BOTTOM_MID, 0, -20);
        slider_prg.set_range(0, 65535);

        /* create 3 objects */
        obj1 = std::make_unique<Container>(root);
        obj1->set_size(obj_width, obj_height);

        obj2 = std::make_unique<Container>(root);
        obj2->set_size(obj_width, obj_height);

        obj3 = std::make_unique<Container>(root);
        obj3->set_size(obj_width, obj_height);
    }
}