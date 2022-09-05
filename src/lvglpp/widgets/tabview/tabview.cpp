/** \file tabview.cpp
 *  \brief Implementation file for C++ wrapper for lv_tabview_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "tabview.h"
#if LV_USE_TABVIEW

namespace lvgl::widgets {

    Tabview::Tabview(lv_dir_t tab_pos, lv_coord_t tab_size) {
        this->initialize(tab_pos, tab_size);
    }

    Tabview::Tabview(Object & parent, lv_dir_t tab_pos, lv_coord_t tab_size) {
        this->initialize(parent, tab_pos, tab_size);
    }

    void Tabview::initialize(lv_dir_t tab_pos, lv_coord_t tab_size) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_tabview_create(nullptr, tab_pos, tab_size));
    }
    void Tabview::initialize(Object & parent, lv_dir_t tab_pos, lv_coord_t tab_size) {
        this->lv_obj = LvPointer<lv_obj_t, lv_obj_del>(lv_tabview_create(parent.raw_ptr(), tab_pos, tab_size));
    }

    Object Tabview::add_tab(const std::string & name) {
        return Object(lv_tabview_add_tab(this->raw_ptr(), name.c_str()));
    }

    void Tabview::rename_tab(uint32_t tab_id, const char * new_name) {
        lv_tabview_rename_tab(this->raw_ptr(), tab_id, new_name);
    }
    void Tabview::rename_tab(uint32_t tab_id, const std::string & new_name) {
        lv_tabview_rename_tab(this->raw_ptr(), tab_id, new_name.c_str());
    }

    Object Tabview::get_content() {
        return Object(lv_tabview_get_content(this->raw_ptr()));
    }

    Object Tabview::get_tab_btns() {
        return Object(lv_tabview_get_tab_btns(this->raw_ptr()));
    }

    void Tabview::set_act(uint32_t id, lv_anim_enable_t anim_en) {
        lv_tabview_set_act(this->raw_ptr(), id, anim_en);
    }

    uint16_t Tabview::get_tab_act() {
        return lv_tabview_get_tab_act(this->raw_ptr());
    }

}
#endif // LV_USE_TABVIEW