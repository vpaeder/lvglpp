/** \file object.cpp
 *  \brief Implementation file for C++ wrapper for lv_obj_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "object.h"
#include "event.h"
#include "theme.h"
#include "group.h"
#include "../misc/style.h"
#include "../misc/area.h"
#include "../misc/color.h"
#include "../draw/desc.h"
#include "../draw/image.h"
#include "../font/font.h"

namespace lvgl::core {

    using namespace lvgl::misc;
    using namespace lvgl::draw;

    Object::~Object() {
        // if lv_obj is invalid, this means it has already been deleted
        // by a LVGL function; it cannot be deleted again.
        if (!this->is_valid()) this->lv_obj.release();
    }

    void Object::add_flag(lv_obj_flag_t f) {
        lv_obj_add_flag(this->raw_ptr(), f);
    }

    void Object::clear_flag(lv_obj_flag_t f) {
        lv_obj_clear_flag(this->raw_ptr(), f);
    }

    bool Object::has_flag(lv_obj_flag_t f) const {
        return lv_obj_has_flag(this->raw_ptr(), f);
    }

    bool Object::has_flag_any(lv_obj_flag_t f) const {
        return lv_obj_has_flag_any(this->raw_ptr(), f);
    }

    void Object::add_state(lv_state_t state) {
        lv_obj_add_state(this->raw_ptr(), state);
    }

    void Object::clear_state(lv_state_t state) {
        lv_obj_clear_state(this->raw_ptr(), state);
    }

    lv_state_t Object::get_state() const {
        return lv_obj_get_state(this->raw_ptr());
    }

    bool Object::has_state(lv_state_t state) const {
        return lv_obj_has_state(this->raw_ptr(), state);
    }

#if LV_USE_USER_DATA
    void Object::set_user_data(const void * arg) {
        lv_obj_set_user_data(this->raw_ptr(), const_cast<void*>(arg));
    }

    void * Object::get_user_data() const {
        return lv_obj_get_user_data(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }
#endif // LV_USE_USER_DATA

    Group Object::get_group() const {
        auto group = lv_obj_get_group(this->raw_ptr());
        return Group(reinterpret_cast<lv_group_t*>(group), false);
    }

    void Object::remove_from_group() {
        lv_group_remove_obj(this->raw_ptr());
    }

    void Object::focus() {
        lv_group_focus_obj(this->raw_ptr());
    }

    bool Object::check_type(const lv_obj_class_t & cls) const {
        return lv_obj_check_type(this->raw_ptr(), &cls);
    }

    bool Object::has_class(const lv_obj_class_t & cls) const {
        return lv_obj_has_class(this->raw_ptr(), &cls);
    }

    const lv_obj_class_t * Object::get_class() const {
        return lv_obj_get_class(this->raw_ptr());
    }

    bool Object::is_valid() const {
        return lv_obj_is_valid(this->raw_ptr());
    }

    lv_coord_t Object::dpx(lv_coord_t n) const {
        return lv_obj_dpx(this->raw_ptr(), n);
    }

    bool Object::is_editable() const {
        return lv_obj_is_editable(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    bool Object::is_group_def() const {
        return lv_obj_is_group_def(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }
    
    void Object::init_draw_rect_dsc(uint32_t part, RectangleDrawDescriptor & draw_dsc) {
        lv_obj_init_draw_rect_dsc(this->raw_ptr(), part, draw_dsc.raw_ptr());
    }

    void Object::init_draw_label_dsc(uint32_t part, LabelDrawDescriptor & draw_dsc) {
        lv_obj_init_draw_label_dsc(this->raw_ptr(), part, draw_dsc.raw_ptr());
    }

    void Object::init_draw_img_dsc(uint32_t part, ImageDrawDescriptor & draw_dsc) {
        lv_obj_init_draw_img_dsc(this->raw_ptr(), part, draw_dsc.raw_ptr());
    }

    void Object::init_draw_line_dsc(uint32_t part, LineDrawDescriptor & draw_dsc) {
        lv_obj_init_draw_line_dsc(this->raw_ptr(), part, draw_dsc.raw_ptr());
    }

    void Object::init_draw_arc_dsc(uint32_t part, ArcDrawDescriptor & draw_dsc) {
        lv_obj_init_draw_arc_dsc(this->raw_ptr(), part, draw_dsc.raw_ptr());
    }

    lv_coord_t Object::calculate_ext_draw_size(uint32_t part) const {
        return lv_obj_calculate_ext_draw_size(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }

    void Object::refresh_ext_draw_size() {
        lv_obj_refresh_ext_draw_size(this->raw_ptr());
    }

    lv_coord_t Object::get_ext_draw_size() const {
        return _lv_obj_get_ext_draw_size(this->raw_ptr());
    }

    void Object::add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter) {
        lv_obj_add_event_cb(this->raw_ptr(), event_cb, filter, static_cast<void*>(this));
    }

    void Object::add_event_cb(EventCb event_cb, lv_event_code_t filter) {
        auto f = [](lv_event_t * e) {
            auto cb = reinterpret_cast<EventCb>(lv_event_get_user_data(e));
            auto evt = Event(e);
            cb(evt);
        };
        lv_obj_add_event_cb(this->raw_ptr(), f, filter, reinterpret_cast<void*>(event_cb));
    }

#if LV_USE_USER_DATA
    void Object::add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter, void * user_data) {
        lv_obj_add_event_cb(this->raw_ptr(), event_cb, filter, user_data);
    }
#endif // LV_USE_USER_DATA

    bool Object::remove_event_cb(lv_event_cb_t event_cb) {
        return lv_obj_remove_event_cb_with_user_data(this->raw_ptr(), event_cb, static_cast<void*>(this));
    }

#if LV_USE_USER_DATA
    bool Object::remove_event_cb(lv_event_cb_t event_cb, const void * user_data) {
        return lv_obj_remove_event_cb_with_user_data(this->raw_ptr(), event_cb, user_data);
    }
#endif // LV_USE_USER_DATA

    bool Object::remove_event_cb(EventCb event_cb) {
        return lv_obj_remove_event_cb_with_user_data(this->raw_ptr(), nullptr, static_cast<void*>(&event_cb));
    }

    bool Object::remove_event_cb() {
        return lv_obj_remove_event_cb(this->raw_ptr(), nullptr);
    }

    lv_res_t Object::send_event(lv_event_code_t event_code, void * param) {
        return lv_event_send(this->raw_ptr(), event_code, param);
    }

    lv_res_t Object::send_event(lv_event_code_t event_code) {
        return lv_event_send(this->raw_ptr(), event_code, nullptr);
    }

    void * Object::get_event_user_data(lv_event_cb_t event_cb) {
        return lv_obj_get_event_user_data(this->raw_ptr(), event_cb);
    }

    void Object::set_pos(lv_coord_t x, lv_coord_t y) {
        lv_obj_set_pos(this->raw_ptr(), x, y);
    }

    void Object::set_x(lv_coord_t x) {
        lv_obj_set_x(this->raw_ptr(), x);
    }

    void Object::set_y(lv_coord_t y) {
        lv_obj_set_y(this->raw_ptr(), y);
    }

    void Object::set_size(lv_coord_t w, lv_coord_t h) {
        lv_obj_set_size(this->raw_ptr(), w, h);
    }

    bool Object::refresh_size() {
        return lv_obj_refr_size(this->raw_ptr());
    }

    void Object::set_width(lv_coord_t w) {
        lv_obj_set_width(this->raw_ptr(), w);
    }

    void Object::set_height(lv_coord_t h) {
        lv_obj_set_height(this->raw_ptr(), h);
    }

    void Object::set_content_width(lv_coord_t w) {
        lv_obj_set_content_width(this->raw_ptr(), w);
    }

    void Object::set_content_height(lv_coord_t h) {
        lv_obj_set_content_height(this->raw_ptr(), h);
    }

    void Object::set_layout(uint32_t layout) {
        lv_obj_set_layout(this->raw_ptr(), layout);
    }

    bool Object::is_layout_positioned() {
        return lv_obj_is_layout_positioned(this->raw_ptr());
    }

    void Object::mark_layout_as_dirty() {
        lv_obj_mark_layout_as_dirty(this->raw_ptr());
    }

    void Object::update_layout() {
        lv_obj_update_layout(this->raw_ptr());
    }

    void Object::set_align(lv_align_t align) {
        lv_obj_set_align(this->raw_ptr(), align);
    }

    void Object::align(lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) {
        lv_obj_align(this->raw_ptr(), align, x_ofs, y_ofs);
    }

    void Object::align_to(const Object & other, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs) {
        lv_obj_align_to(this->raw_ptr(), other.raw_ptr(), align, x_ofs, y_ofs);
    }

    void Object::center() {
        lv_obj_center(this->raw_ptr());
    }

    Area Object::get_coords() const {
        lv_area_t res;
        lv_obj_get_coords(this->raw_ptr(), &res);
        return Area(std::move(res));
    }

    lv_coord_t Object::get_x() const {
        return lv_obj_get_x(this->raw_ptr());
    }

    lv_coord_t Object::get_x2() const {
        return lv_obj_get_x2(this->raw_ptr());
    }

    lv_coord_t Object::get_y() const {
        return lv_obj_get_y(this->raw_ptr());
    }

    lv_coord_t Object::get_y2() const {
        return lv_obj_get_y2(this->raw_ptr());
    }

    lv_coord_t Object::get_x_aligned() const {
        return lv_obj_get_x_aligned(this->raw_ptr());
    }

    lv_coord_t Object::get_y_aligned() const {
        return lv_obj_get_y_aligned(this->raw_ptr());
    }

    lv_coord_t Object::get_width() const {
        return lv_obj_get_width(this->raw_ptr());
    }

    lv_coord_t Object::get_height() const {
        return lv_obj_get_height(this->raw_ptr());
    }

    lv_coord_t Object::get_content_width() const {
        return lv_obj_get_content_width(this->raw_ptr());
    }

    lv_coord_t Object::get_content_height() const {
        return lv_obj_get_content_height(this->raw_ptr());
    }

    Area Object::get_content_coords() const {
        lv_area_t res;
        lv_obj_get_content_coords(this->raw_ptr(), &res);
        return Area(std::move(res));
    }

    lv_coord_t Object::get_self_width() const {
        return lv_obj_get_self_width(this->raw_ptr());
    }

    lv_coord_t Object::get_self_height() const {
        return lv_obj_get_self_height(this->raw_ptr());
    }

    bool Object::refresh_self_size() {
        return lv_obj_refresh_self_size(this->raw_ptr());
    }

    void Object::refresh_pos() {
        lv_obj_refr_pos(this->raw_ptr());
    }
    
    void Object::move_to(lv_coord_t x, lv_coord_t y) {
        lv_obj_move_to(this->raw_ptr(), x, y);
    }

    void Object::move_children_by(lv_coord_t x_diff, lv_coord_t y_diff, bool ignore_floating) {
        lv_obj_move_children_by(this->raw_ptr(), x_diff, y_diff, ignore_floating);
    }

    void Object::transform_point(lv_point_t & p, bool recursive, bool inv) {
        lv_obj_transform_point(this->raw_ptr(), &p, recursive, inv);
    }

    void Object::get_transformed_area(Area & area, bool recursive, bool inv) {
        lv_obj_get_transformed_area(this->raw_ptr(), area.raw_ptr(), recursive, inv);
    }

    void Object::invalidate_area(const Area & area) {
        lv_obj_invalidate_area(this->raw_ptr(), area.raw_ptr());
    }

    void Object::invalidate() {
        lv_obj_invalidate(this->raw_ptr());
    }

    bool Object::area_is_visible(Area & area) const {
        return lv_obj_area_is_visible(this->raw_ptr(), area.raw_ptr());
    }

    bool Object::is_visible() const {
        return lv_obj_is_visible(this->raw_ptr());
    }

    void Object::set_ext_click_area(lv_coord_t size) {
        lv_obj_set_ext_click_area(this->raw_ptr(), size);
    }

    Area Object::get_click_area() const {
        lv_area_t res;
        lv_obj_get_click_area(this->raw_ptr(), &res);
        return Area(std::move(res));
    }

    bool Object::hit_test(const lv_point_t & point) const {
        return lv_obj_hit_test(const_cast<lv_cls_ptr>(this->raw_ptr()), &point);
    }

    /* style */
    void Object::add_style(const Style & style, lv_style_selector_t selector) {
        lv_obj_add_style(this->raw_ptr(), const_cast<lv_style_t*>(style.raw_ptr()), selector);
    }

    void Object::remove_style(lv_style_selector_t selector) {
        lv_obj_remove_style(this->raw_ptr(), nullptr, selector);
    }

    void Object::remove_style(const Style & style, lv_style_selector_t selector) {
        lv_obj_remove_style(this->raw_ptr(), const_cast<lv_style_t*>(style.raw_ptr()), selector);
    }

    void Object::remove_style_all() {
        lv_obj_remove_style_all(this->raw_ptr());
    }

    void Object::refresh_style(lv_part_t part, lv_style_prop_t prop) {
        lv_obj_refresh_style(this->raw_ptr(), part, prop);
    }

    lv_style_value_t Object::get_style_prop(lv_part_t part, lv_style_prop_t prop) const {
        return lv_obj_get_style_prop(this->raw_ptr(), part, prop);
    }

    void Object::set_local_style_prop(lv_style_prop_t prop, lv_style_value_t value, lv_style_selector_t selector) {
        lv_obj_set_local_style_prop(this->raw_ptr(), prop, value, selector);
    }

    void Object::set_local_style_prop_meta(lv_style_prop_t prop, uint16_t meta, lv_style_selector_t selector) {
        lv_obj_set_local_style_prop_meta(this->raw_ptr(), prop, meta, selector);
    }

    lv_style_value_t Object::get_local_style_prop(lv_style_prop_t prop, lv_style_selector_t selector) const {
        lv_style_value_t value;
        lv_obj_get_local_style_prop(const_cast<lv_cls_ptr>(this->raw_ptr()), prop, &value, selector);
        return value;
    }

    bool Object::remove_local_style_prop(lv_style_prop_t prop, lv_style_selector_t selector) {
        return lv_obj_remove_local_style_prop(this->raw_ptr(), prop, selector);
    }

    /* animation */
    void Object::fade_in(uint32_t time, uint32_t delay) {
        lv_obj_fade_in(this->raw_ptr(), time, delay);
    }

    void Object::fade_out(uint32_t time, uint32_t delay) {
        lv_obj_fade_out(this->raw_ptr(), time, delay);   
    }

    void Object::set_scrollbar_mode(lv_scrollbar_mode_t mode) {
        lv_obj_set_scrollbar_mode(this->raw_ptr(), mode);
    }

    void Object::set_scroll_dir(lv_dir_t dir) {
        lv_obj_set_scroll_dir(this->raw_ptr(), dir);
    }

    void Object::set_scroll_snap_x(lv_scroll_snap_t align) {
        lv_obj_set_scroll_snap_x(this->raw_ptr(), align);
    }

    void Object::set_scroll_snap_y(lv_scroll_snap_t align) {
        lv_obj_set_scroll_snap_y(this->raw_ptr(), align);
    }

    lv_scrollbar_mode_t Object::get_scrollbar_mode() const {
        return lv_obj_get_scrollbar_mode(this->raw_ptr());
    }

    lv_dir_t Object::get_scroll_dir() const {
        return lv_obj_get_scroll_dir(this->raw_ptr());
    }

    lv_scroll_snap_t Object::get_scroll_snap_x() const {
        return lv_obj_get_scroll_snap_x(this->raw_ptr());
    }

    lv_scroll_snap_t Object::get_scroll_snap_y() const {
        return lv_obj_get_scroll_snap_y(this->raw_ptr());
    }

    lv_coord_t Object::get_scroll_x() const {
        return lv_obj_get_scroll_x(this->raw_ptr());
    }

    lv_coord_t Object::get_scroll_y() const {
        return lv_obj_get_scroll_y(this->raw_ptr());
    }

    lv_coord_t Object::get_scroll_top() const {
        return lv_obj_get_scroll_top(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_coord_t Object::get_scroll_bottom() const {
        return lv_obj_get_scroll_bottom(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_coord_t Object::get_scroll_left() const {
        return lv_obj_get_scroll_left(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_coord_t Object::get_scroll_right() const {
        return lv_obj_get_scroll_right(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_point_t Object::get_scroll_end() const {
        lv_point_t point;
        lv_obj_get_scroll_end(const_cast<lv_cls_ptr>(this->raw_ptr()), &point);
        return point;
    }

    void Object::scroll_by(lv_coord_t dx, lv_coord_t dy, lv_anim_enable_t anim_en) {
        lv_obj_scroll_by(this->raw_ptr(), dx, dy, anim_en);
    }

    void Object::scroll_by_bounded(lv_coord_t dx, lv_coord_t dy, lv_anim_enable_t anim_en) {
        lv_obj_scroll_by_bounded(this->raw_ptr(), dx, dy, anim_en);
    }

    void Object::scroll_to(lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en) {
        lv_obj_scroll_to(this->raw_ptr(), x, y, anim_en);
    }

    void Object::scroll_to_x(lv_coord_t x, lv_anim_enable_t anim_en) {
        lv_obj_scroll_to_x(this->raw_ptr(), x, anim_en);
    }

    void Object::scroll_to_y(lv_coord_t y, lv_anim_enable_t anim_en) {
        lv_obj_scroll_to_y(this->raw_ptr(), y, anim_en);
    }

    void Object::scroll_to_view(lv_anim_enable_t anim_en) {
        lv_obj_scroll_to_view(this->raw_ptr(), anim_en);
    }

    void Object::scroll_to_view_recursive(lv_anim_enable_t anim_en) {
        lv_obj_scroll_to_view_recursive(this->raw_ptr(), anim_en);
    }

    bool Object::is_scrolling() const {
        return lv_obj_is_scrolling(this->raw_ptr());
    }

    void Object::update_snap(lv_anim_enable_t anim_en) {
        lv_obj_update_snap(this->raw_ptr(), anim_en);
    }

    Area Object::get_scrollbar_area() const {
        lv_area_t hor, ver;
        Area area;
        lv_obj_get_scrollbar_area(const_cast<lv_cls_ptr>(this->raw_ptr()), &hor, &ver);
        area.set_pos(hor.x1, ver.y1);
        area.set_width(lv_area_get_width(&hor));
        area.set_height(lv_area_get_height(&ver));
        return area;
    }

    void Object::scrollbar_invalidate() {
        lv_obj_scrollbar_invalidate(this->raw_ptr());
    }

    void Object::readjust_scroll(lv_anim_enable_t anim_en) {
        lv_obj_readjust_scroll(this->raw_ptr(), anim_en);
    }

    void Object::set_parent(const Object & parent) {
        lv_obj_set_parent(this->raw_ptr(), const_cast<lv_cls_ptr>(parent.raw_ptr()));
    }

    void Object::swap(Object & other) {
        lv_obj_swap(this->raw_ptr(), other.raw_ptr());
    }

    void Object::move_to_index(int32_t index) {
        lv_obj_move_to_index(this->raw_ptr(), index);
    }

    Object Object::get_screen() const {
        return Object(lv_obj_get_screen(this->raw_ptr()), false);
    }

    uint32_t Object::get_child_cnt() const {
        return lv_obj_get_child_cnt(this->raw_ptr());
    }

    uint32_t Object::get_index() const {
        return lv_obj_get_index(this->raw_ptr());
    }

#if LV_USE_USER_DATA
    void Object::tree_walk(lv_obj_tree_walk_cb_t cb, void * user_data) const {
        lv_obj_tree_walk(const_cast<lv_cls_ptr>(this->raw_ptr()), cb, user_data);
    }
#endif // LV_USE_USER_DATA

    void Object::tree_walk(lv_obj_tree_walk_cb_t cb) const {
        this->tree_walk(cb, nullptr);
    }

    void Object::set_style_pad_all(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_pad_all(this->raw_ptr(), value, selector);
    }
    void Object::set_style_pad_hor(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_pad_hor(this->raw_ptr(), value, selector);
    }
    void Object::set_style_pad_ver(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_pad_ver(this->raw_ptr(), value, selector);
    }
    void Object::set_style_pad_gap(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_pad_gap(this->raw_ptr(), value, selector);
    }
    void Object::set_style_size(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_size(this->raw_ptr(), value, selector);
    }
    void Object::set_style_width(lv_coord_t width, lv_style_selector_t selector) {
      lv_obj_set_style_width(this->raw_ptr(), width, selector);
    }
    void Object::set_style_min_width(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_min_width(this->raw_ptr(), value, selector);
    }
    void Object::set_style_max_width(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_max_width(this->raw_ptr(), value, selector);
    }
    void Object::set_style_height(lv_coord_t height, lv_style_selector_t selector) {
      lv_obj_set_style_height(this->raw_ptr(), height, selector);
    }
    void Object::set_style_min_height(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_min_height(this->raw_ptr(), value, selector);
    }
    void Object::set_style_max_height(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_max_height(this->raw_ptr(), value, selector);
    }
    void Object::set_style_x(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_x(this->raw_ptr(), value, selector);
    }
    void Object::set_style_y(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_y(this->raw_ptr(), value, selector);
    }
    void Object::set_style_align(lv_align_t value, lv_style_selector_t selector) {
      lv_obj_set_style_align(this->raw_ptr(), value, selector);
    }
    void Object::set_style_transform_width(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_transform_width(this->raw_ptr(), value, selector);
    }
    void Object::set_style_transform_height(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_transform_height(this->raw_ptr(), value, selector);
    }
    void Object::set_style_translate_x(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_translate_x(this->raw_ptr(), value, selector);
    }
    void Object::set_style_translate_y(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_translate_y(this->raw_ptr(), value, selector);
    }
    void Object::set_style_transform_zoom(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_transform_zoom(this->raw_ptr(), value, selector);
    }
    void Object::set_style_transform_angle(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_transform_angle(this->raw_ptr(), value, selector);
    }
    void Object::set_style_pad_top(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_pad_top(this->raw_ptr(), value, selector);
    }
    void Object::set_style_pad_bottom(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_pad_bottom(this->raw_ptr(), value, selector);
    }
    void Object::set_style_pad_left(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_pad_left(this->raw_ptr(), value, selector);
    }
    void Object::set_style_pad_right(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_pad_right(this->raw_ptr(), value, selector);
    }
    void Object::set_style_pad_row(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_pad_row(this->raw_ptr(), value, selector);
    }
    void Object::set_style_pad_column(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_pad_column(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_color(lv_color_t value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_color(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_grad_color(lv_color_t value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_grad_color(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_grad_dir(lv_grad_dir_t value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_grad_dir(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_main_stop(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_main_stop(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_grad_stop(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_grad_stop(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_grad(const lv_grad_dsc_t * value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_grad(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_dither_mode(lv_dither_mode_t value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_dither_mode(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_img_src(const void * value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_img_src(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_img_src(const ImageDescriptor & value, lv_style_selector_t selector) {
        this->set_style_bg_img_src(static_cast<const void*>(value.raw_ptr()), selector);
    }
    void Object::set_style_bg_img_src(const std::string & value, lv_style_selector_t selector) {
        this->set_style_bg_img_src(static_cast<const void*>(value.c_str()), selector);
    }
    void Object::set_style_bg_img_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_img_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_img_recolor(lv_color_t value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_img_recolor(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_img_recolor_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_img_recolor_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_bg_img_tiled(bool value, lv_style_selector_t selector) {
      lv_obj_set_style_bg_img_tiled(this->raw_ptr(), value, selector);
    }
    void Object::set_style_border_color(lv_color_t value, lv_style_selector_t selector) {
      lv_obj_set_style_border_color(this->raw_ptr(), value, selector);
    }
    void Object::set_style_border_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_border_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_border_width(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_border_width(this->raw_ptr(), value, selector);
    }
    void Object::set_style_border_side(lv_border_side_t value, lv_style_selector_t selector) {
      lv_obj_set_style_border_side(this->raw_ptr(), value, selector);
    }
    void Object::set_style_border_post(bool value, lv_style_selector_t selector) {
      lv_obj_set_style_border_post(this->raw_ptr(), value, selector);
    }
    void Object::set_style_outline_width(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_outline_width(this->raw_ptr(), value, selector);
    }
    void Object::set_style_outline_color(lv_color_t value, lv_style_selector_t selector) {
      lv_obj_set_style_outline_color(this->raw_ptr(), value, selector);
    }
    void Object::set_style_outline_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_outline_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_outline_pad(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_outline_pad(this->raw_ptr(), value, selector);
    }
    void Object::set_style_shadow_width(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_shadow_width(this->raw_ptr(), value, selector);
    }
    void Object::set_style_shadow_ofs_x(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_shadow_ofs_x(this->raw_ptr(), value, selector);
    }
    void Object::set_style_shadow_ofs_y(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_shadow_ofs_y(this->raw_ptr(), value, selector);
    }
    void Object::set_style_shadow_spread(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_shadow_spread(this->raw_ptr(), value, selector);
    }
    void Object::set_style_shadow_color(lv_color_t value, lv_style_selector_t selector) {
      lv_obj_set_style_shadow_color(this->raw_ptr(), value, selector);
    }
    void Object::set_style_shadow_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_shadow_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_img_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_img_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_img_recolor(lv_color_t value, lv_style_selector_t selector) {
      lv_obj_set_style_img_recolor(this->raw_ptr(), value, selector);
    }
    void Object::set_style_img_recolor_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_img_recolor_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_line_width(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_line_width(this->raw_ptr(), value, selector);
    }
    void Object::set_style_line_dash_width(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_line_dash_width(this->raw_ptr(), value, selector);
    }
    void Object::set_style_line_dash_gap(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_line_dash_gap(this->raw_ptr(), value, selector);
    }
    void Object::set_style_line_rounded(bool value, lv_style_selector_t selector) {
      lv_obj_set_style_line_rounded(this->raw_ptr(), value, selector);
    }
    void Object::set_style_line_color(lv_color_t value, lv_style_selector_t selector) {
      lv_obj_set_style_line_color(this->raw_ptr(), value, selector);
    }
    void Object::set_style_line_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_line_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_arc_width(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_arc_width(this->raw_ptr(), value, selector);
    }
    void Object::set_style_arc_rounded(bool value, lv_style_selector_t selector) {
      lv_obj_set_style_arc_rounded(this->raw_ptr(), value, selector);
    }
    void Object::set_style_arc_color(lv_color_t value, lv_style_selector_t selector) {
      lv_obj_set_style_arc_color(this->raw_ptr(), value, selector);
    }
    void Object::set_style_arc_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_arc_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_arc_img_src(const void * value, lv_style_selector_t selector) {
      lv_obj_set_style_arc_img_src(this->raw_ptr(), value, selector);
    }
    void Object::set_style_arc_img_src(const ImageDescriptor & value, lv_style_selector_t selector) {
        this->set_style_bg_img_src(static_cast<const void*>(value.raw_ptr()), selector);
    }
    void Object::set_style_arc_img_src(const std::string & value, lv_style_selector_t selector) {
        this->set_style_bg_img_src(static_cast<const void*>(value.c_str()), selector);
    }
    void Object::set_style_text_color(lv_color_t value, lv_style_selector_t selector) {
      lv_obj_set_style_text_color(this->raw_ptr(), value, selector);
    }
    void Object::set_style_text_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_text_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_text_font(const lv_font_t * value, lv_style_selector_t selector) {
      lv_obj_set_style_text_font(this->raw_ptr(), value, selector);
    }
    void Object::set_style_text_font(const Font & value, lv_style_selector_t selector) {
      this->set_style_text_font(value.raw_ptr(), selector);
    }
    void Object::set_style_text_letter_space(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_text_letter_space(this->raw_ptr(), value, selector);
    }
    void Object::set_style_text_line_space(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_text_line_space(this->raw_ptr(), value, selector);
    }
    void Object::set_style_text_decor(lv_text_decor_t value, lv_style_selector_t selector) {
      lv_obj_set_style_text_decor(this->raw_ptr(), value, selector);
    }
    void Object::set_style_text_align(lv_text_align_t value, lv_style_selector_t selector) {
      lv_obj_set_style_text_align(this->raw_ptr(), value, selector);
    }
    void Object::set_style_radius(lv_coord_t value, lv_style_selector_t selector) {
      lv_obj_set_style_radius(this->raw_ptr(), value, selector);
    }
    void Object::set_style_clip_corner(bool value, lv_style_selector_t selector) {
      lv_obj_set_style_clip_corner(this->raw_ptr(), value, selector);
    }
    void Object::set_style_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_color_filter_dsc(const lv_color_filter_dsc_t * value, lv_style_selector_t selector) {
      lv_obj_set_style_color_filter_dsc(this->raw_ptr(), value, selector);
    }
#if LV_USE_USER_DATA
    void Object::set_style_color_filter_dsc(const ColorFilter & value, lv_style_selector_t selector) {
      this->set_style_color_filter_dsc(value.raw_ptr(), selector);
    }
#endif // LV_USE_USER_DATA
    void Object::set_style_color_filter_opa(lv_opa_t value, lv_style_selector_t selector) {
      lv_obj_set_style_color_filter_opa(this->raw_ptr(), value, selector);
    }
    void Object::set_style_anim(const lv_anim_t * value, lv_style_selector_t selector) {
      lv_obj_set_style_anim(this->raw_ptr(), value, selector);
    }
    void Object::set_style_anim(const Animation & value, lv_style_selector_t selector) {
        this->set_style_anim(value.raw_ptr(), selector);
    }
    void Object::set_style_anim_time(uint32_t value, lv_style_selector_t selector) {
      lv_obj_set_style_anim_time(this->raw_ptr(), value, selector);
    }
    void Object::set_style_anim_speed(uint32_t value, lv_style_selector_t selector) {
      lv_obj_set_style_anim_speed(this->raw_ptr(), value, selector);
    }
    void Object::set_style_transition(const lv_style_transition_dsc_t * value, lv_style_selector_t selector) {
      lv_obj_set_style_transition(this->raw_ptr(), value, selector);
    }
#if LV_USE_USER_DATA
    void Object::set_style_transition(const StyleTransition & value, lv_style_selector_t selector) {
        this->set_style_transition(value.raw_ptr(), selector);
    }
#endif // LV_USE_USER_DATA
    void Object::set_style_blend_mode(lv_blend_mode_t value, lv_style_selector_t selector) {
      lv_obj_set_style_blend_mode(this->raw_ptr(), value, selector);
    }
    void Object::set_style_layout(uint16_t value, lv_style_selector_t selector) {
      lv_obj_set_style_layout(this->raw_ptr(), value, selector);
    }
    void Object::set_style_base_dir(lv_base_dir_t value, lv_style_selector_t selector) {
      lv_obj_set_style_base_dir(this->raw_ptr(), value, selector);
    }

    lv_coord_t Object::get_style_width(uint32_t part) const {
        return lv_obj_get_style_width(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_min_width(uint32_t part) const {
        return lv_obj_get_style_min_width(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_max_width(uint32_t part) const {
        return lv_obj_get_style_max_width(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_height(uint32_t part) const {
        return lv_obj_get_style_height(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_min_height(uint32_t part) const {
        return lv_obj_get_style_min_height(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_max_height(uint32_t part) const {
        return lv_obj_get_style_max_height(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_x(uint32_t part) const {
        return lv_obj_get_style_x(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_y(uint32_t part) const {
        return lv_obj_get_style_y(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_align_t Object::get_style_align(uint32_t part) const {
        return lv_obj_get_style_align(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_transform_width(uint32_t part) const {
        return lv_obj_get_style_transform_width(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_transform_height(uint32_t part) const {
        return lv_obj_get_style_transform_height(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_translate_x(uint32_t part) const {
        return lv_obj_get_style_translate_x(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_translate_y(uint32_t part) const {
        return lv_obj_get_style_translate_y(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_transform_zoom(uint32_t part) const {
        return lv_obj_get_style_transform_zoom(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_transform_angle(uint32_t part) const {
        return lv_obj_get_style_transform_angle(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_transform_pivot_x(uint32_t part) const {
        return lv_obj_get_style_transform_pivot_x(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_transform_pivot_y(uint32_t part) const {
        return lv_obj_get_style_transform_pivot_y(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_pad_top(uint32_t part) const {
        return lv_obj_get_style_pad_top(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_pad_bottom(uint32_t part) const {
        return lv_obj_get_style_pad_bottom(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_pad_left(uint32_t part) const {
        return lv_obj_get_style_pad_left(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_pad_right(uint32_t part) const {
        return lv_obj_get_style_pad_right(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_pad_row(uint32_t part) const {
        return lv_obj_get_style_pad_row(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_pad_column(uint32_t part) const {
        return lv_obj_get_style_pad_column(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_color_t Object::get_style_bg_color(uint32_t part) const {
        return lv_obj_get_style_bg_color(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_bg_opa(uint32_t part) const {
        return lv_obj_get_style_bg_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_color_t Object::get_style_bg_grad_color(uint32_t part) const {
        return lv_obj_get_style_bg_grad_color(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_grad_dir_t Object::get_style_bg_grad_dir(uint32_t part) const {
        return lv_obj_get_style_bg_grad_dir(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_bg_main_stop(uint32_t part) const {
        return lv_obj_get_style_bg_main_stop(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_bg_grad_stop(uint32_t part) const {
        return lv_obj_get_style_bg_grad_stop(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    const lv_grad_dsc_t * Object::get_style_bg_grad(uint32_t part) const {
        return lv_obj_get_style_bg_grad(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_dither_mode_t Object::get_style_bg_dither_mode(uint32_t part) const {
        return lv_obj_get_style_bg_dither_mode(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    const void * Object::get_style_bg_img_src(uint32_t part) const {
        return lv_obj_get_style_bg_img_src(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_bg_img_opa(uint32_t part) const {
        return lv_obj_get_style_bg_img_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_color_t Object::get_style_bg_img_recolor(uint32_t part) const {
        return lv_obj_get_style_bg_img_recolor(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_bg_img_recolor_opa(uint32_t part) const {
        return lv_obj_get_style_bg_img_recolor_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    bool Object::get_style_bg_img_tiled(uint32_t part) const {
        return lv_obj_get_style_bg_img_tiled(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_color_t Object::get_style_border_color(uint32_t part) const {
        return lv_obj_get_style_border_color(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_border_opa(uint32_t part) const {
        return lv_obj_get_style_border_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_border_width(uint32_t part) const {
        return lv_obj_get_style_border_width(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_border_side_t Object::get_style_border_side(uint32_t part) const {
        return lv_obj_get_style_border_side(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    bool Object::get_style_border_post(uint32_t part) const {
        return lv_obj_get_style_border_post(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_outline_width(uint32_t part) const {
        return lv_obj_get_style_outline_width(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_color_t Object::get_style_outline_color(uint32_t part) const {
        return lv_obj_get_style_outline_color(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_outline_opa(uint32_t part) const {
        return lv_obj_get_style_outline_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_outline_pad(uint32_t part) const {
        return lv_obj_get_style_outline_pad(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_shadow_width(uint32_t part) const {
        return lv_obj_get_style_shadow_width(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_shadow_ofs_x(uint32_t part) const {
        return lv_obj_get_style_shadow_ofs_x(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_shadow_ofs_y(uint32_t part) const {
        return lv_obj_get_style_shadow_ofs_y(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_shadow_spread(uint32_t part) const {
        return lv_obj_get_style_shadow_spread(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_color_t Object::get_style_shadow_color(uint32_t part) const {
        return lv_obj_get_style_shadow_color(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_shadow_opa(uint32_t part) const {
        return lv_obj_get_style_shadow_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_img_opa(uint32_t part) const {
        return lv_obj_get_style_img_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_color_t Object::get_style_img_recolor(uint32_t part) const {
        return lv_obj_get_style_img_recolor(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_img_recolor_opa(uint32_t part) const {
        return lv_obj_get_style_img_recolor_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_line_width(uint32_t part) const {
        return lv_obj_get_style_line_width(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_line_dash_width(uint32_t part) const {
        return lv_obj_get_style_line_dash_width(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_line_dash_gap(uint32_t part) const {
        return lv_obj_get_style_line_dash_gap(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    bool Object::get_style_line_rounded(uint32_t part) const {
        return lv_obj_get_style_line_rounded(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_color_t Object::get_style_line_color(uint32_t part) const {
        return lv_obj_get_style_line_color(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_line_opa(uint32_t part) const {
        return lv_obj_get_style_line_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_arc_width(uint32_t part) const {
        return lv_obj_get_style_arc_width(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    bool Object::get_style_arc_rounded(uint32_t part) const {
        return lv_obj_get_style_arc_rounded(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_color_t Object::get_style_arc_color(uint32_t part) const {
        return lv_obj_get_style_arc_color(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_arc_opa(uint32_t part) const {
        return lv_obj_get_style_arc_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    const void * Object::get_style_arc_img_src(uint32_t part) const {
        return lv_obj_get_style_arc_img_src(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_color_t Object::get_style_text_color(uint32_t part) const {
        return lv_obj_get_style_text_color(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_text_opa(uint32_t part) const {
        return lv_obj_get_style_text_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    const lv_font_t * Object::get_style_text_font(uint32_t part) const {
        return lv_obj_get_style_text_font(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_text_letter_space(uint32_t part) const {
        return lv_obj_get_style_text_letter_space(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_text_line_space(uint32_t part) const {
        return lv_obj_get_style_text_line_space(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_text_decor_t Object::get_style_text_decor(uint32_t part) const {
        return lv_obj_get_style_text_decor(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_text_align_t Object::get_style_text_align(uint32_t part) const {
        return lv_obj_get_style_text_align(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_coord_t Object::get_style_radius(uint32_t part) const {
        return lv_obj_get_style_radius(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    bool Object::get_style_clip_corner(uint32_t part) const {
        return lv_obj_get_style_clip_corner(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_opa(uint32_t part) const {
        return lv_obj_get_style_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    const lv_color_filter_dsc_t * Object::get_style_color_filter_dsc(uint32_t part) const {
        return lv_obj_get_style_color_filter_dsc(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_opa_t Object::get_style_color_filter_opa(uint32_t part) const {
        return lv_obj_get_style_color_filter_opa(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    const lv_anim_t * Object::get_style_anim(uint32_t part) const {
        return lv_obj_get_style_anim(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    uint32_t Object::get_style_anim_time(uint32_t part) const {
        return lv_obj_get_style_anim_time(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    uint32_t Object::get_style_anim_speed(uint32_t part) const {
        return lv_obj_get_style_anim_speed(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    const lv_style_transition_dsc_t * Object::get_style_transition(uint32_t part) const {
        return lv_obj_get_style_transition(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_blend_mode_t Object::get_style_blend_mode(uint32_t part) const {
        return lv_obj_get_style_blend_mode(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    uint16_t Object::get_style_layout(uint32_t part) const {
        return lv_obj_get_style_layout(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }
    lv_base_dir_t Object::get_style_base_dir(uint32_t part) const {
        return lv_obj_get_style_base_dir(const_cast<lv_cls_ptr>(this->raw_ptr()), part);
    }    

#if LV_USE_FLEX
    void Object::set_flex_flow(lv_flex_flow_t flow) {
        lv_obj_set_flex_flow(this->raw_ptr(), flow);
    }

    void Object::set_flex_align(lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_cross_place) {
        lv_obj_set_flex_align(this->raw_ptr(), main_place, cross_place, track_cross_place);
    }
    void Object::set_flex_grow(uint8_t grow) {
        lv_obj_set_flex_grow(this->raw_ptr(), grow);
    }
    void Object::set_style_flex_flow(lv_flex_flow_t value, lv_style_selector_t selector) {
        lv_obj_set_style_flex_flow(this->raw_ptr(), value, selector);
    }
    void Object::set_style_flex_main_place(lv_flex_align_t value, lv_style_selector_t selector) {
        lv_obj_set_style_flex_main_place(this->raw_ptr(), value, selector);
    }
    void Object::set_style_flex_cross_place(lv_flex_align_t value, lv_style_selector_t selector) {
        lv_obj_set_style_flex_cross_place(this->raw_ptr(), value, selector);
    }
    void Object::set_style_flex_track_place(lv_flex_align_t value, lv_style_selector_t selector) {
        lv_obj_set_style_flex_track_place(this->raw_ptr(), value, selector);
    }
    void Object::set_style_flex_grow(uint8_t value, lv_style_selector_t selector) {
        lv_obj_set_style_flex_grow(this->raw_ptr(), value, selector);
    }
    lv_flex_flow_t Object::get_style_flex_flow(uint32_t part) const {
        return lv_obj_get_style_flex_flow(this->raw_ptr(), part);
    }
    lv_flex_align_t Object::get_style_flex_main_place(uint32_t part) const {
        return lv_obj_get_style_flex_main_place(this->raw_ptr(), part);
    }
    lv_flex_align_t Object::get_style_flex_cross_place(uint32_t part) const {
        return lv_obj_get_style_flex_cross_place(this->raw_ptr(), part);
    }
    lv_flex_align_t Object::get_style_flex_track_place(uint32_t part) const {
        return lv_obj_get_style_flex_track_place(this->raw_ptr(), part);
    }
    uint8_t Object::get_style_flex_grow(uint32_t part) const {
        return lv_obj_get_style_flex_grow(this->raw_ptr(), part);
    }
#endif // LV_USE_FLEX

#if LV_USE_GRID
    /* grid layout */
    void Object::set_grid_dsc_array(const std::vector<lv_coord_t> & col_dsc, const std::vector<lv_coord_t> & row_dsc) {
        lv_obj_set_grid_dsc_array(this->raw_ptr(), col_dsc.data(), row_dsc.data());
    }
    void Object::set_grid_align(lv_grid_align_t column_align, lv_grid_align_t row_align) {
        lv_obj_set_grid_align(this->raw_ptr(), column_align, row_align);
    }
    void Object::set_grid_cell(lv_grid_align_t column_align, uint8_t col_pos, uint8_t col_span,
                               lv_grid_align_t row_align, uint8_t row_pos, uint8_t row_span) {
        lv_obj_set_grid_cell(this->raw_ptr(), column_align, col_pos, col_span, row_align, row_pos, row_span);
    }
    void Object::set_style_grid_row_dsc_array(const std::vector<lv_coord_t> & value, lv_style_selector_t selector) {
        lv_obj_set_style_grid_row_dsc_array(this->raw_ptr(), value.data(), selector);
    }
    void Object::set_style_grid_column_dsc_array(const std::vector<lv_coord_t> & value, lv_style_selector_t selector) {
        lv_obj_set_style_grid_column_dsc_array(this->raw_ptr(), value.data(), selector);
    }
    void Object::set_style_grid_row_align(lv_grid_align_t value, lv_style_selector_t selector) {
        lv_obj_set_style_grid_row_align(this->raw_ptr(), value, selector);
    }
    void Object::set_style_grid_column_align(lv_grid_align_t value, lv_style_selector_t selector) {
        lv_obj_set_style_grid_column_align(this->raw_ptr(), value, selector);
    }
    void Object::set_style_grid_cell_column_pos(lv_coord_t value, lv_style_selector_t selector) {
        lv_obj_set_style_grid_cell_column_pos(this->raw_ptr(), value, selector);
    }
    void Object::set_style_grid_cell_column_span(lv_coord_t value, lv_style_selector_t selector) {
        lv_obj_set_style_grid_cell_column_span(this->raw_ptr(), value, selector);
    }
    void Object::set_style_grid_cell_row_pos(lv_coord_t value, lv_style_selector_t selector) {
        lv_obj_set_style_grid_cell_row_pos(this->raw_ptr(), value, selector);
    }
    void Object::set_style_grid_cell_row_span(lv_coord_t value, lv_style_selector_t selector) {
        lv_obj_set_style_grid_cell_row_span(this->raw_ptr(), value, selector);
    }
    void Object::set_style_grid_cell_x_align(lv_coord_t value, lv_style_selector_t selector) {
        lv_obj_set_style_grid_cell_x_align(this->raw_ptr(), value, selector);
    }
    void Object::set_style_grid_cell_y_align(lv_coord_t value, lv_style_selector_t selector) {
        lv_obj_set_style_grid_cell_y_align(this->raw_ptr(), value, selector);
    }
    const lv_coord_t * Object::get_style_grid_row_dsc_array(uint32_t part) const {
        return lv_obj_get_style_grid_row_dsc_array(this->raw_ptr(), part);
    }
    const lv_coord_t * Object::get_style_grid_column_dsc_array(uint32_t part) const {
        return lv_obj_get_style_grid_column_dsc_array(this->raw_ptr(), part);
    }
    lv_grid_align_t Object::get_style_grid_row_align(uint32_t part) const {
        return lv_obj_get_style_grid_row_align(this->raw_ptr(), part);
    }
    lv_grid_align_t Object::get_style_grid_column_align(uint32_t part) const {
        return lv_obj_get_style_grid_column_align(this->raw_ptr(), part);
    }
    lv_coord_t Object::get_style_grid_cell_column_pos(uint32_t part) const {
        return lv_obj_get_style_grid_cell_column_pos(this->raw_ptr(), part);
    }
    lv_coord_t Object::get_style_grid_cell_column_span(uint32_t part) const {
        return lv_obj_get_style_grid_cell_column_span(this->raw_ptr(), part);
    }
    lv_coord_t Object::get_style_grid_cell_row_pos(uint32_t part) const {
        return lv_obj_get_style_grid_cell_row_pos(this->raw_ptr(), part);
    }
    lv_coord_t Object::get_style_grid_cell_row_span(uint32_t part) const {
        return lv_obj_get_style_grid_cell_row_span(this->raw_ptr(), part);
    }
    lv_coord_t Object::get_style_grid_cell_x_align(uint32_t part) const {
        return lv_obj_get_style_grid_cell_x_align(this->raw_ptr(), part);
    }
    lv_coord_t Object::get_style_grid_cell_y_align(uint32_t part) const {
        return lv_obj_get_style_grid_cell_y_align(this->raw_ptr(), part);
    }
#endif // LV_USE_GRID

    /* theme */
    const lv_font_t * Object::get_font_small() const {
        return lv_theme_get_font_small(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    const lv_font_t * Object::get_font_normal() const {
        return lv_theme_get_font_normal(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    const lv_font_t * Object::get_font_large() const {
        return lv_theme_get_font_large(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_color_t Object::get_color_primary() const {
        return lv_theme_get_color_primary(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_color_t Object::get_color_secondary() const {
        return lv_theme_get_color_secondary(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    Theme Object::get_theme() const {
        return Theme(lv_theme_get_from_obj(const_cast<lv_cls_ptr>(this->raw_ptr())), false);
    }

    void Object::apply_act_theme() {
        lv_theme_apply(this->raw_ptr());
    }

    void Object::to_foreground() {
        lv_obj_move_foreground(this->raw_ptr());
    }

    void Object::to_background() {
        lv_obj_move_background(this->raw_ptr());
    }

}