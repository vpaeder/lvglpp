/** \file object.h
 *  \brief Header file for C++ wrapper for lv_obj_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../misc/style.h"
#include "../misc/area.h"
#include "../draw/desc.h"
#include "../lv_thin_wrapper.h"

namespace lvgl::core {
    
    using namespace lvgl::misc;
    using namespace lvgl::draw;
    
    /** \class Object
     *  \brief Wraps a lv_obj_t object. This is the generic LVGL object type.
     */
    class Object : public ThinPointerWrapper<lv_obj_t, lv_obj_del> {
    protected:
        /** \fn void initialize()
         *  \brief Initialize object.
         */
        virtual void initialize() {};
        /** \fn void initialize(Object & parent)
         *  \brief Initialize object and assign parent object.
         *  \param parent: parent LVGL object.
         */
        virtual void initialize(Object & parent) {};

    public:
        using ThinPointerWrapper::ThinPointerWrapper;

        /** \fn ~Object()
         *  \brief Destructor.
         */
        ~Object();

        /** \fn void add_flag(lv_obj_flag_t f)
         *  \brief Sets given flag.
         *  \param f: OR-ed combination of lv_obj_flag_t values.
         */
        void add_flag(lv_obj_flag_t f);

        /** \fn void clear_flag(lv_obj_flag_t f)
         *  \brief Clears given flag.
         *  \param f: OR-ed combination of lv_obj_flag_t values.
         */
        void clear_flag(lv_obj_flag_t f);

        /** \fn bool has_flag(lv_obj_flag_t f) const
         *  \brief Tells if object has every given flags set.
         *  \param f: OR-ed combination of lv_obj_flag_t values.
         *  \returns true if all flags are set, false otherwise.
         */
        bool has_flag(lv_obj_flag_t f) const;

        /** \fn bool has_flag_any(lv_obj_flag_t f) const
         *  \brief Tells if object has any of the given flags set.
         *  \param f: OR-ed combination of lv_obj_flag_t values.
         *  \returns true if any of the given flags is set, false otherwise.
         */
        bool has_flag_any(lv_obj_flag_t f) const;

        /** \fn void add_state(lv_state_t state)
         *  \brief Adds one or more object states.
         *  \param state: OR-ed combination of lv_state_t values.
         */
        void add_state(lv_state_t state);

        /** \fn void clear_state(lv_state_t state)
         *  \brief Removes one or more object states.
         *  \param state: OR-ed combination of lv_state_t values.
         */
        void clear_state(lv_state_t state);

        /** \fn lv_state_t get_state() const
         *  \brief Gets object state.
         *  \returns OR-ed combination of lv_state_t values.
         */
        lv_state_t get_state() const;

        /** \fn bool has_state(lv_state_t state) const
         *  \brief Tells if object has given state.
         *  \param state: OR-ed combination of lv_state_t values.
         *  \returns true if object has states, false otherwise.
         */
        bool has_state(lv_state_t state) const;

        #if LV_USE_USER_DATA
        /** \fn template<class T> void set_user_data(const T & arg)
         *  \brief Sets user data.
         *  \tparam T: class of user data object.
         *  \param arg: user data.
         */
        template<class T> void set_user_data(const T & arg);
        /** \fn void set_user_data(const void * arg)
         *  \brief Sets user data.
         *  \param arg: user data.
         */
        void set_user_data(const void * arg);

        /** \fn void * get_user_data() const
         *  \brief Gets user data.
         *  \returns a pointer to user data.
         */
        void * get_user_data() const;
        #endif // LV_USE_USER_DATA

        /** \fn std::shared_ptr<lv_group_t> get_group() const
         *  \brief Gets object group.
         *  \returns a pointer to the object group instance.
         */
        std::shared_ptr<lv_group_t> get_group() const;

        /** \fn void remove_from_group()
         *  \brief Removes object from its group.
         */
        void remove_from_group();

        /** \fn void focus()
         *  \brief Focuses object.
         */
        void focus();

        /** \fn void allocate_spec_attr()
         *  \brief Allocates special attributes if not allocated yet.
         */
        void allocate_spec_attr();

        /** \fn bool check_type(const lv_obj_class_t & cls) const
         *  \brief Checks if object is of given type.
         *  \param cls: LVGL object class.
         *  \returns true if object is of given type, false otherwise.
         */
        bool check_type(const lv_obj_class_t & cls) const;

        /** \fn bool has_class(const lv_obj_class_t & cls) const
         *  \brief Checks if object is of given type or any of the type's parent types.
         *  \param cls: LVGL object class.
         *  \returns true if object is of given type or any of the type's parent types, false otherwise.
         */
        bool has_class(const lv_obj_class_t & cls) const;

        /** \fn const std::shared_ptr<const lv_obj_class_t> get_class() const
         *  \brief Gets object class.
         *  \returns LVGL class of object.
         */
        const std::shared_ptr<const lv_obj_class_t> get_class() const;

        /** \fn bool is_valid() const
         *  \brief Checks if object is valid (=not destroyed).
         *  \returns true if object is valid, false otherwise.
         */
        bool is_valid() const;

        /** \fn lv_coord_t dpx(lv_coord_t n) const
         *  \brief Scales the given number of pixels relative to a 160dpi display.
         *  \returns the scaled pixel size, as n*current_dpi/160.
         */
        lv_coord_t dpx(lv_coord_t n) const;

        /** \fn bool is_editable() const
         *  \brief Checks if object is editable.
         *  \returns true if object is editable, false otherwise.
         */
        bool is_editable() const;

        /** \fn bool is_group_def() const
         *  \brief Checks if object is in default group.
         *  \returns true if object is in default group, false otherwise.
         */
        bool is_group_def() const;

        /** \fn void init_draw_rect_dsc(uint32_t part, RectangleDrawDescriptor & draw_dsc)
         *  \brief Initializes a rectangle draw descriptor from the current object's styles.
         *  \param part: object part, e.g. LV_PART_MAIN, LV_PART_KNOB, ...
         *  \param draw_dsc: rectangle draw descriptor to initialize.
         */
        void init_draw_rect_dsc(uint32_t part, RectangleDrawDescriptor & draw_dsc);
        /** \fn void init_draw_label_dsc(uint32_t part, LabelDrawDescriptor & draw_dsc)
         *  \brief Initializes a label draw descriptor from the current object's styles.
         *  \param part: object part, e.g. LV_PART_MAIN, LV_PART_KNOB, ...
         *  \param draw_dsc: label draw descriptor to initialize.
         */
        void init_draw_label_dsc(uint32_t part, LabelDrawDescriptor & draw_dsc);
        /** \fn void init_draw_img_dsc(uint32_t part, ImageDrawDescriptor & draw_dsc)
         *  \brief Initializes an image draw descriptor from the current object's styles.
         *  \param part: object part, e.g. LV_PART_MAIN, LV_PART_KNOB, ...
         *  \param draw_dsc: image draw descriptor to initialize.
         */
        void init_draw_img_dsc(uint32_t part, ImageDrawDescriptor & draw_dsc);
        /** \fn void init_draw_line_dsc(uint32_t part, LineDrawDescriptor & draw_dsc)
         *  \brief Initializes a line draw descriptor from the current object's styles.
         *  \param part: object part, e.g. LV_PART_MAIN, LV_PART_KNOB, ...
         *  \param draw_dsc: line draw descriptor to initialize.
         */
        void init_draw_line_dsc(uint32_t part, LineDrawDescriptor & draw_dsc);
        /** \fn void init_draw_arc_dsc(uint32_t part, ArcDrawDescriptor & draw_dsc)
         *  \brief Initializes an arc draw descriptor from the current object's styles.
         *  \param part: object part, e.g. LV_PART_MAIN, LV_PART_KNOB, ...
         *  \param draw_dsc: arc draw descriptor to initialize.
         */
        void init_draw_arc_dsc(uint32_t part, ArcDrawDescriptor & draw_dsc);

        /** \fn lv_coord_t calculate_ext_draw_size(uint32_t part) const
         *  \brief Calculates the extra size needed to draw borders, shadows, etc.
         *  \param part: object part, e.g. LV_PART_MAIN, LV_PART_KNOB, ...
         *  \returns extra size, in pixels.
         */
        lv_coord_t calculate_ext_draw_size(uint32_t part) const;

        /** \fn void refresh_ext_draw_size()
         *  \brief Issues a refresh request to recalculate the extra draw size.
         */
        void refresh_ext_draw_size();

        /** \fn lv_coord_t get_ext_draw_size() const
         *  \brief Gets the extra draw size.
         *  \returns the amount of pixels needed to draw borders, shadows, etc.
         */
        lv_coord_t get_ext_draw_size() const;

        // Events
        /** \fn void add_event_callback(lv_event_cb_t event_cb, lv_event_code_t filter)
         *  \brief Adds an event callback associated with the given event codes.
         *  \param event_cb: pointer to an event callback function.
         *  \param filter: an OR-ed combination of lv_event_code_t values.
         */
        void add_event_callback(lv_event_cb_t event_cb, lv_event_code_t filter);
        /** \fn template <class T> void add_event_callback(lv_event_cb_t event_cb,
         *                                                 lv_event_code_t filter,
         *                                                 const T & user_data);
         *  \brief Adds an event callback associated with the given event codes, with user data.
         *  \tparam T: class of user data.
         *  \param event_cb: pointer to an event callback function.
         *  \param filter: an OR-ed combination of lv_event_code_t values.
         *  \param user_data: custom user data.
         */
        template <class T> void add_event_callback(lv_event_cb_t event_cb, lv_event_code_t filter,
                                                   const T & user_data);

        /** \fn void add_event_callback(lv_event_cb_t event_cb, lv_event_code_t filter,
         *                              void * user_data)
         *  \brief Adds an event callback associated with the given event codes, with user data.
         *  \param event_cb: pointer to an event callback function.
         *  \param filter: an OR-ed combination of lv_event_code_t values.
         *  \param user_data: custom user data.
         */
        void add_event_callback(lv_event_cb_t event_cb, lv_event_code_t filter, void * user_data);

        /** \fn bool remove_event_callback(lv_event_cb_t event_cb)
         *  \brief Removes an event callback.
         *  \param event_cb: pointer to an event callback function.
         *  \returns true if the event callback could be removed, false otherwise.
         */
        bool remove_event_callback(lv_event_cb_t event_cb);

        /** \fn template <class T> bool remove_event_callback(lv_event_cb_t event_cb, const T & user_data)
         *  \brief Removes an event callback with user data.
         *  \tparam T: class of user data.
         *  \param event_cb: pointer to an event callback function.
         *  \param user_data: custom user data.
         *  \returns true if the event callback could be removed, false otherwise.
         */
        template <class T> bool remove_event_callback(lv_event_cb_t event_cb, const T & user_data);

        /** \fn bool remove_event_callback(lv_event_cb_t event_cb, const void * user_data)
         *  \brief Removes an event callback with user data.
         *  \param event_cb: pointer to an event callback function.
         *  \param user_data: custom user data.
         *  \returns true if the event callback could be removed, false otherwise.
         */
        bool remove_event_callback(lv_event_cb_t event_cb, const void * user_data);

        /** \fn template <class T> lv_res_t send_event(lv_event_code_t event_code, const T & param)
         *  \brief Sends an event to the object.
         *  \tparam T: class of user data object.
         *  \param event_code: event code.
         *  \param param: event parameter.
         *  \returns LV_RES_INV if object was deleted, LV_RES_OK otherwise.
         */
        template <class T> lv_res_t send_event(lv_event_code_t event_code, const T & param);
        /** \fn lv_res_t send_event(lv_event_code_t event_code, void * param)
         *  \brief Sends an event to the object.
         *  \param event_code: event code.
         *  \param param: event parameter.
         *  \returns LV_RES_INV if object was deleted, LV_RES_OK otherwise.
         */
        lv_res_t send_event(lv_event_code_t event_code, void * param);

        /** \fn template <class T> T get_event_user_data(lv_event_cb_t event_cb)
         *  \brief Gets user data associated with event callback.
         *  \tparam T: user data class.
         *  \param event_cb: event callback function.
         *  \returns user data associated with callback function.
         */
        template <class T> T get_event_user_data(lv_event_cb_t event_cb);

        /** \brief Gets user data associated with event callback.
         *  \param event_cb: event callback function.
         *  \returns pointer to user data associated with callback function.
         */
        void * get_event_user_data(lv_event_cb_t event_cb);

        /** \fn void set_pos(lv_coord_t x, lv_coord_t y)
         *  \brief Sets object position.
         *  \param x: horizontal position.
         *  \param y: vertical position.
         */
        void set_pos(lv_coord_t x, lv_coord_t y);

        /** \fn void set_x(lv_coord_t x)
         *  \brief Sets object horizontal position.
         *  \param x: horizontal position.
         */
        void set_x(lv_coord_t x);

        /** \fn void set_y(lv_coord_t y)
         *  \brief Sets object vertical position.
         *  \param y: vertical position.
         */
        void set_y(lv_coord_t y);

        /** \fn void set_size(lv_coord_t w, lv_coord_t h)
         *  \brief Sets object size.
         *  \param w: object width.
         *  \param h: object height.
         */
        void set_size(lv_coord_t w, lv_coord_t h);

        /** \fn bool refresh_size()
         *  \brief Recalculates the size of the object.
         *  \returns true if the size could be recalculated, false otherwise.
         */
        bool refresh_size();

        /** \fn void set_width(lv_coord_t w)
         *  \brief Sets object width.
         *  \param w: object width.
         */
        void set_width(lv_coord_t w);

        /** \fn void set_height(lv_coord_t h)
         *  \brief Sets object height.
         *  \param h: object height.
         */
        void set_height(lv_coord_t h);

        /** \fn void set_content_width(lv_coord_t w)
         *  \brief Sets the width of the object's content (width - padding - border).
         *  \param w: content width.
         */
        void set_content_width(lv_coord_t w);

        /** \fn void set_content_height(lv_coord_t h)
         *  \brief Sets the height of the object's content (height - padding - border).
         *  \param h: content height.
         */
        void set_content_height(lv_coord_t h);

        /** \fn void set_layout(uint32_t layout)
         *  \brief Sets the layout for the object.
         *  \param layout: ID of layout to set.
         */
        void set_layout(uint32_t layout);

        /** \fn bool is_layout_positioned()
         *  \brief Tells if object is positioned by a layout.
         *  \returns true if the object is positioned by a layout, false otherwise.
         */
        bool is_layout_positioned();

        /** \fn void mark_layout_as_dirty()
         *  \brief Marks the object for layout update.
         */
        void mark_layout_as_dirty();

        /** \fn void update_layout()
         *  \brief Updates the layout of the object.
         */
        void update_layout();
        
        /** \fn void set_align(lv_align_t align)
         *  \brief Sets the alignment of the object.
         *  \param align: type of alignment (see lv_align_t enum).
         */
        void set_align(lv_align_t align);

        /** \fn void align(lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs)
         *  \brief Aligns the object within its parent, given the alignment parameters.
         *  \param align: type of alignment (see lv_align_t enum).
         *  \param x_ofs: horizontal offset.
         *  \param y_ofs: vertical offset.
         */
        void align(lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs);

        /** \fn void align_to(const Object & other, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs)
         *  \brief Aligns the object relative to another object, given the alignment parameters.
         *  \param other: reference object.
         *  \param align: type of alignment (see lv_align_t enum).
         *  \param x_ofs: horizontal offset.
         *  \param y_ofs: vertical offset.
         */
        void align_to(const Object & other, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs);

        /** \fn void center()
         *  \brief Centers the object on its parent.
         */
        void center();

        /** \fn Area get_coords() const
         *  \brief Gets object coordinates.
         *  \returns object coordinates.
         */
        Area get_coords() const;

        /** \fn lv_coord_t get_x() const
         *  \brief Gets the object horizontal position.
         *  \returns object's horizontal position.
         */
        lv_coord_t get_x() const;

        /** \fn lv_coord_t get_x2() const
         *  \brief Gets the horizontal position of the object's right side.
         *  \returns horizontal position of object's right side.
         */
        lv_coord_t get_x2() const;

        /** \fn lv_coord_t get_y() const
         *  \brief Gets the object vertical position.
         *  \returns object's vertical position.
         */
        lv_coord_t get_y() const;

        /** \fn lv_coord_t get_y2() const
         *  \brief Gets the vertical position of the object's bottom side.
         *  \returns vertical position of object's bottom side.
         */
        lv_coord_t get_y2() const;

        /** \fn lv_coord_t get_x_aligned() const
         *  \brief Gets the object's horizontal offset.
         *  \returns object's horizontal offset.
         */
        lv_coord_t get_x_aligned() const;

        /** \fn lv_coord_t get_y_aligned() const
         *  \brief Gets the object's vertical offset.
         *  \returns object's vertical offset.
         */
        lv_coord_t get_y_aligned() const;

        /** \fn lv_coord_t get_width() const
         *  \brief Gets the object width.
         *  \returns object width.
         */
        lv_coord_t get_width() const;

        /** \fn lv_coord_t get_height() const
         *  \brief Gets the object height.
         *  \returns object height.
         */
        lv_coord_t get_height() const;

        /** \fn lv_coord_t get_content_width() const
         *  \brief Gets the object's content width.
         *  \returns object's content width.
         */
        lv_coord_t get_content_width() const;

        /** \fn lv_coord_t get_content_height() const
         *  \brief Gets the object's content height.
         *  \returns object's content height.
         */
        lv_coord_t get_content_height() const;

        /** \fn Area get_content_coords() const
         *  \brief Gets the object's content coordinates.
         *  \returns object's content coordinates.
         */
        Area get_content_coords() const;

        /** \fn lv_coord_t get_self_width() const
         *  \brief Gets the virtual width of all the parts of the object.
         *  \returns width of all the parts of the object.
         */
        lv_coord_t get_self_width() const;

        /** \fn lv_coord_t get_self_height() const
         *  \brief Gets the virtual height of all the parts of the object.
         *  \returns height of all the parts of the object.
         */
        lv_coord_t get_self_height() const;

        /** \fn bool refresh_self_size()
         *  \brief Recalculates the size of all the parts of the object.
         *  \returns true if size was recalculated, false otherwise.
         */
        bool refresh_self_size();

        /** \fn void refresh_pos()
         *  \brief Recalculates the position of the object.
         */
        void refresh_pos();

        /** \fn void move_to(lv_coord_t x, lv_coord_t y)
         *  \brief Moves object to given position.
         *  \param x: horizontal position.
         *  \param y: vertical position.
         */
        void move_to(lv_coord_t x, lv_coord_t y);

        /** \fn void move_children_by(lv_coord_t x_diff, lv_coord_t y_diff, bool ignore_floating)
         *  \brief Moves object's children by given amount.
         *  \param x_diff: horizontal offset.
         *  \param y_diff: vertical offset.
         *  \param ignore_floating: if true, ignores floating children.
         */
        void move_children_by(lv_coord_t x_diff, lv_coord_t y_diff, bool ignore_floating);

        /** \fn void invalidate_area(const Area & area)
         *  \brief Marks given area to be redrawn.
         *  \param area: area to mark.
         */
        void invalidate_area(const Area & area);

        /** \fn void invalidate()
         *  \brief Marks object to be redrawn.
         */
        void invalidate();

        /** \fn bool area_is_visible(Area & area) const
         *  \brief Checks if object's area is visible.
         *  \param area: area to check.
         *  \returns true if area is visible, false otherwise.
         */
        bool area_is_visible(Area & area) const;

        /** \fn bool is_visible() const
         *  \brief Checks if object is visible.
         *  \returns true if object is visible, false otherwise.
         */
        bool is_visible() const;

        /** \fn void set_ext_click_area(lv_coord_t size)
         *  \brief Sets the size of the object's extended clickable area.
         *  \param size: extended clickable area in all four directions.
         */
        void set_ext_click_area(lv_coord_t size);

        /** \fn Area get_click_area() const
         *  \brief Gets the object's clickable area.
         *  \returns object's clickable area.
         */
        Area get_click_area() const;

        /** \fn bool hit_test(const lv_point_t & point) const
         *  \brief Tells if a click on the given point would trigger an object's event.
         *  \returns true if a click on the point triggers an event, false otherwise.
         */
        bool hit_test(const lv_point_t & point) const;

        /* style */
        /** \fn void add_style(const Style & style, lv_style_selector_t selector)
         *  \brief Adds a style to the object.
         *  \param style: style to add.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void add_style(const Style & style, lv_style_selector_t selector);

        /** \fn void remove_style(const Style & style, lv_style_selector_t selector)
         *  \brief Removes a style from the object.
         *  \param style: style to remove.
         *  \param selector: OR-ed combination of parts and states to remove the style from.
         */
        void remove_style(const Style & style, lv_style_selector_t selector);

        /** \fn void remove_style_all()
         *  \brief Clears all styles from the object.
         */
        void remove_style_all();

        /** \fn void refresh_style(lv_part_t part, lv_style_prop_t prop)
         *  \brief Refreshes style properties on some parts.
         *  \param part: OR-ed combination of object parts.
         *  \param prop: OR-ed combination of style properties.
         */
        void refresh_style(lv_part_t part, lv_style_prop_t prop);

        /** \fn lv_style_value_t get_style_prop(lv_part_t part, lv_style_prop_t prop) const
         *  \brief Gets the value of a style property.
         *  \param part: object part.
         *  \param prop: style property.
         *  \returns the value of the style property.
         */
        lv_style_value_t get_style_prop(lv_part_t part, lv_style_prop_t prop) const;

        /** \fn void set_local_style_prop(lv_style_prop_t prop, lv_style_value_t value, lv_style_selector_t selector)
         *  \brief Sets the value of a local style property.
         *  \param prop: style property.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_local_style_prop(lv_style_prop_t prop, lv_style_value_t value, lv_style_selector_t selector);

        /** \fn lv_style_value_t get_local_style_prop(lv_style_prop_t prop, lv_style_selector_t selector) const
         *  \brief Gets the value of a local style property.
         *  \param prop: style property.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         *  \returns the value of the style property.
         */
        lv_style_value_t get_local_style_prop(lv_style_prop_t prop, lv_style_selector_t selector) const;

        /** \fn bool remove_local_style_prop(lv_style_prop_t prop, lv_style_selector_t selector)
         *  \brief Removes a local style property.
         *  \param prop: style property.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         *  \returns true if property could be removed, false otherwise.
         */
        bool remove_local_style_prop(lv_style_prop_t prop, lv_style_selector_t selector);

        /* animation */
        /** \fn void fade_in(uint32_t time, uint32_t delay)
         *  \brief Fades in the object.
         *  \param time: duration of fade-in effect.
         *  \param delay: delay before fade-in effect.
         */
        void fade_in(uint32_t time, uint32_t delay);

        /** \fn void fade_out(uint32_t time, uint32_t delay)
         *  \brief Fades out the object.
         *  \param time: duration of fade-out effect.
         *  \param delay: delay before fade-out effect.
         */
        void fade_out(uint32_t time, uint32_t delay);

        /** \fn void set_scrollbar_mode(lv_scrollbar_mode_t mode)
         *  \brief Sets how the scrollbars behave.
         *  \param mode: code for scrollbar mode (LV_SCROLL_MODE_ON/OFF/AUTO/ACTIVE).
         */
        void set_scrollbar_mode(lv_scrollbar_mode_t mode);

        /** \fn void set_scroll_dir(lv_dir_t dir)
         *  \brief Sets allowed scroll directions.
         *  \param dir: an OR-ed combination of lv_dir_t values.
         */
        void set_scroll_dir(lv_dir_t dir);

        /** \fn void set_scroll_snap_x(lv_scroll_snap_t align)
         *  \brief Sets on what to align object's children when horizontal scrolling stops.
         *  \param align: snap align code.
         */
        void set_scroll_snap_x(lv_scroll_snap_t align);

        /** \fn void set_scroll_snap_y(lv_scroll_snap_t align)
         *  \brief Sets on what to align object's children when vertical scrolling stops.
         *  \param align: snap align code.
         */
        void set_scroll_snap_y(lv_scroll_snap_t align);

        /** \fn lv_scrollbar_mode_t get_scrollbar_mode() const
         *  \brief Gets how the scrollbars behave.
         *  \returns scrollbar behaviour code.
         */
        lv_scrollbar_mode_t get_scrollbar_mode() const;

        /** \fn lv_dir_t get_scroll_dir() const
         *  \brief Gets allowed scroll directions.
         *  \returns an OR-ed combination of lv_dir_t values.
         */
        lv_dir_t get_scroll_dir() const;

        /** \fn lv_scroll_snap_t get_scroll_snap_x() const
         *  \brief Gets on what object's children align when horizontal scrolling stops.
         *  \returns the snap align code.
         */
        lv_scroll_snap_t get_scroll_snap_x() const;

        /** \fn lv_scroll_snap_t get_scroll_snap_y() const
         *  \brief Gets on what object's children align when vertical scrolling stops.
         *  \returns the snap align code.
         */
        lv_scroll_snap_t get_scroll_snap_y() const;

        /** \fn lv_coord_t get_scroll_x() const
         *  \brief Gets the horizontal scroll position.
         *  \returns horizontal scroll position.
         */
        lv_coord_t get_scroll_x() const;

        /** \fn lv_coord_t get_scroll_y() const
         *  \brief Gets the vertical scroll position.
         *  \returns vertical scroll position.
         */
        lv_coord_t get_scroll_y() const;

        /** \fn lv_coord_t get_scroll_top() const
         *  \brief Gets the scroll distance to the content's top.
         *  \returns distance to the content's top.
         */
        lv_coord_t get_scroll_top() const;

        /** \fn lv_coord_t get_scroll_bottom() const
         *  \brief Gets the scroll distance to the content's bottom.
         *  \returns distance to the content's bottom.
         */
        lv_coord_t get_scroll_bottom() const;

        /** \fn lv_coord_t get_scroll_left() const
         *  \brief Gets the scroll distance to the content's left edge.
         *  \returns distance to the content's left edge.
         */
        lv_coord_t get_scroll_left() const;

        /** \fn lv_coord_t get_scroll_right() const
         *  \brief Gets the scroll distance to the content's right edge.
         *  \returns distance to the content's right edge.
         */
        lv_coord_t get_scroll_right() const;

        /** \fn lv_point_t get_scroll_end() const
         *  \brief Gets the point where an ongoing scrolling animation will stop.
         *  If no animation is ongoing, returns current scroll position.
         *  \returns scrolling end point or current scrolling position.
         */
        lv_point_t get_scroll_end() const;

        /** \fn void scroll_by(lv_coord_t dx, lv_coord_t dy, lv_anim_enable_t anim_en)
         *  \brief Scrolls content by given amount.
         *  \param dx: horizontal displacement.
         *  \param dy: vertical displacement.
         *  \param anim_en: defines if scrolling is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void scroll_by(lv_coord_t dx, lv_coord_t dy, lv_anim_enable_t anim_en);

        /** \fn void scroll_by_bounded(lv_coord_t dx, lv_coord_t dy, lv_anim_enable_t anim_en)
         *  \brief Scrolls content by given amount.
         *  This version limits scrolling to available content.
         *  \param dx: horizontal displacement.
         *  \param dy: vertical displacement.
         *  \param anim_en: defines if scrolling is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void scroll_by_bounded(lv_coord_t dx, lv_coord_t dy, lv_anim_enable_t anim_en);

        /** \fn void scroll_to(lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en)
         *  \brief Scrolls content to given point.
         *  \param x: horizontal coordinate.
         *  \param y: vertical coordinate.
         *  \param anim_en: defines if scrolling is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void scroll_to(lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim_en);

        /** \fn void scroll_to_x(lv_coord_t x, lv_anim_enable_t anim_en)
         *  \brief Scrolls content to given horizontal point.
         *  \param x: horizontal coordinate.
         *  \param anim_en: defines if scrolling is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void scroll_to_x(lv_coord_t x, lv_anim_enable_t anim_en);

        /** \fn void scroll_to_y(lv_coord_t y, lv_anim_enable_t anim_en)
         *  \brief Scrolls content to given horizontal point.
         *  \param y: vertical coordinate.
         *  \param anim_en: defines if scrolling is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void scroll_to_y(lv_coord_t y, lv_anim_enable_t anim_en);

        /** \fn void scroll_to_view(lv_anim_enable_t anim_en)
         *  \brief Scrolls view until object is visible.
         *  \param anim_en: defines if scrolling is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void scroll_to_view(lv_anim_enable_t anim_en);

        /** \fn void scroll_to_view_recursive(lv_anim_enable_t anim_en)
         *  \brief Scrolls view until object and its parents are visible.
         *  \param anim_en: defines if scrolling is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void scroll_to_view_recursive(lv_anim_enable_t anim_en);

        /** \fn bool is_scrolling() const
         *  \brief Tells if object is currently scrolling.
         *  \returns true if object is scrolling, false otherwise.
         */
        bool is_scrolling() const;

        /** \fn void update_snap(lv_anim_enable_t anim_en)
         *  \brief Updates object's children to fulfill snap settings.
         *  \param anim_en: defines if scrolling is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void update_snap(lv_anim_enable_t anim_en);

        /** \fn Area get_scrollbar_area() const
         *  \brief Gets scrollable area.
         *  \returns area spanned by horizontal and vertical scrollbars.
         */
        Area get_scrollbar_area() const;

        /** \fn void scrollbar_invalidate()
         *  \brief Marks the scrollbar area for redraw.
         */
        void scrollbar_invalidate();

        /** \fn void readjust_scroll(lv_anim_enable_t anim_en)
         *  \brief Checks and readjusts content scroll position.
         *  \param anim_en: defines if scrolling is animated (LV_ANIM_ON) or immediate (LV_ANIM_OFF).
         */
        void readjust_scroll(lv_anim_enable_t anim_en);

        /** \fn void set_parent(const Object & parent)
         *  \brief Sets the object's parent.
         *  \param parent: object to set as parent.
         */
        void set_parent(const Object & parent);
        
        /** \fn void swap(Object & other);
         *  \brief Swap object position with given object.
         *  \param other: object to swap position with.
         */
        void swap(Object & other);

        /** \fn void move_to_index(int32_t index)
         *  \brief Moves the object to the given index within its parent's children.
         *  \param index: index to move object to.
         */
        void move_to_index(int32_t index);

        /** \fn Object get_screen() const
         *  \brief Gets the screen on which the object is displayed.
         *  \returns an object representing the screen.
         */
        Object get_screen() const;

        /** \fn Object get_parent() const
         *  \brief Gets the object's parent.
         *  \returns an object representing the object's parent.
         */
        Object get_parent() const;

        /** \fn Object get_child(int32_t id) const
         *  \brief Gets the child object at given index.
         *  \param id: child object's index.
         *  \returns an object representing the a child object.
         */
        Object get_child(int32_t id) const;

        /** \fn template<class T> void tree_walk(lv_obj_tree_walk_cb_t cb, T & user_data) const
         *  \brief Performs a tree walk starting from current object.
         *  \tparam T: user data type.
         *  \param cb: callback function called for each object in the tree.
         *  \param user_data: a custom user data passed to callback.
         */
        template<class T> void tree_walk(lv_obj_tree_walk_cb_t cb, T & user_data) const;
        /** \fn void tree_walk(lv_obj_tree_walk_cb_t cb, void * user_data) const
         *  \brief Performs a tree walk starting from current object.
         *  \param cb: callback function called for each object in the tree.
         *  \param user_data: a custom user data passed to callback.
         */
        void tree_walk(lv_obj_tree_walk_cb_t cb, void * user_data) const;
        /** \fn void tree_walk(lv_obj_tree_walk_cb_t cb) const
         *  \brief Performs a tree walk starting from current object.
         *  \param cb: callback function called for each object in the tree.
         */
        void tree_walk(lv_obj_tree_walk_cb_t cb) const;
    };

}
