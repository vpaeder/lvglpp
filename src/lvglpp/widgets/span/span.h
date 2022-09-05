/** \file span.h
 *  \brief Header file for C++ wrapper for lv_spangroup_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once

#include "../../core/object.h"

#if LV_USE_SPAN != 0

namespace lvgl::widgets {

    using namespace lvgl::core;
    
    class SpanGroup;

    /** \class Span
     *  \brief Wraps a lv_spangroup_t object.
     */
    class Span : public PointerWrapper<lv_span_t, lv_mem_free> {
    public:
        /** \fn Span(lv_span_t* span)
         *  \brief Constructor with C object.
         *  \param span: span object to wrap.
         */
        Span(lv_span_t* span);

        /** \fn void set_text(const std::string & text)
         *  \brief Sets span text. Text gets copied.
         *  \param text: text string.
         */
        void set_text(const std::string & text);

        /** \fn void set_text_static(const std::string & text)
         *  \brief Sets span text. Text object must remain allocated.
         *  \param text: text string.
         */
        void set_text_static(const std::string & text);

        /** \fn Style get_style() const
         *  \brief Gives access to span style.
         *  \returns the style object.
         */
        Style get_style() const;

        /** \fn void set_style(const Style & style)
         *  \brief Sets the span style.
         *  \param style: the style to set.
         */
        void set_style(const Style & style);

    };

    /** \class SpanGroup
     *  \brief Wraps a lv_spangroup_t object.
     */
    class SpanGroup : public Widget<lv_spangroup_create> {
    public:
        using Widget::Widget;

        /** \fn Span new_span()
         *  \brief Creates a new span.
         *  \returns the new span object.
         */
        Span new_span();

        /** \fn void del_span(Span & span)
         *  \brief Deletes the given span.
         *  \param span: the span object to delete.
         */
        void del_span(Span & span);

        /** \fn void set_align(lv_text_align_t align)
         *  \brief Sets text alignment.
         *  \param align: text alignment code.
         */
        void set_align(lv_text_align_t align);

        /** \fn void set_overflow(lv_span_overflow_t overflow)
         *  \brief Sets behaviour with overflow.
         *  \param overflow: code for overflow behaviour.
         */
        void set_overflow(lv_span_overflow_t overflow);

        /** \fn void set_indent(lv_coord_t indent)
         *  \brief Sets text indent.
         *  \param indent: amount of text indent.
         */
        void set_indent(lv_coord_t indent);

        /** \fn void set_mode(lv_span_mode_t mode)
         *  \brief Sets span group mode.
         *  \param mode: mode.
         */
        void set_mode(lv_span_mode_t mode);

        /** \brief Sets number of lines that can be displayed.
         *  \param lines: number of lines (<0 to disable limit)
         */
        void set_lines(int32_t lines);

        /** \fn Span get_child(int32_t id) const
         *  \brief Gets span with given index.
         *  \param id: span index.
         *  \returns span object for given index.
         */
        Span get_child(int32_t id) const;

        /** \fn uint32_t get_child_cnt() const
         *  \brief Gets number of spans.
         *  \returns number of spans.
         */
        uint32_t get_child_cnt() const;

        /** \fn lv_text_align_t get_align() const
         *  \brief Gets text alignment.
         *  \returns text alignment code.
         */
        lv_text_align_t get_align() const;

        /** \fn lv_span_overflow_t get_overflow() const
         *  \brief Gets behaviour with text overflow.
         *  \returns code for behaviour with text overflow.
         */
        lv_span_overflow_t get_overflow() const;

        /** \fn lv_coord_t get_indent() const
         *  \brief Gets text indent.
         *  \returns amount of text indent.
         */
        lv_coord_t get_indent() const;

        /** \fn lv_span_mode_t get_mode() const
         *  \brief Gets span group mode.
         *  \returns mode code.
         */
        lv_span_mode_t get_mode() const;

        /** \brief Gets number of lines that can be displayed.
         *  \returns number of lines (<0 to disable limit).
         */
        int32_t get_lines() const;

        /** \fn lv_coord_t get_max_line_h() const
         *  \brief Gets maximum line height of all spans.
         *  \returns maximum line height.
         */
        lv_coord_t get_max_line_h() const;
        
        /** \fn uint32_t get_expand_width(uint32_t max_width) const
         *  \brief Gets aggregate width of spans. If larger than max_width,
         *  returns max_width.
         *  \param max_width: maximum width to return.
         *  \returns aggregate width of spans, or max_width.
         */
        uint32_t get_expand_width(uint32_t max_width) const;

        /** \fn lv_coord_t get_expand_height(lv_coord_t width) const
         *  \brief Gets the text height with given span group width.
         *  \param width: imposed span group width.
         *  \returns span group height for given width.
         */
        lv_coord_t get_expand_height(lv_coord_t width) const;

        /** \fn void refresh_mode()
         *  \brief Updates the span group mode.
         */
        void refresh_mode();

    };

}
#endif // LV_USE_SPAN