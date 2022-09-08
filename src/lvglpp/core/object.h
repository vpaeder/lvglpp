/** \file object.h
 *  \brief Header file for C++ wrapper for lv_obj_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../lv_wrapper.h"

namespace lvgl::misc {
    class Animation;
    class StyleTransition;
    class Style;
    class Area;
    class ColorFilter;
}

namespace lvgl::draw {
    class RectangleDrawDescriptor;
    class LabelDrawDescriptor;
    class ImageDrawDescriptor;
    class LineDrawDescriptor;
    class ArcDrawDescriptor;
    class ImageDescriptor;
}

namespace lvgl::font {
    class Font;
}

namespace lvgl::core {
    
    using namespace lvgl::misc;
    using namespace lvgl::draw;
    using namespace lvgl::font;
    
    class Event;
    class Theme;
    class Group;
    
    /** \class Object
     *  \brief Wraps a lv_obj_t object. This is the generic LVGL object type.
     */
    class Object : public PointerWrapper<lv_obj_t, lv_obj_del> {
    private:
        /** \typedef EventCb
         *  \brief Type for event callback function.
         */
        using EventCb = void(*)(Event & e);

    public:
        using PointerWrapper::PointerWrapper;

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
        template<class T> void set_user_data(const T & arg) {
            lv_obj_set_user_data(this->raw_ptr(), static_cast<void*>(&arg));
        }
        /** \fn void set_user_data(const void * arg)
         *  \brief Sets user data.
         *  \param arg: user data.
         */
        void set_user_data(const void * arg);

        /** \fn template <class T> T & get_user_data() const
         *  \brief Gets user data.
         *  \returns user data.
         */
        template <class T> T & get_user_data() const {
            return *reinterpret_cast<T*>(lv_obj_get_user_data(this->raw_ptr()));
        }
        /** \fn void * get_user_data() const
         *  \brief Gets user data.
         *  \returns a pointer to user data.
         */
        void * get_user_data() const;
#endif // LV_USE_USER_DATA

        /** \fn Group get_group() const
         *  \brief Gets object group.
         *  \returns a pointer to the object group instance.
         */
        Group get_group() const;

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

        /** \fn const lv_obj_class_t * get_class() const
         *  \brief Gets object class.
         *  \returns LVGL class of object.
         */
        const lv_obj_class_t * get_class() const;

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
        /** \fn void add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter)
         *  \brief Adds an event callback associated with the given event codes.
         *  \param event_cb: pointer to an event callback function.
         *  \param filter: an OR-ed combination of lv_event_code_t values.
         */
        void add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter);

        /** \fn void add_event_cb(EventCb event_cb, lv_event_code_t filter)
         *  \brief Adds an event callback associated with the given event codes.
         *  \param event_cb: pointer to an event callback function.
         *  \param filter: an OR-ed combination of lv_event_code_t values.
         */
        void add_event_cb(EventCb event_cb, lv_event_code_t filter);

        /** \brief Adds an event callback associated with the given event codes, with user data.
         *  \tparam T: class of user data.
         *  \param event_cb: pointer to an event callback function.
         *  \param filter: an OR-ed combination of lv_event_code_t values.
         *  \param user_data: custom user data.
         */
        template <class T> void add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter,
                                             const T & user_data) {
            lv_obj_add_event_cb(this->raw_ptr(), event_cb, filter, static_cast<void*>(&user_data));
        }

        /** \fn void add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter,
         *                              void * user_data)
         *  \brief Adds an event callback associated with the given event codes, with user data.
         *  \param event_cb: pointer to an event callback function.
         *  \param filter: an OR-ed combination of lv_event_code_t values.
         *  \param user_data: custom user data.
         */
        void add_event_cb(lv_event_cb_t event_cb, lv_event_code_t filter, void * user_data);

        /** \fn bool remove_event_cb(lv_event_cb_t event_cb)
         *  \brief Removes an event callback.
         *  \param event_cb: pointer to an event callback function.
         *  \returns true if the event callback could be removed, false otherwise.
         */
        bool remove_event_cb(lv_event_cb_t event_cb);

        /** \fn template <class T> bool remove_event_cb(lv_event_cb_t event_cb, const T & user_data)
         *  \brief Removes an event callback with user data.
         *  \tparam T: class of user data.
         *  \param event_cb: pointer to an event callback function.
         *  \param user_data: custom user data.
         *  \returns true if the event callback could be removed, false otherwise.
         */
        template <class T> bool remove_event_cb(lv_event_cb_t event_cb, const T & user_data) {
            return lv_obj_remove_event_cb_with_user_data(this->raw_ptr(), event_cb, static_cast<void*>(&user_data));
        }

        /** \fn bool remove_event_cb(lv_event_cb_t event_cb, const void * user_data)
         *  \brief Removes an event callback with user data.
         *  \param event_cb: pointer to an event callback function.
         *  \param user_data: custom user data.
         *  \returns true if the event callback could be removed, false otherwise.
         */
        bool remove_event_cb(lv_event_cb_t event_cb, const void * user_data);

        /** \fn bool remove_event_cb(EventCb event_cb)
         *  \brief Removes an event callback.
         *  \param event_cb: pointer to an event callback function.
         *  \returns true if the event callback could be removed, false otherwise.
         */
        bool remove_event_cb(EventCb event_cb);

        /** \fn bool remove_event_cb()
         *  \brief Removes the first event callback in the callback list.
         *  \returns true if the event callback could be removed, false otherwise.
         */
        bool remove_event_cb();

        /** \fn template <class T> lv_res_t send_event(lv_event_code_t event_code, const T & param)
         *  \brief Sends an event to the object.
         *  \tparam T: class of user data object.
         *  \param event_code: event code.
         *  \param param: event parameter.
         *  \returns LV_RES_INV if object was deleted, LV_RES_OK otherwise.
         */
        template <class T> lv_res_t send_event(lv_event_code_t event_code, const T & param) {
            return lv_event_send(this->raw_ptr(), event_code, static_cast<void*>(&param));
        }
        /** \fn lv_res_t send_event(lv_event_code_t event_code, void * param)
         *  \brief Sends an event to the object.
         *  \param event_code: event code.
         *  \param param: event parameter.
         *  \returns LV_RES_INV if object was deleted, LV_RES_OK otherwise.
         */
        lv_res_t send_event(lv_event_code_t event_code, void * param);
        /** \fn lv_res_t send_event(lv_event_code_t event_code)
         *  \brief Sends an event to the object.
         *  \param event_code: event code.
         *  \returns LV_RES_INV if object was deleted, LV_RES_OK otherwise.
         */
        lv_res_t send_event(lv_event_code_t event_code);

        /** \fn template <class T> T get_event_user_data(lv_event_cb_t event_cb)
         *  \brief Gets user data associated with event callback.
         *  \tparam T: user data class.
         *  \param event_cb: event callback function.
         *  \returns user data associated with callback function.
         */
        template <class T> T get_event_user_data(lv_event_cb_t event_cb) {
            return reinterpret_cast<T>(*lv_obj_get_event_user_data(this->raw_ptr(), event_cb));
        }

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

        /** \brief Transform a point using the angle and zoom style properties of an object.
         *  \param p: point to transform (will be overwritten)
         *  \param recursive: if true, apply transforms of parent objects as well
         *  \param inv: if true, execute inverse transform (-angle and 1/zoom)
         */
        void transform_point(lv_point_t & p, bool recursive, bool inv);

        /** \brief Transform an area using the angle and zoom style properties of an object.
         *  \param area: area to transform (will be overwritten)
         *  \param recursive: if true, apply transforms of parent objects as well
         *  \param inv: if true, execute inverse transform (-angle and 1/zoom)
         */
        void get_transformed_area(Area & area, bool recursive, bool inv);

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

        /** \fn void remove_style(lv_style_selector_t selector)
         *  \brief Strips styles associated with given selector from the object.
         *  \param selector: OR-ed combination of parts and states to remove styles from.
         */
        void remove_style(lv_style_selector_t selector);

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

        /** \brief Sets the value of a local style meta state.
         *  \param prop: style property.
         *  \param meta: meta value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_local_style_prop_meta(lv_style_prop_t prop, uint16_t meta, lv_style_selector_t selector);

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
        template <class T> T get_parent() const {
            return T(lv_obj_get_parent(this->raw_ptr()), false);
        }

        /** \fn template <class T> T get_child(int32_t id) const
         *  \brief Gets the child object at given index.
         *  \param id: child object's index.
         *  \returns an object representing the a child object.
         */
        template <class T> T get_child(int32_t id) const {
            return T(lv_obj_get_child(this->raw_ptr(), id), false);
        }

        /** \fn uint32_t get_child_cnt() const
         *  \brief Gets number of children.
         *  \returns number of children.
         */
        uint32_t get_child_cnt() const;

        /** \fn uint32_t get_index() const
         *  \brief Gets object index within parent.
         *  \returns object index.
         */
        uint32_t get_index() const;

        /** \fn template<class T> void tree_walk(lv_obj_tree_walk_cb_t cb, T & user_data) const
         *  \brief Performs a tree walk starting from current object.
         *  \tparam T: user data type.
         *  \param cb: callback function called for each object in the tree.
         *  \param user_data: a custom user data passed to callback.
         */
        template<class T> void tree_walk(lv_obj_tree_walk_cb_t cb, T & user_data) const {
            lv_obj_tree_walk(const_cast<lv_cls_ptr>(this->raw_ptr()), cb, static_cast<void*>(&user_data));
        }
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

        /* styling */
        /** \fn void set_style_pad_all(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets padding on all sides.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_pad_all(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_pad_hor(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets padding on left and right sides.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_pad_hor(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_pad_ver(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets padding on top and bottom sides.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_pad_ver(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_pad_gap(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets padding in between rows and columns.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_pad_gap(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_pad_top(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets top padding.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_pad_top(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_pad_bottom(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets bottom padding.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_pad_bottom(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_pad_left(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets left padding.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_pad_left(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_pad_right(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets right padding.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_pad_right(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_pad_row(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets row padding.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_pad_row(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_pad_column(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets column padding.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_pad_column(lv_coord_t value, lv_style_selector_t selector);

        /** \brief Sets size.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_size(lv_coord_t value, lv_style_selector_t selector);

        /** \brief Sets width.
         *  \param width: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_width(lv_coord_t width, lv_style_selector_t selector);

        /** \fn void set_style_min_width(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets minimum width.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_min_width(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_max_width(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets maximum width.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_max_width(lv_coord_t value, lv_style_selector_t selector);

        /** \brief Sets height.
         *  \param height: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_height(lv_coord_t height, lv_style_selector_t selector);

        /** \fn void set_style_min_height(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets minimum height.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_min_height(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_max_height(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets maximum height.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_max_height(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_x(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets horizontal position.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_x(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_y(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets vertical position.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_y(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_align(lv_align_t value, lv_style_selector_t selector)
         *  \brief Sets alignment code.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_align(lv_align_t value, lv_style_selector_t selector);

        /** \fn void set_style_transform_width(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets width after transform.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_transform_width(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_transform_height(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets height after transform.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_transform_height(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_translate_x(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets horizontal translation.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_translate_x(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_translate_y(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets vertical translation.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_translate_y(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_transform_zoom(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets transform zoom factor.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_transform_zoom(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_transform_angle(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets transform angle.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_transform_angle(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_bg_color(lv_color_t value, lv_style_selector_t selector)
         *  \brief Sets background color.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_color(lv_color_t value, lv_style_selector_t selector);

        /** \fn void set_style_bg_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets background opacity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_bg_grad_color(lv_color_t value, lv_style_selector_t selector)
         *  \brief Sets background gradient second color.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_grad_color(lv_color_t value, lv_style_selector_t selector);

        /** \fn void set_style_bg_grad_dir(lv_grad_dir_t value, lv_style_selector_t selector)
         *  \brief Sets background gradient direction.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_grad_dir(lv_grad_dir_t value, lv_style_selector_t selector);

        /** \fn void set_style_bg_main_stop(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets relative position of background's gradient first stop.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_main_stop(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_bg_grad_stop(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets relative position of background's gradient second stop.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_grad_stop(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_bg_grad(const lv_grad_dsc_t * value, lv_style_selector_t selector)
         *  \brief Sets background gradient.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_grad(const lv_grad_dsc_t * value, lv_style_selector_t selector);

        /** \fn void set_style_bg_dither_mode(lv_dither_mode_t value, lv_style_selector_t selector)
         *  \brief Sets background dither mode.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_dither_mode(lv_dither_mode_t value, lv_style_selector_t selector);

        /** \fn void set_style_bg_img_src(const void * value, lv_style_selector_t selector)
         *  \brief Sets background image.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_img_src(const void * value, lv_style_selector_t selector);
        /** \fn void set_style_bg_img_src(const ImageDescriptor & value, lv_style_selector_t selector)
         *  \brief Sets background image.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_img_src(const ImageDescriptor & value, lv_style_selector_t selector);
        /** \fn void set_style_bg_img_src(const std::string & value, lv_style_selector_t selector)
         *  \brief Sets background image path.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_img_src(const std::string & value, lv_style_selector_t selector);

        /** \fn void set_style_bg_img_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets background image opacity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_img_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_bg_img_recolor(lv_color_t value, lv_style_selector_t selector)
         *  \brief Sets background image recoloring color.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_img_recolor(lv_color_t value, lv_style_selector_t selector);

        /** \fn void set_style_bg_img_recolor_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets background image recoloring intensity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_img_recolor_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_bg_img_tiled(bool value, lv_style_selector_t selector)
         *  \brief Enables/disables background image tiling.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_bg_img_tiled(bool value, lv_style_selector_t selector);

        /** \fn void set_style_border_color(lv_color_t value, lv_style_selector_t selector)
         *  \brief Sets border color.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_border_color(lv_color_t value, lv_style_selector_t selector);

        /** \fn void set_style_border_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets border opacity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_border_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_border_width(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets border width.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_border_width(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_border_side(lv_border_side_t value, lv_style_selector_t selector)
         *  \brief Sets on which side border gets drawn.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_border_side(lv_border_side_t value, lv_style_selector_t selector);

        /** \fn void set_style_border_post(bool value, lv_style_selector_t selector)
         *  \brief Sets border rendering order. If true, renders after everything else.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_border_post(bool value, lv_style_selector_t selector);

        /** \fn void set_style_outline_width(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets outline width.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_outline_width(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_outline_color(lv_color_t value, lv_style_selector_t selector)
         *  \brief Sets outline color.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_outline_color(lv_color_t value, lv_style_selector_t selector);

        /** \fn void set_style_outline_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets outline opacity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_outline_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_outline_pad(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets outline padding.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_outline_pad(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_shadow_width(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets shadow width.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_shadow_width(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_shadow_ofs_x(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets shadow horizontal offset.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_shadow_ofs_x(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_shadow_ofs_y(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets shadow vertical offset.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_shadow_ofs_y(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_shadow_spread(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets shadow spread.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_shadow_spread(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_shadow_color(lv_color_t value, lv_style_selector_t selector)
         *  \brief Sets shadow color.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_shadow_color(lv_color_t value, lv_style_selector_t selector);

        /** \fn void set_style_shadow_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets shadow opacity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_shadow_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_img_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets image opacity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_img_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_img_recolor(lv_color_t value, lv_style_selector_t selector)
         *  \brief Sets image recoloring color.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_img_recolor(lv_color_t value, lv_style_selector_t selector);

        /** \fn void set_style_img_recolor_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets image recoloring intensity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_img_recolor_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_line_width(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets line width.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_line_width(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_line_dash_width(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets line dash width.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_line_dash_width(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_line_dash_gap(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets line dash spacing.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_line_dash_gap(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_line_rounded(bool value, lv_style_selector_t selector)
         *  \brief Enables/disables line end rounding.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_line_rounded(bool value, lv_style_selector_t selector);

        /** \fn void set_style_line_color(lv_color_t value, lv_style_selector_t selector)
         *  \brief Sets line color.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_line_color(lv_color_t value, lv_style_selector_t selector);

        /** \fn void set_style_line_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets line opacity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_line_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_arc_width(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets arc width.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_arc_width(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_arc_rounded(bool value, lv_style_selector_t selector)
         *  \brief Enables/disables arc end rounding.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_arc_rounded(bool value, lv_style_selector_t selector);

        /** \fn void set_style_arc_color(lv_color_t value, lv_style_selector_t selector)
         *  \brief Sets arc color.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_arc_color(lv_color_t value, lv_style_selector_t selector);

        /** \fn void set_style_arc_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets arc opacity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_arc_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_arc_img_src(const void * value, lv_style_selector_t selector)
         *  \brief Sets arc image source.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_arc_img_src(const void * value, lv_style_selector_t selector);
        /** \fn void set_style_arc_img_src(const ImageDescriptor & value, lv_style_selector_t selector)
         *  \brief Sets arc image source.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_arc_img_src(const ImageDescriptor & value, lv_style_selector_t selector);
        /** \fn void set_style_arc_img_src(const std::string & value, lv_style_selector_t selector)
         *  \brief Sets arc image path.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_arc_img_src(const std::string & value, lv_style_selector_t selector);

        /** \fn void set_style_text_color(lv_color_t value, lv_style_selector_t selector)
         *  \brief Sets text color.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_text_color(lv_color_t value, lv_style_selector_t selector);

        /** \fn void set_style_text_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets text opacity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_text_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_text_font(const lv_font_t * value, lv_style_selector_t selector)
         *  \brief Sets text font.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_text_font(const lv_font_t * value, lv_style_selector_t selector);
        /** \fn void set_style_text_font(const Font & value, lv_style_selector_t selector)
         *  \brief Sets text font.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_text_font(const Font & value, lv_style_selector_t selector);

        /** \fn void set_style_text_letter_space(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets text letter spacing.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_text_letter_space(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_text_line_space(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets text line spacing.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_text_line_space(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_text_decor(lv_text_decor_t value, lv_style_selector_t selector)
         *  \brief Sets text decoration style.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_text_decor(lv_text_decor_t value, lv_style_selector_t selector);

        /** \fn void set_style_text_align(lv_text_align_t value, lv_style_selector_t selector)
         *  \brief Sets text alignment.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_text_align(lv_text_align_t value, lv_style_selector_t selector);

        /** \fn void set_style_radius(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets radius.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_radius(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_clip_corner(bool value, lv_style_selector_t selector)
         *  \brief Enables/disables corner clipping with rounded corners.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_clip_corner(bool value, lv_style_selector_t selector);

        /** \fn void set_style_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets opacity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_color_filter_dsc(const lv_color_filter_dsc_t * value, lv_style_selector_t selector)
         *  \brief Sets color filter.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_color_filter_dsc(const lv_color_filter_dsc_t * value, lv_style_selector_t selector);
        /** \fn void set_style_color_filter_dsc(const ColorFilter & value, lv_style_selector_t selector)
         *  \brief Sets color filter.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_color_filter_dsc(const ColorFilter & value, lv_style_selector_t selector);

        /** \fn void set_style_color_filter_opa(lv_opa_t value, lv_style_selector_t selector)
         *  \brief Sets color filter intensity.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_color_filter_opa(lv_opa_t value, lv_style_selector_t selector);

        /** \fn void set_style_anim(const lv_anim_t * value, lv_style_selector_t selector)
         *  \brief Sets animation.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_anim(const lv_anim_t * value, lv_style_selector_t selector);
        /** \fn void set_style_anim(const Animation & value, lv_style_selector_t selector)
         *  \brief Sets animation.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_anim(const Animation & value, lv_style_selector_t selector);

        /** \fn void set_style_anim_time(uint32_t value, lv_style_selector_t selector)
         *  \brief Sets animation duration.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_anim_time(uint32_t value, lv_style_selector_t selector);

        /** \fn void set_style_anim_speed(uint32_t value, lv_style_selector_t selector)
         *  \brief Sets animation speed.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_anim_speed(uint32_t value, lv_style_selector_t selector);

        /** \fn void set_style_transition(const lv_style_transition_dsc_t * value, lv_style_selector_t selector)
         *  \brief Sets transition descriptor.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_transition(const lv_style_transition_dsc_t * value, lv_style_selector_t selector);

#if LV_USE_USER_DATA
        /** \fn void set_style_transition(const StyleTransition & value, lv_style_selector_t selector)
         *  \brief Sets transition descriptor.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_transition(const StyleTransition & value, lv_style_selector_t selector);
#endif // LV_USE_USER_DATA

        /** \fn void set_style_blend_mode(lv_blend_mode_t value, lv_style_selector_t selector);
         *  \brief Sets blending mode.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_blend_mode(lv_blend_mode_t value, lv_style_selector_t selector);

        /** \fn void set_style_layout(uint16_t value, lv_style_selector_t selector)
         *  \brief Sets layout.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_layout(uint16_t value, lv_style_selector_t selector);

        /** \fn void set_style_base_dir(lv_base_dir_t value, lv_style_selector_t selector)
         *  \brief Sets base direction (LTR/RTL).
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_base_dir(lv_base_dir_t value, lv_style_selector_t selector);

        /** \fn lv_coord_t get_style_width(uint32_t part) const
         *  \brief Gets width.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_width(uint32_t part) const;

        /** \fn lv_coord_t get_style_min_width(uint32_t part) const
         *  \brief Gets minimum width.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_min_width(uint32_t part) const;

        /** \fn lv_coord_t get_style_max_width(uint32_t part) const
         *  \brief Gets maximum width.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_max_width(uint32_t part) const;

        /** \fn lv_coord_t get_style_height(uint32_t part) const
         *  \brief Gets height.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_height(uint32_t part) const;

        /** \fn lv_coord_t get_style_min_height(uint32_t part) const
         *  \brief Gets minimum height.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_min_height(uint32_t part) const;

        /** \fn lv_coord_t get_style_max_height(uint32_t part) const
         *  \brief Gets maximum height.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_max_height(uint32_t part) const;

        /** \fn lv_coord_t get_style_x(uint32_t part) const
         *  \brief Gets horizontal position.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_x(uint32_t part) const;

        /** \fn lv_coord_t get_style_y(uint32_t part) const
         *  \brief Gets vertical position.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_y(uint32_t part) const;

        /** \fn lv_align_t get_style_align(uint32_t part) const
         *  \brief Gets alignment code.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_align_t get_style_align(uint32_t part) const;

        /** \fn lv_coord_t get_style_transform_width(uint32_t part) const
         *  \brief Gets width after transform.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_transform_width(uint32_t part) const;

        /** \fn lv_coord_t get_style_transform_height(uint32_t part) const
         *  \brief Gets height after transform.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_transform_height(uint32_t part) const;

        /** \fn lv_coord_t get_style_translate_x(uint32_t part) const
         *  \brief Gets horizontal translation.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_translate_x(uint32_t part) const;

        /** \fn lv_coord_t get_style_translate_y(uint32_t part) const
         *  \brief Gets vertical translation.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_translate_y(uint32_t part) const;

        /** \fn lv_coord_t get_style_transform_zoom(uint32_t part) const
         *  \brief Gets transform zoom factor.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_transform_zoom(uint32_t part) const;

        /** \fn lv_coord_t get_style_transform_angle(uint32_t part) const
         *  \brief Gets transform angle.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_transform_angle(uint32_t part) const;

        /** \brief Gets transform pivot point x coordinate.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_transform_pivot_x(uint32_t part) const;

        /** \brief Gets transform pivot point y coordinate.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_transform_pivot_y(uint32_t part) const;

        /** \fn lv_coord_t get_style_pad_top(uint32_t part) const
         *  \brief Gets top padding.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_pad_top(uint32_t part) const;

        /** \fn lv_coord_t get_style_pad_bottom(uint32_t part) const
         *  \brief Gets bottom padding.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_pad_bottom(uint32_t part) const;

        /** \fn lv_coord_t get_style_pad_left(uint32_t part) const
         *  \brief Gets left padding.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_pad_left(uint32_t part) const;

        /** \fn lv_coord_t get_style_pad_right(uint32_t part) const
         *  \brief Gets right padding.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_pad_right(uint32_t part) const;

        /** \fn lv_coord_t get_style_pad_row(uint32_t part) const
         *  \brief Gets row padding.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_pad_row(uint32_t part) const;

        /** \fn lv_coord_t get_style_pad_column(uint32_t part) const
         *  \brief Gets column padding.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_pad_column(uint32_t part) const;

        /** \fn lv_color_t get_style_bg_color(uint32_t part) const
         *  \brief Gets background color.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_color_t get_style_bg_color(uint32_t part) const;

        /** \fn lv_opa_t get_style_bg_opa(uint32_t part) const
         *  \brief Gets background opacity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_bg_opa(uint32_t part) const;

        /** \fn lv_color_t get_style_bg_grad_color(uint32_t part) const
         *  \brief Gets background gradient second color.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_color_t get_style_bg_grad_color(uint32_t part) const;

        /** \fn lv_grad_dir_t get_style_bg_grad_dir(uint32_t part) const
         *  \brief Gets background gradient direction.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_grad_dir_t get_style_bg_grad_dir(uint32_t part) const;

        /** \fn lv_coord_t get_style_bg_main_stop(uint32_t part) const
         *  \brief Gets relative position of background's gradient first stop.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_bg_main_stop(uint32_t part) const;

        /** \fn lv_coord_t get_style_bg_grad_stop(uint32_t part) const
         *  \brief Gets relative position of background's gradient second stop.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_bg_grad_stop(uint32_t part) const;

        /** \fn const lv_grad_dsc_t * get_style_bg_grad(uint32_t part) const
         *  \brief Gets background gradient descriptor.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        const lv_grad_dsc_t * get_style_bg_grad(uint32_t part) const;

        /** \fn lv_dither_mode_t get_style_bg_dither_mode(uint32_t part) const
         *  \brief Gets background dithering mode.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_dither_mode_t get_style_bg_dither_mode(uint32_t part) const;

        /** \fn const void * get_style_bg_img_src(uint32_t part) const
         *  \brief Gets background image source.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        const void * get_style_bg_img_src(uint32_t part) const;

        /** \fn lv_opa_t get_style_bg_img_opa(uint32_t part) const
         *  \brief Gets background image opacity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_bg_img_opa(uint32_t part) const;

        /** \fn lv_color_t get_style_bg_img_recolor(uint32_t part) const
         *  \brief Gets background image recoloring color.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_color_t get_style_bg_img_recolor(uint32_t part) const;

        /** \fn lv_opa_t get_style_bg_img_recolor_opa(uint32_t part) const
         *  \brief Gets background image recoloring intensity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_bg_img_recolor_opa(uint32_t part) const;

        /** \fn bool get_style_bg_img_tiled(uint32_t part) const
         *  \brief Gets if background image is tiled.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        bool get_style_bg_img_tiled(uint32_t part) const;

        /** \fn lv_color_t get_style_border_color(uint32_t part) const
         *  \brief Gets border color.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_color_t get_style_border_color(uint32_t part) const;

        /** \fn lv_opa_t get_style_border_opa(uint32_t part) const
         *  \brief Gets border opacity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_border_opa(uint32_t part) const;

        /** \fn lv_coord_t get_style_border_width(uint32_t part) const
         *  \brief Gets border width.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_border_width(uint32_t part) const;

        /** \fn lv_border_side_t get_style_border_side(uint32_t part) const
         *  \brief Gets on which side border is drawn.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_border_side_t get_style_border_side(uint32_t part) const;

        /** \fn bool get_style_border_post(uint32_t part) const
         *  \brief Gets if border is drawn last.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        bool get_style_border_post(uint32_t part) const;

        /** \fn lv_coord_t get_style_outline_width(uint32_t part) const
         *  \brief Gets outline width.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_outline_width(uint32_t part) const;

        /** \fn lv_color_t get_style_outline_color(uint32_t part) const
         *  \brief Gets outline color.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_color_t get_style_outline_color(uint32_t part) const;
        
        /** \fn lv_opa_t get_style_outline_opa(uint32_t part) const
         *  \brief Gets outline opacity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_outline_opa(uint32_t part) const;

        /** \fn lv_coord_t get_style_outline_pad(uint32_t part) const
         *  \brief Gets outline padding.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_outline_pad(uint32_t part) const;

        /** \fn lv_coord_t get_style_shadow_width(uint32_t part) const
         *  \brief Gets shadow width.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_shadow_width(uint32_t part) const;

        /** \fn lv_coord_t get_style_shadow_ofs_x(uint32_t part) const
         *  \brief Gets shadow horizontal offset.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_shadow_ofs_x(uint32_t part) const;

        /** \fn lv_coord_t get_style_shadow_ofs_y(uint32_t part) const
         *  \brief Gets shadow vertical offset.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_shadow_ofs_y(uint32_t part) const;

        /** \fn lv_coord_t get_style_shadow_spread(uint32_t part) const
         *  \brief Gets shadow spread.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_shadow_spread(uint32_t part) const;

        /** \fn lv_color_t get_style_shadow_color(uint32_t part) const
         *  \brief Gets shadow color.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_color_t get_style_shadow_color(uint32_t part) const;

        /** \fn lv_opa_t get_style_shadow_opa(uint32_t part) const
         *  \brief Gets shadow opacity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_shadow_opa(uint32_t part) const;

        /** \fn lv_opa_t get_style_img_opa(uint32_t part) const
         *  \brief Gets image opacity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_img_opa(uint32_t part) const;

        /** \fn lv_color_t get_style_img_recolor(uint32_t part) const
         *  \brief Gets image recoloring color.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_color_t get_style_img_recolor(uint32_t part) const;

        /** \fn lv_opa_t get_style_img_recolor_opa(uint32_t part) const
         *  \brief Gets image recoloring intensity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_img_recolor_opa(uint32_t part) const;

        /** \fn lv_coord_t get_style_line_width(uint32_t part) const
         *  \brief Gets line width.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_line_width(uint32_t part) const;

        /** \fn lv_coord_t get_style_line_dash_width(uint32_t part) const
         *  \brief Gets line dash width.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_line_dash_width(uint32_t part) const;

        /** \fn lv_coord_t get_style_line_dash_gap(uint32_t part) const
         *  \brief Gets line dash spacing.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_line_dash_gap(uint32_t part) const;

        /** \fn bool get_style_line_rounded(uint32_t part) const
         *  \brief Gets if line ends are rounded.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        bool get_style_line_rounded(uint32_t part) const;

        /** \fn lv_color_t get_style_line_color(uint32_t part) const
         *  \brief Gets line color.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_color_t get_style_line_color(uint32_t part) const;

        /** \fn lv_opa_t get_style_line_opa(uint32_t part) const
         *  \brief Gets line opacity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_line_opa(uint32_t part) const;

        /** \fn lv_coord_t get_style_arc_width(uint32_t part) const
         *  \brief Gets arc width.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_arc_width(uint32_t part) const;

        /** \fn bool get_style_arc_rounded(uint32_t part) const
         *  \brief Gets if arc ends are rounded.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        bool get_style_arc_rounded(uint32_t part) const;

        /** \fn lv_color_t get_style_arc_color(uint32_t part) const
         *  \brief Gets arc color.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_color_t get_style_arc_color(uint32_t part) const;

        /** \fn lv_opa_t get_style_arc_opa(uint32_t part) const
         *  \brief Gets arc opacity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_arc_opa(uint32_t part) const;

        /** \fn const void * get_style_arc_img_src(uint32_t part) const
         *  \brief Gets arc image source.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        const void * get_style_arc_img_src(uint32_t part) const;

        /** \fn lv_color_t get_style_text_color(uint32_t part) const
         *  \brief Gets text color.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_color_t get_style_text_color(uint32_t part) const;

        /** \fn lv_opa_t get_style_text_opa(uint32_t part) const
         *  \brief Gets text opacity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_text_opa(uint32_t part) const;

        /** \fn const lv_font_t * get_style_text_font(uint32_t part) const
         *  \brief Gets text font.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        const lv_font_t * get_style_text_font(uint32_t part) const;

        /** \fn lv_coord_t get_style_text_letter_space(uint32_t part) const
         *  \brief Gets text letter spacing.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_text_letter_space(uint32_t part) const;

        /** \fn lv_coord_t get_style_text_line_space(uint32_t part) const
         *  \brief Gets text line spacing.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_text_line_space(uint32_t part) const;

        /** \fn lv_text_decor_t get_style_text_decor(uint32_t part) const
         *  \brief Gets text decoration style.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_text_decor_t get_style_text_decor(uint32_t part) const;

        /** \fn lv_text_align_t get_style_text_align(uint32_t part) const
         *  \brief Gets text alignment.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_text_align_t get_style_text_align(uint32_t part) const;

        /** \fn lv_coord_t get_style_radius(uint32_t part) const
         *  \brief Gets radius.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_radius(uint32_t part) const;

        /** \fn bool get_style_clip_corner(uint32_t part) const
         *  \brief Gets if content's corners are clipped if they are rounded.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        bool get_style_clip_corner(uint32_t part) const;

        /** \fn lv_opa_t get_style_opa(uint32_t part) const
         *  \brief Gets opacity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_opa(uint32_t part) const;

        /** \fn const lv_color_filter_dsc_t * get_style_color_filter_dsc(uint32_t part) const
         *  \brief Gets color filter descriptor.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        const lv_color_filter_dsc_t * get_style_color_filter_dsc(uint32_t part) const;

        /** \fn lv_opa_t get_style_color_filter_opa(uint32_t part) const
         *  \brief Gets color filter opacity.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_opa_t get_style_color_filter_opa(uint32_t part) const;

        /** \fn const lv_anim_t * get_style_anim(uint32_t part) const
         *  \brief Gets animation.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        const lv_anim_t * get_style_anim(uint32_t part) const;

        /** \fn uint32_t get_style_anim_time(uint32_t part) const
         *  \brief Gets animation duration.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        uint32_t get_style_anim_time(uint32_t part) const;

        /** \fn uint32_t get_style_anim_speed(uint32_t part) const
         *  \brief Gets animation speed.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        uint32_t get_style_anim_speed(uint32_t part) const;

        /** \fn const lv_style_transition_dsc_t * get_style_transition(uint32_t part) const
         *  \brief Gets transition descriptor.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        const lv_style_transition_dsc_t * get_style_transition(uint32_t part) const;

        /** \fn lv_blend_mode_t get_style_blend_mode(uint32_t part) const
         *  \brief Gets blending mode.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_blend_mode_t get_style_blend_mode(uint32_t part) const;

        /** \fn uint16_t get_style_layout(uint32_t part) const
         *  \brief Gets layout.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        uint16_t get_style_layout(uint32_t part) const;

        /** \fn lv_base_dir_t get_style_base_dir(uint32_t part) const
         *  \brief Gets base direction.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_base_dir_t get_style_base_dir(uint32_t part) const;

#if LV_USE_FLEX
        /* flex layout */
        /** \fn void set_flex_flow(lv_flex_flow_t flow)
         *  \brief Sets flex flow.
         *  \param flow: code for flex flow (see lv_flex_flow_t for options).
         */
        void set_flex_flow(lv_flex_flow_t flow);

        /** \fn void set_flex_align(lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_cross_place)
         *  \brief Sets flex alignment.
         *  \param main_place: alignment for main direction.
         *  \param cross_place: alignment for other direction.
         *  \param track_cross_place: content alignement.
         */
        void set_flex_align(lv_flex_align_t main_place, lv_flex_align_t cross_place, lv_flex_align_t track_cross_place);

        /** \fn void set_flex_grow(uint8_t grow)
         *  \brief Sets flex grow. This is the amount an item can grow relative to other items.
         *  \param grow: relative amount the item can grow.
         */
        void set_flex_grow(uint8_t grow);

        /** \fn void set_style_flex_flow(lv_flex_flow_t value, lv_style_selector_t selector);
         *  \brief Sets flex flow.
         *  \param value: code for flex flow (see lv_flex_flow_t for options).
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_flex_flow(lv_flex_flow_t value, lv_style_selector_t selector);

        /** \fn void set_style_flex_main_place(lv_flex_align_t value, lv_style_selector_t selector)
         *  \brief Sets flex alignment for main direction.
         *  \param value: alignment code.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_flex_main_place(lv_flex_align_t value, lv_style_selector_t selector);

        /** \fn void set_style_flex_cross_place(lv_flex_align_t value, lv_style_selector_t selector)
         *  \brief Sets flex alignment for alternate direction.
         *  \param value: alignment code.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_flex_cross_place(lv_flex_align_t value, lv_style_selector_t selector);

        /** \fn void set_style_flex_track_place(lv_flex_align_t value, lv_style_selector_t selector)
         *  \brief Sets flex alignment for content.
         *  \param value: alignment code.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_flex_track_place(lv_flex_align_t value, lv_style_selector_t selector);

        /** \fn void set_style_flex_grow(uint8_t value, lv_style_selector_t selector)
         *  \brief Sets flex grow.
         *  \param value: alignment code.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_flex_grow(uint8_t value, lv_style_selector_t selector);

        /** \fn lv_flex_flow_t get_style_flex_flow(uint32_t part) const
         *  \brief Gets flex flow.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_flex_flow_t get_style_flex_flow(uint32_t part) const;

        /** \fn lv_flex_align_t get_style_flex_main_place(uint32_t part) const
         *  \brief Gets flex alignment for main direction.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_flex_align_t get_style_flex_main_place(uint32_t part) const;

        /** \fn lv_flex_align_t get_style_flex_cross_place(uint32_t part) const
         *  \brief Gets flex alignment for alternate direction.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_flex_align_t get_style_flex_cross_place(uint32_t part) const;

        /** \fn lv_flex_align_t get_style_flex_track_place(uint32_t part) const
         *  \brief Gets flex alignment for content.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_flex_align_t get_style_flex_track_place(uint32_t part) const;

        /** \fn uint8_t get_style_flex_grow(uint32_t part) const
         *  \brief Gets flex grow.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        uint8_t get_style_flex_grow(uint32_t part) const;
#endif // LV_USE_FLEX

#if LV_USE_GRID
        /* grid layout */
        /** \fn void set_grid_dsc_array(const std::vector<lv_coord_t> & col_dsc, const std::vector<lv_coord_t> & row_dsc)
         *  \brief Sets grid layout properties.
         *  \param col_dsc: list of column sizes.
         *  \param row_dsc: list of row sizes.
         */
        void set_grid_dsc_array(const std::vector<lv_coord_t> & col_dsc, const std::vector<lv_coord_t> & row_dsc);

        /** \fn void set_grid_align(lv_grid_align_t column_align, lv_grid_align_t row_align)
         *  \brief Sets grid alignment properties.
         *  \param column_align: alignment in columns.
         *  \param row_align: alignment in rows.
         */
        void set_grid_align(lv_grid_align_t column_align, lv_grid_align_t row_align);

        /** \fn void set_grid_cell(lv_grid_align_t column_align, uint8_t col_pos, uint8_t col_span,
         *                         lv_grid_align_t row_align, uint8_t row_pos, uint8_t row_span)
         *  \brief Sets properties for a given grid cell.
         *  \param column_align: horizontal alignment.
         *  \param col_pos: column index (zero-based).
         *  \param col_span: number of columns spanned (1 or larger).
         *  \param row_align: vertical alignment.
         *  \param row_pos: row index (zero-based).
         *  \param row_span: number of rows spanned (1 or larger).
         */
        void set_grid_cell(lv_grid_align_t column_align, uint8_t col_pos, uint8_t col_span,
                           lv_grid_align_t row_align, uint8_t row_pos, uint8_t row_span);

        /** \fn void set_style_grid_row_dsc_array(const std::vector<lv_coord_t> & value, lv_style_selector_t selector)
         *  \brief Sets row heights.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_grid_row_dsc_array(const std::vector<lv_coord_t> & value, lv_style_selector_t selector);

        /** \fn void set_style_grid_column_dsc_array(const std::vector<lv_coord_t> & value, lv_style_selector_t selector)
         *  \brief Sets column widths.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_grid_column_dsc_array(const std::vector<lv_coord_t> & value, lv_style_selector_t selector);

        /** \fn void set_style_grid_row_align(lv_grid_align_t value, lv_style_selector_t selector)
         *  \brief Sets content's vertical alignment.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_grid_row_align(lv_grid_align_t value, lv_style_selector_t selector);

        /** \fn void set_style_grid_column_align(lv_grid_align_t value, lv_style_selector_t selector)
         *  \brief Sets content's horizontal alignment.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_grid_column_align(lv_grid_align_t value, lv_style_selector_t selector);

        /** \fn void set_style_grid_cell_column_pos(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets column index.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_grid_cell_column_pos(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_grid_cell_column_span(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets column span.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_grid_cell_column_span(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_grid_cell_row_pos(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets row index.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_grid_cell_row_pos(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_grid_cell_row_span(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets row span.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_grid_cell_row_span(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_grid_cell_x_align(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets content's horizontal alignment.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_grid_cell_x_align(lv_coord_t value, lv_style_selector_t selector);

        /** \fn void set_style_grid_cell_y_align(lv_coord_t value, lv_style_selector_t selector)
         *  \brief Sets content's vertical alignment.
         *  \param value: property value.
         *  \param selector: OR-ed combination of parts and states to apply the style to.
         */
        void set_style_grid_cell_y_align(lv_coord_t value, lv_style_selector_t selector);

        /** \fn const lv_coord_t * get_style_grid_row_dsc_array(uint32_t part) const
         *  \brief Gets row heights.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        const lv_coord_t * get_style_grid_row_dsc_array(uint32_t part) const;

        /** \fn const lv_coord_t * get_style_grid_column_dsc_array(uint32_t part) const
         *  \brief Gets column widths.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        const lv_coord_t * get_style_grid_column_dsc_array(uint32_t part) const;

        /** \fn lv_grid_align_t get_style_grid_row_align(uint32_t part) const
         *  \brief Gets vertical alignment.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_grid_align_t get_style_grid_row_align(uint32_t part) const;

        /** \fn lv_grid_align_t get_style_grid_column_align(uint32_t part) const
         *  \brief Gets horizontal alignment.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_grid_align_t get_style_grid_column_align(uint32_t part) const;

        /** \fn lv_coord_t get_style_grid_cell_column_pos(uint32_t part) const
         *  \brief Gets column index.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_grid_cell_column_pos(uint32_t part) const;

        /** \fn lv_coord_t get_style_grid_cell_column_span(uint32_t part) const
         *  \brief Gets column span.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_grid_cell_column_span(uint32_t part) const;

        /** \fn lv_coord_t get_style_grid_cell_row_pos(uint32_t part) const
         *  \brief Gets row index.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_grid_cell_row_pos(uint32_t part) const;

        /** \fn lv_coord_t get_style_grid_cell_row_span(uint32_t part) const
         *  \brief Gets row span.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_grid_cell_row_span(uint32_t part) const;

        /** \fn lv_coord_t get_style_grid_cell_x_align(uint32_t part) const
         *  \brief Gets cell's horizontal alignment.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_grid_cell_x_align(uint32_t part) const;

        /** \fn lv_coord_t get_style_grid_cell_y_align(uint32_t part) const
         *  \brief Gets cell's vertical alignment.
         *  \param part: OR-ed combination of parts and states to get style from.
         *  \returns property value.
         */
        lv_coord_t get_style_grid_cell_y_align(uint32_t part) const;
#endif // LV_USE_GRID

        /* theme */
        /** \fn const lv_font_t * get_font_small() const
         *  \brief Gets theme's small font.
         *  \returns pointer to font.
         */
        const lv_font_t * get_font_small() const;

        /** \fn const lv_font_t * get_font_normal() const
         *  \brief Gets theme's normal font.
         *  \returns pointer to font.
         */
        const lv_font_t * get_font_normal() const;

        /** \fn const lv_font_t * get_font_large() const
         *  \brief Gets theme's large font.
         *  \returns pointer to font.
         */
        const lv_font_t * get_font_large() const;

        /** \fn lv_color_t get_color_primary() const
         *  \brief Gets primary color.
         *  \returns color.
         */
        lv_color_t get_color_primary() const;

        /** \fn lv_color_t get_color_secondary() const
         *  \brief Gets secondary color.
         *  \returns color.
         */
        lv_color_t get_color_secondary() const;

        /** \fn Theme get_theme() const
         *  \brief Gets theme.
         *  \returns theme object.
         */
        Theme get_theme() const;

        /** \fn void apply_act_theme()
         *  \brief Applies current theme to displayed items.
         */
        void apply_act_theme();

        /* from lv_api_map */
        /** \fn void to_foreground()
         *  \brief Moves object to foreground.
         */
        void to_foreground();

        /** \fn void to_background()
         *  \brief Moves object to background.
         */
        void to_background();

    };


    /** \brief Wraps a lv_obj_t object created with the given allocator.
     *  \tparam lv_allocator: an allocator function that returns a pointer
     *  to a lv_obj_t instance.
     */
    template <auto lv_allocator> class Widget : public Object {
    protected:
        /** \fn void initialize()
         *  \brief Initialize object.
         */
        virtual void initialize() {
            this->lv_obj = LvPointerType(lv_allocator(nullptr));
        }

        /** \fn void initialize(Object & parent)
         *  \brief Initialize object and assign parent object.
         *  \param parent: parent LVGL object.
         */
        virtual void initialize(Object & parent) {
            this->lv_obj = LvPointerType(lv_allocator(parent.raw_ptr()));
        }
    
        /** \fn void initialize(const Object & parent)
         *  \brief Initialize object and assign parent object.
         *  \param parent: parent LVGL object.
         */
        virtual void initialize(const Object & parent) {
            this->lv_obj = LvPointerType(
                lv_allocator(const_cast<lv_cls_ptr>(parent.raw_ptr())));
        }

    public:
        using Object::Object;

        /** \fn Widget()
         *  \brief Default constructor.
         */
        Widget() {
            this->initialize();
        }

        /** \fn Widget(Object & parent)
         *  \brief Constructor with parent object.
         */
        Widget(Object & parent) {
            this->initialize(parent);
        }

        /** \fn Widget(const Object & parent)
         *  \brief Constructor with parent object.
         */
        Widget(const Object & parent) {
            this->initialize(parent);
        }

        /** \fn Widget(Widget & parent)
         *  \brief Constructor with parent widget object.
         *  
         *  This is for cases when parent is of the same type.
         *  Compiler otherwise wants to use base class
         *  copy constructor, which doesn't exist.
         *  Note that we could define an explicit copy constructor
         *  in the Object class, but this leaves the default
         *  constructor out.
         * 
         */
        Widget(Widget & parent) {
            this->initialize(parent);
        }

        /** \fn Widget(const Widget & parent)
         *  \brief Constructor with parent widget object.
         *  
         *  This is for cases when parent is of the same type.
         *  Compiler otherwise wants to use base class
         *  copy constructor, which doesn't exist.
         * 
         */
        Widget(const Widget & parent) {
            this->initialize(parent);
        }

    };


    /** \class Container
     *  \brief Wraps a lv_obj_t object created with the default allocator.
     */
    class Container : public Widget<lv_obj_create> {
    public:
        using Widget::Widget;
    };


    /** \namespace lvgl::core::obj
     *  \brief General functions involving objects.
     */
    namespace obj {

        /** \fn template <typename T> bool draw_part_check_type(lv_obj_draw_part_dsc_t * dsc, uint32_t type)
         *  \brief Compares the type of an object in a draw descriptor with given class and type.
         *  \tparam T: object class.
         *  \param dsc: pointer to object draw descriptor.
         *  \param type: type code.
         */
        template <typename T> bool draw_part_check_type(lv_obj_draw_part_dsc_t * dsc, uint32_t type) {
            static auto cls = T().get_class();
            return lv_obj_draw_part_check_type(dsc, cls, type);
        }
        
    }

}
