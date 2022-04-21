/** \file timer.h
 *  \brief Header file for C++ wrapper for LVGL timer functions.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "../lv_wrapper.h"

// we need user_data to store pointer to C++ object, otherwise we cannot
// access callbacks defined as class members.
#if LV_USE_USER_DATA

namespace lvgl::misc {

    /** \class Timer
     *  \brief Wraps a lv_timer_t object. This is a base class to construct
     *  timers for LVGL. Create a derived class and override the callback function
     *  to define the timer behaviour.
     */
    class Timer : public PointerWrapper<lv_timer_t, lv_timer_del> {
    public:
        using PointerWrapper::PointerWrapper;

        /** \typedef TimerCb
         *  \brief Function called on timer tick.
         */
        using TimerCb = void(*)(Timer &);

        /** \fn Timer()
         *  \brief Default constructor.
         */
        Timer();

        /** \fn Timer(uint32_t period)
         *  \brief Constructor with parameters.
         *  \param period: timer period, in ms.
         */
        Timer(uint32_t period);

        /** \fn virtual void callback(Timer & timer)
         *  \brief Function called periodically during execution.
         *  \param timer: pointer to timer instance.
         */
        virtual void callback(Timer & timer) {}

        /** \fn void set_callback()
         *  \brief Sets callback function defined in class as class member callback.
         */
        void set_callback();

        /** \fn void set_callback(TimerCb timer_cb)
         *  \brief Sets callback function.
         *  \param timer_cb: function pointer.
         */
        void set_callback(TimerCb timer_cb);

        /** \fn void pause()
         *  \brief Pauses timer execution.
         */
        void pause();

        /** \fn void resume()
         *  \brief Resumes timer execution.
         */
        void resume();

        /** \fn void set_period(uint32_t period)
         *  \brief Sets timer period.
         *  \param period: timer period, in ms.
         */
        void set_period(uint32_t period);

        /** \fn void set_ready()
         *  \brief Sets timer as ready.
         */
        void set_ready();

        /** \fn void set_repeat_count(int32_t repeat_count)
         *  \brief Sets timer repetition count.
         *  \param repeat_count: number of times timer callback gets called.
         */
        void set_repeat_count(int32_t repeat_count);

        /** \fn void reset()
         *  \brief Resets timer.
         */
        void reset();

    };

}
#endif // LV_USE_USER_DATA