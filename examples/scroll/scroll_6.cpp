#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/widgets/button/button.h" // for Button
#include "lvglpp/misc/area.h" // for Area

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    static void scroll_event_cb(Event & e) {
        auto cont = e.get_target<Object>();
        Area cont_a = cont.get_coords();

        auto cont_y_center = cont_a->y1 + cont_a.get_height() / 2;
        auto r = cont.get_height() * 7 / 10;

        uint32_t child_cnt = cont.get_child_cnt();
        for(uint32_t i = 0; i < child_cnt; i++) {
            auto child = cont.get_child<Object>(i);
            Area child_a = child.get_coords();

            auto child_y_center = child_a->y1 + child_a.get_height() / 2;
            auto diff_y = child_y_center - cont_y_center;
            diff_y = LV_ABS(diff_y);
            /*Get the x of diff_y on a circle.*/
            lv_coord_t x;
            /*If diff_y is out of the circle use the last point of the circle (the radius)*/
            if(diff_y >= r) {
                x = r;
            } else {
                /*Use Pythagoras theorem to get x from radius and y*/
                uint32_t x_sqr = r * r - diff_y * diff_y;
                lv_sqrt_res_t res;
                lv_sqrt(x_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
                x = r - res.i;
            }
            /*Translate the item by the calculated X coordinate*/
            child.set_style_translate_x(x, 0);
            /*Use some opacity with larger translations*/
            lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
            child.set_style_opa(LV_OPA_COVER - opa, 0);
        }
    }

    void scroll_6() {
        static auto cont = Container(scr_act());
        cont.set_size(200, 200);
        cont.center();
        cont.set_flex_flow(LV_FLEX_FLOW_COLUMN);
        cont.add_event_cb(scroll_event_cb, LV_EVENT_SCROLL);
        cont.set_style_radius(LV_RADIUS_CIRCLE, 0);
        cont.set_style_clip_corner(true, 0);
        cont.set_scroll_dir(LV_DIR_VER);
        cont.set_scroll_snap_y(LV_SCROLL_SNAP_CENTER);
        cont.set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);

        for(uint32_t i = 0; i < 20; i++) {
            auto btn = Button(cont);
            btn.set_width(lv_pct(100));
            auto label = Label(btn);
            labelset_text_fmt("Button %" LV_PRIu32, i);
            btn.release_ptr();
            label.release_ptr();
        }
        /*Update the buttons position manually for first*/
        cont.send_event(cont, LV_EVENT_SCROLL);
        /*Be sure the fist button is in the middle*/
        cont.get_child<Object>(0).scroll_to_view(LV_ANIM_OFF);
    }
}