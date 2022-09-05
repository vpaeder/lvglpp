/** \file anim.h
 *  \brief Header file for C++ wrapper for lv_anim_t and lv_anim_timeline_t objects.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../lv_wrapper.h"

/** \namespace lvgl::misc
 *  \brief LVGL miscellaneous components.
 */
namespace lvgl::misc {

    /** \class Animation
     *  \brief Wraps a lv_anim_t object.
     */
    class Animation : public PointerWrapper<lv_anim_t, lv_mem_free> {
    public:
        using PointerWrapper::PointerWrapper;

        /** \typedef template <class T> using ExecCb
         *  \brief Type of callback function used to animate variable.
         *  \tparam T: type of the variable to animate.
         */
        template <class T> using ExecCb = void(*)(T &, int32_t);

        /** \typedef CustomExecCb
         *  \brief Type of callback function used for custom variable animation.
         */
        using CustomExecCb = void(*)(Animation &, int32_t);

        /** \typedef PathCb
         *  \brief Type of callback function to calculate the animation path.
         */
        using PathCb = int32_t(*)(const Animation &);

        /** \typedef StartCb
         *  \brief Type of callback function called on animation start.
         */
        using StartCb = void(*)(Animation &);

        /** \typedef GetValueCb
         *  \brief Type of callback function called to convert path to variable value.
         */
        using GetValueCb = int32_t(*)(Animation &);

        /** \typedef DeletedCb
         *  \brief Type of callback function called when animation gets deleted.
         */
        using DeletedCb = void(*)(Animation &);

        /** \typedef ReadyCb
         *  \brief Type of callback function called when the animation ends.
         */
        using ReadyCb = void(*)(Animation &);

        /** \property std::shared_ptr<GenericVariable> var
         *  \brief Animation variable. This is a reference to the element
         *  being animated.
         */
        std::shared_ptr<GenericVariable> var;

        /** \property std::shared_ptr<GenericCallback> exec_cb
         *  \brief Function used to animate variable.
         */
        std::shared_ptr<GenericCallback> exec_cb;

        /** \property std::shared_ptr<GenericCallback> custom_exec_cb
         *  \brief Function used for custom variable animation.
         */
        std::shared_ptr<GenericCallback> custom_exec_cb;

        /** \property std::shared_ptr<GenericCallback> path_cb
         *  \brief Function used to calculate the animation path.
         */
        std::shared_ptr<GenericCallback> path_cb;

        /** \property std::shared_ptr<GenericCallback> start_cb
         *  \brief Function called on animation start.
         */
        std::shared_ptr<GenericCallback> start_cb;

        /** \property std::shared_ptr<GenericCallback> get_value_cb
         *  \brief Function used to convert path to variable value.
         */
        std::shared_ptr<GenericCallback> get_value_cb;

        /** \property std::shared_ptr<GenericCallback> ready_cb
         *  \brief Function called when the animation ends.
         */
        std::shared_ptr<GenericCallback> ready_cb;

        /** \property std::shared_ptr<GenericCallback> deleted_cb
         *  \brief Function called when the animation gets deleted.
         */
        std::shared_ptr<GenericCallback> deleted_cb;

        /** \fn Animation()
         *  \brief Default constructor.
         */
        Animation();

        /** \fn template <class T> void set_var(T & var)
         *  \brief Sets animation variable.
         *  \tparam T: variable type.
         *  \param var: variable to animate. Must remain allocated.
         */
        template <class T> void set_var(T & var) {
            this->var = std::make_shared<Variable<T>>(var);
            lv_anim_set_var(this->raw_ptr(), static_cast<void*>(this));
        }

        /** \fn void set_var(void * var)
         *  \brief Sets animation variable.
         *  \param var: pointer to variable to animate.
         */
        void set_var(void * var);

        /** \fn template <class T> T & get_var()
         *  \brief Gets animation variable.
         *  \tparam T: variable type.
         *  \returns animation variable.
         */
        template <class T> T & get_var() {
            assert(this->var != nullptr);
            auto v = *std::dynamic_pointer_cast<Variable<T>>(this->var);
            return v();
        }

        /** \fn void set_exec_cb(lv_anim_exec_xcb_t exec_cb)
         *  \brief Sets callback function used to animate variable.
         *  \param exec_cb: callback function.
         */
        void set_exec_cb(lv_anim_exec_xcb_t exec_cb);

        /** \fn template <class T> void set_exec_cb(ExecCb<T> exec_cb)
         *  \brief Sets callback function used to animate variable.
         *  \tparam T: animated variable type.
         *  \param exec_cb: callback function.
         */
        template <class T> void set_exec_cb(ExecCb<T> exec_cb) {
            // the exec_cb callback takes a void* as 1st parameter, in order to
            // accommodate pointers of any type; this means the animation object
            // isn't passed to the callback; to make the callback accept a reference
            // to a C++ class instance, we need to be able to pass a reference
            // to the callback function somehow. For callbacks with lv_anim_t* first
            // params, it's easy: set user_data to this and retrieve this in callback.
            // For this one, this is trickier. My approach is to provide a callback
            // container that also stores the variable that would normally be passed
            // to exec_cb. Then we change the variable in the lv_anim_t object to
            // a pointer to the callback container. We can then access the callback
            // and the variable upon which it acts.
            lv_anim_set_var(this->raw_ptr(), static_cast<void*>(this));
            using ExecCbType = Callback<void, T&, int32_t>;
            this->exec_cb = std::make_shared<ExecCbType>(exec_cb);
            // definition of callback wrapper function; this will call C++ callback
            // with stored var
            auto f = [](void * lv_obj, int32_t value) {
                auto anim = reinterpret_cast<Animation*>(lv_obj);
                auto cb = *std::dynamic_pointer_cast<ExecCbType>(anim->exec_cb);
                cb(anim->get_var<T>(), value);
            };
            lv_anim_set_exec_cb(this->raw_ptr(), f);
        }

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

        /** \fn void set_custom_exec_cb(CustomExecCb exec_cb)
         *  \brief Sets a custom function used to animate variable. This version
         *  takes a Animation* as 1st variable instead of void*.
         *  \param exec_cb: callback function.
         */
        void set_custom_exec_cb(CustomExecCb exec_cb);

        /** \fn void set_path_cb(lv_anim_path_cb_t path_cb)
         *  \brief Sets the function that calculates the animation's path.
         *  \param path_cb: callback function.
         */
        void set_path_cb(lv_anim_path_cb_t path_cb);

        /** \fn void set_path_cb(PathCb path_cb)
         *  \brief Sets the function that calculates the animation's path.
         *  \param path_cb: callback function.
         */
        void set_path_cb(PathCb path_cb);

        /** \fn void set_start_cb(lv_anim_start_cb_t start_cb)
         *  \brief Sets the function called on animation start.
         *  \param start_cb: callback function.
         */
        void set_start_cb(lv_anim_start_cb_t start_cb);

        /** \fn void set_start_cb(StartCb start_cb)
         *  \brief Sets the function called on animation start.
         *  \param start_cb: callback function.
         */
        void set_start_cb(StartCb start_cb);

        /** \fn void set_get_value_cb(lv_anim_get_value_cb_t get_value_cb)
         *  \brief Sets a function that transforms the actual animation position
         *  into a value in variable space. This is for instance if we have
         *  a variable that has a logarithmic behaviour.
         *  \param get_value_cb: callback function.
         */
        void set_get_value_cb(lv_anim_get_value_cb_t get_value_cb);

        /** \fn void set_get_value_cb(GetValueCb get_value_cb)
         *  \brief Sets a function that transforms the actual animation position
         *  into a value in variable space.
         *  \param get_value_cb: callback function.
         */
        void set_get_value_cb(GetValueCb get_value_cb);

        /** \fn void set_ready_cb(lv_anim_ready_cb_t ready_cb)
         *  \brief Sets the function called when the animation ends.
         *  \param ready_cb: callback function.
         */
        void set_ready_cb(lv_anim_ready_cb_t ready_cb);

        /** \fn void set_ready_cb(ReadyCb ready_cb)
         *  \brief Sets the function called when the animation ends.
         *  \param ready_cb: callback function.
         */
        void set_ready_cb(ReadyCb ready_cb);

        /** \brief Sets the function called when the animation gets deleted.
         *  \param deleted_cb: callback function.
         */
        void set_deleted_cb(lv_anim_deleted_cb_t deleted_cb);

        /** \brief Sets the function called when the animation gets deleted.
         *  \param deleted_cb: callback function.
         */
        void set_deleted_cb(DeletedCb deleted_cb);

        /** \fn void set_playback_time(uint32_t time)
         *  \brief Sets the animation playback duration.
         *  \param time: duration, in ms; 0=no playback.
         */
        void set_playback_time(uint32_t time);

        /** \fn void set_playback_delay(uint32_t delay)
         *  \brief Sets the animation playback delay.
         *  \param delay: delay, in ms.
         */
        void set_playback_delay(uint32_t delay);

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

#if LV_USE_USER_DATA
        /** \fn template <class T> void set_user_data(T & user_data)
         *  \brief Sets user data.
         *  \tparam T: user data type.
         *  \param user_data: user data.
         */
        template <class T> void set_user_data(T & user_data) {
            lv_anim_set_user_data(this->raw_ptr(), static_cast<void*>(&user_data));
        }

        /** \fn void set_user_data(void * user_data)
         *  \brief Sets user data.
         *  \param user_data: pointer to user data.
         */
        void set_user_data(void * user_data);
#endif // LV_USE_USER_DATA

        /** \fn void start()
         *  \brief Starts animation.
         */
        void start();

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

#if LV_USE_USER_DATA
        /** \fn template <class T> T get_user_data() const
         *  \brief Gets user data.
         *  \tparam T: user data type.
         *  \returns user data.
         */
        template <class T> T get_user_data() const {
            return *reinterpret_cast<T*>(lv_anim_get_user_data(this->raw_ptr()));
        }

        /** \brief Gets user data.
         *  \returns pointer to user data.
         */
        void * get_user_data() const;
#endif // LV_USE_USER_DATA
        
    };

    /** \class AnimationTimeline
     *  \brief Wraps a lv_anim_timeline_t object.
     */
    class AnimationTimeline : public PointerWrapper<lv_anim_timeline_t, lv_anim_timeline_del> {
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