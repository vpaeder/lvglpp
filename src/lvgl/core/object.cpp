/** \file object.cpp
 *  \brief Implementation file for C++ wrapper for lv_obj_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "object.h"

namespace lvgl::core {

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
    template<class T> void Object::set_user_data(const T & arg) {
        lv_obj_set_user_data(this->raw_ptr(), static_cast<void*>(&arg));
    }
    void Object::set_user_data(const void * arg) {
        lv_obj_set_user_data(this->raw_ptr(), const_cast<void*>(arg));
    }

    void * Object::get_user_data() const {
        return lv_obj_get_user_data(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }
    #endif // LV_USE_USER_DATA

    std::shared_ptr<lv_group_t> Object::get_group() const {
        auto group = lv_obj_get_group(this->raw_ptr());
        if (group == nullptr)
            return nullptr;
        return std::shared_ptr<lv_group_t>(reinterpret_cast<lv_group_t*>(group));
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

    const std::shared_ptr<const lv_obj_class_t> Object::get_class() const {
        return std::shared_ptr<const lv_obj_class_t>(lv_obj_get_class(this->raw_ptr()));
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

    void Object::add_event_callback(lv_event_cb_t event_cb, lv_event_code_t filter) {
        lv_obj_add_event_cb(this->raw_ptr(), event_cb, filter, static_cast<void*>(this));
    }

    template <class T> void Object::add_event_callback(lv_event_cb_t event_cb, lv_event_code_t filter,
                                                       const T & user_data) {
        lv_obj_add_event_cb(this->raw_ptr(), event_cb, filter, static_cast<void*>(&user_data));
    }

    void Object::add_event_callback(lv_event_cb_t event_cb, lv_event_code_t filter, void * user_data) {
        lv_obj_add_event_cb(this->raw_ptr(), event_cb, filter, user_data);
    }

    bool Object::remove_event_callback(lv_event_cb_t event_cb) {
        return lv_obj_remove_event_cb_with_user_data(this->raw_ptr(), event_cb, static_cast<void*>(this));
    }

    template <class T> bool Object::remove_event_callback(lv_event_cb_t event_cb, const T & user_data) {
        return lv_obj_remove_event_cb_with_user_data(this->raw_ptr(), event_cb, static_cast<void*>(&user_data));
    }

    bool Object::remove_event_callback(lv_event_cb_t event_cb, const void * user_data) {
        return lv_obj_remove_event_cb_with_user_data(this->raw_ptr(), event_cb, user_data);
    }

    template <class T> lv_res_t Object::send_event(lv_event_code_t event_code, const T & param) {
        return lv_event_send(this->raw_ptr(), event_code, static_cast<void*>(&param));
    }

    lv_res_t Object::send_event(lv_event_code_t event_code, void * param) {
        return lv_event_send(this->raw_ptr(), event_code, param);
    }

    template <class T> T Object::get_event_user_data(lv_event_cb_t event_cb) {
        return reinterpret_cast<T>(*lv_obj_get_event_user_data(this->raw_ptr(), event_cb));
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
        return Object(lv_obj_get_screen(this->raw_ptr()));
    }

    Object Object::get_parent() const {
        return Object(lv_obj_get_parent(this->raw_ptr()));
    }
    
    Object Object::get_child(int32_t id) const {
        return Object(lv_obj_get_child(this->raw_ptr(), id));
    }

    template <class T> void Object::tree_walk(lv_obj_tree_walk_cb_t cb, T & user_data) const {
        lv_obj_tree_walk(const_cast<lv_cls_ptr>(this->raw_ptr()), cb, static_cast<void*>(&user_data));
    }
    void Object::tree_walk(lv_obj_tree_walk_cb_t cb, void * user_data) const {
        lv_obj_tree_walk(const_cast<lv_cls_ptr>(this->raw_ptr()), cb, user_data);
    }
    void Object::tree_walk(lv_obj_tree_walk_cb_t cb) const {
        this->tree_walk(cb, nullptr);
    }


}