/** \file anim.h
 *  \brief Header file for C++ wrapper for lv_anim_t and lv_anim_timeline_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../lv_thin_wrapper.h"

/** \namespace lvgl::misc
 *  \brief LVGL miscellaneous components.
 */
namespace lvgl::misc {

    /** \class Animation
     *  \brief Wraps a lv_anim_t object.
     */
    class Animation : public ThinPointerWrapper<lv_anim_t, lv_mem_free> {
    public:
        using ThinPointerWrapper::ThinPointerWrapper;

        /** \fn Animation()
         *  \brief Default constructor.
         */
        Animation();

        /** \fn template <class T> void set_var(T & var)
         *  \brief Sets animation variable.
         *  \tparam T: variable type.
         *  \param var: variable to animate. Must remain allocated.
         */
        template <class T> void set_var(T & var);

        /** \fn void set_var(void * var)
         *  \brief Sets animation variable.
         *  \param var: pointer to variable to animate.
         */
        void set_var(void * var);

        /** \fn void set_exec_cb(lv_anim_exec_xcb_t exec_cb)
         *  \brief Sets callback function used to animate variable.
         *  \param exec_cb: callback function.
         */
        void set_exec_cb(lv_anim_exec_xcb_t exec_cb);

        /** \fn void set_time(uint32_t duration)
         *  \brief Sets animation duration.
         *  \param duration: duration, in ms.
         */
        void set_time(uint32_t duration);

        /** \fn void set_delay(uint32_t delay)
         *  \brief Sets animation delay.
         *  \param delay: delay, in ms.
         */
        void set_delay(uint32_t delay);

        /** \fn void set_values(int32_t start, int32_t end)
         *  \brief Sets start and end values.
         *  \param start: start value.
         *  \param end: end value.
         */
        void set_values(int32_t start, int32_t end);

        /** \fn void set_custom_exec_cb(lv_anim_custom_exec_cb_t exec_cb)
         *  \brief Sets a custom function used to animate variable. This version
         *  takes a lv_anim_t* as 1st variable instead of void*.
         *  \param exec_cb: callback function.
         */
        void set_custom_exec_cb(lv_anim_custom_exec_cb_t exec_cb);

        /** \fn void set_path_cb(lv_anim_path_cb_t path_cb)
         *  \brief Sets the function that calculates the animation's path.
         *  \param path_cb: callback function.
         */
        void set_path_cb(lv_anim_path_cb_t path_cb);

        /** \fn void set_start_cb(lv_anim_start_cb_t start_cb)
         *  \brief Sets the function called on animation start.
         *  \param start_cb: callback function.
         */
        void set_start_cb(lv_anim_start_cb_t start_cb);

        /** \fn void set_get_value_cb(lv_anim_get_value_cb_t get_value_cb)
         *  \brief Sets a function that transforms the actual animation position
         *  into a value in variable space. This is for instance if we have
         *  a variable that has a logarithmic behaviour.
         *  \param get_value_cb: callback function.
         */
        void set_get_value_cb(lv_anim_get_value_cb_t get_value_cb);

        /** \fn void set_ready_cb(lv_anim_ready_cb_t ready_cb)
         *  \brief Sets the function called when the animation ends.
         *  \param ready_cb: callback function.
         */
        void set_ready_cb(lv_anim_ready_cb_t ready_cb);

        /** \fn void set_reverse_time(uint32_t time)
         *  \brief Sets the animation duration in reverse direction.
         *  \param time: duration, in ms; 0=no reverse.
         */
        void set_reverse_time(uint32_t time);

        /** \fn void set_reverse_delay(uint32_t delay)
         *  \brief Sets the animation delay before playing in reverse direction.
         *  \param delay: delay, in ms.
         */
        void set_reverse_delay(uint32_t delay);

        /** \fn void set_repeat_count(uint16_t cnt)
         *  \brief Sets the animation repeat count.
         *  \param cnt: repeat count.
         */
        void set_repeat_count(uint16_t cnt);

        /** \fn void set_repeat_delay(uint32_t delay)
         *  \brief Sets the animation repeat delay.
         *  \param delay: delay, in ms.
         */
        void set_repeat_delay(uint32_t delay);

        /** \fn void set_early_apply(bool en)
         *  \brief Sets when the animation anounces it has started.
         *  \param en: if false, anounces after delay; if true, anounces before.
         */
        void set_early_apply(bool en);

        /** \fn template <class T> void set_user_data(T & user_data)
         *  \brief Sets user data.
         *  \tparam T: user data type.
         *  \param user_data: user data.
         */
        template <class T> void set_user_data(T & user_data);

        /** \fn void set_user_data(void * user_data)
         *  \brief Sets user data.
         *  \param user_data: pointer to user data.
         */
        void set_user_data(void * user_data);
        
        /** \fn uint32_t get_delay() const
         *  \brief Gets delay before animation starts.
         *  \returns delay, in ms.
         */
        uint32_t get_delay() const;

        /** \fn uint32_t get_playtime() const
         *  \brief Gets animation duration.
         *  \returns duration, in ms.
         */
        uint32_t get_playtime() const;

        /** \fn template <class T> T get_user_data() const
         *  \brief Gets user data.
         *  \tparam T: user data type.
         *  \returns user data.
         */
        template <class T> T get_user_data() const;

        /** \brief Gets user data.
         *  \returns pointer to user data.
         */
        void * get_user_data() const;
        
    };

    /** \class AnimationTimeline
     *  \brief Wraps a lv_anim_timeline_t object.
     */
    class AnimationTimeline : public ThinPointerWrapper<lv_anim_timeline_t, lv_anim_timeline_del> {
    public:
        /** \fn AnimationTimeline()
         *  \brief Constructor.
         */
        AnimationTimeline();

        /** \fn void add(uint32_t start_time, const Animation & anim)
         *  \brief Adds an animation to the timeline.
         *  \param start_time: animation start time (overrides animation delay).
         *  \param anim: animation instance.
         */
        void add(uint32_t start_time, const Animation & anim);

        /** \fn uint32_t start()
         *  \brief Starts playing through timeline.
         *  \returns how long the timeline has played already.
         */
        uint32_t start();

        /** \fn void stop()
         *  \brief Stops playing through timeline.
         */
        void stop();

        /** \fn void set_reverse(bool reverse)
         *  \brief Enables/disables reverse mode.
         *  \param reverse: if true, plays backwards; if false, plays forwards.
         */
        void set_reverse(bool reverse);

        /** \fn void set_progress(uint16_t progress)
         *  \brief Sets position along timeline.
         *  \param progress: position; 0=start, 65535=end.
         */
        void set_progress(uint16_t progress);

        /** \fn uint32_t get_playtime() const
         *  \brief Gets position along timeline, in time units (ms).
         *  \returns time elapsed down timeline, in ms.
         */
        uint32_t get_playtime() const;

        /** \fn bool get_reverse() const
         *  \brief Tells if timeline is playing reversed.
         *  \returns true if timeline is playing reversed, false otherwise.
         */
        bool get_reverse() const;
    };

}