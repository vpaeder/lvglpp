#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/btnmatrix/btnmatrix.h" // for ButtonMatrix
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/style.h" // for Style
#include "lvglpp/misc/color.h" // for colors
#include <vector>
#include <string>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;
    using namespace lvgl::misc;

    static void event_cb(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<ButtonMatrix>();
        
        if(code == LV_EVENT_DRAW_PART_BEGIN) {
            auto dsc = e.get_draw_part_dsc();

            /*Change the draw descriptor the 2nd button*/
            if(dsc->id == 1) {
                dsc->rect_dsc->radius = 0;
                if(obj.get_selected_btn() == dsc->id)  dsc->rect_dsc->bg_color = palette::dark(Color::Blue, 3);
                else dsc->rect_dsc->bg_color = palette::main(Color::Blue);

                dsc->rect_dsc->shadow_width = 6;
                dsc->rect_dsc->shadow_ofs_x = 3;
                dsc->rect_dsc->shadow_ofs_y = 3;
                dsc->label_dsc->color = palette::white();
            }
            /*Change the draw descriptor the 3rd button*/
            else if(dsc->id == 2) {
                dsc->rect_dsc->radius = LV_RADIUS_CIRCLE;
                if(obj.get_selected_btn() == dsc->id)  dsc->rect_dsc->bg_color = palette::dark(Color::Red, 3);
                else dsc->rect_dsc->bg_color = palette::main(Color::Red);

                dsc->label_dsc->color = palette::white();
            }
            else if(dsc->id == 3) {
                dsc->label_dsc->opa = LV_OPA_TRANSP; /*Hide the text if any*/

            }
        }
        if(code == LV_EVENT_DRAW_PART_END) {
            auto dsc = e.get_draw_part_dsc();

            /*Add custom content to the 4th button when the button itself was drawn*/
            if(dsc->id == 3) {
                auto img = ImageDescriptor();
                img.set_src(img_star_map, 30, 29, LV_IMG_PX_SIZE_ALPHA_BYTE);
                auto hdr = ImageDecoder::get_info(img);
                if(hdr.is_valid()) return;

                Area a;
                a->x1 = dsc->draw_area->x1 + (Area(dsc->draw_area).get_width() - hdr->w) / 2;
                a->x2 = a->x1 + hdr->w - 1;
                a->y1 = dsc->draw_area->y1 + (Area(dsc->draw_area).get_height() - hdr->h) / 2;
                a->y2 = a->y1 + hdr->h - 1;

                ImageDrawDescriptor img_draw_dsc;
                img_draw_dsc->recolor = palette::black();
                if (obj.get_selected_btn() == dsc->id)
                    img_draw_dsc->recolor_opa = LV_OPA_30;
                
                img_draw_dsc.draw(dsc->draw_ctx, a, img);
            }
        }
    }

    void btnmatrix_2() {
        static auto btnm = ButtonMatrix(scr_act());
        btnm.add_event_cb(event_cb, LV_EVENT_ALL);
        btnm.center();
   }

}