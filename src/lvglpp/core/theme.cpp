/** \file theme.cpp
 *  \brief Implementation file for C++ wrapper for LVGL themes.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */

#include "theme.h"
#include "object.h"

namespace lvgl::core {

    Theme::Theme() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
    }

    void Theme::set_parent(Theme & parent) {
        lv_theme_set_parent(this->raw_ptr(), parent.raw_ptr());
    }

    void Theme::set_apply_cb(ThemeApplyCb apply_cb) {
        auto f = [](lv_theme_t* lv_thm, lv_obj_t* lv_obj) {
            auto cb = reinterpret_cast<ThemeApplyCb>(lv_thm->user_data);
            auto thm = Theme(lv_thm, false);
            auto obj = Object(lv_obj, false);
            cb(thm, obj);
        };
        this->raw_ptr()->user_data = reinterpret_cast<void*>(apply_cb);
        lv_theme_set_apply_cb(this->raw_ptr(), f);
    }


    Theme get_active_theme() {
        return Theme(lv_disp_get_theme(nullptr), false);
    }

    void set_active_theme(Theme & th) {
        lv_disp_set_theme(nullptr, th.raw_ptr());
    }

}