#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/core/object.h" // for Container
#include "lvglpp/widgets/label/label.h" // for Label
#include "lvglpp/misc/style.h" // for Style

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    void scroll_4() {
        static auto obj = Container(scr_act());
        obj.set_size(200, 100);
        obj.center();

        static auto label = Label(obj);
        label.set_text("Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n"
                       "Etiam dictum, tortor vestibulum lacinia laoreet, mi neque consectetur neque, vel mattis odio dolor egestas ligula. \n"
                       "Sed vestibulum sapien nulla, id convallis ex porttitor nec. \n"
                       "Duis et massa eu libero accumsan faucibus a in arcu. \n"
                       "Ut pulvinar odio lorem, vel tempus turpis condimentum quis. Nam consectetur condimentum sem in auctor. \n"
                       "Sed nisl augue, venenatis in blandit et, gravida ac tortor. \n"
                       "Etiam dapibus elementum suscipit. \n"
                       "Proin mollis sollicitudin convallis. \n"
                       "Integer dapibus tempus arcu nec viverra. \n"
                       "Donec molestie nulla enim, eu interdum velit placerat quis. \n"
                       "Donec id efficitur risus, at molestie turpis. \n"
                       "Suspendisse vestibulum consectetur nunc ut commodo. \n"
                       "Fusce molestie rhoncus nisi sit amet tincidunt. \n"
                       "Suspendisse a nunc ut magna ornare volutpat.");

        /*Remove the style of scrollbar to have clean start*/
        obj.remove_style(LV_PART_SCROLLBAR | LV_STATE_ANY);

        /*Create a transition the animate the some properties on state change*/
        static const std::vector<lv_style_prop_t> props = {LV_STYLE_BG_OPA, LV_STYLE_WIDTH, LV_STYLE_PROP_INV};
        static LinearStyleTransition trans(props, 200, 0);

        /*Create a style for the scrollbars*/
        static Style style;
        style.set_width(4);      /*Width of the scrollbar*/
        style.set_pad_right(5);  /*Space from the parallel side*/
        style.set_pad_top(5);    /*Space from the perpendicular side*/
        style.set_radius(2);
        style.set_bg_opa(LV_OPA_70);
        style.set_bg_color(lv_palette_main(LV_PALETTE_BLUE));
        style.set_border_color(lv_palette_darken(LV_PALETTE_BLUE, 3));
        style.set_border_width(2);
        style.set_shadow_width(8);
        style.set_shadow_spread(2);
        style.set_shadow_color(lv_palette_darken(LV_PALETTE_BLUE, 1));
        style.set_transition(trans);

        /*Make the scrollbars wider and use 100% opacity when scrolled*/
        static Style style_scrolled;
        style_scrolled.set_width(8);
        style_scrolled.set_bg_opa(LV_OPA_COVER);

        obj.add_style(style, LV_PART_SCROLLBAR);
        obj.add_style(style_scrolled, LV_PART_SCROLLBAR | LV_STATE_SCROLLED);
    }
}