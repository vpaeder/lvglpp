/** \file style.cpp
 *  \brief Implementation file for C++ wrapper for lv_style_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "style.h"

#define LV_ANIM_RESOLUTION 1024 ///< span of animation internal counter
#define LV_ANIM_RES_SHIFT 10 ///< bits to shift in computation of animation value (should be log2(LV_ANIM_RESOLUTION))

namespace lvgl::misc {
    
    // we need user_data to store pointer to C++ object, otherwise we cannot
    // access callbacks defined as class members.
    #if LV_USE_USER_DATA

    StyleTransition::StyleTransition() {
        this->initialize({}, 0, 0);
    }

    StyleTransition::StyleTransition(const std::vector<lv_style_prop_t> & props, uint32_t time, uint32_t delay) {
        this->initialize(props, time, delay);
    }

    void StyleTransition::initialize(const std::vector<lv_style_prop_t> & props, uint32_t time, uint32_t delay) {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
        auto path_xcb = [](const lv_anim_t * anim) -> int32_t {
            auto obj = reinterpret_cast<StyleTransition*>(anim->user_data);
            return obj->callback(anim);
        };
        lv_style_transition_dsc_init(this->raw_ptr(), props.data(), path_xcb, time, delay, static_cast<void*>(this));
    }

    void StyleTransition::set_props(const std::vector<lv_style_prop_t> & props) {
        this->lv_obj->props = props.data();
    }

    void StyleTransition::set_time(uint32_t time) {
        this->lv_obj->time = time;
    }

    void StyleTransition::set_delay(uint32_t delay) {
        this->lv_obj->delay = delay;
    }


    int32_t LinearStyleTransition::callback(const struct _lv_anim_t * anim) {
        return lv_anim_path_linear(anim);
    }

    int32_t EaseInStyleTransition::callback(const struct _lv_anim_t * anim) {
        return lv_anim_path_ease_in(anim);
    }
    
    int32_t EaseOutStyleTransition::callback(const struct _lv_anim_t * anim) {
        return lv_anim_path_ease_out(anim);
    }

    int32_t EaseInOutStyleTransition::callback(const struct _lv_anim_t * anim) {
        return lv_anim_path_ease_in_out(anim);
    }

    int32_t OvershootStyleTransition::callback(const struct _lv_anim_t * anim) {
        return lv_anim_path_overshoot(anim);
    }

    int32_t BounceStyleTransition::callback(const struct _lv_anim_t * anim) {
        return lv_anim_path_bounce(anim);
    }

    int32_t StepStyleTransition::callback(const struct _lv_anim_t * anim) {
        return lv_anim_path_step(anim);
    }

    int32_t BlinkStyleTransition::callback(const struct _lv_anim_t * anim) {
        int32_t step = lv_map(anim->act_time, 0, anim->time, 0, LV_ANIM_RESOLUTION);
        step = LV_ANIM_RESOLUTION - 2*std::abs(step - LV_ANIM_RESOLUTION/2);
        int32_t new_value;
        new_value = step * (anim->end_value - anim->start_value);
        new_value = new_value >> LV_ANIM_RES_SHIFT;
        new_value += anim->start_value;

        return new_value;
    }

    #endif // LV_USE_USER_DATA

    Style::Style() {
        this->lv_obj = LvPointerType(lv_cls_alloc<lv_cls>());
        lv_style_init(this->raw_ptr());
    }

    Style::~Style() {
        this->reset();
    }

    void Style::reset() {
        lv_style_reset(this->raw_ptr());
    }

    lv_style_prop_t Style::register_prop(uint8_t flag) {
        return lv_style_register_prop(flag);
    }

    lv_style_prop_t Style::get_num_custom_props() {
        return lv_style_get_num_custom_props();
    }

    bool Style::remove_prop(lv_style_prop_t prop) {
        return lv_style_remove_prop(this->raw_ptr(), prop);
    }

    void Style::set_prop(lv_style_prop_t prop, lv_style_value_t value) {
        lv_style_set_prop(this->raw_ptr(), prop, value);
    }

    void Style::set_prop_meta(lv_style_prop_t prop, uint16_t meta) {
        lv_style_set_prop_meta(this->raw_ptr(), prop, meta);
    }

    lv_style_value_t Style::get_prop(lv_style_prop_t prop) const {
        lv_style_value_t value;
        lv_style_get_prop(this->raw_ptr(), prop, &value);
        return value;
    }

    lv_style_value_t Style::get_prop_default(lv_style_prop_t prop) {
        return lv_style_prop_get_default(prop);
    }

    lv_style_value_t Style::get_prop_inlined(lv_style_prop_t prop) const {
        lv_style_value_t value;
        lv_style_get_prop_inlined(this->raw_ptr(), prop, &value);
        return value;
    }

    void Style::report_style_change() {
        lv_obj_report_style_change(this->raw_ptr());
    }

    void Style::set_size(lv_coord_t value) {
        lv_style_set_size(this->raw_ptr(), value);
    }

    void Style::set_pad_all(lv_coord_t value) {
        lv_style_set_pad_all(this->raw_ptr(), value);
    }

    void Style::set_pad_hor(lv_coord_t value) {
        lv_style_set_pad_hor(this->raw_ptr(), value);
    }

    void Style::set_pad_ver(lv_coord_t value) {
        lv_style_set_pad_ver(this->raw_ptr(), value);
    }

    void Style::set_pad_gap(lv_coord_t value) {
        lv_style_set_pad_gap(this->raw_ptr(), value);
    }

    void Style::set_width(lv_coord_t value) {
        lv_style_set_width(this->raw_ptr(), value);
    }

    void Style::set_min_width(lv_coord_t value) {
        lv_style_set_min_width(this->raw_ptr(), value);
    }

    void Style::set_max_width(lv_coord_t value) {
        lv_style_set_max_width(this->raw_ptr(), value);
    }

    void Style::set_height(lv_coord_t value) {
        lv_style_set_height(this->raw_ptr(), value);
    }

    void Style::set_height_min(lv_coord_t value) {
        lv_style_set_min_height(this->raw_ptr(), value);
    }

    void Style::set_height_max(lv_coord_t value) {
        lv_style_set_max_height(this->raw_ptr(), value);
    }

    void Style::set_x(lv_coord_t value) {
        lv_style_set_x(this->raw_ptr(), value);
    }

    void Style::set_y(lv_coord_t value) {
        lv_style_set_y(this->raw_ptr(), value);
    }

    void Style::set_align(lv_align_t value) {
        lv_style_set_align(this->raw_ptr(), value);
    }

    void Style::set_transform_width(lv_coord_t value) {
        lv_style_set_transform_width(this->raw_ptr(), value);
    }

    void Style::set_transform_height(lv_coord_t value) {
        lv_style_set_transform_height(this->raw_ptr(), value);
    }

    void Style::set_translate_x(lv_coord_t value) {
        lv_style_set_translate_x(this->raw_ptr(), value);
    }

    void Style::set_translate_y(lv_coord_t value) {
        lv_style_set_translate_y(this->raw_ptr(), value);
    }

    void Style::set_transform_zoom(lv_coord_t value) {
        lv_style_set_transform_zoom(this->raw_ptr(), value);
    }

    void Style::set_transform_angle(lv_coord_t value) {
        lv_style_set_transform_angle(this->raw_ptr(), value);
    }

    void Style::set_pad_top(lv_coord_t value) {
        lv_style_set_pad_top(this->raw_ptr(), value);
    }
    
    void Style::set_pad_bottom(lv_coord_t value) {
        lv_style_set_pad_bottom(this->raw_ptr(), value);
    }

    void Style::set_pad_left(lv_coord_t value) {
        lv_style_set_pad_left(this->raw_ptr(), value);
    }

    void Style::set_pad_right(lv_coord_t value) {
        lv_style_set_pad_right(this->raw_ptr(), value);
    }

    void Style::set_pad_row(lv_coord_t value) {
        lv_style_set_pad_row(this->raw_ptr(), value);
    }

    void Style::set_pad_column(lv_coord_t value) {
        lv_style_set_pad_column(this->raw_ptr(), value);
    }

    void Style::set_bg_color(lv_color_t value) {
        lv_style_set_bg_color(this->raw_ptr(), value);
    }

    void Style::set_bg_opa(lv_opa_t value) {
        lv_style_set_bg_opa(this->raw_ptr(), value);
    }

    void Style::set_bg_grad_color(lv_color_t value) {
        lv_style_set_bg_grad_color(this->raw_ptr(), value);
    }

    void Style::set_bg_grad_dir(lv_grad_dir_t value) {
        lv_style_set_bg_grad_dir(this->raw_ptr(), value);
    }

    void Style::set_bg_main_stop(lv_coord_t value) {
        lv_style_set_bg_main_stop(this->raw_ptr(), value);
    }

    void Style::set_bg_grad_stop(lv_coord_t value) {
        lv_style_set_bg_grad_stop(this->raw_ptr(), value);
    }

    void Style::set_bg_grad(const lv_grad_dsc_t * value) {
        lv_style_set_bg_grad(this->raw_ptr(), value);
    }

    void Style::set_bg_img_src(const ImageDescriptor & img) {
        lv_style_set_bg_img_src(this->raw_ptr(), static_cast<const void*>(img.raw_ptr()));
    }

    void Style::set_bg_img_opa(lv_opa_t value) {
        lv_style_set_bg_img_opa(this->raw_ptr(), value);
    }

    void Style::set_bg_img_recolor(lv_color_t value) {
        lv_style_set_bg_img_recolor(this->raw_ptr(), value);
    }

    void Style::set_bg_img_recolor_opa(lv_opa_t value) {
        lv_style_set_bg_img_recolor_opa(this->raw_ptr(), value);
    }

    void Style::set_bg_img_tiled(bool value) {
        lv_style_set_bg_img_tiled(this->raw_ptr(), value);
    }

    void Style::set_border_color(lv_color_t value) {
        lv_style_set_border_color(this->raw_ptr(), value);
    }

    void Style::set_border_opa(lv_opa_t value) {
        lv_style_set_border_opa(this->raw_ptr(), value);
    }

    void Style::set_border_width(lv_coord_t value) {
        lv_style_set_border_width(this->raw_ptr(), value);
    }

    void Style::set_border_side(lv_border_side_t value) {
        lv_style_set_border_side(this->raw_ptr(), value);
    }

    void Style::set_border_post(bool value) {
        lv_style_set_border_post(this->raw_ptr(), value);
    }

    void Style::set_outline_width(lv_coord_t value) {
        lv_style_set_outline_width(this->raw_ptr(), value);
    }

    void Style::set_outline_color(lv_color_t value) {
        lv_style_set_outline_color(this->raw_ptr(), value);
    }

    void Style::set_outline_opa(lv_opa_t value) {
        lv_style_set_outline_opa(this->raw_ptr(), value);
    }

    void Style::set_outline_pad(lv_coord_t value) {
        lv_style_set_outline_pad(this->raw_ptr(), value);
    }

    void Style::set_shadow_width(lv_coord_t value) {
        lv_style_set_shadow_width(this->raw_ptr(), value);
    }

    void Style::set_shadow_ofs_x(lv_coord_t value) {
        lv_style_set_shadow_ofs_x(this->raw_ptr(), value);
    }

    void Style::set_shadow_ofs_y(lv_coord_t value) {
        lv_style_set_shadow_ofs_y(this->raw_ptr(), value);
    }

    void Style::set_shadow_spread(lv_coord_t value) {
        lv_style_set_shadow_spread(this->raw_ptr(), value);
    }

    void Style::set_shadow_color(lv_color_t value) {
        lv_style_set_shadow_color(this->raw_ptr(), value);
    }

    void Style::set_shadow_opa(lv_opa_t value) {
        lv_style_set_shadow_opa(this->raw_ptr(), value);
    }

    void Style::set_img_opa(lv_opa_t value) {
        lv_style_set_img_opa(this->raw_ptr(), value);
    }

    void Style::set_img_recolor(lv_color_t value) {
        lv_style_set_img_recolor(this->raw_ptr(), value);
    }

    void Style::set_img_recolor_opa(lv_opa_t value) {
        lv_style_set_img_recolor_opa(this->raw_ptr(), value);
    }

    void Style::set_line_width(lv_coord_t value) {
        lv_style_set_line_width(this->raw_ptr(), value);
    }

    void Style::set_line_dash_width(lv_coord_t value) {
        lv_style_set_line_dash_width(this->raw_ptr(), value);
    }

    void Style::set_line_dash_gap(lv_coord_t value) {
        lv_style_set_line_dash_gap(this->raw_ptr(), value);
    }

    void Style::set_line_rounded(bool value) {
        lv_style_set_line_rounded(this->raw_ptr(), value);
    }

    void Style::set_line_color(lv_color_t value) {
        lv_style_set_line_color(this->raw_ptr(), value);
    }

    void Style::set_line_opa(lv_opa_t value) {
        lv_style_set_line_opa(this->raw_ptr(), value);
    }

    void Style::set_arc_width(lv_coord_t value) {
        lv_style_set_arc_width(this->raw_ptr(), value);
    }

    void Style::set_arc_rounded(bool value) {
        lv_style_set_arc_rounded(this->raw_ptr(), value);
    }

    void Style::set_arc_color(lv_color_t value) {
        lv_style_set_arc_color(this->raw_ptr(), value);
    }

    void Style::set_arc_opa(lv_opa_t value) {
        lv_style_set_arc_opa(this->raw_ptr(), value);
    }

    void Style::set_arc_img_src(const ImageDescriptor & img) {
        lv_style_set_arc_img_src(this->raw_ptr(), static_cast<const void*>(img.raw_ptr()));
    }

    void Style::set_text_color(lv_color_t value) {
        lv_style_set_text_color(this->raw_ptr(), value);
    }

    void Style::set_text_opa(lv_opa_t value) {
        lv_style_set_text_opa(this->raw_ptr(), value);
    }

    void Style::set_text_font(const Font & value) {
        this->set_text_font(value.raw_ptr());
    }

    void Style::set_text_font(const lv_font_t * value) {
        lv_style_set_text_font(this->raw_ptr(), value);
    }

    void Style::set_text_letter_space(lv_coord_t value) {
        lv_style_set_text_letter_space(this->raw_ptr(), value);
    }

    void Style::set_text_line_space(lv_coord_t value) {
        lv_style_set_text_line_space(this->raw_ptr(), value);
    }

    void Style::set_text_decor(lv_text_decor_t value) {
        lv_style_set_text_decor(this->raw_ptr(), value);
    }

    void Style::set_text_align(lv_text_align_t value) {
        lv_style_set_text_align(this->raw_ptr(), value);
    }

    void Style::set_radius(lv_coord_t value) {
        lv_style_set_radius(this->raw_ptr(), value);
    }

    void Style::set_clip_corner(bool value) {
        lv_style_set_clip_corner(this->raw_ptr(), value);
    }

    void Style::set_opa(lv_opa_t value) {
        lv_style_set_opa(this->raw_ptr(), value);
    }

#if LV_USE_USER_DATA
    void Style::set_color_filter_dsc(const ColorFilter & value) {
        lv_style_set_color_filter_dsc(this->raw_ptr(), value.raw_ptr());
    }
#endif // LV_USE_USER_DATA

    void Style::set_color_filter_dsc(const lv_color_filter_dsc_t * value) {
        lv_style_set_color_filter_dsc(this->raw_ptr(), value);
    }

    void Style::set_color_filter_opa(lv_opa_t value) {
        lv_style_set_color_filter_opa(this->raw_ptr(), value);
    }

    void Style::set_anim(const Animation & value) {
        lv_style_set_anim(this->raw_ptr(), value.raw_ptr());
    }

    void Style::set_anim_time(uint32_t value) {
        lv_style_set_anim_time(this->raw_ptr(), value);
    }

    void Style::set_anim_speed(uint32_t value) {
        lv_style_set_anim_speed(this->raw_ptr(), value);
    }

#if LV_USE_USER_DATA
    void Style::set_transition(const StyleTransition & value) {
        lv_style_set_transition(this->raw_ptr(), value.raw_ptr());
    }
#endif // LV_USE_USER_DATA

    void Style::set_transition(const lv_style_transition_dsc_t * value) {
        lv_style_set_transition(this->raw_ptr(), value);
    }

    void Style::set_blend_mode(lv_blend_mode_t value) {
        lv_style_set_blend_mode(this->raw_ptr(), value);
    }

    void Style::set_layout(uint16_t value) {
        lv_style_set_layout(this->raw_ptr(), value);
    }

    void Style::set_base_dir(lv_base_dir_t value) {
        lv_style_set_base_dir(this->raw_ptr(), value);
    }

    bool Style::is_empty() const {
        return lv_style_is_empty(this->raw_ptr());
    }

#if LV_USE_FLEX
    void Style::set_flex_flow(lv_flex_flow_t value) {
        lv_style_set_flex_flow(this->raw_ptr(), value);
    }
    void Style::set_flex_main_place(lv_flex_align_t value) {
        lv_style_set_flex_main_place(this->raw_ptr(), value);
    }
    void Style::set_flex_cross_place(lv_flex_align_t value) {
        lv_style_set_flex_cross_place(this->raw_ptr(), value);
    }
    void Style::set_flex_track_place(lv_flex_align_t value) {
        lv_style_set_flex_track_place(this->raw_ptr(), value);
    }
    void Style::set_flex_grow(uint8_t value) {
        lv_style_set_flex_grow(this->raw_ptr(), value);
    }
#endif // LV_USE_FLEX

#if LV_USE_GRID
    void Style::set_grid_row_dsc_array(const std::vector<lv_coord_t> & value) {
        lv_style_set_grid_row_dsc_array(this->raw_ptr(), value.data());
    }
    void Style::set_grid_column_dsc_array(const std::vector<lv_coord_t> & value) {
        lv_style_set_grid_column_dsc_array(this->raw_ptr(), value.data());
    }
    void Style::set_grid_row_align(lv_grid_align_t value) {
        lv_style_set_grid_row_align(this->raw_ptr(), value);
    }
    void Style::set_grid_column_align(lv_grid_align_t value) {
        lv_style_set_grid_column_align(this->raw_ptr(), value);
    }
    void Style::set_grid_cell_column_pos(lv_coord_t value) {
        lv_style_set_grid_cell_column_pos(this->raw_ptr(), value);
    }
    void Style::set_grid_cell_column_span(lv_coord_t value) {
        lv_style_set_grid_cell_column_span(this->raw_ptr(), value);
    }
    void Style::set_grid_cell_row_pos(lv_coord_t value) {
        lv_style_set_grid_cell_row_pos(this->raw_ptr(), value);
    }
    void Style::set_grid_cell_row_span(lv_coord_t value) {
        lv_style_set_grid_cell_row_span(this->raw_ptr(), value);
    }
    void Style::set_grid_cell_x_align(lv_coord_t value) {
        lv_style_set_grid_cell_x_align(this->raw_ptr(), value);
    }
    void Style::set_grid_cell_y_align(lv_coord_t value) {
        lv_style_set_grid_cell_y_align(this->raw_ptr(), value);
    }
#endif // LV_USE_GRID
}