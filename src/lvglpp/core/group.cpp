/** \file group.cpp
 *  \brief Implementation file for C++ wrapper for LVGL groups.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */

#include "object.h"
#include "group.h"

namespace lvgl::core {

    void Group::set_default() {
        lv_group_set_default(this->raw_ptr());
    }

    void Group::add_obj(const Object & obj) {
        lv_group_add_obj(this->raw_ptr(), const_cast<lv_obj_t*>(obj.raw_ptr()));
    }

    void Group::remove_all_objs() {
        lv_group_remove_all_objs(this->raw_ptr());
    }

    void Group::focus_next() {
        lv_group_focus_next(this->raw_ptr());
    }

    void Group::focus_prev() {
        lv_group_focus_prev(this->raw_ptr());
    }

    void Group::focus_freeze(bool en) {
        lv_group_focus_freeze(this->raw_ptr(), en);
    }

    lv_res_t Group::send_data(uint32_t c) {
        return lv_group_send_data(this->raw_ptr(), c);
    }

    void Group::set_focus_cb(lv_group_focus_cb_t focus_cb) {
        lv_group_set_focus_cb(this->raw_ptr(), focus_cb);
    }

    void Group::set_edge_cb(lv_group_edge_cb_t edge_cb) {
        lv_group_set_edge_cb(this->raw_ptr(), edge_cb);
    }

    void Group::set_refocus_policy(lv_group_refocus_policy_t policy) {
        lv_group_set_refocus_policy(this->raw_ptr(), policy);
    }

    void Group::set_editing(bool edit) {
        lv_group_set_editing(this->raw_ptr(), edit);
    }

    void Group::set_wrap(bool en) {
        lv_group_set_wrap(this->raw_ptr(), en);
    }

    Object Group::get_focused() const {
        return Object(lv_group_get_focused(this->raw_ptr()), false);
    }

    lv_group_focus_cb_t Group::get_focus_cb() const {
        return lv_group_get_focus_cb(this->raw_ptr());
    }

    lv_group_edge_cb_t Group::get_edge_cb() const {
        return lv_group_get_edge_cb(this->raw_ptr());
    }

    bool Group::get_editing() const {
        return lv_group_get_editing(this->raw_ptr());
    }

    bool Group::get_wrap() const {
        return lv_group_get_wrap(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    uint32_t Group::get_obj_count() const {
        return lv_group_get_obj_count(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    Group get_default_group() {
        return Group(lv_group_get_default());
    }

    void set_default_group(Group & group) {
        lv_group_set_default(group.raw_ptr());
    }

    void swap_objs_in_group(Object & obj1, Object & obj2) {
        lv_group_swap_obj(obj1.raw_ptr(), obj2.raw_ptr());
    }


}