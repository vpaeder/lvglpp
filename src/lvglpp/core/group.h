/** \file group.h
 *  \brief Header file for C++ wrapper for LVGL groups.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */

#include "../lv_wrapper.h"

namespace lvgl::core {

    class Object;

    /** \class Group
     *  \brief Wraps a lv_group_t object.
     */
    class Group : public PointerWrapper<lv_group_t, lv_group_del> {
    public:
        using PointerWrapper::PointerWrapper;
        
        /** \fn void set_default()
         *  \brief Sets group as default group for new objects.
         */
        void set_default();

        /** \fn void add_obj(const Object & obj);
         *  \brief Adds given object to group.
         *  \param obj: object to add.
         */
        void add_obj(const Object & obj);

        /** \fn void remove_all_objs()
         *  \brief Clears group from all objects.
         */
        void remove_all_objs();

        /** \fn void focus_next()
         *  \brief Focuses next object.
         */
        void focus_next();
        
        /** \fn void focus_prev()
         *  \brief Focuses previous object.
         */
        void focus_prev();

        /** \fn void focus_freeze(bool en)
         *  \brief Enables/disables focus freeze.
         *  \param en: if true, focus is frozen on current object.
         */
        void focus_freeze(bool en);

        /** \fn lv_res_t send_data(uint32_t c)
         *  \brief Sends a character to the currently focused object.
         *  \param c: character index.
         *  \returns result code: LV_RES_OK if success, LV_RES_INV otherwise.
         */
        lv_res_t send_data(uint32_t c);

        /** \fn void set_focus_cb(lv_group_focus_cb_t focus_cb)
         *  \brief Sets callback for focus events.
         *  \param focus_cb: callback function.
         */
        void set_focus_cb(lv_group_focus_cb_t focus_cb);

        /** \brief Sets callback to call when edge is reached.
         *  \param edge_cb: callback function.
         */
        void set_edge_cb(lv_group_edge_cb_t edge_cb);

        /** \fn void set_refocus_policy(lv_group_refocus_policy_t policy)
         *  \brief Sets policy when focused object is deleted.
         *  \param policy: policy code (LV_GROUP_REFOCUS_POLICY_NEXT/PREV).
         */
        void set_refocus_policy(lv_group_refocus_policy_t policy);

        /** \fn void set_editing(bool edit)
         *  \brief Sets group mode.
         *  \param edit: if true, sets editing mode; if false, navigation mode.
         */
        void set_editing(bool edit);

        /** \fn void set_wrap(bool en)
         *  \brief Sets behaviour of focus prev/next on group boundaries.
         *  \param en: if true, allows jumping from first to last and reverse.
         */
        void set_wrap(bool en);

        /** \fn Object get_focused() const
         *  \brief Gets currently focused object.
         *  \returns currently focused object.
         */
        Object get_focused() const;

        /** \fn lv_group_focus_cb_t get_focus_cb() const
         *  \brief Gets callback for focus events.
         *  \returns callback function for focus event, or nullptr if none set.
         */
        lv_group_focus_cb_t get_focus_cb() const;

        /** \brief Gets function called when edge is reached.
         *  \returns callback function for edge events, or nullptr if none set.
         */
        lv_group_edge_cb_t get_edge_cb() const;

        /** \fn bool get_editing() const
         *  \brief Gets group mode.
         *  \returns true if in editing mode, false if in navigation mode.
         */
        bool get_editing() const;

        /** \fn bool get_wrap() const
         *  \brief Gets behaviour of focus prev/next on group boundaries.
         *  \returns true if focus can jump from first to last and reverse, false otherwise.
         */
        bool get_wrap() const;
        
        /** \fn uint32_t get_obj_count() const
         *  \brief Gets the number of objects in the group.
         *  \returns the number of objects in the group.
         */
        uint32_t get_obj_count() const;

    };

    /** \fn Group get_default_group()
     *  \brief Gets default group.
     *  \returns default group.
     */
    Group get_default_group();

    /** \fn void set_default_group(Group & group)
     *  \brief Sets default group. Equivalent to Group::set_default.
     *  \param group: group to set as default.
     */
    void set_default_group(Group & group);

    /** \fn void swap_objs_in_group(Object & obj1, Object & obj2)
     *  \brief Swap indices of given objects (must be in the same group).
     *  \param obj1: first object.
     *  \param obj2: second object.
     */
    void swap_objs_in_group(Object & obj1, Object & obj2);
}
