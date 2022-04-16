#include "lvglpp/core/display.h" // for scr_act()
#include "lvglpp/widgets/btnmatrix.h" // for ButtonMatrix
#include "lvglpp/core/event.h" // for Event
#include "lvglpp/misc/style.h" // for Style
#include <vector>
#include <string>

namespace lvgl::examples {
    
    using namespace lvgl::core;
    using namespace lvgl::widgets;

    static void event_cb(Event & e) {
        auto code = e.get_code();
        auto obj = e.get_target<ButtonMatrix>();
        
        if(code == LV_EVENT_DRAW_PART_BEGIN) {
            auto dsc = e.get_draw_part_dsc();

            /*Change the draw descriptor the 2nd button*/
            if(dsc->id == 1) {
                dsc->rect_dsc->radius = 0;
                if(obj.get_selected_btn() == dsc->id)  dsc->rect_dsc->bg_color = lv_palette_darken(LV_PALETTE_BLUE, 3);
                else dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_BLUE);

                dsc->rect_dsc->shadow_width = 6;
                dsc->rect_dsc->shadow_ofs_x = 3;
                dsc->rect_dsc->shadow_ofs_y = 3;
                dsc->label_dsc->color = lv_color_white();
            }
            /*Change the draw descriptor the 3rd button*/
            else if(dsc->id == 2) {
                dsc->rect_dsc->radius = LV_RADIUS_CIRCLE;
                if(obj.get_selected_btn() == dsc->id)  dsc->rect_dsc->bg_color = lv_palette_darken(LV_PALETTE_RED, 3);
                else dsc->rect_dsc->bg_color = lv_palette_main(LV_PALETTE_RED);

                dsc->label_dsc->color = lv_color_white();
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
                img_draw_dsc->recolor = lv_color_black();
                if (obj.get_selected_btn() == dsc->id)
                    img_draw_dsc->recolor_opa = LV_OPA_30;
                
                img_draw_dsc.draw(dsc->draw_ctx, a, img);
            }
        }
    }

    void btnmatrix_2() {
        auto root = scr_act();
        auto btnm = ButtonMatrix(root);
        btnm.add_event_cb(event_cb, LV_EVENT_ALL);
        btnm.center();
   }

}