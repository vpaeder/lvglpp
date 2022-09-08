/** \file style.h
 *  \brief Header file for C++ wrapper for lv_style_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include <memory>
#include "lvgl.h"
#include "color.h"
#include "anim.h"
#include "../font/font.h"
#include "../draw/image.h"
#include "../lv_wrapper.h"

namespace lvgl::misc {
    
    using namespace lvgl::font;
    using namespace lvgl::draw;

    // we need user_data to store pointer to C++ object, otherwise we cannot
    // access callbacks defined as class members.
    #if LV_USE_USER_DATA
    /** \class StyleTransition
     *  \brief Wraps a lv_style_transition_dsc_t object. This is a base class
     *  to define style transition.
     */
    class StyleTransition : public PointerWrapper<lv_style_transition_dsc_t, lv_mem_free> {
    protected:
        /** \fn void initialize(const std::vector<lv_style_prop_t> & props, uint32_t time, uint32_t delay)
         *  \brief Initializes style transition.
         *  \param props: a list of style properties.
         *  \param time: transition duration.
         *  \param delay: transition delay.
         */
        void initialize(const std::vector<lv_style_prop_t> & props, uint32_t time, uint32_t delay);

        /** \fn virtual int32_t callback(const struct _lv_anim_t * anim)
         *  \brief Callback function called on style transition.
         *  \param anim: pointer to an animation descriptor.
         */
        virtual int32_t callback(const struct _lv_anim_t * anim) = 0;

    public:
        using PointerWrapper::PointerWrapper;

        /** \fn StyleTransition()
         *  \brief Default constructor.
         */
        StyleTransition();

        /** \fn StyleTransition(const std::vector<lv_style_prop_t> & props, uint32_t time, uint32_t delay)
         *  \brief Constructor with parameters.
         *  \param props: a list of style properties.
         *  \param time: transition duration.
         *  \param delay: transition delay.
         */
        StyleTransition(const std::vector<lv_style_prop_t> & props, uint32_t time, uint32_t delay);

        /** \fn void set_props(const std::vector<lv_style_prop_t> & props)
         *  \brief Sets style properties affected by transition.
         *  \param props: a list of style properties.
         */
        void set_props(const std::vector<lv_style_prop_t> & props);

        /** \fn void set_time(uint32_t time)
         *  \brief Sets transition duration, in ms.
         *  \param time: transition duration.
         */
        void set_time(uint32_t time);

        /** \fn void set_delay(uint32_t delay)
         *  \brief Sets transition delay, in ms.
         *  \param delay: transition delay.
         */
        void set_delay(uint32_t delay);
    };

    
    /** \class LinearStyleTransition
     *  \brief This is a style transition with a linear animation.
     */
    class LinearStyleTransition : public StyleTransition {
        public:
            using StyleTransition::StyleTransition;

        protected:
        /** \fn int32_t callback(const struct _lv_anim_t * anim)
         *  \brief Callback function called on style transition.
         *  \param anim: pointer to an animation descriptor.
         */
            int32_t callback(const struct _lv_anim_t * anim) override;
    };


    /** \class EaseInStyleTransition
     *  \brief This is a style transition with an easing-in animation.
     */
    class EaseInStyleTransition : public StyleTransition {
        public:
            using StyleTransition::StyleTransition;
            
        protected:
        /** \fn int32_t callback(const struct _lv_anim_t * anim)
         *  \brief Callback function called on style transition.
         *  \param anim: pointer to an animation descriptor.
         */
            int32_t callback(const struct _lv_anim_t * anim) override;
    };


    /** \class EaseOutStyleTransition
     *  \brief This is a style transition with an easing-out animation.
     */
    class EaseOutStyleTransition : public StyleTransition {
        public:
            using StyleTransition::StyleTransition;
            
        protected:
        /** \fn int32_t callback(const struct _lv_anim_t * anim)
         *  \brief Callback function called on style transition.
         *  \param anim: pointer to an animation descriptor.
         */
            int32_t callback(const struct _lv_anim_t * anim) override;
    };


    /** \class EaseInOutStyleTransition
     *  \brief This is a style transition with a easing-in and easing-out animation.
     */
    class EaseInOutStyleTransition : public StyleTransition {
        public:
            using StyleTransition::StyleTransition;
            
        protected:
        /** \fn int32_t callback(const struct _lv_anim_t * anim)
         *  \brief Callback function called on style transition.
         *  \param anim: pointer to an animation descriptor.
         */
            int32_t callback(const struct _lv_anim_t * anim) override;
    };


    /** \class OvershootStyleTransition
     *  \brief This is a style transition with an animation overshooting on the end.
     */
    class OvershootStyleTransition : public StyleTransition {
        public:
            using StyleTransition::StyleTransition;
            
        protected:
        /** \fn int32_t callback(const struct _lv_anim_t * anim)
         *  \brief Callback function called on style transition.
         *  \param anim: pointer to an animation descriptor.
         */
            int32_t callback(const struct _lv_anim_t * anim) override;
    };


    /** \class BounceStyleTransition
     *  \brief This is a style transition with an animation with 3 bounces.
     */
    class BounceStyleTransition : public StyleTransition {
        public:
            using StyleTransition::StyleTransition;
            
        protected:
        /** \fn int32_t callback(const struct _lv_anim_t * anim)
         *  \brief Callback function called on style transition.
         *  \param anim: pointer to an animation descriptor.
         */
            int32_t callback(const struct _lv_anim_t * anim) override;
    };


    /** \class StepStyleTransition
     *  \brief This is a style transition with a step animation.
     */
    class StepStyleTransition : public StyleTransition {
        public:
            using StyleTransition::StyleTransition;
            
        protected:
        /** \fn int32_t callback(const struct _lv_anim_t * anim)
         *  \brief Callback function called on style transition.
         *  \param anim: pointer to an animation descriptor.
         */
            int32_t callback(const struct _lv_anim_t * anim) override;
    };


    /** \class BlinkStyleTransition
     *  \brief This is a style transition with blinking (turns on then off).
     */
    class BlinkStyleTransition : public StyleTransition {
        public:
            using StyleTransition::StyleTransition;
            
        protected:
        /** \fn int32_t callback(const struct _lv_anim_t * anim)
         *  \brief Callback function called on style transition.
         *  \param anim: pointer to an animation descriptor.
         */
            int32_t callback(const struct _lv_anim_t * anim) override;
    };
    #endif // LV_USE_USER_DATA

    /** \class Style
     *  \brief Wraps a lv_style_t object.
     */
    class Style : public PointerWrapper<lv_style_t, lv_mem_free> {
    public:
        using PointerWrapper::PointerWrapper;
        
        /** \fn Style()
         *  \brief Default constructor.
         */
        Style();

        /** \fn ~Style()
         *  \brief Default destructor.
         */
        ~Style();

        /** \fn void reset()
         *  \brief Resets style.
         */
        void reset();

        /** \fn bool is_empty() const
         *  \brief Tells if style is empty.
         *  \returns true if style is empty, false otherwise.
         */
        bool is_empty() const;

        /** \fn lv_style_prop_t register_prop(uint8_t flag)
         *  \brief Registers a new custom style property.
         *  \param flag: default style property value.
         *  \returns a new property ID, or LV_STYLE_PROP_INV if none are available.
         */
        static lv_style_prop_t register_prop(uint8_t flag);

        /** \brief Get the number of custom properties that have been registered thus far.
         *  \returns number of custom properties.
         */
        static lv_style_prop_t get_num_custom_props();

        /** \fn bool remove_prop(lv_style_prop_t prop)
         *  \brief Removes a style property.
         *  \param prop: style property ID.
         *  \returns true if property could be removed, false otherwise.
         */
        bool remove_prop(lv_style_prop_t prop);

        /** \fn void set_prop(lv_style_prop_t prop, lv_style_value_t value)
         *  \brief Sets the value of a style property.
         *  \param prop: style property ID.
         *  \param value: style property value.
         */
        void set_prop(lv_style_prop_t prop, lv_style_value_t value);

        /** \brief Sets the value of a meta state.
         *  \param prop: style property ID.
         *  \param meta: meta value.
         */
        void set_prop_meta(lv_style_prop_t prop, uint16_t meta);

        /** \fn lv_style_value_t get_prop(lv_style_prop_t prop) const
         *  \brief Gets the value of a style property.
         *  \param prop: style property ID.
         *  \returns the style property value.
         */
        lv_style_value_t get_prop(lv_style_prop_t prop) const;

        /** \brief Gets the default value of a style property.
         *  \param prop: style property ID.
         *  \returns the style property default value.
         */
        static lv_style_value_t get_prop_default(lv_style_prop_t prop);

        /** \fn lv_style_value_t get_prop_inlined(lv_style_prop_t prop) const
         *  \brief Gets the value of a style property. This does the same as get_prop,
         *  but it is there for performance-critical tasks.
         *  \param prop: style property ID.
         *  \returns the style property value.
         */
        lv_style_value_t get_prop_inlined(lv_style_prop_t prop) const;

        /** \fn void report_style_change()
         *  \brief Notifies objects that a style was modified.
         */
        void report_style_change();

        /** \fn void set_size(lv_coord_t value)
         *  \brief Sets size property.
         *  \param value: size value.
         */
        void set_size(lv_coord_t value);

        /** \fn void set_pad_all(lv_coord_t value)
         *  \brief Sets all padding properties.
         *  \param value: padding size value.
         */
        void set_pad_all(lv_coord_t value);

        /** \fn void set_pad_hor(lv_coord_t value)
         *  \brief Sets horizontal padding properties.
         *  \param value: padding size value.
         */
        void set_pad_hor(lv_coord_t value);

        /** \fn void set_pad_ver(lv_coord_t value)
         *  \brief Sets vertical padding properties.
         *  \param value: padding size value.
         */
        void set_pad_ver(lv_coord_t value);

        /** \fn void set_pad_gap(lv_coord_t value)
         *  \brief Sets inter-cell padding properties.
         *  \param value: padding size value.
         */
        void set_pad_gap(lv_coord_t value);

        /** \fn void set_width(lv_coord_t value)
         *  \brief Sets width property.
         *  \param value: width value.
         */
        void set_width(lv_coord_t value);

        /** \fn void set_min_width(lv_coord_t value)
         *  \brief Sets minimum width property.
         *  \param value: minimum width value.
         */
        void set_min_width(lv_coord_t value);

        /** \fn void set_max_width(lv_coord_t value)
         *  \brief Sets maximum width property.
         *  \param value: maximum width value.
         */
        void set_max_width(lv_coord_t value);

        /** \fn void set_height(lv_coord_t value)
         *  \brief Sets height property.
         *  \param value: height value.
         */
        void set_height(lv_coord_t value);

        /** \fn void set_height_min(lv_coord_t value)
         *  \brief Sets minimum height property.
         *  \param value: minimum height value.
         */
        void set_height_min(lv_coord_t value);

        /** \fn void set_height_max(lv_coord_t value)
         *  \brief Sets maximum height property.
         *  \param value: maximum height value.
         */
        void set_height_max(lv_coord_t value);

        /** \fn void set_x(lv_coord_t value)
         *  \brief Sets horizontal coordinate property.
         *  \param value: horizontal coordinate value.
         */
        void set_x(lv_coord_t value);

        /** \fn void set_y(lv_coord_t value)
         *  \brief Sets vertical coordinate property.
         *  \param value: vertical coordinate value.
         */
        void set_y(lv_coord_t value);

        /** \fn void set_align(lv_align_t value)
         *  \brief Sets alignment property.
         *  \param value: alignement type code.
         */
        void set_align(lv_align_t value);

        /** \fn void set_transform_width(lv_coord_t value)
         *  \brief Sets transform width property.
         *  \param value: transform width value.
         */
        void set_transform_width(lv_coord_t value);

        /** \fn void set_transform_height(lv_coord_t value)
         *  \brief Sets transform height property.
         *  \param value: transform height value.
         */
        void set_transform_height(lv_coord_t value);

        /** \fn void set_translate_x(lv_coord_t value)
         *  \brief Sets horizontal translation coordinate property.
         *  \param value: horizontal translation coordinate value.
         */
        void set_translate_x(lv_coord_t value);

        /** \fn void set_translate_y(lv_coord_t value)
         *  \brief Sets vertical translation coordinate property.
         *  \param value: vertical translation coordinate value.
         */
        void set_translate_y(lv_coord_t value);

        /** \fn void set_transform_zoom(lv_coord_t value)
         *  \brief Sets transform zoom factor property.
         *  \param value: zoom factor value.
         */
        void set_transform_zoom(lv_coord_t value);

        /** \fn void set_transform_angle(lv_coord_t value)
         *  \brief Sets transform rotation angle property.
         *  \param value: rotation angle value.
         */
        void set_transform_angle(lv_coord_t value);

        /** \fn void set_pad_top(lv_coord_t value)
         *  \brief Sets top padding property.
         *  \param value: padding value.
         */
        void set_pad_top(lv_coord_t value);

        /** \fn void set_pad_bottom(lv_coord_t value)
         *  \brief Sets bottom padding property.
         *  \param value: padding value.
         */
        void set_pad_bottom(lv_coord_t value);

        /** \fn void set_pad_left(lv_coord_t value)
         *  \brief Sets left padding property.
         *  \param value: padding value.
         */
        void set_pad_left(lv_coord_t value);

        /** \fn void set_pad_right(lv_coord_t value)
         *  \brief Sets right padding property.
         *  \param value: padding value.
         */
        void set_pad_right(lv_coord_t value);

        /** \fn void set_pad_row(lv_coord_t value)
         *  \brief Sets inter-row padding property.
         *  \param value: padding value.
         */
        void set_pad_row(lv_coord_t value);

        /** \fn void set_pad_column(lv_coord_t value)
         *  \brief Sets inter-column padding property.
         *  \param value: padding value.
         */
        void set_pad_column(lv_coord_t value);

        /** \fn void set_bg_color(lv_color_t value)
         *  \brief Sets background color property.
         *  \param value: color value.
         */
        void set_bg_color(lv_color_t value);

        /** \fn void set_bg_opa(lv_opa_t value)
         *  \brief Sets background opacity property.
         *  \param value: opacity value.
         */
        void set_bg_opa(lv_opa_t value);

        /** \fn void set_bg_grad_color(lv_color_t value)
         *  \brief Sets background gradient color property.
         *  \param value: color value.
         */
        void set_bg_grad_color(lv_color_t value);

        /** \fn void set_bg_grad_dir(lv_grad_dir_t value)
         *  \brief Sets background gradient direction property.
         *  \param value: direction code.
         */
        void set_bg_grad_dir(lv_grad_dir_t value);

        /** \fn void set_bg_main_stop(lv_coord_t value)
         *  \brief Sets background color main stop property.
         *  This is the position until which the background is filled
         *  with main color.
         *  \param value: main stop value.
         */
        void set_bg_main_stop(lv_coord_t value);

        /** \fn void set_bg_grad_stop(lv_coord_t value)
         *  \brief Sets background color gradient stop property.
         *  This is the position from which the background is filled
         *  with second color.
         *  \param value: main stop value.
         */
        void set_bg_grad_stop(lv_coord_t value);

        /** \fn void set_bg_grad(const lv_grad_dsc_t * value)
         *  \brief Sets background gradient.
         *  \param value: gradient descriptor.
         */
        void set_bg_grad(const lv_grad_dsc_t * value);

        /** \fn void set_bg_img_src(const ImageDescriptor & img)
         *  \brief Sets the background image property.
         *  \param img: image descriptor.
         */
        void set_bg_img_src(const ImageDescriptor & img);

        /** \fn void set_bg_img_opa(lv_opa_t value)
         *  \brief Sets the background image opacity property.
         *  \param value: image opacity property.
         */
        void set_bg_img_opa(lv_opa_t value);

        /** \fn void set_bg_img_recolor(lv_color_t value)
         *  \brief Sets the color used to recolor the background image.
         *  \param value: color value.
         */
        void set_bg_img_recolor(lv_color_t value);

        /** \fn void set_bg_img_recolor_opa(lv_opa_t value)
         *  \brief Sets the opacity of background image recoloring.
         *  \param value: recoloring opacity value.
         */
        void set_bg_img_recolor_opa(lv_opa_t value);

        /** \fn void set_bg_img_tiled(bool value)
         *  \brief Enables/disables background image tiling.
         *  \param value: if true, background image tiling is enabled.
         */
        void set_bg_img_tiled(bool value);

        /** \fn void set_border_color(lv_color_t value)
         *  \brief Sets border color property.
         *  \param value: color value.
         */
        void set_border_color(lv_color_t value);

        /** \fn void set_border_opa(lv_opa_t value)
         *  \brief Sets border opacity property.
         *  \param value: opacity value.
         */
        void set_border_opa(lv_opa_t value);

        /** \fn void set_border_width(lv_coord_t value)
         *  \brief Sets border width property.
         *  \param value: width value.
         */
        void set_border_width(lv_coord_t value);

        /** \fn void set_border_side(lv_border_side_t value)
         *  \brief Sets border side property.
         *  \param value: an OR-ed combination of lv_border_side_t values.
         */
        void set_border_side(lv_border_side_t value);

        /** \fn void set_border_post(bool value)
         *  \brief Sets whether border is drawn after children.
         *  \param value: if true, border is drawn after children.
         */
        void set_border_post(bool value);

        /** \fn void set_outline_width(lv_coord_t value)
         *  \brief Sets outline width property.
         *  \param value: width value.
         */
        void set_outline_width(lv_coord_t value);

        /** \fn void set_outline_color(lv_color_t value)
         *  \brief Sets outline color property.
         *  \param value: color value.
         */
        void set_outline_color(lv_color_t value);

        /** \fn void set_outline_opa(lv_opa_t value)
         *  \brief Sets outline opacity property.
         *  \param value: opacity value.
         */
        void set_outline_opa(lv_opa_t value);

        /** \fn void set_outline_pad(lv_coord_t value)
         *  \brief Sets outline padding property.
         *  \param value: padding value.
         */
        void set_outline_pad(lv_coord_t value);

        /** \fn void set_shadow_width(lv_coord_t value)
         *  \brief Sets shadow width property.
         *  \param value: width value.
         */
        void set_shadow_width(lv_coord_t value);

        /** \fn void set_shadow_ofs_x(lv_coord_t value)
         *  \brief Sets shadow horizontal offset property.
         *  \param value: horizontal offset value.
         */
        void set_shadow_ofs_x(lv_coord_t value);

        /** \fn void set_shadow_ofs_y(lv_coord_t value)
         *  \brief Sets shadow vertical offset property.
         *  \param value: vertical offset value.
         */
        void set_shadow_ofs_y(lv_coord_t value);

        /** \fn void set_shadow_spread(lv_coord_t value)
         *  \brief Sets shadow spread property.
         *  \param value: shadow spread value.
         */
        void set_shadow_spread(lv_coord_t value);

        /** \fn void set_shadow_color(lv_color_t value)
         *  \brief Sets shadow color property.
         *  \param value: color value.
         */
        void set_shadow_color(lv_color_t value);

        /** \fn void set_shadow_opa(lv_opa_t value)
         *  \brief Sets shadow opacity property.
         *  \param value: opacity value.
         */
        void set_shadow_opa(lv_opa_t value);

        /** \fn void set_img_opa(lv_opa_t value)
         *  \brief Sets image opacity property.
         *  \param value: opacity value.
         */
        void set_img_opa(lv_opa_t value);

        /** \fn void set_img_recolor(lv_color_t value)
         *  \brief Sets the color used to recolor the image.
         *  \param value: color value.
         */
        void set_img_recolor(lv_color_t value);

        /** \fn void set_img_recolor_opa(lv_opa_t value)
         *  \brief Sets the opacity of image recoloring.
         *  \param value: opacity value.
         */
        void set_img_recolor_opa(lv_opa_t value);

        /** \fn void set_line_width(lv_coord_t value)
         *  \brief Sets the line width property.
         *  \param value: width value.
         */
        void set_line_width(lv_coord_t value);

        /** \fn void set_line_dash_width(lv_coord_t value)
         *  \brief Sets the dash width property.
         *  \param value: dash width value.
         */
        void set_line_dash_width(lv_coord_t value);

        /** \fn void set_line_dash_gap(lv_coord_t value)
         *  \brief Sets the dash gap property.
         *  \param value: dash gap value.
         */
        void set_line_dash_gap(lv_coord_t value);

        /** \fn void set_line_rounded(bool value)
         *  \brief Enables/disables line ends rounding.
         *  \param value: if true, lines ends are rounded.
         */
        void set_line_rounded(bool value);

        /** \fn void set_line_color(lv_color_t value)
         *  \brief Sets line color property.
         *  \param value: color value.
         */
        void set_line_color(lv_color_t value);

        /** \fn void set_line_opa(lv_opa_t value)
         *  \brief Sets line opacity property.
         *  \param value: opacity value.
         */
        void set_line_opa(lv_opa_t value);

        /** \fn void set_arc_width(lv_coord_t value)
         *  \brief Sets arc width property.
         *  \param value: arc width value.
         */
        void set_arc_width(lv_coord_t value);

        /** \fn void set_arc_rounded(bool value)
         *  \brief Sets arc width property.
         *  \param value: arc width value.
         */
        void set_arc_rounded(bool value);

        /** \fn void set_arc_color(lv_color_t value)
         *  \brief Sets arc color property.
         *  \param value: color value.
         */
        void set_arc_color(lv_color_t value);

        /** \fn void set_arc_opa(lv_opa_t value)
         *  \brief Sets arc opacity property.
         *  \param value: opacity value.
         */
        void set_arc_opa(lv_opa_t value);

        /** \fn void set_arc_img_src(const ImageDescriptor & img)
         *  \brief Sets arc image property.
         *  \param img: a pointer to an image descriptor.
         */
        void set_arc_img_src(const ImageDescriptor & img);

        /** \fn void set_text_color(lv_color_t value)
         *  \brief Sets text color property.
         *  \param value: color value.
         */
        void set_text_color(lv_color_t value);

        /** \fn void set_text_opa(lv_opa_t value)
         *  \brief Sets text opacity property.
         *  \param value: opacity value.
         */
        void set_text_opa(lv_opa_t value);

        /** \fn void set_text_font(const Font & value)
         *  \brief Sets text font property.
         *  \param value: font object.
         */
        void set_text_font(const Font & value);

        /** \fn void set_text_font(const lv_font_t * value)
         *  \brief Sets text font property.
         *  \param value: pointer to font descriptor.
         */
        void set_text_font(const lv_font_t * value);

        /** \fn void set_text_letter_space(lv_coord_t value)
         *  \brief Sets text letter spacing property.
         *  \param value: letter spacing value.
         */
        void set_text_letter_space(lv_coord_t value);

        /** \fn void set_text_line_space(lv_coord_t value)
         *  \brief Sets text line spacing property.
         *  \param value: line spacing value.
         */
        void set_text_line_space(lv_coord_t value);

        /** \fn void set_text_decor(lv_text_decor_t value)
         *  \brief Sets text decoration property.
         *  \param value: OR-ed combination of lv_text_decor_t values.
         */
        void set_text_decor(lv_text_decor_t value);

        /** \fn void set_text_align(lv_text_align_t value)
         *  \brief Sets text align property.
         *  \param value: text align code.
         */
        void set_text_align(lv_text_align_t value);

        /** \fn void set_radius(lv_coord_t value)
         *  \brief Sets radius property.
         *  \param value: radius value.
         */
        void set_radius(lv_coord_t value);

        /** \fn void set_clip_corner(bool value)
         *  \brief Enables/disables corner clipping.
         *  \param value: if true, corners are clipped by radius property.
         */
        void set_clip_corner(bool value);

        /** \fn void set_opa(lv_opa_t value)
         *  \brief Sets opacity property.
         *  \param value: opacity value.
         */
        void set_opa(lv_opa_t value);

#if LV_USE_USER_DATA
        /** \fn void set_color_filter_dsc(const ColorFilter & value)
         *  \brief Sets color filter property.
         *  \param value: color filter descriptor.
         */
        void set_color_filter_dsc(const ColorFilter & value);
#endif //LV_USE_USER_DATA

        /** \fn void set_color_filter_dsc(const lv_color_filter_dsc_t * value)
         *  \brief Sets color filter property.
         *  \param value: color filter descriptor.
         */
        void set_color_filter_dsc(const lv_color_filter_dsc_t * value);

        /** \fn void set_color_filter_opa(lv_opa_t value)
         *  \brief Sets color filter opacity property.
         *  \param value: opacity value.
         */
        void set_color_filter_opa(lv_opa_t value);

        /** \fn void set_anim(const Animation & value)
         *  \brief Sets associated animation.
         *  \param value: animation object.
         */
        void set_anim(const Animation & value);

        /** \fn void set_anim_time(uint32_t value)
         *  \brief Sets animation duration property.
         *  \param value: animation duration, in ms.
         */
        void set_anim_time(uint32_t value);

        /** \fn void set_anim_speed(uint32_t value)
         *  \brief Sets animation speed property.
         *  \param value: animation speed, in ms.
         */
        void set_anim_speed(uint32_t value);

#if LV_USE_USER_DATA
        /** \fn void set_transition(const StyleTransition & value)
         *  \brief Sets style transition property.
         *  \param value: style transition descriptor.
         */
        void set_transition(const StyleTransition & value);
#endif // LV_USE_USER_DATA

        /** \fn void set_transition(const lv_style_transition_dsc_t * value)
         *  \brief Sets style transition property.
         *  \param value: style transition descriptor.
         */
        void set_transition(const lv_style_transition_dsc_t * value);

        /** \fn void set_blend_mode(lv_blend_mode_t value)
         *  \brief Sets blend mode property.
         *  \param value: blend mode code.
         */
        void set_blend_mode(lv_blend_mode_t value);

        /** \fn void set_layout(uint16_t value)
         *  \brief Sets layout property.
         *  \param value: layout index.
         */
        void set_layout(uint16_t value);

        /** \fn void set_base_dir(lv_base_dir_t value)
         *  \brief Sets base direction property.
         *  \param value: direction code.
         */
        void set_base_dir(lv_base_dir_t value);

#if LV_USE_FLEX
        /* flex layout */
        /** \fn void set_flex_flow(lv_flex_flow_t value)
         *  \brief Sets flex flow.
         *  \param value: code for flex flow (see lv_flex_flow_t for options).
         */
        void set_flex_flow(lv_flex_flow_t value);

        /** \fn void set_flex_main_place(lv_flex_align_t value)
         *  \brief Sets flex alignment in main direction.
         *  \param value: alignment code.
         */
        void set_flex_main_place(lv_flex_align_t value);

        /** \fn void set_flex_cross_place(lv_flex_align_t value)
         *  \brief Sets flex alignment in alternate direction.
         *  \param value: alignment code.
         */
        void set_flex_cross_place(lv_flex_align_t value);

        /** \fn void set_flex_track_place(lv_flex_align_t value)
         *  \brief Sets flex content alignment.
         *  \param value: alignment code.
         */
        void set_flex_track_place(lv_flex_align_t value);

        /** \fn void set_flex_grow(uint8_t value)
         *  \brief Sets flex grow.
         *  \param value: relative grow value.
         */
        void set_flex_grow(uint8_t value);
#endif // LV_USE_FLEX

#if LV_USE_GRID
        /* grid layout */
        /** \fn void set_grid_row_dsc_array(const std::vector<lv_coord_t> & value)
         *  \brief Sets grid row heights.
         *  \param value: array of row heights.
         */
        void set_grid_row_dsc_array(const std::vector<lv_coord_t> & value);

        /** \fn void set_grid_column_dsc_array(const std::vector<lv_coord_t> & value)
         *  \brief Sets grid column widths.
         *  \param value: array of column widths.
         */
        void set_grid_column_dsc_array(const std::vector<lv_coord_t> & value);

        /** \fn void set_grid_row_align(lv_grid_align_t value)
         *  \brief Sets grid content's vertical alignment.
         *  \param value: array of column widths.
         */
        void set_grid_row_align(lv_grid_align_t value);

        /** \fn void set_grid_column_align(lv_grid_align_t value)
         *  \brief Sets grid content's horizontal alignment.
         *  \param value: array of column widths.
         */
        void set_grid_column_align(lv_grid_align_t value);

        /** \fn void set_grid_cell_column_pos(lv_coord_t value)
         *  \brief Sets grid's active column index.
         *  \param value: column index (zero-based).
         */
        void set_grid_cell_column_pos(lv_coord_t value);

        /** \fn void set_grid_cell_column_span(lv_coord_t value)
         *  \brief Sets grid's active column span.
         *  \param value: column span (1 or more).
         */
        void set_grid_cell_column_span(lv_coord_t value);

        /** \fn void set_grid_cell_row_pos(lv_coord_t value)
         *  \brief Sets grid's active row index.
         *  \param value: row index (zero-based).
         */
        void set_grid_cell_row_pos(lv_coord_t value);

        /** \fn void set_grid_cell_row_span(lv_coord_t value)
         *  \brief Sets grid's active row span.
         *  \param value: row span (1 or more).
         */
        void set_grid_cell_row_span(lv_coord_t value);

        /** \fn void set_grid_cell_x_align(lv_coord_t value)
         *  \brief Sets grid's active cell horizontal offset.
         *  \param value: horizontal offset value.
         */
        void set_grid_cell_x_align(lv_coord_t value);

        /** \fn void set_grid_cell_y_align(lv_coord_t value)
         *  \brief Sets grid's active cell vertical offset.
         *  \param value: vertical offset value.
         */
        void set_grid_cell_y_align(lv_coord_t value);
#endif // LV_USE_GRID
    };

}
