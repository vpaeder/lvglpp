/** \file span.cpp
 *  \brief Implementation file for C++ wrapper for lv_spangroup_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#include "span.h"
#if LV_USE_SPAN != 0

#include "../../misc/style.h"

namespace lvgl::widgets {

    Span::Span(lv_span_t* span) {
        this->owns_ptr = false;
        this->lv_obj = LvPointer<lv_span_t, lv_mem_free>(span);
    }

    void Span::set_text(const std::string & text) {
        lv_span_set_text(this->raw_ptr(), text.c_str());
    }

    void Span::set_text_static(const std::string & text) {
        lv_span_set_text_static(this->raw_ptr(), text.data());
    }

    Style Span::get_style() const {
        return Style(const_cast<lv_style_t*>(&this->raw_ptr()->style), false);
    }

    void Span::set_style(const Style & style) {
        this->raw_ptr()->style = style.raw();
    }


    Span SpanGroup::new_span() {
        return Span(lv_spangroup_new_span(this->raw_ptr()));
    }

    void SpanGroup::del_span(Span & span) {
        lv_spangroup_del_span(this->raw_ptr(), span.raw_ptr());
    }

    void SpanGroup::set_align(lv_text_align_t align) {
        lv_spangroup_set_align(this->raw_ptr(), align);
    }

    void SpanGroup::set_overflow(lv_span_overflow_t overflow) {
        lv_spangroup_set_overflow(this->raw_ptr(), overflow);
    }

    void SpanGroup::set_indent(lv_coord_t indent) {
        lv_spangroup_set_indent(this->raw_ptr(), indent);
    }

    void SpanGroup::set_mode(lv_span_mode_t mode) {
        lv_spangroup_set_mode(this->raw_ptr(), mode);
    }

    void SpanGroup::set_lines(int32_t lines) {
        lv_spangroup_set_lines(this->raw_ptr(), lines);
    }

    Span SpanGroup::get_child(int32_t id) const {
        return Span(lv_spangroup_get_child(this->raw_ptr(), id));
    }

    uint32_t SpanGroup::get_child_cnt() const {
        return lv_spangroup_get_child_cnt(this->raw_ptr());
    }

    lv_text_align_t SpanGroup::get_align() const {
        return lv_spangroup_get_align(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_span_overflow_t SpanGroup::get_overflow() const {
        return lv_spangroup_get_overflow(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_coord_t SpanGroup::get_indent() const {
        return lv_spangroup_get_indent(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_span_mode_t SpanGroup::get_mode() const {
        return lv_spangroup_get_mode(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    int32_t SpanGroup::get_lines() const {
        return lv_spangroup_get_lines(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }

    lv_coord_t SpanGroup::get_max_line_h() const {
        return lv_spangroup_get_max_line_h(const_cast<lv_cls_ptr>(this->raw_ptr()));
    }
    
    uint32_t SpanGroup::get_expand_width(uint32_t max_width) const {
        return lv_spangroup_get_expand_width(const_cast<lv_cls_ptr>(this->raw_ptr()), max_width);
    }

    lv_coord_t SpanGroup::get_expand_height(lv_coord_t width) const {
        return lv_spangroup_get_expand_height(const_cast<lv_cls_ptr>(this->raw_ptr()), width);
    }

    void SpanGroup::refresh_mode() {
        lv_spangroup_refr_mode(this->raw_ptr());
    }

}
#endif // LV_USE_SPAN