/** \file event.h
 *  \brief Header file for C++ wrapper for LVGL events.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */

#include "../lv_wrapper.h"
#include "../misc/anim.h"
#include "../misc/area.h"

namespace lvgl::core {

    using namespace lvgl::misc;

    class Object;
    class InputDevice;

    /** \class Event
     *  \brief Wraps a lv_event_t object.
     */
    class Event {
    /** \typedef LvPointerType
     *  \brief Another way to express lv_event_t*.
     */
    using LvPointerType = lv_event_t*;
    private:
        /** \property LvPointerType lv_obj
         *  \brief Wrapped event object pointer.
         */
        LvPointerType lv_obj;

    public:
        // we don't allow creating Event objects from scratch; events are generated
        // by LVGL in different ways in the form of lv_event_t instances.
        // We also don't allow copying, as this would mean creating a new event.
        // We can then move-construct Event objects if we want to take ownership
        // of the event. Be aware that lv_event_t instances may be deleted by LVGL
        // and hence the Event object will become invalid.
        Event() = delete;
        Event(const lv_event_t & e) = delete;
        Event(const Event & e) = delete;
        Event & operator=(const Event & e) = delete;

        /** \fn Event(lv_event_t * obj)
         *  \brief Constructor.
         *  \param obj: pointer to LVGL event instance to wrap.
         */
        Event(lv_event_t * obj) {
            this->lv_obj = LvPointerType(obj);
        }

        /** \fn LvPointerType raw_ptr() const
         *  \brief Gives access to the wrapped pointer.
         *  \returns pointer to wrapped instance.
         */
        LvPointerType raw_ptr() const {
            return this->lv_obj;
        }

        /** \fn template <class T> T get_target() const
         *  \brief Gets event target.
         *  \returns target object.
         */
        template <class T> T get_target() const {
            return T(lv_event_get_target(const_cast<lv_event_t*>(this->raw_ptr())), false);
        }

        /** \fn template <class T> T get_current_target() const
         *  \brief Gets event's current target (can be different from original
         *  target if event is bubbling).
         *  \returns current target object.
         */
        template <class T> T get_current_target() const {
            return T(lv_event_get_current_target(const_cast<lv_event_t*>(this->raw_ptr())), false);
        }

        /** \fn lv_event_code_t get_code() const
         *  \brief Gets event code.
         *  \returns event code.
         */
        lv_event_code_t get_code() const;

        /** \fn template <class T> T & get_param() const
         *  \brief Gets parameter passed when event was sent.
         *  \tparam T: parameter class.
         *  \returns pointer to the event parameter.
         */
        //template <class T> T* get_param() const;
        /** \brief Gets parameter passed when event was sent.
         *  \returns pointer to the event parameter.
         */
        template <class T> T* get_param() const {
            return reinterpret_cast<T*>(this->lv_obj->param);
        }

#if LV_USE_USER_DATA
        /** \fn template <class T> T & get_user_data() const;
         *  \brief Gets user data passed when event was registered with the object.
         *  \tparam T: parameter class.
         *  \returns pointer to user data.
         */
        template <class T> T & get_user_data() const {
            return reinterpret_cast<T>(*lv_event_get_user_data(const_cast<lv_event_t*>(this->raw_ptr())));
        }
        /** \brief Gets user data passed when event was registered with the object.
         *  \returns pointer to user data.
         */
        void * get_user_data() const;
#endif // LV_USE_USER_DATA

        /** \fn void stop_bubbling()
         *  \brief Stops event bubbling.
         */
        void stop_bubbling();

        /** \fn void stop_processing()
         *  \brief Stops processing the event.
         */
        void stop_processing();

        /** \fn static uint32_t register_id()
         *  \brief Registers a new event ID.
         *  \returns new event ID.
         */
        static uint32_t register_id();

#if LV_USE_USER_DATA
        /** \fn InputDevice get_indev() const
         *  \brief Gets input device associated with event, if any.
         *  \returns input device object.
         */
        InputDevice get_indev() const;
#else
        /** \fn lv_indev_t * get_indev() const
         *  \brief Gets input device associated with event, if any.
         *  \returns pointer to input device instance, or nullptr if none.
         */
        lv_indev_t * get_indev() const;
#endif // LV_USE_USER_DATA

        /** \fn lv_obj_draw_part_dsc_t* get_draw_part_dsc() const
         *  \brief Gets draw part descriptor associated with event, if any.
         *  \returns pointer to draw part descriptor instance, or nullptr if none.
         */
        lv_obj_draw_part_dsc_t* get_draw_part_dsc() const;

        /** \fn lv_draw_ctx_t* get_draw_ctx() const
         *  \brief Gets draw context associated with event, if any.
         *  \returns pointer to draw context instance, or nullptr if none.
         */
        lv_draw_ctx_t* get_draw_ctx() const;

        /** \fn const Area get_old_size() const
         *  \brief Gets size of object before the event happened
         *  (valid for LV_EVENT_SIZE_CHANGED events).
         *  \returns size of object before event.
         */
        const Area get_old_size() const;

        /** \fn uint32_t get_key() const
         *  \brief For LV_EVENT_KEY, gets the key triggering the event.
         *  \returns key index.
         */
        uint32_t get_key() const;

        /** \fn Animation get_scroll_anim() const
         *  \brief For LV_EVENT_SCROLL_BEGIN, gets scroll animation descriptor.
         *  \returns pointer to scroll animation descriptor, or nullptr if none.
         */
        Animation get_scroll_anim() const;

        /** \fn void set_ext_draw_size(lv_coord_t size)
         *  \brief For LV_EVENT_REFR_EXT_DRAW_SIZE, sets the new extra draw size.
         *  \param size: new extra draw size.
         */
        void set_ext_draw_size(lv_coord_t size);

        /** \fn lv_point_t* get_self_size_info() const
         *  \brief For LV_EVENT_GET_SELF_SIZE, gets size info.
         *  \returns pointer to a point with point->x = width and point->y = height,
         *  or nullptr if not applicable.
         */
        lv_point_t* get_self_size_info() const;

        /** \fn lv_hit_test_info_t* get_hit_test_info() const
         *  \brief For LV_EVENT_HIT_TEST, gets hit test info.
         *  \returns pointer to hit test info, or nullptr if not applicable.
         */
        lv_hit_test_info_t* get_hit_test_info() const;

        /** \fn const Area get_cover_area() const
         *  \brief For LV_EVENT_COVER_CHECK, gets the area that should be tested.
         *  \returns area tested in LV_EVENT_COVER_CHECK, or empty area if irrelevant.
         */
        const Area get_cover_area() const;

        /** \fn void set_cover_res(lv_cover_res_t res)
         *  \brief For LV_EVENT_COVER_CHECK, sets the result of area cover check.
         *  \param res: cover check result (LV_COVER_RES_COVER/NOT_COVER/MASKED).
         */
        void set_cover_res(lv_cover_res_t res);

    };

}