/** \file tileview.cpp
 *  \brief Implementation file for C++ wrapper for lv_tileview_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "tileview.h"
#if LV_USE_TILEVIEW

namespace lvgl::widgets {

    Object Tileview::add_tile(uint8_t col_id, uint8_t row_id, lv_dir_t dir) {
        return Object(lv_tileview_add_tile(this->raw_ptr(), col_id, row_id, dir));
    }

    void Tileview::set_tile(Object & tile_obj, lv_anim_enable_t anim_en) {
        lv_obj_set_tile(this->raw_ptr(), tile_obj.raw_ptr(), anim_en);
    }
    
    void Tileview::set_tile_by_id(uint32_t col_id, uint32_t row_id, lv_anim_enable_t anim_en) {
        lv_obj_set_tile_id(this->raw_ptr(), col_id, row_id, anim_en);
    }

    Object Tileview::get_tile_act() const {
        return Object(lv_tileview_get_tile_act(const_cast<lv_cls_ptr>(this->raw_ptr())));
    }

}
#endif // LV_USE_TILEVIEW